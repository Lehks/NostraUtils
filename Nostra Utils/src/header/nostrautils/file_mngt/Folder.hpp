#ifndef NOU_FILE_MNGT_FOLDER_HPP
#define NOU_FILE_MNGT_FOLDER_HPP

#include "nostrautils\file_mngt\File.hpp"
#include "nostrautils\file_mngt\Path.hpp"
#include "nostrautils/dat_alg/StringView.hpp"
/** \file Folder.hpp
\author  Mahan Karimi
\since   0.0.1
\version 0.0.1
\brief    This class provides an implementation for a simple folder system.
*/




namespace NOU::NOU_FILE_MNGT
{
	class NOU_CLASS Folder 
	{
	private :

		Path m_path;

		NOU::NOU_DAT_ALG::String8 m_name = "."; 

	public :
		/*
		\brief Constructor of the class 
		\param m_path (location of you folder )
		*/

		Folder(const Path &path);

		/*
		\brief A function that lists you all folders in a directory and safes the result in a vector { ls commando }  
		\return all folders and safes in a vector  
		*/

		NOU::NOU_DAT_ALG::Vector<Folder> listFolders() const;

		/*
		\ brief A function that lists you all files in a directory and safes the result in a vector 
		\ return all files and safes in a vector
		*/
												
		NOU::NOU_DAT_ALG::Vector<Folder> listFiles() const;
		
		/*
		\brief  A function that returns you the current path 
		\return the path which you give you constructor as parameter
		*/

		const Path & getPath() const;

		/*
		\ brief A function that creates you a folder with an object
		\ return a folder in the path you give the constructor as parameter 
		*/

		boolean create();

		/*
		\ brief A function that creates you a folder without an object
		\ param a path where you folder will be create
		\ return a folder in the path you give the constructor as parameter
		*/
		
		static boolean create(const Path &path);

 
		//void read_directory(const NOU::NOU_DAT_ALG::String8 &name,  v);

		
	};
}
#endif