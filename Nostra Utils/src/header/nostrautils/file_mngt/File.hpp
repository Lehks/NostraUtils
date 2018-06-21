#ifndef NOU_FILE_MNGT_FILE_HPP
#define NOU_FILE_MNGT_FILE_HPP

#include "nostrautils/dat_alg/String.hpp"
#include "nostrautils/dat_alg/StringView.hpp"
#include "nostrautils/dat_alg/Vector.hpp"
#include "nostrautils/file_mngt/Path.hpp"

#include <stdio.h>
//#include <io.h>

/** file_mngt/File.hpp
\author  Leslie Marxen
\author	 Lukas Gross
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
	\brief Class that handles very basic i/o on a single file.
	*/
	class NOU_CLASS File
	{
	private:
		const static sizeType INVALID_SIZE;

		/**
		 \param mode     The mode to open the file with.

		 \brief Wraps around either fopen() on POSIX systems or fopen_s() on a Windows system.
		*/
		void openStream(const char8 *mode);

		/**
		\brief File stream of the opened File.
		*/
		FILE															*m_data;

		/**
		\brief Whether the file is in append, write, read mode or any combination of those.
		*/
		AccessMode														m_mode;

		/**
		\brief Path to the folder containing the file.
		*/
		Path															m_path;

		/**
		\return True if the closing was successful, false if not.

		\brief This is a private function, that closes the file without checking whether it is opened or not.
		*/
		boolean closeUnchecked();

	public:

		/**
		\param path Path object containing the path to the file.
		
		\brief Constructor of the File class.
		*/
		File(const Path &path);
		
		/**
		\param other The object to copy.

		\brief Copy-constructor of the File class.
		*/
		File(const File &other) = delete;

		/**
		\param other The object to move.

		\brief Move-constructor of the File class.
		*/
		File(File &&other);

		/**
		\brief Destructor of the File Class.
		*/
		~File();

		/**
		\return The read byte.

		\brief Reads a single byte from the file.
		*/
		byte read();

		/**
		\param size   The size of the buffer.
		\param buffer The buffer to store the output in.

		\brief reads a string of given size
		*/
		sizeType read(sizeType size, char8 *buffer);

		/**
		\param buffer A reference to a string where the read data will be written to.
		\param size How many chars/bytes will be read into the String (0 = the whole File).

		\brief reads the whole file into a string.
		*/
		void read(NOU::NOU_DAT_ALG::String8 &buffer, sizeType size = 0);

		/**
		\param b The byte to write.

		\return True if successfully written, false if otherwise.

		\brief Writes a single byte into a file according to the i/o mode that is set.
		*/
		boolean write(byte b);


		/**
		\param s The given string.

		\return True if successfully written, false if otherwise.

		\brief Writes a string into a file.
		*/
		boolean write(const NOU::NOU_DAT_ALG::StringView8 &s);

		/**
		\return True if successfully opened, false if otherwise.

		\brief Opens the internal file stream.
		*/
		boolean open(AccessMode mode = AccessMode::READ_WRITE);

		/**
		\return True if successfully closed, false if otherwise.

		\brief Closes the internal file stream.
		*/
		boolean close();

		/**
		\brief Creates the file if not already existing.
		*/
		void createFile();

		/** 
		\return True if currently opened, false if not.

		\brief Checks if the file stream is opened.
		*/

		boolean isCurrentlyOpen();

		/**
		\return Returns the current access mode of the file.

		\brief Getter for the access mode that was used the last time.
		*/
		const AccessMode& getMode();

		/**
		\return Returns the path of the object.

		\brief Getter for the object path.
		*/
		const Path& getPath();

		/**
		\return The data stream.

		\brief Getter for data stream.
		*/
		FILE* getData(); 

		/**
		\return True if file exists, false otherwise.

		\brief Checks if a file is already existing according to the set path.
		*/
		boolean exists();

		/**
		\return The size of the file in bytes.
		
		\brief Returns the file size in bytes, pushes an error if the file is not existent.
		*/
		sizeType size();

		/**
		\return True if successfully deleted, false if otherwise.
		
		\brief Deletes the corresponding file.
		*/
		boolean deleteFile();

	private:

		/**
		\param mode AccessMode of the file
		
		\return if mode was set successfully
		
		\brief Setter for AccessMode
		*/
		boolean setMode(AccessMode mode);
	};
}

#endif