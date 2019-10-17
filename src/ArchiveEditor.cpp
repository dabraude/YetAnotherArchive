
#include <iostream>
#include <fstream>

#include "yaa.h"
#include "Archive.hpp"
#include "ArchiveEditor.hpp"
#include "Log.hpp"
#include "utils.hpp"

namespace YAA {

static const char * _blank_json = "{}2";

ArchiveEditor::ArchiveEditor() : _sha1("SHA1") {};

enum YAA_RESULT ArchiveEditor::write(Archive * archive, const char * filename)
{
    Log log;
    log.info("creating a new archive file");
   
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

    // TODO: write the objects

    // fill in the minimal header, signature & checksum size
    archive_file << _blank_json; // header
    archive_file << _blank_json; // signature
    for (int i = 0; i < YAA_NUM_CHECKSUM_CHARS; i++)
        archive_file << ".";
    _write_header(archive, archive_file);

    return YAA_RESULT_SUCCESS;
}


void ArchiveEditor::_write_magic_string(std::fstream& archive_file)
{
    Log log;
    log.debug("writing magic string");
    archive_file.clear();
    archive_file.seekp(0, std::ios::beg);
    archive_file << ARCHIVE_MAGIC_STRING;
}


void ArchiveEditor::_write_header(Archive * archive,
                                    std::fstream& archive_file)
{
    Log log;
    log.debug("writing header to file");
    archive_file.clear();

    _seek_header_start(archive_file, false);

    std::string header_json = archive->header_as_json();
    archive_file << header_json;
    archive_file << header_json.length();

    // TODO: truncate the file here

    // this has invalidated the sigature and checksum so blank them out
    archive_file << _blank_json;
    for (int i = 0; i < YAA_NUM_CHECKSUM_CHARS; i++)
        archive_file << ".";

    _write_checksum(archive_file);
}


void ArchiveEditor::_seek_stream(std::fstream& archive_file, int move,
                                    bool read_stream, std::streampos read_pos)
{
    if (read_stream) {
        archive_file.seekg(move, std::ios::cur);
    }
    else {
        archive_file.seekp(archive_file.tellg());
        archive_file.seekp(move, std::ios::cur);
        archive_file.seekg(read_pos);
    }
}


void ArchiveEditor::_seek_json_start(std::fstream& archive_file,
                                        bool read_stream)
{
    auto read_pos = archive_file.tellg();
    if (read_stream)
        archive_file.seekg(-1, std::ios::cur);
    else
        archive_file.seekp(-1, std::ios::cur);
    if (!read_stream)
        archive_file.seekg(archive_file.tellp());
    int move_size = _json_size(archive_file) - 1; 
    if (!read_stream)
        archive_file.seekp(archive_file.tellg());
    _seek_stream(archive_file, -move_size, read_pos, read_stream);
}


void ArchiveEditor::_seek_header_start(std::fstream& archive_file,
                                        bool read_stream)
{
    _seek_signature_start(archive_file, read_stream);
    _seek_json_start(archive_file, read_stream);
}


void ArchiveEditor::_seek_signature_start(std::fstream& archive_file,
                                            bool read_stream)
{
    _seek_checksum_start(archive_file, read_stream);
    _seek_json_start(archive_file, read_stream);
}


void ArchiveEditor::_seek_checksum_start(std::fstream& archive_file,
                                            bool read_stream)
{
    if (read_stream)
        archive_file.seekg(-YAA_NUM_CHECKSUM_CHARS, std::ios::end);
    else
        archive_file.seekp(-YAA_NUM_CHECKSUM_CHARS, std::ios::end);
}


void ArchiveEditor::_write_checksum(std::fstream& archive_file)
{
    Log().debug("writing integrity hash");
    archive_file.clear();
    std::string hash = _calculate_integrity_hash(archive_file);
    _seek_checksum_start(archive_file, false);
    archive_file << hash;
}


std::string ArchiveEditor::_calculate_integrity_hash(std::fstream& archive_file)
{
    if (YAA_NUM_CHECKSUM_CHARS != _sha1.num_digest_chars()) {
        std::string msg = "digest should have ";
        msg += std::to_string(YAA_NUM_CHECKSUM_CHARS);
        msg += " characters, but has ";
        msg += std::to_string(_sha1.num_digest_chars());
        Log().critical(msg);
        throw "digest has wrong number of characters";
    }

    _sha1.reset();
    char file_data[YAA_WRITE_BLOCK_SIZE+1];
    std::size_t message_sz;

    archive_file.clear();
    _seek_signature_start(archive_file, false);
    auto body_end = archive_file.tellg();
    
    archive_file.seekg(0, std::ios::beg);
    
    while (!archive_file.eof()) {
        archive_file.read(file_data, YAA_WRITE_BLOCK_SIZE);
        message_sz = archive_file.gcount();

        if (archive_file.eof()) {
            archive_file.clear();
            archive_file.seekg(0, std::ios::end);
        }

        if (archive_file.tellg() > body_end) {
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
    archive_file.seekp(0, std::ios::end);
    std::size_t n = 0;
    for (std::size_t wrote = 0; wrote < num_bytes; wrote += n) {
        n = num_bytes - wrote;
        n = (n > YAA_WRITE_BLOCK_SIZE) ? YAA_WRITE_BLOCK_SIZE : n;
        archive_file.write(file_data, n);
    }

    // move enerything in block sizes
    archive_file.seekg(-num_bytes,  std::ios::end);
    bool finished = false;
    while (!finished) {
        int block_sz;
        auto old_pos = archive_file.tellg();

        block_sz = old_pos - out_pos;
        if (block_sz > YAA_WRITE_BLOCK_SIZE)
            block_sz = YAA_WRITE_BLOCK_SIZE;
        else 
            finished = true;

        archive_file.seekg(-block_sz, std::ios::cur);
        archive_file.read(file_data, block_sz);
        archive_file.seekg(-block_sz, std::ios::cur);

        archive_file.seekp(archive_file.tellg());
        archive_file.seekp(num_bytes, std::ios::cur);
        archive_file.write(file_data, block_sz);

        archive_file.seekg(old_pos);
        archive_file.seekg(-block_sz, std::ios::cur);
    }
        
    archive_file.seekp(out_pos);
    archive_file.write(static_cast<const char*>(bytes), num_bytes);
}


std::size_t ArchiveEditor::_json_size(std::fstream& archive_file)
{
    std::size_t exp10 = 0;
    std::size_t size = 0;

    if (archive_file.eof()) {
        Log().warn("trying to read json size with eof flag set\n");
    }

    char digit = archive_file.peek();
    while (digit != '}') {
        int digit_int = digit - '0';
        size += digit_int * pow10(exp10);
        exp10++;
        archive_file.seekg(-1, std::ios::cur);
        digit = archive_file.peek();
    };

    return size;
}


}