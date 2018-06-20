cmake_minimum_required(VERSION 3.8.2 FATAL_ERROR)

project(NostraUtils 
	VERSION 1.0.1
	DESCRIPTION "A utility library for the Nostra GameEngine."
	#HOMEPAGE_URL "https://github.com/Lehks/NostraUtils"
	LANGUAGES CXX)
	
#Generate doc
add_subdirectory("doc")

find_package(Threads REQUIRED)

file(GLOB_RECURSE NOU_SOURCE_FILES "src/source/nostrautils/*.cpp")

configure_file("src/header/nostrautils/core/Config.hpp.in" 
										"${PROJECT_SOURCE_DIR}/src/header/nostrautils/core/Config.hpp" @ONLY)

add_library(NostraUtils SHARED ${NOU_SOURCE_FILES})
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

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	target_compile_definitions(NostraUtils
		PUBLIC
			"NOU_DEBUG")
endif()

target_compile_features(NostraUtils
	PUBLIC 
		cxx_std_17)

if(MSVC)
	target_compile_options(NostraUtils
		PRIVATE
			"-wd4251")
endif()

install(TARGETS NostraUtils
	RUNTIME DESTINATION "bin"
	LIBRARY DESTINATION "bin"
	ARCHIVE DESTINATION "lib"
	INCLUDES DESTINATION "include")

install(DIRECTORY "src/header/" DESTINATION "include")