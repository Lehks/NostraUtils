#ifndef NOU_FILE_MNGT_FILEMANAGER_HPP
#define NOU_FILE_MNGT_FILEMANAGER_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include <stdlib.h>

namespace NOU::NOU_FILE_MNGT
{

	class NOU_CLASS FileManager
	{
	private	:
		FileManager();
	public:
		static FileManager getInstance();

		boolean createFile(const char *name, const char *mode);

		boolean openFile(const char *name, const char *mode);

		boolean deleteFile(NOU::NOU_DAT_ALG::String<char8> fullpath);

		boolean createFolder(NOU::NOU_DAT_ALG::String<char8> path, NOU::NOU_DAT_ALG::String<char8> name);

		boolean openFolder(NOU::NOU_DAT_ALG::String<char8> fullpath);

		boolean deleteFolder(NOU::NOU_DAT_ALG::String<char8> fullpath);

		enum fileModes
		{

			/**
			\brief Opens an existing text file for reading purpose.
			*/
			READING = 'r',
			/**
			\brief Opens a text file for writing. If it does not exist, then a new file is created. 
			Here your program will start writing content from the beginning of the file.
			*/
			WRITING_W = 'w',
			/**
			\brief Opens a text file for writing in appending mode. If it does not exist, then a new file is created. 
			Here your program will start appending content in the existing file content.
			*/
			WRITING_A = 'a',
			/**
			\brief	Opens a text file for both reading and writing.
			*/
			READ_AND_WRITE_R = 'r+',
			/**
			\brief	Opens a text file for both reading and writing. 
			It first truncates the file to zero length if it exists, otherwise creates a file if it does not exist.
			*/
			READ_AND_WRITE_W = 'w+',
			/**
			\brief Opens a text file for both reading and writing. 
			It creates the file if it does not exist. 
			The reading will start from the beginning but writing can only be appended.
			*/
			READ_AND_WRITE_A = 'a+',
		};

		enum fileModesBinary
		{

			/**
			\brief Opens an existing text file for reading purpose.
			*/
			READING = 'rb',
			/**
			\brief Opens a text file for writing. If it does not exist, then a new file is created.
			Here your program will start writing content from the beginning of the file.
			*/
			WRITING_W = 'wb',
			/**
			\brief Opens a text file for writing in appending mode. If it does not exist, then a new file is created.
			Here your program will start appending content in the existing file content.
			*/
			WRITING_A = 'ab',
			/**
			\brief	Opens a text file for both reading and writing.
			*/
			READ_AND_WRITE_R = 'rb+',
			/**
			\brief	Opens a text file for both reading and writing.
			It first truncates the file to zero length if it exists, otherwise creates a file if it does not exist.
			*/
			READ_AND_WRITE_W = 'wb+',
			/**
			\brief Opens a text file for both reading and writing.
			It creates the file if it does not exist.
			The reading will start from the beginning but writing can only be appended.
			*/
			READ_AND_WRITE_A = 'ab+'
		};

	};

}

#endif
