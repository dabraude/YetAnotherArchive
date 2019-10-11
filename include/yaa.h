/** Copyright David Braude 2019 */

#ifndef YET_ANOTHER_ARCHIVE_H_
#define YET_ANOTHER_ARCHIVE_H_

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef void* YAA_Archive; /** an archive */
typedef struct YAA_Data YAA_Data; /** data to be added to or saved in the archive */

/** Apart from the creation, all API calls return this enum */
enum YAA_RESULT {
    YAA_RESULT_ERROR    =  0,
    YAA_RESULT_SUCCESS  =  1,
    YAA_RESULT_WARN     = -1
};

struct YAA_Data {
    void * data; /** data contained in the blob */
    size_t size; /** number of bytes in this data blob */
    int end;     /** is this the last blob in a file */
};

/** Create a new empty archive
 *
 * Allocates the appropraite memory, under the hood this returns a pointer to an object
 * 
 * @returns a new archive 
 */
extern YAA_Archive YAA_new();


/** Frees the memory of an existing archive
 * 
 * @param yaa the archive to be freed
 * @returns
 *      YAA_RESULT_ERROR if the pointer is void or if an exception was raised
 *      YAA_RESULT_SUCCESS if the memory was freed normally
 */
extern enum YAA_RESULT YAA_delete(YAA_Archive yaa);


/** Loads an existing archive from disk
 *
 *  @param yaa the archive object to store the loaded info
 *  @param filename the name of the file load
 *  @param public_key your public key for checking the creator signature (or NULL)
 *  @returns results of attempting to load
 *      YAA_RESULT_ERROR an exception was raised or the integraty check failed
 *      YAA_RESULT_WARN file was loaded but the signature did not match
 *      YAA_RESULT_SUCCESS file was loaded and signature matched or public_key is NULL
 */
extern enum YAA_RESULT YAA_load(YAA_Archive yaa, const char * filename, const char * public_key);


/** Saves archive to disk
 * 
 *  @param yaa the archive object to save
 *  @param filename the name of the file where to save the archive
 *  @param private_key your private key for signing the file
 *  @returns results of attempting to save
 *      YAA_RESULT_ERROR an exception was raised
 *      YAA_RESULT_SUCCESS file was saved and signed
 */
extern enum YAA_RESULT YAA_save(YAA_Archive yaa, const char * filename, const char * private_key);

// get YAA_Data
// add data
// add meta
// encrypt data
// compress data
// data recovery
// remove file
// append file
// status

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* YET_ANOTHER_ARCHIVE_H_ */