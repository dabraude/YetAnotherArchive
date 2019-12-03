/** Copyright David Braude 2019 */

#ifndef YET_ANOTHER_ARCHIVE_H_
#define YET_ANOTHER_ARCHIVE_H_

#include <stdbool.h>

#include <cJSON.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef void* YAA_Archive; /** an archive */
typedef struct YAA_Entity YAA_Entity; /** entities in the archive */

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


/** Writes an archive to disc
 *
 *  @param yaa the archive to store the loaded info
  * @param filename where to save the archive
 *  @returns results of attempting to write
 *      YAA_RESULT_ERROR an exception was raised
 *      YAA_RESULT_SUCCESS file was successfully written to disc
 */
extern enum YAA_RESULT YAA_write(YAA_Archive yaa, const char * filename);


/** Loads an existing archive file
 * 
 * @param yaa archive to load into
 * @param filename which archive to load
 * @param load_entities if true will load all entities in the archive
 *          into memory
  */ 
extern enum YAA_RESULT YAA_load(YAA_Archive yaa, const char * filename,
                                bool load_entities);


/** Gets the file name of the archive
 * 
 * @param yaa the archive to get the file name of
 * @returns the filename, or NULL if a memory only archive
 */
const char * YAA_filename(YAA_Archive yaa);


struct YAA_Entity
{
/**
 * The data in the archive 
 */
    const char *  name;       /** name of the entity in the archive */
    char *        data;       /** data payload */
    size_t        data_size;  /** the amount of data */
    cJSON *       meta_data;  /** meta data of the entity */
    long int      file_start; /** position relative to start of file */
};


// New entity
// Delete entity

// TODOs

// functions:
//  YAA_add_object
//  YAA_remove_object
//  YAA_retrieve_object
//  YAA_verify_creator
//  YAA_verify_checksum
//  YAA_sign
//  YAA_parse_string

// general
//  mutex locking for write operations

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* YET_ANOTHER_ARCHIVE_H_ */