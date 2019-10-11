/** Copyright David Braude 2019 */
#include <iostream>

#include "yaa.h"
#include "Archive.hpp"

/** Create a new empty archive */
YAA_Archive YAA_new()
{
    auto yaa = new YAA::Archive();
    return yaa;
}


/** Frees the memory of an existing archive */
enum YAA_RESULT YAA_delete(YAA_Archive yaa)
{
    if (!yaa)
    {
        return YAA_RESULT_ERROR;
    }

    try
    {
        auto yaa_arc = reinterpret_cast<YAA::Archive*>(yaa);
        delete yaa_arc;
        return YAA_RESULT_SUCCESS;
    }
    catch(const std::exception& e)
    {
        std::cerr << "exception was raised in deleting YAA archive "<< e.what() << '\n';
        return YAA_RESULT_ERROR;
    }
}


/** Saves archive to disk */
extern enum YAA_RESULT YAA_save(YAA_Archive yaa, const char * filename, const char * private_key) 
{
    if (!yaa)
    {
        return YAA_RESULT_ERROR;
    }

    try
    {
        auto yaa_arc = reinterpret_cast<YAA::Archive*>(yaa);
        return yaa_arc->save(filename, private_key);
    }
    catch(const std::exception& e)
    {
        return YAA_RESULT_ERROR;
    }
}