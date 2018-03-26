#ifndef NOU_FILE_MNGT_FOLDER_HPP
#define NOU_FILE_MNGT_FOLDER_HPP

#include "nostrautils\dat_alg\String.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include <stdlib.h>

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


	public :
		/*
		\brief Constructor of the class 
		\param m_name (name of you folder)
		\param m_path (location of you folder)
		*/

		Folder(const NOU::NOU_DAT_ALG::StringView<char8> &m_name, const NOU::NOU_DAT_ALG::StringView<char8> &m_path);

		//listContent(); 

		/*
		\ brief A function that gives you the currently path of you folder.
		\ param an object of type Folder .
		\ return current path of you folder.
		*/

		void getPath(Folder); 

		/*
		\brief A function that gives you the name of you folder.
		\param an object of type folder .
		\return name of the folder. 
		*/

		void getName(Folder);

		/*
		\brief A function that allows you to change the name of you folder. 
		\param an object of type folder.
		*/

		void setName(Folder);

		/*
		\brief A function that allows you to change the current path of a folder.
		\param an object of type folder . 
		*/

		void setPath(Folder); 

		/*
		\brief A function that allows you to change the rights of a folder. 
		*/

		void changeRights(); 

		/*
		\brief A function that allows you to change the groups of a folder .
		*/

		void changeGroups();
	};
}
#endif