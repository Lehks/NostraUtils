#include "nostrautils/file_mngt/Folder.hpp"
#include "nostrautils/core/ErrorHandler.hpp"

#include <thread>

#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
	#include <Windows.h>
	#include <stdlib.h>
	#include <direct.h>
#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
	#include <unistd.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <dirent.h>
	#include <errno.h>
	#include <string.h>
#endif

namespace NOU::NOU_FILE_MNGT
{
	Folder::Folder(const Path& path) :
		m_path(path)
	{}

	boolean Folder::create()
	{
		return Folder::create(m_path);
	}

	boolean Folder::create(const Path &path)
	{
#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H

		if (!CreateDirectory(path.getAbsolutePath().rawStr(), NULL))
		{
			DWORD lastError = GetLastError();

			if (lastError == ERROR_PATH_NOT_FOUND)
				NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), 
					NOU_CORE::ErrorCodes::PATH_NOT_FOUND, "The path to the folder was not found.");
			else if (lastError == ERROR_ALREADY_EXISTS)
				NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), 
					NOU_CORE::ErrorCodes::ALREADY_EXISTS, "The folder is already exists.");
			else
				NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), 
					NOU_CORE::ErrorCodes::UNKNOWN_ERROR, 
					"The folder could not be created due to unknown reasons.");

			return false;
		}

#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
		
        int err = mkdir(path.getAbsolutePath().rawStr(), 0777);
		
		if(err == -1)
		{
			switch(errno)
			{
			case EEXIST:
				NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), 
					NOU_CORE::ErrorCodes::ALREADY_EXISTS, "The folder is already exists.");
				break;
			default:
				NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), 
					NOU_CORE::ErrorCodes::UNKNOWN_ERROR, 
					"The folder could not be created due to unknown reasons.");
				break;
			}
		}
#endif
       return true;
	}

	const Path & Folder::getPath() const
	{
		return m_path;
	}

	NOU_DAT_ALG::Vector<Folder> Folder::listFolders() const
	{
#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H

		NOU_DAT_ALG::Vector<Folder> v;

		NOU::NOU_DAT_ALG::String8 pattern(m_path.getAbsolutePath().rawStr());
		pattern.append("\\*");

		WIN32_FIND_DATA data;
		HANDLE hFind;

		NOU::boolean firstFolder = true;

		hFind = FindFirstFile(pattern.rawStr(), &data);

		if (hFind != INVALID_HANDLE_VALUE) 
		{
			do
			{
				if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					Folder f1(m_path + data.cFileName);
					v.emplaceBack(f1);
				}
			} while (FindNextFile(hFind, &data) != 0);

			FindClose(hFind);
		}

#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX

		NOU_DAT_ALG::Vector<Folder> v;
		
		DIR* dirp = opendir(m_path.getAbsolutePath().rawStr());

		if(dirp == nullptr) //abort, if opendir() failed
			return v;

		struct dirent *dstruct;

		while ((dstruct = readdir(dirp)) != NULL)
		{
			if(dstruct->d_type == DT_DIR)
			{
				Folder f1(m_path + dstruct->d_name);
				v.emplaceBack(f1);
			}
		}
		closedir(dirp);
#endif
		return v;
	}

	NOU_DAT_ALG::Vector<NOU::file_mngt::File> Folder::listFiles() const
	{
#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H

		NOU_DAT_ALG::Vector<NOU::file_mngt::File> v;

		NOU::NOU_DAT_ALG::String8 pattern(m_path.getAbsolutePath().rawStr());
		pattern.append("\\*");

		WIN32_FIND_DATA data;
		HANDLE hFind;

		NOU::boolean firstFolder = true;
		
		if ((hFind = FindFirstFile(pattern.rawStr(), &data)) != INVALID_HANDLE_VALUE)
		{
			do
			{
				if (data.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
				{
					File f1(m_path + data.cFileName);
					v.emplaceBack(NOU::NOU_CORE::move(f1));
				}

			} while (FindNextFile(hFind, &data) != 0);
			FindClose(hFind);
		}

#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX

		NOU_DAT_ALG::Vector<NOU::file_mngt::File> v;

		DIR* dirp = opendir(m_path.getAbsolutePath().rawStr());

		if(dirp == nullptr) //abort, if opendir() failed
			return v;

		struct dirent *dstruct;

		while ((dstruct = readdir(dirp)) != nullptr)
		{
			if(dstruct->d_type == DT_REG)
			{
				File f1(m_path + dstruct->d_name);
				v.emplaceBack(NOU::core::move(f1));
			}
		}

		closedir(dirp);

#endif
		return v;
	}

	void Folder::remove()
	{
		remove(m_path);
	}

	void Folder::remove(const Path &path)
	{
#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
		if (_rmdir(path.getAbsolutePath().rawStr()) != 0)
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::UNKNOWN_ERROR, "The folder at the passed path could not be deleted!");
		}

#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX

		 if(rmdir(path.getAbsolutePath().rawStr()) != 0 )
		 {
			 NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::UNKNOWN_ERROR, "The folder at the passed path could not be deleted!");
		 }

#endif
	}

	boolean Folder::exists() const
	{
		return Folder::exists(m_path);
	}

	boolean Folder::exists(const Path &path)
	{
#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
		
		DWORD fileAttributes = GetFileAttributesA(path.getAbsolutePath().rawStr());

		if (fileAttributes == INVALID_FILE_ATTRIBUTES)
			return false;
		else if (fileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			return true;
		else
			return false;

#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX

		struct stat sb;

		if (stat(path.getAbsolutePath().rawStr(), &sb) == 0 && S_ISDIR(sb.st_mode))
		    return true;
		else
			return false;

#endif
	}
}



	

	


