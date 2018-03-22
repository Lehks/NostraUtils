#ifndef NOU_FILE_MNGT_FILE_HPP
#define NOU_FILE_MNGT_FILE_HPP

#include "nostrautils\dat_alg\String.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include <stdlib.h>


//todo
/* 
	-check FilePermissions(Linux/Windows/MacOS)
	-




*/




namespace NOU::NOU_FILE_MNGT
{


	class NOU_CLASS File
	{
	private:
		FILE							*m_data;
		byte							*m_head;

		NOU::NOU_DAT_ALG::String<char8>	m_path;
		NOU::NOU_DAT_ALG::String<char8> m_name;

	public:
		File(const char8 *path, const char8 *name, const char8 *mode);
		File(FILE* f);
		//copy
		File(const File &other);
		//mv
		File(File &&other);

		byte read();
		void open();
		void close();
		//void write();
		//void getName();
		//void getPath();
		//void setPath();
		//void changePermissions();
		//void changeGroups();


	};
}

#endif