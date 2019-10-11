/** Copyright David Braude 2019 */
#include <exception>
#include "Archive.hpp"
#include "io/ArchiveWriter.hpp"

enum YAA_RESULT YAA::Archive::load(const char * filename, const char * public_key)
{
    return YAA_RESULT_SUCCESS;
}


enum YAA_RESULT YAA::Archive::save(const char * filename, const char * private_key)
{
    try
    {
        YAA::ArchiveWriter writer(this);
        return writer.save(filename, private_key);
    }
    catch(const std::exception& e)
    {
        return YAA_RESULT_ERROR;
    }
}


