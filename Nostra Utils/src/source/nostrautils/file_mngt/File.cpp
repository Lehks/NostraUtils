#include "nostrautils/file_mngt/File.hpp"
#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/dat_alg/Vector.hpp"

#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
#	include <sys/stat.h>
#	include <string.h>
#endif

namespace NOU::NOU_FILE_MNGT
{
	const sizeType File::INVALID_SIZE = -1;

	void File::openStream(const char8 *mode)
	{
		#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
			fopen_s(&m_data, this->m_path.getAbsolutePath().rawStr(), mode);
		#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
			m_data = fopen(this->m_path.getAbsolutePath().rawStr(), mode);
		#endif
	}

	boolean File::closeUnchecked()
	{
		int err;
		err = fclose(m_data);
		m_data = nullptr;
		return (err == 0);
	}

	File::File(const Path &path) :
		m_path(path),
		m_data(nullptr)
	{}
	
	//Move constructor
	File::File(File &&other) :
		m_path(other.m_path),
		m_mode(other.m_mode),
		m_data(other.m_data)
	{
		other.m_data = nullptr;
	}

	File::~File()
	{
		if (isCurrentlyOpen())
			closeUnchecked();
	}

	byte File::read()
	{
		NOU_COND_PUSH_ERROR((m_mode == AccessMode::WRITE), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't access write-only file");
		NOU_COND_PUSH_ERROR((m_mode == AccessMode::APPEND), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't access append-only file");
		NOU_COND_PUSH_ERROR(!exists(), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "File does not Exist");
		if(!exists())
		{
			return 0;
		}
		if(!isCurrentlyOpen())
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "FileStream is not open");
			return 0;
		}
		if (m_mode == AccessMode::WRITE || m_mode == AccessMode::APPEND)
		{
			return 0;
		} 

		return fgetc(m_data);
	}

	sizeType File::read(sizeType size, char8 *buffer)
	{
		NOU_COND_PUSH_ERROR((m_mode == AccessMode::WRITE), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't access write-only file");
		NOU_COND_PUSH_ERROR((m_mode == AccessMode::APPEND), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't access append-only file");

		if(!exists())
		{
			NOU_COND_PUSH_ERROR(!exists(), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "File does not exist");
			return INVALID_SIZE;
		}

		if(!isCurrentlyOpen())
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "FileStream is not open");
		}

		if (m_mode == AccessMode::WRITE || m_mode == AccessMode::APPEND)
		{
			return INVALID_SIZE;
		}

		sizeType ret = fread(buffer, size, 1, m_data);

		return ret;
	}

	boolean File::write(byte b)
	{
		NOU::boolean err;
		NOU_COND_PUSH_ERROR((m_mode == AccessMode::READ), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't access read-only file");
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
		NOU_COND_PUSH_ERROR((m_mode == AccessMode::READ), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't access read-only file");
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
		if(isCurrentlyOpen())
		{
			return false;
		}
		if (setMode(mode) == false){
			return false;
		}
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
			return closeUnchecked();
		}
		else
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Cannot close an already closed Stream");
			return false;
		}
	}

	void File::createFile()
	{
		if(!exists())
		{
			if (!isCurrentlyOpen())
			{
				open(AccessMode::WRITE);
				close();
			}
		}
		else
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "File already exists");
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

	boolean File::setMode(AccessMode mode)
	{
		if(isCurrentlyOpen())
		{
			return false;
		}
		m_mode = mode;
		return true;
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
		if (!exists())
			return INVALID_SIZE;

		boolean wasOpened = true;

		if (!isCurrentlyOpen())
		{
			wasOpened = true;
			open();
		}

		sizeType oldPos = ftell(m_data);

		fseek(m_data, 0, SEEK_END);

		sizeType ret = ftell(m_data);

		fseek(m_data, oldPos, SEEK_SET);

		if (!wasOpened)
		{
			close();
		}

		return ret;
	}

	boolean File::exists()
	{
		struct stat   buffer;
		boolean r = (stat(m_path.getAbsolutePath().rawStr(), &buffer) == 0);
		return r;
	}

	boolean File::deleteFile()
	{
		if(isCurrentlyOpen())
		{
			close();
		}

		if(!exists())
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "File does not exist");
			return false;
		}

		int err = remove(m_path.getAbsolutePath().rawStr());
		return err == 0;
	}

	void File::read(NOU::NOU_DAT_ALG::String8 &buffer, sizeType size)
	{
		sizeType fileSize = this->size();

		if(!exists())
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "File does not exist");
			return;
		}

		if (m_mode == AccessMode::WRITE || m_mode == AccessMode::APPEND)
		{
			NOU_COND_PUSH_ERROR((m_mode == AccessMode::WRITE), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't access write-only file");
			NOU_COND_PUSH_ERROR((m_mode == AccessMode::APPEND), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't access append-only file");
			return;
		}

		if (fileSize == INVALID_SIZE)
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Could not read the size of the file.");
			return;
		}

		if(size > fileSize)
		{
			size = fileSize;
		}

		if(size == 0)
		{
			size = fileSize;
		}

		char8* buff = new char8[size + 1];
		memset(buff, 0, size + 1);
		open();
		sizeType ret = fread(buff, sizeof(char8), size, m_data);
		buff[ret] = 0;
		if(buffer.size() != 0)
		{
			buffer.clear();
		}
		buffer.append(buff);
		delete[] buff;
	}
}