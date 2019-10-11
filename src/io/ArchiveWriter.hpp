/** Copyright David Braude 2019 */

#ifndef SRC_IO_ARCHIVEWRITER_HPP_
#define SRC_IO_ARCHIVEWRITER_HPP_

#include "Archive.hpp"

namespace YAA {
class ArchiveWriter {
public:
    ArchiveWriter(const Archive* archive);

    enum YAA_RESULT save(const char * filename, const char * private_key);

protected:
    const Archive * _archive;
};


}

#endif // SRC_IO_ARCHIVEWRITER_HPP_