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


protected:
    /** Writes the magic string at the start of the file in the file stream */
    void _write_magic_string(std::fstream& archive_file);


    // _write_object();


    /** Generates the header JSON and writes to the disc */
    void _write_header(Archive * archive, std::fstream& archive_file);


    /** writes the checksum to the end of the file */
    void _write_checksum(std::fstream& archive_file);


    /** sends the archive read or write stream to the start of the header
     * 
     * @param archive_file stream
     * @param read_stream if true moves the read stream otherwise move the
     *  write stream, relative to the current position of the read stream
     * @returns the size of the header JSON
     */
    std::size_t _seek_header_start(std::fstream& archive_file,
                                    bool read_stream);


    /** sends the archive read or write stream to the start of the signature
     * 
     * @param archive_file stream
     * @param read_stream if true moves the read stream otherwise move the
     *  write stream, relative to the current position of the read stream
     * @returns the size of the signature JSON
     */
    std::size_t _seek_signature_start(std::fstream& archive_file,
                                        bool read_stream);


    /** sends the archive read or write stream to the start of the checksum
     * 
     * @param archive_file stream
     * @param read_stream if true moves the read stream otherwise move the
     *  write stream, relative to the current position of the read stream
     */
    void _seek_checksum_start(std::fstream& archive_file, bool read_stream);


    /** moves to the start of the next JSON, assumes stream is one past the
     *  end of the json
     * 
     * @param archive_file stream
     * @param read_stream if true moves the read stream otherwise move the
     *  write stream, relative to the current position of the read stream
     * @returns the size of JSON
     */
    std::size_t _seek_json_start(std::fstream& archive_file, bool read_stream);


    /** moves the read / write stream relative to the read stream, 
     * 
     * @param archive_file stream
     * @param move the change in the stream
     * @param read_stream if true moves the read stream otherwise move the
     *  write stream, relative to the current position of the read stream
     * @param read_pos if moving the write stream where to send the read stream
     *  afterwards
     */
    void _seek_stream(std::fstream& archive_file, int move, bool read_stream,
                        std::streampos read_pos);


    /** calculates the hash of the file as it stands */
    std::string _calculate_checksum(std::fstream& archive_file);


    /** determines the size of the next JSON in the read stream
     * 
     * must be one char past the end of the JSON
     * 
     * @param archive_file stream to read the JSON size from
     * @returns the size of the JSON
     */
    std::size_t _json_size(std::fstream& archive_file);


    /** inserts bytesat the current point into the file */
    void _insert_into_file(std::fstream& archive_file,
                            const void * bytes,
                            std::size_t num_bytes);


    // Hash calculator for the checksum
    Hash _sha1;
};
}

#endif