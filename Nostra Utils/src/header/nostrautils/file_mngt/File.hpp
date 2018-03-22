#ifndef NOU_FILE_MNGT_FILE_HPP
#define NOU_FILE_MNGT_FILE_HPP

#include "nostrautils\dat_alg\String.hpp"



//todo
/* 
	-check FilePermissions(Linux/Windows/MacOS)
	-




*/




namespace NOU::NOU_FILE_MNGT
{


	class File
	{
	private:
		NOU::NOU_DAT_ALG::String<char8> m_data;
	public:
		File(NOU::NOU_DAT_ALG::String<char8> path);

		void read();
		void replace();
		void append();
		void setWriteMode();
		void getName();
		void getPath();
		void setPath();
		void changeRights();
		void changeGroups();


	};
}

#endif