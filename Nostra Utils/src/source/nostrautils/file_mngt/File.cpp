#include "nostrautils/file_mngt/File.hpp"

namespace NOU::NOU_FILE_MNGT
{
	File::File(const char8 *name, const char8 *mode, const char8 *path = "")
	{
		//#pragma warning(suppress : 4996)
		//m_data = fopen(name, mode);
		//m_head = reinterpret_cast<byte*>(m_data);

		setPath(path);
		setMode(mode);
		setName(name);
		m_absolutePath;
		m_absolutePath.append(path);
		m_absolutePath.append("/");
		m_absolutePath.append(name);
	}

	
	//copy
	File::File(const File &other)
	{

	}
	//mv
	File::File(File &&other)
	{

	}

	byte File::read()
	{
		return fgetc(m_data);
	}
	void File::write()
	{
		if (getAppendMode())	//true
		{

		}
	}


	bool File::open()
	{

		#pragma warning(suppress : 4996)
		setData(fopen(m_name, m_mode));
		return getData() != NULL;
	}
	bool File::close()
	{
		return (fclose(m_data) == NULL);
	}
	
	const char8* File::getName()
	{
		return m_name;
	}
	void File::setName(const char8 *name)
	{
		m_name = name;
	}
	const char8* File::getMode()
	{
		return m_mode;
	}
	void File::setMode(const char8 *mode)
	{
		m_mode = mode;
	}
	const char8* File::getPath()
	{
		return m_path;
	}
	void File::setPath(const char8 *path)
	{
		m_path = path;
	}
	void File::setData(FILE *data)
	{
		m_data = data;
	}
	FILE* File::getData()
	{
		return m_data;
	}
	void File::setAppendMode(bool mode)
	{
		m_appendMode = mode;
	}
	bool File::getAppendMode()
	{
		return m_appendMode;
	}
}