/** Copyright David Braude 2019 */

#include "yaa.h"

namespace YAA {

class Archive {
    /** The implementation of the Archive parts of the API
     * 
     */

public:
    /** Loads an existing archive from disk
     *
     * Implementation of YAA_load
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


};


};