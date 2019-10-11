/** Copyright David Braude 2019 */
#ifndef SRC_ARCHIVE_HPP_
#define SRC_ARCHIVE_HPP_

#include "yaa.h"

namespace YAA {
class Archive {
    /** The implementation of the Archive parts of the API
     * 
     */

public:
    /** Implementation of YAA_load
     * 
     * @see YAA_load
     * 
     *  @param filename the name of the file load
     *  @param public_key your public key for checking the creator signature (or NULL)
     *  @returns results of attempting to load
     *      YAA_RESULT_ERROR an exception was raised or the integraty check failed
     *      YAA_RESULT_WARN file was loaded but the signature did not match
     *      YAA_RESULT_SUCCESS file was loaded and signature matched or public_key is NULL
     */
    enum YAA_RESULT load(const char * filename, const char * public_key);

    /** Implementation of YAA_save
     * 
     * @see YAA_save
     * 
     * @param filename the name of the file where to save the archive
     * @param private_key your private key for signing the file
     * @returns results of attempting to save
     *      YAA_RESULT_ERROR an exception was raised
     *      YAA_RESULT_SUCCESS file was saved and signed
     */
    enum YAA_RESULT save(const char * filename, const char * private_key);
};
}

#endif // SRC_ARCHIVE_HPP_