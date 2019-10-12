/** Copyright David Braude 2019 */

#include <cstring>
#include "Archive.hpp"
#include "ArchiveEditor.hpp"

namespace YAA {

extern const char ARCHIVE_MAGIC_STRING[] = "YAA_MAGIC_STRING|1\0";

Archive::Archive(const char * filename) :
    _filename(filename)
{

}

Archive::~Archive()
{
    if (_file.is_open())
        close();
}

enum YAA_RESULT Archive::open(const char * mode)
{
    if (_file.is_open())
    {
        // LOG cannot reopen file
        return YAA_RESULT_WARN;
    }

    try 
    {
        auto write_mode = std::ios::binary | std::ios::out;
        auto access_mode = _determine_write_mode(mode);
        

        if (access_mode == write_mode)
        {
            ArchiveEditor editor;
            return editor.write_new(const_cast<Archive*>(this));
        }
        else
        { 
            _file.open(_filename, access_mode);
            if (!_file.is_open()) {
                // LOG failed to open
                return YAA_RESULT_ERROR;
            }
        }

        return YAA_RESULT_SUCCESS;
    }
    catch (const std::exception& e)
    {
        // LOG failed to determine access mode
        return YAA_RESULT_ERROR;
    }

    return YAA_RESULT_ERROR;
}


std::ios_base::openmode Archive::_determine_write_mode(const char * mode) {
    if (!mode || std::strlen(mode) != 1)
        throw "mode string must be present and contain 1 character only";

    auto access_mode = std::ios::binary;
    switch (mode[0])
    {
        case 'r' :
            access_mode = access_mode | std::ios::in;
            break;
        case 'w' :
            access_mode = access_mode | std::ios::out;
            break;
        case 'a' : 
            access_mode = access_mode | std::ios::in | std::ios::out | std::ios::app;
            break;
        default:
            throw "mode string must one of \"r\", \"w\", or \"a\"";
    }
    return access_mode;
}

enum YAA_RESULT Archive::close()
{
    if (!_file.is_open())
        return YAA_RESULT_WARN;

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

}