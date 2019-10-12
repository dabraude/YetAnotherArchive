
#include <fstream>

#include "yaa.h"
#include "ArchiveEditor.hpp"

namespace YAA {

enum YAA_RESULT ArchiveEditor::write_new(Archive * archive)
{
    bool was_open = archive->is_open();
    
    // delete the old file first
    _clear_content(archive);

    
    


    if (!was_open)
        archive->close();

    return YAA_RESULT_SUCCESS;
}


void ArchiveEditor::_clear_content(Archive * archive)
{
    (void) archive->close();
    std::ofstream file;
    file.open(archive->filename());
    if (file.is_open())
        file.close();
    else
        throw "failed to open file";
}

}