#ifndef NOU_FILE_MNGT_FILE_HPP
#define NOU_FILE_MNGT_FILE_HPP

#include "nostrautils/dat_alg/String.hpp"
#include "nostrautils/dat_alg/StringView.hpp"
#include "nostrautils/dat_alg/Vector.hpp"
#include <stdio.h>


/** \file File.hpp
\author  Leslie Marxen
\since   1.0.0
\version 1.0.0
\brief   This file provides very basic file i/o implementations
*/





namespace NOU::NOU_FILE_MNGT
{
	/*
	\brief Enum that stores all different AccessModes of a file
	\details	READ				= opens file for reading purposes
				WRITE				= opens file for writing purposes (overwriting)
				APPEND				= opens file for appending purposes (not overwriting)
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
	\brief Class that handles very basic i/o on a single file
	*/

	class NOU_CLASS File
	{
	private:
		/**
		 \param file     The file handle of the opened file. This is an output parameter.
		 \param filename The name of the file to open.
		 \param mode     The mode to open the file with.

		 \return A handle to the opened file.

		 \brief Wraps around either fopen() on POSIX systems or fopen_s() on a Windows system.
		*/
		static void fopen(FILE** file, const NOU_DAT_ALG::StringView8 &filename, const NOU_DAT_ALG::StringView8 mode);

		/**
		\brief File stream of the opened File
		*/
		FILE															*m_data;
		/**
		\brief Wether the file is in append, write, read mode or any combination of those
		*/
		AccessMode														m_mode;


		/**
		\brief Path to the folder containing the file
		*/
		NOU::NOU_DAT_ALG::StringView8							m_path;
		/**
		\brief Absolute path to the corresponding File
		*/
		NOU::NOU_DAT_ALG::String8								m_absolutePath;
		/**
		\brief Name of the File
		*/
		NOU::NOU_DAT_ALG::StringView8							m_name;

	public:

		/**
		\brief Constructor of the File class
		0
		\param name name of the file
		\param mode how the file will be interpreted(Read/Write)
		\param path absolute path to the file
		*/
		File(const NOU::NOU_DAT_ALG::StringView8 &name, const NOU::NOU_DAT_ALG::StringView8 &path, AccessMode mode = AccessMode::READ_WRITE);
		
		/**
		\brief Copy-constructor of the File class

		\param other other constructer from which this constructor will copy
		*/
		File(const File &other) = delete;
		/**
		\brief Move-construcor of the File class

		\param other other constructer from which this constructor will move
		*/
		File(File &&other);
		/**
		\brief destructor of the File Class
		*/
		~File();
		/**
		\brief Reads a single byte from the file

		\return the read byte
		*/
		byte read();

		/**
		\param size   The size of the buffer.
		\param buffer The buffer to store the output in.

		\brief reads a string of given size
		*/
		void read(sizeType size, char8 &buffer);

		/**
		\param b The byte to write
		\brief writes a single byte into a file according to the i/o mode that is set

		\return true if successfully written, false if otherwise
		*/
		bool write(byte b);


		/**
		\brief Writes a string into a file
		\param s the given string
		\return true if successfully written, false if otherwise
		*/
		bool write(const NOU::NOU_DAT_ALG::StringView8 &s);

		/**
		\brief Opens the internal filestream

		\return true if successfully opened, false if otherwise
		*/
		bool open();

		/**
		\brief Closes the internal filestream

		\return true if successfully closed, false if otherwise
		*/
		bool close();

		/**
		\brief Creates the file if not allready existing
		*/
		void createFile();

		/** 
		\brief Checks if the Filestream is opened

		\return true if currently opened, false if not
		*/

		bool isCurrentlyOpen();

		
		/**
		\brief Getter for name
		\return name
		*/
		const NOU::NOU_DAT_ALG::StringView8& getName();

		/**
		\brief Setter for name
		\param name name of the File
		*/
		void setName(const NOU::NOU_DAT_ALG::StringView8 &name);

		/**
		\brief Getter for AccessMode
		\return current AccessMode 
		*/
		const AccessMode& getMode();

		/**
		\brief Setter for AccessMode
		\param mode AccessMode of the file
		*/
		void setMode(AccessMode mode);

		/**
		\brief Getter for Path
		\return path
		*/
		const NOU::NOU_DAT_ALG::StringView8& getPath();
		/**
		\brief Setter for the Path
		\param path Path of the file
		*/
		void setPath(const NOU::NOU_DAT_ALG::StringView8 &path);

		/**
		\brief Getter for absolutepath
		\return absolutepath
		*/
		const NOU::NOU_DAT_ALG::StringView8& getAbsolutePath();

		/**
		\brief Getter for datastream
		\return datastream
		*/
		FILE* getData(); 

	private:

		/**
		\brief Calculates the internal stored absulute path from the name and path
		*/
		void calcAbsolutePath();

	};
}

#endif