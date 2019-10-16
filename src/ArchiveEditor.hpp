/** Copyright David Braude 2019 */
#ifndef SRC_ARCHIVE_EDITOR_HPP_
#define SRC_ARCHIVE_EDITOR_HPP_

#include "yaa.h"
#include "Archive.hpp"
#include "Hash.hpp"

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

    /** Constructor just to initialise the Hash functions
     */
    ArchiveEditor();

    /** Write a whole archive to disc
     *
     * This will delete any content already in the archive. It is important to
     * sign the archive after it has been written.
     * 
     * @param archive Archive to write, filename will be retrieved from the
     *      archive
     * @returns
     *      YAA_RESULT_ERROR if the file was open
     *      YAA_RESULT_SUCCESS if the file was written
     */
    enum YAA_RESULT write(Archive * archive, const char * filename);

    // update header (bool inplace)

    // remove entity (bool inplace)

    // insert entity (bool inplace)

    // sign 


protected:
    /** Writes the magic string at the start of the file in the file stream */
    void _write_magic_string(std::fstream& archive_file);
    
    // _write_object();
    
    /** Generates the header JSON and writes to the disc */
    void _write_header(Archive * archive, std::fstream& archive_file);


    /** writes the checksum to the end of the file */
    void _write_checksum(std::fstream& archive_file);

    /** inserts bytesat the current point into the file */
    void _insert_into_file(std::fstream& archive_file,
                            const void * bytes,
                            std::size_t num_bytes);

    /** calculates the hash of the file as it stands */
    std::string _calculate_integrity_hash(std::fstream& archive_file);

    /** sends the archive read or write stream to the start of the header */
    void _seek_header_start(std::fstream& archive_file, bool read_stream);

    /** sends the archive read or write stream to the start of the signature */
    void _seek_signature_start(std::fstream& archive_file, bool read_stream);

    /** sends the archive read or write stream to the start of the checksum */
    void _seek_checksum_start(std::fstream& archive_file, bool read_stream);

    /** moves the read / write stream */
    void _seek_stream(std::fstream& archive_file, std::size_t move_size,
                        std::streampos old_read_pos, bool read_stream);

    /** determines the size of the next JSON in the read stream */
    std::size_t _json_size(std::fstream& archive_file);

    Hash _sha1;
};
}

#endif