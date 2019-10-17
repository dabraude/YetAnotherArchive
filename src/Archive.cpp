/** Copyright David Braude 2019 */

#include <cstring>
#include <iostream>

#include "Archive.hpp"
#include "ArchiveEditor.hpp"
#include "Log.hpp"
#include "utils.hpp"

namespace YAA {

extern const char ARCHIVE_MAGIC_STRING[] = "YAA_MAGIC_STRING(1)";

Archive::Archive() : 
    _header(const_cast<Archive*>(this))
{

}


enum YAA_RESULT Archive::write(const char * filename)
{
    Log log;
    try {
        ArchiveEditor editor;
        auto archive = const_cast<Archive*>(this);
        if (editor.write(archive, filename) == YAA_RESULT_ERROR) {
            log.error("failed to create empty archive file");
            return YAA_RESULT_ERROR;
        }
        _filename = filename;
        return YAA_RESULT_SUCCESS;
    }
    catch (const std::exception& e) {
        std::string msg("exception occured while writing file: ");
        log.critical(msg + e.what());
        return YAA_RESULT_ERROR;
    }
}


const char * Archive::filename() const
{
    return _filename.c_str();
}


std::string Archive::header_as_json() const
{
    return _header.to_string();
}


}

