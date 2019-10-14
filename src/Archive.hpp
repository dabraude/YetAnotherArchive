/** Copyright David Braude 2019 */
#ifndef SRC_ARCHIVE_HPP_
#define SRC_ARCHIVE_HPP_

#include <fstream>
#include <memory>
#include <string>

#include "yaa.h" // for enum YAA_RESULT 

#include "Header.hpp"

namespace YAA {

#define YAA_NUM_SIGNATURE_CHARS 64
#define YAA_NUM_HASH_CHARS 32
#define YAA_NUM_FOOTER_CHARS (YAA_NUM_SIGNATURE_CHARS + YAA_NUM_HASH_CHARS)

extern const char ARCHIVE_MAGIC_STRING[];

class Archive {
    /** The implementation of the Archive parts of the API
     * 
     */

public:
    
    Archive();

    /** Destructor
     * 
     * will close the archive if it is open
     */
    ~Archive();

    /** Opens an archive for editing
     * 
     *  @see YAA_open
     *
     *  @returns results of attempting to load
     *      YAA_RESULT_ERROR an exception was raised or the integrity check
     *          failed
     *      YAA_RESULT_WARN file was already open
     *      YAA_RESULT_SUCCESS file was opened and signature matched or
     *          hmac_public_key is NULL
     */
    enum YAA_RESULT open(const char * filename, bool read_only);

    /** Closes an open archive
     *
     *  @see YAA_close
     * 
     *  @returns results of attempting to close
     *      YAA_RESULT_ERROR an exception was raised
     *      YAA_RESULT_WARN the file was already closed
     *      YAA_RESULT_SUCCESS file was closed successfully
     */
    enum YAA_RESULT close();

    /** Returns if an archive is open
     * 
     * @see YAA_is_open
     * 
     * @returns true if open
     */
    bool is_open() const;

    /** File name of the archive
     * 
     * @returns the file name of archive.
     */
    const char * filename() const;


    /** Gets the header in JSON format
     * 
     * @returns the header of the archive as it stands in JSON format
     */
    std::string header_as_json() const;

    // Allow the Header directly modify 
    friend class Header;

protected:

    // flag for marking the file should be treated as read only
    bool  _read_only;

    // filename, if opened with a file
    std::string _filename;
    
    // file stream to use
    std::fstream _file;

    Header _header;

};
}

#endif // SRC_ARCHIVE_HPP_