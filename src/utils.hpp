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

/** Converts bytes to a hex dump string
 * 
 * @param bytes raw byte to conver
 * @param num_bytes the number of bytes in the bytes array
 * @returns the hex dump (lower case ascii)
 */
std::string hex_dump(const char * bytes, std::size_t num_bytes);

/** calculates 10 ^ exponent */
std::size_t pow10(std::size_t exponent);

}

#endif // SRC_UTILS_HPP_