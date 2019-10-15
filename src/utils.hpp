/** Copyright David Braude 2019 */
#ifndef SRC_UTILS_HPP_
#define SRC_UTILS_HPP_

#include <string>

namespace YAA {

/** Check if a file is empty
 *  
 * @param filename file to check if it empty
 * @returns true if the file is empty or does not exist
 */
bool empty_file(const std::string & filename);

std::string hex_dump(const char * bytes, std::size_t num_bytes);

}

#endif // SRC_UTILS_HPP_