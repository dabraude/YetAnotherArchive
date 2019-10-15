/** Copyright David Braude 2019 */

#include <cstring>
#include <iostream>

#include "Archive.hpp"
#include "ArchiveEditor.hpp"
#include "Log.hpp"
#include "utils.hpp"

namespace YAA {

extern const char ARCHIVE_MAGIC_STRING[] = "YAA_MAGIC_STRING|1|";

Archive::Archive() : 
    _header(const_cast<Archive*>(this))
{

}


Archive::~Archive()
{
    if (_file.is_open()) {
        close();
    }
}


enum YAA_RESULT Archive::open(const char * filename, bool read_only)
{
    Log log;
    if (_file.is_open()) {
        log.warn("cannot reopen a file");
        return YAA_RESULT_WARN;
    }

    _read_only = read_only;
    try {
        if (_read_only) {
            if (empty_file(filename)) {
                log.error("read only file is empty");
                return YAA_RESULT_ERROR;
            }
            _file.open(filename, std::ios::binary | std::ios::in);
        }
        else { 
            if (empty_file(filename)) {
                auto archive = const_cast<Archive*>(this);
                ArchiveEditor editor;
                if (editor.write(archive, filename) == YAA_RESULT_ERROR)
                {
                    log.error("failed to create empty archive file");
                    return YAA_RESULT_ERROR;
                }
            }

            _file.open(filename, std::ios::binary | std::ios::in 
                                    | std::ios::out | std::ios::app);
        }

        if (_file.is_open()) {
            log.debug("file was successfully opened, checking integrity");
            // TODO: check integrity
            _filename = filename;
            return YAA_RESULT_SUCCESS;
        }
        else {
            log.debug("failed to open archive file");
            return YAA_RESULT_ERROR;
        }
    }
    catch (const std::exception& e) {
        log.debug("unknown error while opening file");
        return YAA_RESULT_ERROR;
    }
}


enum YAA_RESULT Archive::close()
{
    if (!_file.is_open())
        return YAA_RESULT_WARN;

    // write out
    _filename.clear();
    _file.close();

    if (_file.is_open())
        return YAA_RESULT_ERROR;
    else
        return YAA_RESULT_SUCCESS;
}


bool Archive::is_open() const
{
    return _file.is_open();
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

