/** Copyright David Braude 2019 */
#include <exception>

#include <cJSON.h>

#include "Header.hpp"
#include "Log.hpp"

namespace YAA {

Header::Header(Archive* archive)
{
    _archive = archive;
    _extra = cJSON_CreateObject();
}

Header::~Header()
{
    cJSON_Delete(_extra);
}

std::string Header::to_string() const
{
    Log log;
    cJSON * headerJSON = nullptr; 

    if (cJSON_GetArraySize(_extra))
        headerJSON = cJSON_Duplicate(_extra, true);
    else
        headerJSON = cJSON_CreateObject();

    if (!headerJSON) {
        log.critical("cannot allocate memory for generating the header JSON");
        throw std::bad_alloc();
    }

    // entries
    // auto entries = cJSON_CreateArray();
    // cJSON_AddItemToObject(headerJSON, "entries", entries);

    char * json_cstr = cJSON_PrintUnformatted(headerJSON);
    if (!json_cstr) {
        cJSON_Delete(headerJSON);
        log.critical("failed to create the header JSON string");
        throw std::bad_alloc();
    }

    std::string json_str(json_cstr);
    free(json_cstr);
    cJSON_Delete(headerJSON);
    return json_str;
}

}
