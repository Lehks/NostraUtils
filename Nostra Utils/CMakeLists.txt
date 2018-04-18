cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

find_package(Threads)

file(GLOB_RECURSE NOU_SOURCE_FILES "src/source/nostrautils/*.cpp")

include_directories("${NOU_INCLUDE_DIR}")

add_library("${NOU_LIB_NAME}" SHARED "${NOU_SOURCE_FILES}")

target_link_libraries("${NOU_LIB_NAME}" "${CMAKE_THREAD_LIBS_INIT}")

install(TARGETS "${NOU_LIB_NAME}" DESTINATION "bin")

# Append / to avoid having installed src/header instead of src/header/nostrautils
install(DIRECTORY "${NOU_INCLUDE_DIR}/" DESTINATION "include")