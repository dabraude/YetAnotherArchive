/** Copyright David Braude 2019 */
#include <iostream>

#include "yaa.h"
#include "Archive.hpp"

// The API should just be a pass through to undelying objects, this macro
// can handle everything other than the constructor and destructor

#define C_API_ARCHIVE_CALL(Y, return_type, error_value, func, ...)                  \
{                                                                                   \
    if (!Y)                                                                         \
        return error_value;                                                         \
    try {                                                                           \
        auto archive = reinterpret_cast<YAA::Archive*>(Y);                          \
        return_type result = static_cast<return_type>(archive->func(__VA_ARGS__));  \
        return result;                                                              \
    }                                                                               \
    catch(const std::exception& e) {                                                \
        std::cerr << "exception was raised in YAA_ " << #func                       \
            << ": " << e.what() << '\n';                                            \
        return error_value;                                                         \
    }                                                                               \
}                                                                                   \

// The wrapped API functions
enum YAA_RESULT YAA_write(YAA_Archive yaa, const char * filename)   
    C_API_ARCHIVE_CALL(yaa, enum YAA_RESULT, YAA_RESULT_ERROR, write,
                        filename);

enum YAA_RESULT YAA_load(YAA_Archive yaa, const char * filename,
                            bool load_entities)   
    C_API_ARCHIVE_CALL(yaa, enum YAA_RESULT, YAA_RESULT_ERROR, load, filename,
                        load_entities);

const char * YAA_filename(YAA_Archive yaa)
    C_API_ARCHIVE_CALL(yaa, const char *, nullptr, filename);


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
        return YAA_RESULT_ERROR;

    try
    {
        auto archive = reinterpret_cast<YAA::Archive*>(yaa);
        delete archive;
        return YAA_RESULT_SUCCESS;
    }
    catch(const std::exception& e)
    {
        std::cerr << "exception was raised in YAA_delete " << e.what() << '\n';
        return YAA_RESULT_ERROR;
    }
}

