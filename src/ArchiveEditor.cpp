
#include <iostream>
#include <fstream>

#include "yaa.h"
#include "Archive.hpp"
#include "ArchiveEditor.hpp"
#include "Log.hpp"

namespace YAA {

ArchiveEditor::ArchiveEditor() :
    _sha1("SHA1"),
    _sha256(YAA_HASH_SHA256)
{}

enum YAA_RESULT ArchiveEditor::write(Archive * archive, const char * filename)
{
    Log log;
    log.debug("creating a new archive file");
    if (archive->is_open()) {
        log.error("creating a new archive file");
        return YAA_RESULT_ERROR;
    }
    
    std::fstream archive_file;
    // we need the file to exist so we can open it for reading
    archive_file.open(filename, std::ios::out | std::ios::binary);
    if (!archive_file.is_open()) {
        log.error("failed to open file for writing");
        return YAA_RESULT_ERROR;
    }
    archive_file.close();

    // need the file open for read and write so we can calculate the hash
    archive_file.open(filename, std::ios::in | std::ios::out 
                        | std::ios::binary);
    if (!archive_file.is_open()) {
        log.error("failed to open file for writing");
        return YAA_RESULT_ERROR;
    }

    _write_magic_string(archive_file);
    // write the objects
    _write_header(archive, archive_file);

    // fill in zeros so the file is the right length for the hash function
    for (int i = 0; i < YAA_NUM_FOOTER_CHARS; i++)
        archive_file << "0";
    
    // _write_blank_signature(archive_file);
    _write_integrity_hash(archive_file);

    return YAA_RESULT_SUCCESS;
}


void ArchiveEditor::_write_magic_string(std::fstream& archive_file) {
    Log log;
    log.debug("writing magic string");
    archive_file << ARCHIVE_MAGIC_STRING;
}


void ArchiveEditor::_write_header(Archive * archive,
                                    std::fstream& archive_file)
{
    Log log;
    log.debug("writing header to file");
    // archive_file.seekp(-YAA_NUM_FOOTER_CHARS, std::ios_base::end);
    std::string header_json = archive->header_as_json();
    archive_file << header_json;
    archive_file << header_json.length();
}


void ArchiveEditor::_write_blank_signature(std::fstream& archive_file)
{
    Log log;
    log.debug("writing blank signature");
    char blank[YAA_NUM_SIGNATURE_CHARS+1];
    for (int i = 0; i < YAA_NUM_SIGNATURE_CHARS; i++)
        blank[i] = '0';
    blank[YAA_NUM_SIGNATURE_CHARS] = '\0';
    archive_file.clear();
    archive_file.seekp(-YAA_NUM_FOOTER_CHARS, std::ios_base::end);
    archive_file.write(blank, YAA_NUM_SIGNATURE_CHARS); 
}


void ArchiveEditor::_write_integrity_hash(std::fstream& archive_file)
{
    Log log;
    log.debug("writing integrity hash");
    std::string hash = _calculate_integrity_hash(archive_file);

    archive_file.clear();
    archive_file.seekp(-YAA_NUM_HASH_CHARS, std::ios_base::end);
    archive_file << hash;
}


std::string ArchiveEditor::_calculate_integrity_hash(std::fstream& archive_file)
{
    if (YAA_NUM_HASH_CHARS != _sha1.num_digest_chars()) {
        std::string msg = "digest should have ";
        msg += std::to_string(YAA_NUM_HASH_CHARS);
        msg += " characters, but has ";
        msg += std::to_string(_sha1.num_digest_chars());
        Log().critical(msg);
        throw "digest has wrong number of characters";
    }

    _sha1.reset();
    char file_data[YAA_WRITE_BLOCK_SIZE+1];
    std::size_t message_sz;
    archive_file.seekg(-YAA_NUM_FOOTER_CHARS, std::ios_base::end);
    auto body_end = archive_file.tellg();
    archive_file.seekg(0, std::ios_base::beg);
    while (!archive_file.eof()) {
        archive_file.read(file_data, YAA_WRITE_BLOCK_SIZE);
        message_sz = archive_file.gcount();

        if (archive_file.eof()) {
            if (message_sz > YAA_NUM_FOOTER_CHARS) {
                message_sz -= YAA_NUM_FOOTER_CHARS;
            }
            else {
                break;
            }
        }
        else if (archive_file.tellg() > body_end) {
            std::size_t num_passed = archive_file.tellg() - body_end;
            if (num_passed >= message_sz)
                break;
            else 
                message_sz -= num_passed;
        }

        bool added = _sha1.add_to_message(file_data, message_sz);
        if (!added) {
            throw "failed to add to digest";
        }
    }

    return _sha1.finish();
}

/** inserts stuff into an existing file */
void ArchiveEditor::_insert_into_file(std::fstream& archive_file,
                                        const void * bytes,
                                        std::size_t num_bytes)
{
    auto out_pos = archive_file.tellp();
    char file_data[YAA_WRITE_BLOCK_SIZE + 1];
    file_data[YAA_WRITE_BLOCK_SIZE] = '\0';
    
    for (int i = 0; i < YAA_WRITE_BLOCK_SIZE; i++)
        file_data[i] = 'q';

    // add enough characters to the end of the file
    archive_file.seekp(0, std::ios_base::end);
    std::size_t n = 0;
    for (std::size_t wrote = 0; wrote < num_bytes; wrote += n) {
        n = num_bytes - wrote;
        n = (n > YAA_WRITE_BLOCK_SIZE) ? YAA_WRITE_BLOCK_SIZE : n;
        archive_file.write(file_data, n);
    }

    // move enerything in block sizes
    archive_file.seekg(-num_bytes,  std::ios_base::end);
    bool finished = false;
    while (!finished) {
        int block_sz;
        auto old_pos = archive_file.tellg();

        block_sz = old_pos - out_pos;
        if (block_sz > YAA_WRITE_BLOCK_SIZE)
            block_sz = YAA_WRITE_BLOCK_SIZE;
        else 
            finished = true;

        archive_file.seekg(-block_sz, std::ios_base::cur);
        archive_file.read(file_data, block_sz);
        archive_file.seekg(-block_sz, std::ios_base::cur);

        archive_file.seekp(archive_file.tellg());
        archive_file.seekp(num_bytes, std::ios_base::cur);
        archive_file.write(file_data, block_sz);

        archive_file.seekg(old_pos);
        archive_file.seekg(-block_sz, std::ios_base::cur);
    }
        
    archive_file.seekp(out_pos);
    archive_file.write(static_cast<const char*>(bytes), num_bytes);
}


}