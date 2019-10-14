/** Copyright David Braude 2019 */
#ifndef SRC_ARCHIVE_EDITOR_HPP_
#define SRC_ARCHIVE_EDITOR_HPP_

#include "yaa.h"
#include "Archive.hpp"

#ifndef YAA_WRITE_BLOCK_SIZE
#define YAA_WRITE_BLOCK_SIZE 1048576 // 1MB
#endif

namespace YAA {

class ArchiveEditor
{
    /** Edits files on the disk
     * 
     * Signing must always be called seperately
     */

public:

    /** Write a whole archive to disc
     *
     * It is important to sign the archive after it has been written. This will
     * delete any content already in the archive
     * 
     * @param archive Archive to write, filename will be retrieved from the
     *      archive
     * @returns
     *      YAA_RESULT_ERROR if the file was open
     *      YAA_RESULT_SUCCESS if the file was written
     */
    enum YAA_RESULT write(Archive * archive, const char * filename);

    // rewrite header

    // remove entity

    // insert entity

    // sign


protected:
    /** Writes the magic string at the start of the file in the file stream */
    void _write_magic_string(std::fstream& archive_file);
    
    // _write_object();
    
    /** Generates the header JSON and writes to the disc */
    void _write_header(Archive * archive, std::fstream& archive_file);
    
    /** Writes a blank signature */
    void _write_blank_signature(std::fstream& archive_file);

    //void _write_integrity_hash(std::fstream& archive_file);

    /** inserts bytesat the current point into the file */
    void _insert_into_file(std::fstream& archive_file,
                            const void * bytes,
                            std::size_t num_bytes);

};
}

#endif