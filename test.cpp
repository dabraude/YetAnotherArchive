#include <iostream>

#include "yaa.h"

int main() {
    YAA_Archive yaa = YAA_new("test.yaa");
    enum YAA_RESULT result = YAA_delete(yaa);
    std::cout << "Test delete: " << result << "\n";


    yaa = YAA_new("test.yaa");
    result = YAA_open(yaa, "w");
    YAA_delete(yaa);
    std::cout << "Test open a new file: " << result << "\n";

    return 0;
}