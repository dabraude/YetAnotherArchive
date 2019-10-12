/** Copyright David Braude 2019 */


#include "Archive.hpp"

namespace YAA {

Archive::Archive(const char * filename) :
    _filename(filename)
{

}

Archive::~Archive()
{
    if (_file.is_open())
        close();
}

enum YAA_RESULT Archive::open()
{
    if (_file.is_open())
        return YAA_RESULT_WARN;

    _file.open(_filename, std::ios::in | std::ios::out | std::ios::app | std::ios::binary);

    if (_file.is_open())
        return YAA_RESULT_SUCCESS;
    else
        return YAA_RESULT_ERROR;
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

bool Archive::is_open()
{
    return _file.is_open();
}

}
