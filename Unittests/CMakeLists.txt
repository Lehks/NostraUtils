cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project("Tests" CXX)

set (CMAKE_CXX_STANDARD 17)

include_directories("${PROJECT_SOURCE_DIR}/../Nostra Utils/src/header")

add_executable("Test" "unittests.cpp" "DebugClass.cpp")

target_link_libraries("Test" "NostraUtils")