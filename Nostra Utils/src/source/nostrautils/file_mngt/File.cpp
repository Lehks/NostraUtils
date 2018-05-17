#include "nostrautils/file_mngt/File.hpp"
#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/dat_alg/Vector.hpp"

#include <iostream>
#include <fstream>
#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
#	include <sys/stat.h>
#endif

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
		m_data(nullptr),
		m_size(0)
	{
		if(exists())
		{
			fetchSize();
		}
	}
	
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

	void File::read(sizeType size, char8 *buffer)
	{
		NOU_COND_PUSH_ERROR((m_mode == AccessMode::WRITE), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't acces write-only file");
		NOU_COND_PUSH_ERROR((m_mode == AccessMode::APPEND), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't acces append-only file");
		NOU_COND_PUSH_ERROR(!exists(), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "File does not exist");
		if(!exists())
		{
			return;
		}
		if(!isCurrentlyOpen())
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "FileStream is not open");
		}
		if (m_mode == AccessMode::WRITE || m_mode == AccessMode::APPEND)
		{
			return;
		}
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
		if(exists()){
			std::ifstream in(m_path.getAbsolutePath().rawStr(), std::ifstream::ate | std::ifstream::binary);
			// return in.tellg();
			return m_size;
		} else
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::PATH_NOT_FOUND, "File does not exist"); // PATH_NOT_FOUND
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
		if(!isCurrentlyOpen())
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "File stream is currently opened");
			return false;
		}
		if(!exists())
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "File does not exist");
			return false;
		}
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
			NOU_COND_PUSH_ERROR((m_mode == AccessMode::WRITE), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't acces write-only file");
			NOU_COND_PUSH_ERROR((m_mode == AccessMode::APPEND), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't acces append-only file");
			return;
		}
		if (fileSize == 0)
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Could not fetch Filesize, or file dos not contain data");
			fileSize == 0;
			return;
		}
		if(size > fileSize)
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Size has to be smaller or equal than the actual FileSize");
			size = fileSize;
		}
		if(size == 0)
		{
			size = fileSize;
		}

		NOU::NOU_DAT_ALG::Vector<char8> buff(size+1);
		open();
		fread(buff.data(), size, 1, m_data);
		buff[size] = 0;
		if(buffer.size() != 0)
		{
			buffer.clear();
		}
		buffer.append(buff.data());
	}

	/* void File::read(NOU::NOU_DAT_ALG::String8 &buffer)
	{
		if(!exists())
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "File does not exist");
			return;
		}
		if (m_mode == AccessMode::WRITE || m_mode == AccessMode::APPEND)
		{
			NOU_COND_PUSH_ERROR((m_mode == AccessMode::WRITE), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't acces write-only file");
			NOU_COND_PUSH_ERROR((m_mode == AccessMode::APPEND), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't acces append-only file");
			return;
		}


		sizeType size = this->size();
		NOU::NOU_DAT_ALG::Vector<char8> buff(size+1);

		open();
		fread(buff.data(), size, 1, m_data);
		buff[size] = 0;
		if(buffer.size() != 0)
		{
			buffer.clear();
		}
		buffer.append(buff.data());
	}*/

	void File::fetchSize()
	{
		if(isCurrentlyOpen()){
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Cannot read size of currently opened file");
			return;
		}
		if(exists()){
			std::ifstream in(m_path.getAbsolutePath().rawStr(), std::ifstream::ate | std::ifstream::binary);
			m_size = in.tellg();
		} else
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::PATH_NOT_FOUND, "File does not exist"); // PATH_NOT_FOUND
			return;
		}
	}
}