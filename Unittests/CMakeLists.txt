cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(NostraUtilsTests CXX)

option(NOU_GENERATE_TESTS "Enables or disables generation of the Unit-Tests." OFF)
option(NOU_UNITTEST_COLOR "Enables or disables color in the Unit-Test output. \
										This variable has only an effect, if NOU_GENERATE_TESTS is ON." ON)

# Build Test-Executable
add_executable(NostraUtilsUnitTests unittests.cpp DebugClass.cpp)

# Link against NOU 
target_link_libraries(NostraUtilsUnitTests Nostra::Utils)

if(NOT NOU_UNITTEST_COLOR)
	target_compile_definitions(NostraUtilsUnitTests 
		PRIVATE	
			CATCH_CONFIG_COLOUR_NONE)
endif()

install(TARGETS NostraUtilsUnitTests DESTINATION "bin")