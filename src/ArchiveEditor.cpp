
#include <iostream>
#include <fstream>

#include "yaa.h"
#include "ArchiveEditor.hpp"

namespace YAA {

enum YAA_RESULT ArchiveEditor::write_new(Archive * archive)
{
    // LOG DEBUG creating a new archive file
    bool was_open = archive->is_open();
    
    std::fstream archive_file;
    archive_file.open(archive->filename(), std::ios::out | std::ios::binary);
    if (!archive_file.is_open())
    {
        // LOG ERROR: failed to open file for writing
        return YAA_RESULT_ERROR;
    }

    _write_magic_string(archive_file);
    
    // write the objects
    // write the header

    // fill in zeros so the file is the right length for the hash function
    for (int i = 0; i < YAA_NUM_SIGNATURE_CHARACTERS + YAA_NUM_HASH_CHARACTERS; i++)
        archive_file << "0";

    // write blank signature
    // _write_integrity_hash

    if (!was_open)
        archive->close();

    return YAA_RESULT_SUCCESS;
}


void ArchiveEditor::_write_magic_string(std::fstream& archive_file) {
    archive_file << ARCHIVE_MAGIC_STRING;
}
    

}