#ifndef NOU_FILE_MNGT_FILE_HPP
#define NOU_FILE_MNGT_FILE_HPP

#include "nostrautils\dat_alg\String.hpp"
#include "nostrautils\dat_alg\StringView.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
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
		\param
		*/
		File(const NOU::NOU_DAT_ALG::StringView<char8> &name, AccessMode mode, const NOU::NOU_DAT_ALG::StringView<char8> &path);
		//copy
		File(const File &other);
		//mv
		File(File &&other);

		byte read();
		bool write(byte b);

		bool open();

		//returns true if sucessfully closed
		bool close();


		NOU::NOU_DAT_ALG::StringView<char8> getName();
		void setName(const NOU::NOU_DAT_ALG::StringView<char8> &name);

		AccessMode getMode();
		void setMode(AccessMode mode);

		NOU::NOU_DAT_ALG::StringView<char8> getPath();
		void setPath(const NOU::NOU_DAT_ALG::StringView<char8> &path);

		void setData(FILE *data);
		FILE* getData();

		//void changePermissions();
		//void changeGroups();

	};
}

#endif