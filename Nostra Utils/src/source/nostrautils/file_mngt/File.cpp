/*
#include "nostrautils/file_mngt/File.hpp"
#include "nostrautils/core/StdIncludes.hpp"

#include <fstream>

namespace NOU::NOU_FILE_MNGT
{
	void File::fopen(FILE** file, const NOU_DAT_ALG::StringView8 &filename, const NOU_DAT_ALG::StringView8 mode)
	{
		#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
			fopen_s(file, filename.rawStr(), mode.rawStr());
		#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
			fopen(file, filename.rawStr(), mode.rawStr());
		#endif
	}

	File::File(const Path &path) :
		m_path(path),
		m_data(nullptr)
	{}
	
	//mv
	File::File(File &&other) :
		m_path(other.m_path),
		m_mode(other.m_mode),
		m_data(other.m_data)

	{
		other.m_data = nullptr;
	}

	File::~File()
	{
		close();
	}

	byte File::read()
	{
		NOU_COND_PUSH_ERROR((m_mode == AccessMode::WRITE), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't acces write-only file");
		NOU_COND_PUSH_ERROR((m_mode == AccessMode::APPEND), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't acces append-only file");

		if (m_mode == AccessMode::WRITE || m_mode == AccessMode::APPEND)
		{
			return 0;
		} 

		open();
		return fgetc(m_data);
	}

	void File::read(sizeType size, char8 *buffer)
	{
		NOU_COND_PUSH_ERROR((m_mode == AccessMode::WRITE), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't acces write-only file");
		NOU_COND_PUSH_ERROR((m_mode == AccessMode::APPEND), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't acces append-only file");

		if (m_mode == AccessMode::WRITE || m_mode == AccessMode::APPEND)
		{
			return;
		}
		open();
		fread(buffer, size, 1, m_data);
	}

	boolean File::write(byte b)
	{
		NOU_COND_PUSH_ERROR((m_mode == AccessMode::READ), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't acces read-only file");
		if (m_mode != AccessMode::READ)
		{
			fputc(b, getData());
			return true;
		}
		return false;
	}

	boolean File::write(const NOU::NOU_DAT_ALG::StringView8 &s)
	{
		NOU_COND_PUSH_ERROR((m_mode == AccessMode::READ), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't acces read-only file");
		if (m_mode != AccessMode::READ)
		{
			fwrite(s.rawStr(), sizeof(s.rawStr()[0]), s.size(), m_data);
			return true;
		}
		return false;
	}

	boolean File::open(AccessMode mode)
	{
		setMode(mode);
		if (!isCurrentlyOpen())
		{
			switch (m_mode)
			{
				case AccessMode::READ:
					fopen(&m_data, m_path.getAbsolutePath(), "r");
					break;
				case AccessMode::WRITE:
					fopen(&m_data, m_path.getAbsolutePath(), "w");
					break;
				case AccessMode::APPEND:
					fopen(&m_data, m_path.getAbsolutePath(), "a");
					break;
				case AccessMode::READ_WRITE:
					fopen(&m_data, m_path.getAbsolutePath(), "r+");
					break;
				case AccessMode::READ_WRITE_RESET:
					fopen(&m_data, m_path.getAbsolutePath(), "w+");
					break;
				case AccessMode::READ_APPEND:
					fopen(&m_data, m_path.getAbsolutePath(), "a+");
					break;
			}
		}
		return m_data != nullptr;
	}

	boolean File::close()
	{
		if (isCurrentlyOpen())
		{
			int tmp;
			tmp = fclose(m_data);
			m_data = nullptr;
			return (tmp == 0);
		} else
		{
			return 1;
		}

	}

	void File::createFile()
	{
		open();
		close();
	}

	boolean File::isCurrentlyOpen()
	{
		return m_data != nullptr;
	}	

	const AccessMode& File::getMode()
	{
		return m_mode;
	}

	void File::setMode(AccessMode mode)
	{
		close();
		m_mode = mode;
	}

	const Path& File::getPath()
	{
		return m_path;
	}

	FILE* File::getData()
	{
		return m_data;
	}

	sizeType File::size()
	{
		std::ifstream in(m_path.getAbsolutePath().rawStr(), std::ifstream::ate | std::ifstream::binary);
		return in.tellg();
	}

	boolean File::exists()
	{
		/*if (_access(m_path.getAbsolutePath().rawStr(), 0) == -1)
		{
			return false;
		}*/
		//return true;

		//#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
		struct stat   buffer;
		return (stat(m_path.getAbsolutePath().rawStr(), &buffer) == 0);
		//#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
			
		//#endif
		return true;
	}
}