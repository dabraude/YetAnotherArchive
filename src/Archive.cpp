/** Copyright David Braude 2019 */

#include <cstring>

#include "Archive.hpp"
#include "ArchiveEditor.hpp"
#include "utils.hpp"

namespace YAA {

extern const char ARCHIVE_MAGIC_STRING[] = "YAA_MAGIC_STRING|1";

Archive::Archive(const char * filename) :
    _filename(filename)
{

}

Archive::~Archive()
{
    if (_file.is_open())
        close();
}

enum YAA_RESULT Archive::open(bool read_only)
{
    if (_file.is_open())
    {
        // LOG WARN: cannot reopen file
        return YAA_RESULT_WARN;
    }

    _read_only = read_only;
    try 
    {
        if (_read_only)
        {
            _file.open(_filename, std::ios::binary | std::ios::in);
        }
        else
        { 
            if (empty_file(_filename))
            {
                auto archive = const_cast<Archive*>(this);
                ArchiveEditor editor;
                if (editor.write_new(archive) == YAA_RESULT_ERROR)
                {
                    // LOG ERROR: failed to create empty file
                    return YAA_RESULT_ERROR;
                }
            }

            _file.open(_filename, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
        }

        if (_file.is_open())
        {
            // LOG INFO: failed to open
            return YAA_RESULT_SUCCESS;
        }
        else
        {
            // LOG ERROR: failed to open
            return YAA_RESULT_ERROR;
        }
    }
    catch (const std::exception& e)
    {
        // LOG ERROR: unknown error
        return YAA_RESULT_ERROR;
    }
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