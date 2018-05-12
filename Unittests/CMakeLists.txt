cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project("NostraUtilsTests" CXX)

include_directories("${PROJECT_SOURCE_DIR}/../Nostra Utils/src/header")

# Build Test-Executable
add_executable("${NOU_UNIT_TEST_NAME}" "unittests.cpp" "DebugClass.cpp")

# Link against NOU 
target_link_libraries("${NOU_UNIT_TEST_NAME}" "${NOU_LIB_NAME}")
add_dependencies("${NOU_UNIT_TEST_NAME}" "${NOU_LIB_NAME}")

install(TARGETS "${NOU_UNIT_TEST_NAME}" DESTINATION "bin")