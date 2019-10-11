cmake_minimum_required(VERSION 3.0.0)
project(YetAnotherArchive VERSION 0.1.0)

include_directories(include)

add_library(YetAnotherArchive
    src/api.cpp
    src/Archive.cpp
)

add_executable(testexe test.cpp)
target_link_libraries(testexe YetAnotherArchive)


set_property(TARGET YetAnotherArchive PROPERTY CXX_STANDARD 11)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
