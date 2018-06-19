cmake_minimum_required(VERSION 3.8.2 FATAL_ERROR)

project(NostraUtils CXX)

find_package(Threads REQUIRED)

file(GLOB_RECURSE NOU_SOURCE_FILES "src/source/nostrautils/*.cpp")

add_library(NostraUtils SHARED "${NOU_SOURCE_FILES}")
add_library(Nostra::Utils ALIAS NostraUtils)

target_link_libraries(NostraUtils
	PRIVATE 
		Threads::Threads)

target_include_directories(NostraUtils
	PUBLIC 
		"src/header")

target_compile_definitions(NostraUtils
	INTERFACE
		"NOU_DLL")

target_compile_features(NostraUtils
	PUBLIC 
		cxx_std_17)

target_compile_options(NostraUtils
	PRIVATE
		"-wd4251")

install(TARGETS NostraUtils
	RUNTIME DESTINATION "bin"
	LIBRARY DESTINATION "bin"
	ARCHIVE DESTINATION "lib"
	INCLUDES DESTINATION "include")