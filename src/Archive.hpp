/** Copyright David Braude 2019 */
#ifndef SRC_ARCHIVE_HPP_
#define SRC_ARCHIVE_HPP_

#include <fstream>
#include <memory>
#include <string>

#include "yaa.h" // for enum YAA_RESULT 

#include "ArchiveFile.hpp"
#include "Header.hpp"

namespace YAA {

#define YAA_NUM_CHECKSUM_CHARS 40

extern const char ARCHIVE_MAGIC_STRING[];

class Archive {
    /** The implementation of the Archive parts of the API
     * 
     */

public:


    // External API


    /** Constructor initialises internal variables */
    Archive();

    /** Writes an archive to disc
     *
     * @param filename where to save the archive
     * @returns results of attempting to write
     *      YAA_RESULT_ERROR an exception was raised
     *      YAA_RESULT_SUCCESS file was successfully written to disc
     */
    enum YAA_RESULT write(const char * filename);


    /** Loads an existing archive file
     * 
     * @param filename which archive to load
     * @param load_entities if true will load all entities in the archive
     *          into memory
     * @returns the result of loading the file
     *          YAA_RESULT_ERROR if not a YAA file, checksum does not match
     *          YAA_RESULE_SUCESSS if no problems loading the file
     */ 
    enum YAA_RESULT load(const char * filename, bool load_entities);


    /** File name of the archive
     * 
     * @returns the file name of archive, or NULL if not opened from disc
     */
    const char * filename() const;


    // Allows underlying classes to work without creating extra interfaces
    friend class Header;
    friend class ArchiveFile;

protected:

    // flag for marking the file should be treated as read only
    bool  _read_only;

    // filename, if opened with a file
    std::string _filename;
    
    Header _header;
};
}

#endif // SRC_ARCHIVE_HPP_