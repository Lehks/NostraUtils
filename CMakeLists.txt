cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

if(NOT DEFINED "${CMAKE_BUILD_TYPE}")
	set(CMAKE_BUILD_TYPE "Release")
endif()

message(STATUS "NOU:  Building in configuration \"${CMAKE_BUILD_TYPE}\".")

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



include(CMakePackageConfigHelpers)

write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/NostraUtilsConfigVersion.cmake"
	VERSION "${NostraUtils_VERSION}"
	COMPATIBILITY AnyNewerVersion)

export(EXPORT UtilsTargets
	FILE "${CMAKE_CURRENT_BINARY_DIR}/NostraUtilsConfig.cmake"
	NAMESPACE Nostra::)

configure_file("cmake/NostraUtilsConfig.cmake" "${CMAKE_CURRENT_BINARY_DIR}/NostraUtilsConfig.cmake" COPYONLY)

set(CONFIG_PACKAGE_LOCATION "lib/cmake/NostraUtils")

install(EXPORT UtilsTargets
	FILE
		NostraUtilsConfig.cmake
	NAMESPACE
		Nostra::
	DESTINATION
		${CONFIG_PACKAGE_LOCATION})

install(
  FILES
    cmake/NostraUtilsConfig.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/NostraUtilsConfig.cmake"
  DESTINATION
    ${CONFIG_PACKAGE_LOCATION}
  COMPONENT
    Develop
)


configure_file("cmake/CPackConfig.cmake" "cmake/CPackConfig.cmake" @ONLY)

include("${CMAKE_BINARY_DIR}/cmake/CPackConfig.cmake")

include(CPack)