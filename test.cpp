#include <iostream>

#include "yaa.h"

int main() {
    YAA_Archive yaa = YAA_new();
    enum YAA_RESULT result = YAA_delete(yaa);
    std::cout << "Test delete: " << result << "\n";


    yaa = YAA_new();
    result = YAA_save(yaa, "test.yaa", 0);
    YAA_delete(yaa);
    std::cout << "Test save an empty file: " << result << "\n";

    return 0;
}