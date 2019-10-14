/** Copyright David Braude 2019 */

#ifndef YET_ANOTHER_ARCHIVE_H_
#define YET_ANOTHER_ARCHIVE_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef void* YAA_Archive; /** an archive */

/** When appropriate all API calls return this enum */
enum YAA_RESULT {
    YAA_RESULT_WARN     = -1,
    YAA_RESULT_ERROR    =  0,
    YAA_RESULT_SUCCESS  =  1
};

/** Create a new empty archive
 *
 * Allocates the appropriate memory, under the hood this returns a pointer to
 * an object
 * 
 * @returns a new archive or null if there is a problem
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


/** Opens an archive for editing
 *
 *  @param yaa the archive to store the loaded info
  * @param filename the name of the archive to edit
 *  @param read_only if true then editing of the file is not allowed
 *  @returns results of attempting to load
 *      YAA_RESULT_ERROR an exception was raised or the integrity check failed
 *      YAA_RESULT_WARN if the file was already open
 *      YAA_RESULT_SUCCESS file was opened and signature matched or
 *          hmac_public_key is NULL
 */
extern enum YAA_RESULT YAA_open(YAA_Archive yaa,
                                const char * filename,
                                bool read_only);


/** Closes an open archive
 *
 *  @param yaa the archive to store the loaded info
 *  @returns results of attempting to close
 *      YAA_RESULT_ERROR an exception was raised
 *      YAA_RESULT_WARN the file was already closed
 *      YAA_RESULT_SUCCESS file was closed successfully
 */
extern enum YAA_RESULT YAA_close(YAA_Archive yaa);

/** Check if an archive is open
 *
 *  @param yaa the archive to check if open
 *  @returns 1 if open
 */
int YAA_is_open(YAA_Archive yaa);

/** Gets the file name of the archive
 * 
 * @param yaa the archive to get the file name of
 * @returns the filename, or NULL
 */
const char * YAA_filename(YAA_Archive yaa);


// TODOs

// functions:
//  YAA_add_object
//  YAA_remove_object
//  YAA_retrieve_object
//  YAA_verify_creator
//  YAA_verify_integrity
//  YAA_sign
//  YAA_save
//  YAA_parse_string

// general
//  mutex locking for write operations

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* YET_ANOTHER_ARCHIVE_H_ */