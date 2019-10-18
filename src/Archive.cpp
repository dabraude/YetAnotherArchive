/** Copyright David Braude 2019 */

#include <cstring>
#include <iostream>

#include "Archive.hpp"
#include "ArchiveFile.hpp"
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
        ArchiveFile file;
        auto archive = const_cast<Archive*>(this);
        if (file.write(archive, filename) == YAA_RESULT_ERROR) {
            log.error("failed to write archive file");
            return YAA_RESULT_ERROR;
        }
        _filename = filename;
        std::string msg("successfully wrote: '");
        msg += _filename;
        msg += "'";
        log.info(msg);
        return YAA_RESULT_SUCCESS;
    }
    catch (const std::exception& e) {
        std::string msg("exception occured while writing file: ");
        log.critical(msg + e.what());
        return YAA_RESULT_ERROR;
    }
}


enum YAA_RESULT Archive::load(const char * filename, bool load_entities)
{
    Log log;
    try {


        
        _filename = filename;
        std::string msg("successfully loaded: '");
        msg += _filename;
        msg += "'";
        log.info(msg);
        return YAA_RESULT_SUCCESS;
    }
    catch (const std::exception& e) {
        std::string msg("exception occured while loading file: ");
        log.critical(msg + e.what());
        return YAA_RESULT_ERROR;
    }
}


const char * Archive::filename() const
{
    return _filename.c_str();
}


}

