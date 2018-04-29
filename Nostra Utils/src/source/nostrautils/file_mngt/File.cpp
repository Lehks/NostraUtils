#include "nostrautils/file_mngt/File.hpp"
#include "nostrautils/core/StdIncludes.hpp"

#include <iostream>
#include <fstream>

namespace NOU::NOU_FILE_MNGT
{
	void File::openStream(const char8 *mode)
	{
		#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
			fopen_s(&m_data, this->m_path.getAbsolutePath().rawStr(), mode);
		#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
			m_data = fopen(this->m_path.getAbsolutePath().rawStr(), mode);
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
		NOU_COND_PUSH_ERROR(!exists(), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "File does not Exist");
		if(!exists())
		{
			return 0;
		}
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
		NOU_COND_PUSH_ERROR(!exists(), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "File does not exist");
		if(!exists())
		{
			return;
		}
		if (m_mode == AccessMode::WRITE || m_mode == AccessMode::APPEND)
		{
			return;
		}
		open();
		fread(buffer, size, 1, m_data);
	}

	boolean File::write(byte b)
	{
		NOU::boolean err;
		NOU_COND_PUSH_ERROR((m_mode == AccessMode::READ), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't acces read-only file");
		if(!isCurrentlyOpen())
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "File stream is not opened");
			return false;
		}
		if (m_mode != AccessMode::READ)
		{
			fputc(b, getData());
			err = (ferror(m_data) == 0);
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Unknown Error");
			return err;
		}
		return false;
	}

	boolean File::write(const NOU::NOU_DAT_ALG::StringView8 &s)
	{
		NOU_COND_PUSH_ERROR((m_mode == AccessMode::READ), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't acces read-only file");
		if(!isCurrentlyOpen())
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "File stream is not opened");
			return false;
		}
		if (m_mode != AccessMode::READ)
		{
			fwrite(s.rawStr(), sizeof(s.rawStr()[0]), s.size(), m_data);
			return (ferror(m_data)) == 0;
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
					openStream("r");
					break;
				case AccessMode::WRITE:
					openStream("w");
					break;
				case AccessMode::APPEND:
					openStream("a");
					break;
				case AccessMode::READ_WRITE:
					openStream("r+");
					break;
				case AccessMode::READ_WRITE_RESET:
					openStream("w+");
					break;
				case AccessMode::READ_APPEND:
					openStream("a+");
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
		if(!exists())
		{
			std::fstream fs;
			fs.open(m_path.getAbsolutePath().rawStr(), std::ios::out);
			fs.flush();
			fs.close();
		}else
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Fille allready exists");
		}
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
		if(isCurrentlyOpen()){
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Cannot read size of currently opened file");
			return 0;
		}
		if(exists()){
			std::ifstream in(m_path.getAbsolutePath().rawStr(), std::ifstream::ate | std::ifstream::binary);
			return in.tellg();
		} else
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::PATH_NOT_FOUND, "File does not exist"); //PATH_NOT_FOUND
			return 0;
		}
	}

	boolean File::exists()
	{
		struct stat   buffer;
		boolean r = (stat(m_path.getAbsolutePath().rawStr(), &buffer) == 0);
		return r;
	}

	boolean File::deleteFile()
	{
		int err = remove(m_path.getAbsolutePath().rawStr());
		return err == 0;
	}
}