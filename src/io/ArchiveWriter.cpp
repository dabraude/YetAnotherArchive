/** Copyright David Braude 2019 */
#include "fstream"
#include "./ArchiveWriter.hpp"

YAA::ArchiveWriter::ArchiveWriter(const Archive* archive) {
    _archive = archive;
}



enum YAA_RESULT YAA::ArchiveWriter::save(const char * filename, const char * private_key) {

    ofstream yaa_file;
    yaa_file.open(filename, ios::binary);

    if (!yaa_file.is_open()) {
        // need to do something about logging
        return YAA_RESULT_ERROR;
    }
}
