#ifndef NOU_FILE_MNGT_FILE_HPP
#define NOU_FILE_MNGT_FILE_HPP

#include "nostrautils\dat_alg\String.hpp"
#include "nostrautils\dat_alg\StringView.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\file_mngt\FileManager.hpp"
#include <stdlib.h>


/** \file File.hpp
\author  Leslie Marxen
\since   0.0.1
\version 0.0.1
\brief   This file provides very basic file i/o implementations
*/





namespace NOU::NOU_FILE_MNGT
{
	/*
	insert Enum doc here
	*/
	enum AccessMode
	{
		READ,
		WRITE,
		APPEND,
		READ_WRITE,
		READ_WRITE_RESET,
		READ_APPEND
	};

	/**
	\brief Class that handles very basic i/o for a single File
	*/

	class NOU_CLASS File
	{
	private:
		/**
		\brief File stream of the opened File
		*/
		FILE															*m_data;
		/**
		\brief wether the file is in append, write, read mode or any combination of those
		*/
		AccessMode														m_mode;


		/**
		\brief path to the Folder containing the File
		*/
		const NOU::NOU_DAT_ALG::StringView<char8>						*m_path;
		/**
		\brief absolute path to the corresponding File
		*/
		NOU::NOU_DAT_ALG::String<char8>									m_absolutePath;
		/**
		\brief name of the File
		*/
		const NOU::NOU_DAT_ALG::StringView<char8>						*m_name;

	public:

		/**
		\brief construcor of the File class

		\param name name of the File
		\param mode how the File will be interpreted(Read/Write)
		\param path absolute path to the file
		*/
		File(const NOU::NOU_DAT_ALG::StringView<char8> &name, AccessMode mode, const NOU::NOU_DAT_ALG::StringView<char8> &path);
		
		/**
		\brief copy construcor of the File class

		\param other other constructer from which this will copy
		*/
		File(const File &other);
		/**
		\brief move construcor of the File class

		\param other other constructer from where everything will be moved
		*/
		File(File &&other);
		/**
		\brief destructor of the File Class
		*/
		~File();
		/**
		\brief reads a single byte from the File

		\return read byte
		*/
		byte read();

		/**
		\brief writes a single byte into a file according to the i/o mode that is set

		\return true if successfully written, false if otherwise
		*/
		bool write(byte b);

		/**
		\brief opens the internal filestream

		\return true if successfully opened, false if otherwise
		*/
		bool open();

		/**
		\brief closes the internal filestream

		\return true if successfully closed, false if otherwise
		*/
		bool close();

		/**
		\brief creates the file if not allready existing
		*/
		void createFile();

		
		/**
		\brief corresponding getter/setter for the given attributes
		*/
		///BEGIN COMMENT
		NOU::NOU_DAT_ALG::StringView<char8> getName();
		void setName(const NOU::NOU_DAT_ALG::StringView<char8> &name);

		AccessMode getMode();
		void setMode(AccessMode mode);

		NOU::NOU_DAT_ALG::StringView<char8> getPath();
		void setPath(const NOU::NOU_DAT_ALG::StringView<char8> &path);

		void setData(FILE *data);
		FILE* getData(); 

		///END COMMENT

	};
}

#endif