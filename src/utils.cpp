
#include <iostream>
#include <fstream>
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

}