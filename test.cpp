#include <iostream>

#include "yaa.h"

int main() {
    YAA_Archive yaa = YAA_new();
    enum YAA_RESULT result = YAA_delete(yaa);
    std::cout << "Test delete: " << result << "\n";


    YAA_Archive yaa2 = YAA_new();
    result = YAA_write(yaa2, "test.yaa");
    YAA_delete(yaa2);
    std::cout << "Test open a new file: " << result << "\n";

    return 0;
}