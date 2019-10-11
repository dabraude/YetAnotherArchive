#include <iostream>

#include "yaa.h"

int main() {
    YAA_Archive yaa = YAA_new();
    enum YAA_RESULT result = YAA_delete(yaa);
    std::cout << "Test delete: " << result << "\n";


    return 0;
}