#include "nostrautils/file_mngt/File.hpp"

namespace NOU::NOU_FILE_MNGT
{
	File::File(const char8 *path, const char8 *name, const char8* mode)
	{
		#pragma warning(suppress : 4996)
		m_data = fopen(name, mode);
		m_head = reinterpret_cast<byte*>(m_data);
	}

	File::File(FILE *f)
	{
		m_data = f;
	}

	
	//copy
	File::File(const File &other)
	{
		m_data = other.m_data;
		m_head = other.m_head;
	}
	//mv
	File::File(File &&other)
	{

	}

	byte File::read()
	{
		NOU::char8 tmp;
		fgets(&tmp, 0, m_data);
		return static_cast<byte>(tmp);

	}


	void open()
	{

	}
	void close()
	{
		
	}
	//void File::write();
	//void File::getName();
	//void File::getPath();
	//void File::setPath();

}