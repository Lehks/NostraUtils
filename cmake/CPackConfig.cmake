#include("${CMAKE_BINARY_DIR}/CPackConfig.cmake")

#configure_file("cmake/welcome.txt" "cmake/welcome.txt" COPYONLY)
#configure_file("LICENSE.md" "LICENSE.md" COPYONLY)
#configure_file("cmake/welcome.txt" "cmake/welcome.txt" COPYONLY)

#set(CPACK_INSTALL_CMAKE_PROJECTS
#	"Debug;NostraUtils;All;/"
#	"Release;NostraUtils;All;/")

set(CPACK_PACKAGE_NAME "NostraUtils")
set(CPACK_PACKAGE_VENDOR "The Nostra Project Team")
set(CPACK_PACKAGE_VERSION_MAJOR "@NostraUtils_VERSION_MAJOR@")
set(CPACK_PACKAGE_VERSION_MINOR "@NostraUtils_VERSION_MINOR@")
set(CPACK_PACKAGE_VERSION_PATCH "@NostraUtils_VERSION_PATCH@")
#set(CPACK_PACKAGE_DESCRIPTION "NostraUtils")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "NostraUtils_DESCRIPTION")
set(CPACK_PACKAGE_HOMEPAGE_URL "NostraUtils_HOMEPAGE_URL")
#set(CPACK_PACKAGE_ICON "NostraUtils")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.md")
#set(CPACK_RESOURCE_FILE_README "NostraUtils") ###CREATE INSTALL README!
set(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_SOURCE_DIR}/cmake/welcome.txt")