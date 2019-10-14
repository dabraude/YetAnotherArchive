/** Copyright David Braude 2019 */
#ifndef SRC_HEADER_HPP_
#define SRC_HEADER_HPP_

#include <string>

#include "class_defines.hpp" // forward definitions of classes

namespace YAA {
class Header
{

public:
    Header(Archive* archive);

    // parse_file();
    // parse_string();

    /** converts the header to a string */
    std::string to_string() const;

protected:

    /** back pointer to the archive */
    Archive* _archive;

};
}

#endif // SRC_HEADER_HPP_