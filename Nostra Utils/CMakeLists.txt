cmake_minimum_required(VERSION 3.8.2 FATAL_ERROR)

project(NostraUtils 
	VERSION 1.0.1
	DESCRIPTION "A utility library for the Nostra GameEngine."
	#HOMEPAGE_URL "https://github.com/Lehks/NostraUtils"
	LANGUAGES CXX)
	
set(NostraUtils_VERSION_MAJOR ${NostraUtils_VERSION_MAJOR} PARENT_SCOPE)
set(NostraUtils_VERSION_MINOR ${NostraUtils_VERSION_MINOR} PARENT_SCOPE)
set(NostraUtils_VERSION_PATCH ${NostraUtils_VERSION_PATCH} PARENT_SCOPE)
set(NostraUtils_VERSION       ${NostraUtils_VERSION}       PARENT_SCOPE)
set(NostraUtils_DESCRIPTION   ${NostraUtils_DESCRIPTION}   PARENT_SCOPE)
set(NostraUtils_HOMEPAGE_URL  ${NostraUtils_HOMEPAGE_URL}  PARENT_SCOPE)

#Generate doc
add_subdirectory("doc")

option(NOU_CPP14_COMPATIBILITY "If true, some C++17 STL features will be disabled (useful on Mac)." OFF)

find_package(Threads REQUIRED)

file(GLOB_RECURSE NOU_SOURCE_FILES "src/source/nostrautils/*.cpp")

configure_file("src/header/nostrautils/core/Config.hpp.in" 
										"${PROJECT_SOURCE_DIR}/src/header/nostrautils/core/Config.hpp" @ONLY)

set(CMAKE_DEBUG_POSTFIX "-dbg")

add_library(NostraUtilsDgb SHARED ${NOU_SOURCE_FILES})
add_library(Nostra::UtilsDbg ALIAS NostraUtilsDgb)

target_link_libraries(NostraUtilsDgb
	PRIVATE 
		Threads::Threads)

target_include_directories(NostraUtilsDgb
	PUBLIC 
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/header>"
		"$<INSTALL_INTERFACE:include>")

target_compile_definitions(NostraUtilsDgb
	INTERFACE
		"NOU_DLL")

target_compile_definitions(NostraUtilsDgb
	PUBLIC
		"NOU_DEBUG")

target_compile_features(NostraUtilsDgb
	PUBLIC 
		cxx_std_17)

if(MSVC)
	target_compile_options(NostraUtilsDgb
		PRIVATE
			"/wd4251"
			"/WX")
else()
	target_compile_options(NostraUtilsDgb
		PRIVATE
			"-Werror")
endif()

if(${NOU_CPP14_COMPATIBILITY})
	target_compile_definitions(NostraUtilsDgb
		PUBLIC
			NOU_CPP14_COMPATIBILITY)
endif()

include(GenerateExportHeader)

generate_export_header(NostraUtilsDgb)

install(TARGETS NostraUtilsDgb EXPORT NostraUtilsTargets
	RUNTIME  DESTINATION "bin"
	LIBRARY  DESTINATION "lib"
	ARCHIVE  DESTINATION "lib"
	INCLUDES DESTINATION "include")

if("${CMAKE_BUILD_TYPE}" STREQUAL "Release" OR "${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDbgInfo")

	add_library(NostraUtils SHARED ${NOU_SOURCE_FILES})
	add_library(Nostra::Utils ALIAS NostraUtils)
	
	target_link_libraries(NostraUtils
		PRIVATE 
			Threads::Threads)
	
	target_include_directories(NostraUtils
		PUBLIC 
			"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/header>"
			"$<INSTALL_INTERFACE:include>")
	
	target_compile_definitions(NostraUtils
		INTERFACE
			"NOU_DLL")
	
	target_compile_features(NostraUtils
		PUBLIC 
			cxx_std_17)
	
	if(MSVC)
		target_compile_options(NostraUtils
			PRIVATE
				"/wd4251"
				"/WX")
	else()
		target_compile_options(NostraUtils
			PRIVATE
				"-Werror")
	endif()
	
	if(${NOU_CPP14_COMPATIBILITY})
		target_compile_definitions(NostraUtils
			PUBLIC
				NOU_CPP14_COMPATIBILITY)
	endif()
	
	generate_export_header(NostraUtils)

	install(TARGETS NostraUtils EXPORT NostraUtilsTargets
		RUNTIME  DESTINATION "bin"
		LIBRARY  DESTINATION "lib"
		ARCHIVE  DESTINATION "lib"
		INCLUDES DESTINATION "include")

endif()

install(DIRECTORY "src/header/" 
	DESTINATION 
		"include" 
	COMPONENT 
		Develop)