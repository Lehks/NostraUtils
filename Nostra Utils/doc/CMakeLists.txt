cmake_minimum_required(VERSION 3.8.2 FATAL_ERROR)

option(NOU_GENERATE_DOC "If enabled, and Doxygen is installed, the documentation will be generated" ON)

if(${NOU_GENERATE_DOC})
	
	message(STATUS "NOU:  Attempting to generate Doxygen-Doc.")

	find_package(Doxygen OPTIONAL_COMPONENTS dot)

	if(${DOXYGEN_FOUND})

		message(STATUS "NOU:  Doxygen-Executable was found, Doc will be generated.")

		configure_file(Doxyfile.in Doxyfile @ONLY)



		add_custom_target(NostraUtilsDoc
			ALL COMMAND Doxygen::doxygen "Doxyfile"
			WORKING_DIRECTORY "."
			COMMENT "Generating Doxygen-Documentation"
			VERBATIM)

		install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html/"
			DESTINATION 
				"doc/NostraUtils")

	else()
	
		message(WARNING "NOU:  Doxygen-Executable could not be found, Doc generation will be omitted.")

	endif()
	
endif()