
#include <iostream>
#include <fstream>

#include "yaa.h"
#include "Archive.hpp"
#include "ArchiveEditor.hpp"
#include "Log.hpp"

namespace YAA {

enum YAA_RESULT ArchiveEditor::write(Archive * archive, const char * filename)
{
    Log log;
    log.debug("creating a new archive file");
    if (archive->is_open()) {
        log.error("creating a new archive file");
        return YAA_RESULT_ERROR;
    }
    
    std::fstream archive_file;
    archive_file.open(filename, std::ios::out | std::ios::binary);
    if (!archive_file.is_open()) {
        log.error("failed to open file for writing");
        return YAA_RESULT_ERROR;
    }
    archive_file.close();

    archive_file.open(filename, std::ios::in | std::ios::out 
                        | std::ios::binary);
    if (!archive_file.is_open()) {
        log.error("failed to open file for writing");
        return YAA_RESULT_ERROR;
    }

    _write_magic_string(archive_file);
    // write the objects

    // fill in zeros so the file is the right length for the hash function
    for (int i = 0; i < YAA_NUM_FOOTER_CHARS; i++)
        archive_file << "0";

    _write_header(archive, archive_file);
    _write_blank_signature(archive_file);
    // _write_integrity_hash

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

    std::string header_json = archive->header_as_json();
    auto len = header_json.length();
    header_json += std::to_string(len);

    archive_file.seekp(-YAA_NUM_FOOTER_CHARS, std::ios_base::end);
    _insert_into_file(archive_file, header_json.c_str(), header_json.length());
}


void ArchiveEditor::_write_blank_signature(std::fstream& archive_file) {
    Log log;
    log.debug("writing blank signature");
    char blank[YAA_NUM_SIGNATURE_CHARS+1];
    for (int i = 0; i < YAA_NUM_SIGNATURE_CHARS; i++)
        blank[i] = '0';
    blank[YAA_NUM_SIGNATURE_CHARS] = '\0';
    archive_file.seekp(-YAA_NUM_FOOTER_CHARS, std::ios_base::end);
    archive_file.write(blank, YAA_NUM_SIGNATURE_CHARS); 
}


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