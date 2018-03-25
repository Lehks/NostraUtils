#ifdef NOU_FILE_MNGT_FILEMANAGER_HPP
#define NOU_FILE_MNGT_FILEMANAGER_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\file_mngt\File.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include <stdlib.h>

/** \file FileManager.hpp
\author  Dennis Franz
\since   0.0.1
\version 0.0.1
\brief   This File provides a file management system for the specific use in the game engine.
*/

namespace NOU::NOU_FILE_MNGT
{
	class NOU_CLASS FileManager
	{
	private	:

		/**
		\brief A Vector which stores the Files that are added to it.
		*/
		NOU::NOU_DAT_ALG::Vector<NOU::NOU_FILE_MNGT::File> m_fileStorage;
		/**
		\brief A Vector which stores the Folders that are added to it.
		*/
		NOU::NOU_DAT_ALG::Vector<NOU::NOU_FILE_MNGT::File> m_folderStorage;
		/**
		\brief A Vector which stores all files which are currently open.
		*/
		NOU::NOU_DAT_ALG::Vector<NOU::NOU_FILE_MNGT::File> m_openedFiles;
		/**
		\brief A counter that stores the amount of file objects in m_fileStorage.
		*/
		sizeType m_storedFiles;
		/**
		\brief A counter that stores the amount of currently opened file objects in m_openedFiles.
		*/
		sizeType m_openedFileCount;
		/**
		\brief A counter that stores the amount of folder objects in m_folderStorage.
		*/
		sizeType m_storedFolders;
		/**
		\brief A private Constructor according to the singleton pattern.
		*/
		FileManager();
		/**
		\param file				A File object from nostra::file_mngt::file.

		\return boolean			A boolean to check if it was successfully or not.

		\brief A Function that closes the selected open file and removes it from the m_openedFiles Vector.
		*/
		boolean removeFromOpenedFiles(const File &file);
	public:
		/**
		\return FileManager		The instance of the FileManager.

		\brief A static Function according to the singleton pattern.
		*/
		static FileManager& getInstance();
		/**
		\param const &name				The name of the file.
		\param const &path				The path where the file is saved or should be saved.

		\return boolean			A boolean to check if it was successfully or not.

		\brief This Function adds a file object to m_fileStorage.
		*/
		boolean addFile(const NOU::NOU_DAT_ALG::StringView<char8> &name, const NOU::NOU_DAT_ALG::StringView<char8> &path);
		/**
		\param file				A File object from nostra::file_mngt::file.

		\return boolean			A boolean to check if it was successfully or not.

		\brief This Function opens a Files (for reading or writing purposes).
		*/
		boolean openFile(const File &file);
		/**
		\param file				A File object from nostra::file_mngt::file.

		\return boolean			A boolean to check if it was successfully or not.

		\brief This function closes the file.
		*/
		boolean closeFile(const File &file);
		/**
		\param const &name		The name of the file which should be returned.

		\return file			A File object from nostra::file_mngt::file.

		\brief This function finds a file based on the given name.
		*/
		NOU::NOU_FILE_MNGT::File getFile(const NOU::NOU_DAT_ALG::StringView<char8> &name);
		/**
		\param file				A File object from nostra::file_mngt::file.

		\return boolean			A boolean to check if it was successfully or not.

		\brief A Function that closes the selected open file and removes it from the m_openedFiles Vector.
		*/
		boolean removeFile(const File &file);
		/**
		\param file				A File object from nostra::file_mngt::file.

		\return const &name		A StrinView<char8> which contains the File name.

		\brief A Function that returns the name from the given file.
		*/
		const NOU::NOU_DAT_ALG::StringView<char8>& getFileName(const File &file) const;
		/**
		\param file				A File object from nostra::file_mngt::file.

		\return const &name		A StrinView<char8> which contains the File path.

		\brief A Function that returns the path from the given file without the name.
		*/
		const NOU::NOU_DAT_ALG::StringView<char8>& getFilePath(const File &file) const;
		/**
		\param file				A File object from nostra::file_mngt::file.

		\return const &name		A StrinView<char8> which contains the absolute file path.

		\brief A Function that returns full path of the file (including the name).
		*/
		const NOU::NOU_DAT_ALG::StringView<char8>& getAbsoluteFilePath(const File &file) const;
	};

}

#endif