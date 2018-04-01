#ifndef NOU_FILE_MNGT_FOLDER_HPP
#define NOU_FILE_MNGT_FOLDER_HPP

#include "nostrautils\dat_alg\String.hpp"
#include "nostrautils\dat_alg\StringView.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\file_mngt\File.hpp"
#include "nostrautils\file_mngt\Path.hpp"

/** \file Folder.hpp
\author  Mahan Karimi
\since   0.0.1
\version 0.0.1
\brief   Folder for File Managment.
*/




namespace NOU::NOU_FILE_MNGT
{
	class NOU_CLASS Folder 
	{
	private :
			NOU::NOU_DAT_ALG::StringView8  m_path; 
			NOU::NOU_DAT_ALG::StringView8  m_name; 

			NOU::NOU_DAT_ALG::String8	   m_absolutePath;
	public :
		/*
		\brief Constructor of the class 
		\param m_name (name of you folder)
		\param m_path (location of you folder)
		*/

		Folder(const NOU::NOU_DAT_ALG::StringView<char8> &m_name, const NOU::NOU_DAT_ALG::StringView<char8> &m_path);

		NOU::NOU_DAT_ALG::Vector<Folder> listFolders() const; // "ls" kommando (Nur alle Ordner anzeigen)

		NOU::NOU_DAT_ALG::Vector<File> listFiles() const; // ls kommando (Alle datein anzeigen und in nem Vector speicher)

		/*
		\ brief A function that gives you the currently path of you folder.
		\ param an object of type Folder .
		\ return current path of you folder.
		*/
		void create(const char * m_path);

		bool exists();

		/*
		\brief A function that allows you to change the groups of a folder .
		*/

		
	};
}
#endif