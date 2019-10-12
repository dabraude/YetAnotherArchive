/** Copyright David Braude 2019 */
#ifndef SRC_ARCHIVE_EDITOR_HPP_
#define SRC_ARCHIVE_EDITOR_HPP_

#include "yaa.h"
#include "Archive.hpp"

namespace YAA {
class ArchiveEditor {
    /** Edits files on the disk
     * 
     */

public:

    /** Write a whole archive, unsigned, to disk
     *
     * It is important to sign the archive after it has been written. This will delete
     * any content already in the archive
     * 
     * @param archive Archive to write, filename will be retrieved from the archive
     * @returns
     *      YAA_RESULT_ERROR if there was a problem
     *      YAA_RESULT_SUCCESS if the file was written
     */
    enum YAA_RESULT write_new(Archive * archive);



protected:
    // _write_magic_string();
    // _write_header();
    // _write_blank_signature();
    // _write_integrity_hash();

    // _sign_document();

    /** Clears the content of an archive completely */
    void clear_content(Archive * archive);

};
}

#endif