#include "nostrautils/file_mngt/File.hpp"

namespace NOU::NOU_FILE_MNGT
{
	/*
	File::File(const NOU::NOU_DAT_ALG::StringView<char8> &name, const NOU::NOU_DAT_ALG::StringView<char8> &path, AccessMode mode)
	{
		//#pragma warning(suppress : 4996)
		//m_data = fopen(name, mode);
		//m_head = reinterpret_cast<byte*>(m_data);

		setPath(path);
		setMode(mode);
		setName(name);
		
	}

	
	//copy
	File::File(const File &other)
	{
		setName(other.m_name);
		setData(other.m_data);
		setPath(other.m_path);
		setMode(other.m_mode);
	}
	//mv
	File::File(File &&other)
	{
		setName(other.m_name);
		setData(other.m_data);
		setPath(other.m_path);
		setMode(other.m_mode);
		other.close();
		other.setMode(READ_WRITE);
		other.setName("");
		other.setPath("");
	}

	File::~File()
	{
		close();
	}

	byte File::read()
	{
		NOU_COND_PUSH_ERROR((m_mode == WRITE), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't acces write-only file");
		NOU_COND_PUSH_ERROR((m_mode == APPEND), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't acces append-only file");

		if (m_mode == WRITE || m_mode == APPEND)
		{
			return 0;
		} 

		return fgetc(m_data);
	}
	bool File::write(byte b)
	{
		NOU_COND_PUSH_ERROR((m_mode == READ), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't acces read-only file");
		if (m_mode != READ)
		{
			fputc(b, getData());
			return true;
		}
		return false;
	}


	bool File::open()
	{
		switch (m_mode)
		{
		case AccessMode::READ:
				#pragma warning(suppress : 4996)
				setData(fopen(m_absolutePath.rawStr(), "r"));
				break;
		case AccessMode::WRITE:
				#pragma warning(suppress : 4996)
				setData(fopen(m_absolutePath.rawStr(), "w"));
				break;
			case 2:
				#pragma warning(suppress : 4996)
				setData(fopen(m_absolutePath.rawStr(), "a"));
				break;
			case 3:
				#pragma warning(suppress : 4996)
				setData(fopen(m_absolutePath.rawStr(), "r+"));
				break;
			case 4:
				#pragma warning(suppress : 4996)
				setData(fopen(m_absolutePath.rawStr(), "w+"));
				break;
			case 5:
				#pragma warning(suppress : 4996)
				setData(fopen(m_absolutePath.rawStr(), "a+"));
				break;
		}
		
		return getData() != nullptr;
	}
	bool File::close()
	{

		int tmp;
		tmp = fclose(m_data);
		m_data = nullptr;
		return (tmp == 0);
	}
	void File::createFile()
	{
		open();
		close();
	}

	bool File::isCurrentlyOpen()
	{
		return m_data != NULL;
	}

	void File::calcAbsolutePath()
	{
		m_absolutePath;
		m_absolutePath.append(m_path);
		m_absolutePath.append("/");
		m_absolutePath.append(m_name);
		close();
	}
	
	NOU::NOU_DAT_ALG::StringView<char8> File::getName()
	{
		//return static_cast<const NOU::NOU_DAT_ALG::StringView<char8>>(m_name);
		return m_name;
	}
	void File::setName(const NOU::NOU_DAT_ALG::StringView<char8> &name)
	{
		m_name = name;
		calcAbsolutePath();
	}

	AccessMode File::getMode()
	{
		return m_mode;
	}
	void File::setMode(AccessMode mode)
	{
		m_mode = mode;
	}

	NOU::NOU_DAT_ALG::StringView<char8> File::getPath()
	{
		return m_path;
	}
	void File::setPath(const NOU::NOU_DAT_ALG::StringView<char8> &path)
	{
		m_path = path;
		calcAbsolutePath();
	}

	NOU::NOU_DAT_ALG::StringView<char8> File::getAbsolutePath()
	{
		return m_absolutePath;
	}

	void File::setData(FILE *data)
	{
		m_data = data;
	}
	FILE* File::getData()
	{
		return m_data;
	}*/
}