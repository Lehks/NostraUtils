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

add_library(UtilsDgb SHARED ${NOU_SOURCE_FILES})
add_library(Nostra::UtilsDbg ALIAS UtilsDgb)

target_link_libraries(UtilsDgb
	PRIVATE 
		Threads::Threads)

target_include_directories(UtilsDgb
	PUBLIC 
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/header>"
		"$<INSTALL_INTERFACE:include>")

target_compile_definitions(UtilsDgb
	INTERFACE
		"NOU_DLL")

target_compile_definitions(UtilsDgb
	PUBLIC
		"NOU_DEBUG")

target_compile_features(UtilsDgb
	PUBLIC 
		cxx_std_17)

if(MSVC)
	target_compile_options(UtilsDgb
		PRIVATE
			"/wd4251"
			"/WX")
else()
	target_compile_options(UtilsDgb
		PRIVATE
			"-Werror")
endif()

if(${NOU_CPP14_COMPATIBILITY})
	target_compile_definitions(UtilsDgb
		PUBLIC
			NOU_CPP14_COMPATIBILITY)
endif()

install(TARGETS UtilsDgb EXPORT UtilsTargets
	RUNTIME  DESTINATION "bin"
	LIBRARY  DESTINATION "lib"
	ARCHIVE  DESTINATION "lib"
	INCLUDES DESTINATION "include")

if("${CMAKE_BUILD_TYPE}" STREQUAL "Release" OR "${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDbgInfo")

	add_library(Utils SHARED ${NOU_SOURCE_FILES})
	add_library(Nostra::Utils ALIAS Utils)
	
	target_link_libraries(Utils
		PRIVATE 
			Threads::Threads)
	
	target_include_directories(Utils
		PUBLIC 
			"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/header>"
			"$<INSTALL_INTERFACE:include>")
	
	target_compile_definitions(Utils
		INTERFACE
			"NOU_DLL")
	
	target_compile_features(Utils
		PUBLIC 
			cxx_std_17)
	
	if(MSVC)
		target_compile_options(Utils
			PRIVATE
				"/wd4251"
				"/WX")
	else()
		target_compile_options(Utils
			PRIVATE
				"-Werror")
	endif()
	
	if(${NOU_CPP14_COMPATIBILITY})
		target_compile_definitions(Utils
			PUBLIC
				NOU_CPP14_COMPATIBILITY)
	endif()
	
	install(TARGETS Utils EXPORT UtilsTargets
		RUNTIME  DESTINATION "bin"
		LIBRARY  DESTINATION "lib"
		ARCHIVE  DESTINATION "lib"
		INCLUDES DESTINATION "include")

endif()

install(DIRECTORY "src/header/" 
	DESTINATION 
		"include" 
	COMPONENT 
		Develop
	FILES_MATCHING 
		PATTERN "*.hpp")