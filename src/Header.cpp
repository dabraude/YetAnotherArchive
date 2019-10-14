/** Copyright David Braude 2019 */


#include <cJSON.h>

#include "Header.hpp"

namespace YAA {

Header::Header(Archive* archive)
{
    _archive = archive;
}

std::string Header::to_string() const
{
    auto headerJSON = cJSON_CreateObject();
    if (!headerJSON) {
        // LOG Critical : cannot allocate memory for generating the header
        throw "cannot allocate memory for generating the header JSON.";
    }

    // entries
    auto entries = cJSON_CreateArray();
    cJSON_AddItemToObject(headerJSON, "entries", entries);

    // other stuff

    char * json_cstr = cJSON_PrintUnformatted(headerJSON);
    if (!json_cstr) {
        // LOG Critical : cannot allocate memory for generating the header
        cJSON_Delete(headerJSON);
        throw "failed to create the header JSON.";
    }

    std::string json_str(json_cstr);
    free(json_cstr);
    cJSON_Delete(headerJSON);
    return json_str;
}

}
