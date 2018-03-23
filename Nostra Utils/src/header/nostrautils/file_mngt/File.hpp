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
		const char8						*m_mode;

		const char8						*m_path;
		NOU::NOU_DAT_ALG::String<char8>	m_absolutePath;
		const char8						*m_name;
		bool							m_appendMode;

	public:
		File(const char8 *name, const char8 *mode, const char8 *path = "");
		//copy
		File(const File &other);
		//mv
		File(File &&other);

		byte read();
		void write();

		bool open();

		//returns true if sucessfully closed
		bool close();


		const char8* getName();
		void setName(const char8 *name);
		const char8* getMode();
		void setMode(const char8 *mode);
		const char8* getPath();
		void setPath(const char8 *path);
		void setData(FILE *data);
		FILE* getData();
		void setAppendMode(bool mode);
		bool getAppendMode();
		//void changePermissions();
		//void changeGroups();

	};
}

#endif