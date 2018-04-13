cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project("NostraUtilsTests" CXX)

set (CMAKE_CXX_STANDARD 17)

include_directories("${PROJECT_SOURCE_DIR}/../Nostra Utils/src/header")

add_executable("${NOU_UNIT_TEST_NAME}" "unittests.cpp" "DebugClass.cpp")

target_link_libraries("${NOU_UNIT_TEST_NAME}" "${NOU_LIB_NAME}")
add_dependencies("${NOU_UNIT_TEST_NAME}" "${NOU_LIB_NAME}")

#enable_testing()
#add_test(NAME "${NOU_UNIT_TEST_NAME}" COMMAND "${NOU_UNIT_TEST_NAME}")