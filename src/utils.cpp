
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "utils.hpp"

namespace YAA {

bool empty_file(const std::string & filename)
{
    std::ifstream file;
    file.open(filename);
    if (!file.is_open())
        return true;
    char c = file.peek();
    file.close();
    return (c == EOF);
}

constexpr char hexmap[] = {'0','1','2','3','4','5','6','7','8','9',
                            'a','b','c','d','e','f'};

std::string hex_dump(const char * bytes, std::size_t num_bytes)
{
    /* thanks to stack overflow
        https://codereview.stackexchange.com/questions/78535/converting-array-of-bytes-to-the-hex-string-representation 
    */
    std::string out(num_bytes*2, ' ');
    for (int b = 0; b < num_bytes; b++) {
        out[2*b]     = hexmap[(bytes[b] & 0xF0) >> 4];
        out[2*b + 1] = hexmap[bytes[b] & 0x0F];
    }
    return out;
}




}