#include "nostrautils/file_mngt/File.hpp"
#include "nostrautils/core/StdIncludes.hpp"

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

	File::File(const NOU::NOU_DAT_ALG::StringView8 &name, const NOU::NOU_DAT_ALG::StringView8 &path, AccessMode mode)
	{

		setPath(path);
		setMode(mode);
		setName(name);
		m_data = nullptr;
		
	}
	//mv
	File::File(File &&other)
	{
		setName(other.m_name);
		m_data = other.m_data;
		setPath(other.m_path);
		setMode(other.m_mode);
		other.close();
		other.setMode(AccessMode::READ_WRITE);
		other.setName("");
		other.setPath("");
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

	void File::read(sizeType size, char8 &buffer)
	{
		NOU_COND_PUSH_ERROR((m_mode == AccessMode::WRITE), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't acces write-only file");
		NOU_COND_PUSH_ERROR((m_mode == AccessMode::APPEND), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't acces append-only file");

		if (m_mode == AccessMode::WRITE || m_mode == AccessMode::APPEND)
		{
			return;
		}
		open();
		fread(&buffer, size, 1, m_data);
	}


	bool File::write(byte b)
	{
		NOU_COND_PUSH_ERROR((m_mode == AccessMode::READ), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't acces read-only file");
		if (m_mode != AccessMode::READ)
		{
			fputc(b, getData());
			return true;
		}
		return false;
	}

	bool File::write(const NOU::NOU_DAT_ALG::StringView8 &s)
	{
		NOU_COND_PUSH_ERROR((m_mode == AccessMode::READ), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Can't acces read-only file");
		if (m_mode != AccessMode::READ)
		{
			char8 *p;
			p = s.rawStr;
			fread(p, s.size(), 1, m_data);
			return true;
		}
		return false;
	}


	bool File::open()
	{
		if (!isCurrentlyOpen())
		{
			switch (m_mode)
			{
				case AccessMode::READ:
					fopen(&m_data, m_absolutePath, "r");
					break;
				case AccessMode::WRITE:
					fopen(&m_data, m_absolutePath.rawStr(), "w");
					break;
				case AccessMode::APPEND:
					fopen(&m_data, m_absolutePath.rawStr(), "a");
					break;
				case AccessMode::READ_WRITE:
					fopen(&m_data, m_absolutePath.rawStr(), "r+");
					break;
				case AccessMode::READ_WRITE_RESET:
					fopen(&m_data, m_absolutePath.rawStr(), "w+");
					break;
				case AccessMode::READ_APPEND:
					fopen(&m_data, m_absolutePath.rawStr(), "a+");
					break;
			}
		}
		return getData() != nullptr;
	}
	bool File::close()
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

	bool File::isCurrentlyOpen()
	{
		return m_data != nullptr;
	}

	void File::calcAbsolutePath()
	{
		m_absolutePath.append(m_path);
		m_absolutePath.append("/");
		m_absolutePath.append(m_name);
		close();
	}
	
	const NOU::NOU_DAT_ALG::StringView8& File::getName()
	{
		return m_name;
	}
	void File::setName(const NOU::NOU_DAT_ALG::StringView8 &name)
	{
		m_name = name;
		calcAbsolutePath();
	}

	const AccessMode& File::getMode()
	{
		return m_mode;
	}
	void File::setMode(AccessMode mode)
	{
		m_mode = mode;
	}

	const NOU::NOU_DAT_ALG::StringView8& File::getPath()
	{
		return m_path;
	}
	void File::setPath(const NOU::NOU_DAT_ALG::StringView8 &path)
	{
		m_path = path;
		calcAbsolutePath();
	}

	const NOU::NOU_DAT_ALG::StringView8& File::getAbsolutePath()
	{
		return m_absolutePath;
	}
	FILE* File::getData()
	{
		return m_data;
	}
}