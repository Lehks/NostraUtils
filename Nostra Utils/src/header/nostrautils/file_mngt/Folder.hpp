#ifndef NOU_FILE_MNGT_FOLDER_HPP
#define NOU_FILE_MNGT_FOLDER_HPP

#include "nostrautils/file_mngt/File.hpp"
#include "nostrautils/file_mngt/Path.hpp"
#include "nostrautils/dat_alg/StringView.hpp"

/** \file Folder.hpp
\author  Mahan Karimi
\since   1.0.0
\version 1.0.1
\brief    This class provides an implementation for a simple folder system.
*/
namespace NOU::NOU_FILE_MNGT
{
	/**
	\brief			A class that provides the functionality to create, remove and operate folders.
	*/
	class Folder 
	{
	private :

		/**
		\brief		The path of the folder.
		*/
		NOU::NOU_FILE_MNGT::Path m_path;

	public :

		/**
		\param path	The folder location.

		\brief		Constructs a new Folder object with a Path object as the location.
		*/
		NOU_FUNC Folder(const Path& path);

		/**
		\return		A vector of folders.
		
		\brief		A function that lists all folders.

		\details	This function is similar to the ls-command (UNIX/LINUX/MAC) and dir-command (Windows).
		*/
		NOU_FUNC NOU::NOU_DAT_ALG::Vector<Folder> listFolders() const;

		/**
		\return		A vector of files.
		
		\brief		A function that lists all files.

		\details	This function is similar to the ls-command (UNIX/LINUX/MAC) and dir-command (Windows).
		*/		
		NOU_FUNC NOU::NOU_DAT_ALG::Vector<NOU::file_mngt::File> listFiles() const;
		
		/**
		\return		The path of the folder.
		
		\brief		This function returns the path of the folder.
		*/
		NOU_FUNC const Path & getPath() const;

		/**
		\return		True when a new folder is created and false if not.
		
		\brief		This function creates a new folder.

		\details	Calls the create(const Path &path) with the m_path attribute as default value.
		*/
		NOU_FUNC boolean create();

		/**
		\param path	The path of the folder that will be created.

		\return		True when a new folder is created and false if not.

		\brief		Creates a new folder on the passed path.
		*/
		NOU_FUNC static boolean create(const Path &path);

		/**
		\brief		Removes the folder.
		*/
		NOU_FUNC void remove();

		/**
		\param path	The path of the folder.

		\brief		Removes the folder on the passed path.
		*/
		NOU_FUNC static void remove(const Path &path);

		/**
		\return True, if the folder exists, false if not.

		\brief Returns whether the folder exists or not. 
		*/
		NOU_FUNC boolean exists() const;

		/**
		\param path The path to the folder to check. 
		
		\return True, if the folder exists, false if not.

		\brief Returns whether the folder exists or not. 
		*/
		NOU_FUNC static boolean exists(const Path &path);
	};
}
#endif
