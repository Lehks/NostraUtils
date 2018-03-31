cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project("NostraUtils")

# set C++17 as language standard
set (CMAKE_CXX_STANDARD 17)

#=== set bin/ as output directory
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#===

#=== If COMPILE_AS_DEBUG is True, NOU_DEBUG will be defined during the compilation
set (COMPILE_AS_DEBUG False CACHE BOOL "If true, the project will be compiled with the macro NOU_DEBUG.")

if (${COMPILE_AS_DEBUG})
	add_definitions (-DNOU_DEBUG)
endif()
#===

add_subdirectory(Nostra\ Utils)