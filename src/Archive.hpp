/** Copyright David Braude 2019 */
#ifndef SRC_ARCHIVE_HPP_
#define SRC_ARCHIVE_HPP_

#include <fstream>
#include <string>

#include "yaa.h" /* for enum YAA_RESULT */

namespace YAA {

extern const char ARCHIVE_MAGIC_STRING[];

class Archive {
    /** The implementation of the Archive parts of the API
     * 
     */

public:
    /** Create a new empty archive
     * 
     * Allocates the appropraite memory, under the hood this returns a pointer to an object
     * 
     * @see YAA_new
     * 
     * @param filename the name of the archive to edit
     * @returns a new archive 
     */
    Archive(const char * filename);

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
     *      YAA_RESULT_ERROR an exception was raised or the integrity check failed
     *      YAA_RESULT_WARN file was already open
     *      YAA_RESULT_SUCCESS file was opened and signature matched or hmac_public_key is NULL
     */
    enum YAA_RESULT open(const char * mode);

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

protected:
    const std::string _filename;
    std::ios_base::openmode  _mode;
    std::fstream _file;

    /** Determines the access mode based on the mode string
     * 
     * @param mode the access mode string
     * @returns the file stream access mode
     */
    std::ios_base::openmode _determine_write_mode(const char * mode);
};
}

#endif // SRC_ARCHIVE_HPP_