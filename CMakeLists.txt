cmake_minimum_required(VERSION 3.0.0)
project(YetAnotherArchive VERSION 0.1.0)

# Options

# TODO: simulate small files

set(CJSON_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/thirdparty/cJSON" CACHE STRING
    "Path to cJSON include files")
set(CJSON_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/thirdparty/cJSON/build" CACHE STRING
    "Path to cJSON library")


# finding cJSON
find_path(cJSON_INCLUDE_PATH cJSON.h paths ${CJSON_INCLUDE_PATH})
string(COMPARE EQUAL "${cJSON_INCLUDE_PATH}" "cJSON_INCLUDE_PATH-NOTFOUND" cJSON_INCLUDE_PATH_NOTFOUND)
if (cJSON_INCLUDE_PATH_NOTFOUND)
    message(FATAL_ERROR "ERROR: cannot find cJSON header at ${CJSON_INCLUDE_PATH}")
endif()
message("-- Found cJSON header: ${cJSON_INCLUDE_PATH}/cJSON.h")

find_library(cJSON_LIBRARY cjson PATHS ${CJSON_LIBRARY_PATH} NO_DEFAULT_PATH)
string(COMPARE EQUAL "${cJSON_LIBRARY}" "cJSON_LIBRARY-NOTFOUND" cJSON_LIBRARY_NOTFOUND)
if (cJSON_LIBRARY_NOTFOUND)
    message(FATAL_ERROR "ERROR: cannot find cJSON library at ${CJSON_LIBRARY_PATH}")
endif()
message("-- Found cJSON: ${cJSON_LIBRARY}")

find_package(OpenSSL REQUIRED)

include_directories(include)
include_directories(src)
include_directories(${cJSON_INCLUDE_PATH})


# YAA_WRITE_BLOCK_SIZE


set(sources
    src/Archive.cpp
    src/ArchiveEditor.cpp
    src/Hash.cpp
    src/Header.cpp
    src/Log.cpp
    src/utils.cpp
    src/yaa.cpp
)

add_library(YetAnotherArchive ${sources})

add_executable(testexe test.cpp)
target_link_libraries(testexe YetAnotherArchive)
target_link_libraries(testexe ${cJSON_LIBRARY})
target_link_libraries(testexe ${OPENSSL_LIBRARIES})

set_property(TARGET YetAnotherArchive PROPERTY CXX_STANDARD 11)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
