/** Copyright David Braude 2019 */

#ifndef YET_ANOTHER_ARCHIVE_H_
#define YET_ANOTHER_ARCHIVE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef void* YAA_Archive; /** an archive */

/** Apart from the creation, all API calls return this enum */
enum YAA_RESULT {
    YAA_RESULT_WARN     = -1,
    YAA_RESULT_ERROR    =  0,
    YAA_RESULT_SUCCESS  =  1
};

/** Create a new empty archive
 *
 * Allocates the appropraite memory, under the hood this returns a pointer to an object
 * 
 * @param filename the name of the file load
 * @returns a new archive 
 */
extern YAA_Archive YAA_new(const char * filename);


/** Frees the memory of an existing archive
 * 
 * @param yaa the archive to be freed
 * @returns
 *      YAA_RESULT_ERROR if the pointer is void or if an exception was raised
 *      YAA_RESULT_SUCCESS if the memory was freed normally
 */
extern enum YAA_RESULT YAA_delete(YAA_Archive yaa);


/** Opens an archive for editing
 *
 *  @param yaa the archive object to store the loaded info
 *  @param hmac_public_key your public key for checking the creator signature (or NULL)
 *  @returns results of attempting to load
 *      YAA_RESULT_ERROR an exception was raised or the integrity check failed
 *      YAA_RESULT_WARN file was opened but the signature did not match
 *      YAA_RESULT_SUCCESS file was opened and signature matched or hmac_public_key is NULL
 */
extern enum YAA_RESULT YAA_open(YAA_Archive yaa);


// TODO functions:

// YAA_add_object
// YAA_remove_object
// YAA_retrieve_object
// YAA_verify_creator
// YAA_sign




#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* YET_ANOTHER_ARCHIVE_H_ */