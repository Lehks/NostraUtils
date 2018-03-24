#ifndef NOU_FILE_MNGT_FILE_HPP
#define NOU_FILE_MNGT_FILE_HPP

#include "nostrautils\dat_alg\String.hpp"
#include "nostrautils\dat_alg\StringView.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include <stdlib.h>


//todo
/* 
	-check FilePermissions(Linux/Windows/MacOS)
	-




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


namespace NOU::NOU_FILE_MNGT
{


	class NOU_CLASS File
	{
	private:
		FILE															*m_data;
		AccessMode														m_mode;

		const NOU::NOU_DAT_ALG::StringView<char8>						*m_path;
		NOU::NOU_DAT_ALG::String<char8>									m_absolutePath;
		const NOU::NOU_DAT_ALG::StringView<char8>						*m_name;

	public:
		File(const NOU::NOU_DAT_ALG::StringView<char8> &name, AccessMode mode, const NOU::NOU_DAT_ALG::StringView<char8> &path = "");
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