cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project("NostraUtils" CXX)

option(NOU_CPP14_COMPATIBLILTY_MODE "Disables some C++17-only features." OFF)
option(NOU_UNITTEST_COLOR "Enables or disables color in the Unit-Test output." ON)

# Set language standard
if ("${NOU_CPP14_COMPATIBLILTY_MODE}")
	set (CMAKE_CXX_STANDARD 14)
	message(STATUS "NOU:  Generating for C++14 compatibility mode.")
	add_definitions(-DNOU_CPP14_COMPATIBILITY)
else()
	set (CMAKE_CXX_STANDARD 17)
	message(STATUS "NOU:  Generating without C++14 compatibility mode.")
endif()

#=== If NOU_COMPILE_AS_DEBUG is True, NOU_DEBUG will be defined during the compilation by default
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	set (NOU_COMPILE_AS_DEBUG True CACHE BOOL "If true, the project will be compiled with the macro NOU_DEBUG.")
	option(NOU_GENERATE_TESTS "If true, an executable that runs the UnitTests will be installed." ON)
else()
	set (NOU_COMPILE_AS_DEBUG False CACHE BOOL "If true, the project will be compiled with the macro NOU_DEBUG.")
	option(NOU_GENERATE_TESTS "If true, an executable that runs the UnitTests will be installed." OFF)
endif()

if (${COMPILE_AS_DEBUG})
	add_definitions (-DNOU_DEBUG)
endif()
#===

if(MSVC)
	add_definitions("-wd4251")
endif()

if(NOT NOU_UNITTEST_COLOR)
	add_definitions(-DCATCH_CONFIG_COLOUR_NONE)
endif()


#=== Set RPATH
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/bin")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
#===

#=== Set name of the NostraUtils include file location
if(NOT DEFINED NOU_INCLUDE_DIR)
	set(NOU_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/Nostra Utils/src/header")
endif()
#=== 

#=== Set name of the NostraUtils library file(s)
if(NOT DEFINED NOU_LIB_NAME)
	set(NOU_LIB_NAME "NostraUtils")
endif()
#=== 

#=== Set name of the Unit Test executable
	set(NOU_UNIT_TEST_NAME "UnitTests")
#=== 


#Build NostraUtils library
add_subdirectory("Nostra Utils")

include_directories("${NOU_INCLUDE_DIR}")

#=== Build Test target
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	message(STATUS "NOU:  Building in Debug mode, Test-executable will be generated.")

	# The source file of the test executable
	set(NOU_TEST_EXECUTABLE_SOURCE "main.cpp")
	
	# The name of The test executable
	set(NOU_TEST_EXECUTABLE "Test")

	#Create testmain.cpp if it does not exist
	if(NOT EXISTS "${CMAKE_SOURCE_DIR}/${NOU_TEST_EXECUTABLE_SOURCE}")
		message(STATUS "NOU:  ${NOU_TEST_EXECUTABLE_SOURCE} was not found. A default one will be generated.")
		FILE(WRITE "${CMAKE_SOURCE_DIR}/${NOU_TEST_EXECUTABLE_SOURCE}" "\n#include \"nostrautils/NostraUtils.hpp\"\n\nint main()\n{\n\treturn 0;\n}")
	endif()
	


	add_executable("${NOU_TEST_EXECUTABLE}" "${NOU_TEST_EXECUTABLE_SOURCE}")

	target_link_libraries("${NOU_TEST_EXECUTABLE}" "${NOU_LIB_NAME}")

	add_dependencies("${NOU_TEST_EXECUTABLE}" "${NOU_LIB_NAME}")


else()
	message(STATUS "NOU:  Building in Release mode, Test-executable will not be generated.")
endif()
#=== 

#=== Build Unit Tests only when explicitly enabled
if("${NOU_GENERATE_TESTS}")
	add_subdirectory("Unittests")
endif()
#=== 

# Installation only from here on
message(STATUS "NOU:  The files will be installed to: ${CMAKE_INSTALL_PREFIX}")

# Have the README.md in the install directory
install(FILES "README.md" DESTINATION ".")

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	install(TARGETS "${NOU_TEST_EXECUTABLE}" DESTINATION "bin")
endif()