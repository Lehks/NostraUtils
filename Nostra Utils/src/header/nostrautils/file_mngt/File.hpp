#ifndef NOU_FILE_MNGT_FILE_HPP
#define NOU_FILE_MNGT_FILE_HPP

#include "nostrautils\dat_alg\String.hpp"
#include "nostrautils\dat_alg\StringView.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include <stdio.h>


/** \file File.hpp
\author  Leslie Marxen
\since   0.0.1
\version 0.0.1
\brief   This file provides very basic file i/o implementations
*/





namespace NOU::NOU_FILE_MNGT
{
	/*
	\brief Enum that stores all different AccessModes of a file
	\details	READ				= opens file for Reading purposes
				WRITE				= opens file for Writing purposes (overwriting)
				APPEND				= opens file for Appending purposes (not overwriting)
				READ_WRITE			= opens file for both reading and writing (overwriting)
				READ_WRITE_RESETS	= opens the file for both reading and writing purposes after clearing the file(overwriting)
				READ_APPEND			= opens the file for both reading and writing purposes (not overwriting)
	*/
	enum class AccessMode
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
		NOU::NOU_DAT_ALG::StringView8							m_path;
		/**
		\brief absolute path to the corresponding File
		*/
		NOU::NOU_DAT_ALG::String8								m_absolutePath;
		/**
		\brief name of the File
		*/
		NOU::NOU_DAT_ALG::StringView8							m_name;

	public:

		/**
		\brief construcor of the File class

		\param name name of the File
		\param mode how the File will be interpreted(Read/Write)
		\param path absolute path to the file
		*/
		File(const NOU::NOU_DAT_ALG::StringView8 &name, const NOU::NOU_DAT_ALG::StringView8 &path, AccessMode mode = AccessMode::READ_WRITE);
		
		/**
		\brief copy construcor of the File class

		\param other other constructer from which this will copy
		*/
		File(const File &other) = delete;
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
		\brief reads a string from given size
		\param size StringSize in byte 
		*/
		void read(sizeType size, char8 &buffer);

		/**
		\brief writes a single byte into a file according to the i/o mode that is set

		\return true if successfully written, false if otherwise
		*/
		bool write(byte b);


		/**
		\brief writes a string into a file
		\param s the given string
		\return true if successfully written, false if otherwise
		*/
		bool write(const NOU::NOU_DAT_ALG::StringView8 &s);

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
		\brief checks if the Filestream is opened

		\return true if currently opened, false if not
		*/

		bool isCurrentlyOpen();

		
		/**
		\brief getter for name
		\return name
		*/
		const NOU::NOU_DAT_ALG::StringView8& getName();

		/**
		\brief setter for name
		\param name name of the File
		*/
		void setName(const NOU::NOU_DAT_ALG::StringView8 &name);

		/**
		\brief getter for AccessMode
		\return AccessMode
		*/
		const AccessMode& getMode();

		/**
		\brief setter for AccessMode
		\param mode AccessMode of the File
		*/
		void setMode(AccessMode mode);

		/**
		\brief getter for Path
		\return Path
		*/
		const NOU::NOU_DAT_ALG::StringView8& getPath();
		/**
		\brief setter for Path
		\param path Path of the file
		*/
		void setPath(const NOU::NOU_DAT_ALG::StringView8 &path);

		/**
		\brief getter for absolutepath
		\return absolutepath
		*/
		const NOU::NOU_DAT_ALG::StringView8& getAbsolutePath();

		/**
		\brief getter for datastream
		\return datastream
		*/
		FILE* getData(); 

	private:

		/**
		\brief calculates the internal stored absulute path from the name and path
		*/
		void calcAbsolutePath();

	};
}

#endif