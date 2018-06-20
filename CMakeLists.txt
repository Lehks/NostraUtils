cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

#Build NostraUtils library
add_subdirectory("Nostra Utils")

#Build UnitTests
add_subdirectory("Unittests")

option(NOU_GENERATE_TESTS "Enables or disables generation of the Test-Executable \
																		(this is NOT the Unit-Tests)." OFF)

#=== Build Test target
if(${NOU_GENERATE_TESTS})
	message(STATUS "NOU:  Test-executable will be generated.")

	#Create testmain.cpp if it does not exist
	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
		add_executable(NostraUtilsTest main.cpp)
		target_link_libraries(NostraUtilsTest Nostra::Utils)

		install(TARGETS NostraUtilsTest DESTINATION "bin")
	else()
		message(WARNING "NOU:  main.cpp was not found. No Test-Executable will be generated.")
	endif()
endif()
#=== 

# Have the README.md in the install directory
install(FILES "README.md" DESTINATION ".")
install(FILES "CHANGELOG.md" DESTINATION ".")
install(FILES "LICENSE.md" DESTINATION ".")