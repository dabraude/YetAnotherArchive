/** Copyright David Braude 2019 */
#include <iostream>

#include "yaa.h"
#include "Archive.hpp"

/** Create a new empty archive */
YAA_Archive YAA_new(const char * filename)
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


/** Opens an archive for editing */
enum YAA_RESULT YAA_open(YAA_Archive yaa)
{
    if (!yaa)
    {
        return YAA_RESULT_ERROR;
    }

    try
    {
        auto yaa_arc = reinterpret_cast<YAA::Archive*>(yaa);
        yaa_arc->open();
        return YAA_RESULT_SUCCESS;
    }
    catch(const std::exception& e)
    {
        std::cerr << "exception was raised in deleting YAA archive "<< e.what() << '\n';
        return YAA_RESULT_ERROR;
    }
}

