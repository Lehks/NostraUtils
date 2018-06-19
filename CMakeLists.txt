cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

#=== Set RPATH
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/bin")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
#===

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
	if(EXISTS "${CMAKE_SOURCE_DIR}/${NOU_TEST_EXECUTABLE_SOURCE}")
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