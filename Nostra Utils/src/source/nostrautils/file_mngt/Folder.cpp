
#include "nostrautils/file_mngt/Folder.hpp"
#include "nostrautils/core/ErrorHandler.hpp"

#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
#include <Windows.h>
#include <stdlib.h>
#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <direct.h>
#endif

namespace NOU::NOU_FILE_MNGT
{
	Folder::Folder(const Path& path) :
		m_path(path)
	{
		DWORD lastError = GetLastError();
		if (lastError == ERROR_PATH_NOT_FOUND)
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::PATH_NOT_FOUND, "The path to the folder was not found.");
	}

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
				NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::PATH_NOT_FOUND, "The path to the folder was not found.");
			else if (lastError == ERROR_ALREADY_EXISTS)
				NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::ALREADY_EXISTS, "The folder is already exists.");
			else
				NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::UNKNOWN_ERROR, "The folder could not be created due to unknown reasons.");

			return false;
		}
		return true;


      #elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX

        mkdir(const char *path, mode_t mode);

      #endif

	}

	const Path & Folder::getPath() const
	{
		return m_path;
	}

	NOU_DAT_ALG::Vector<Folder> Folder::listFolders() const
	{
     #if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
		NOU_DAT_ALG::Vector<Folder> v ;
		NOU::NOU_DAT_ALG::String8 pattern(m_path.getAbsolutePath().rawStr());
		pattern.append("\\*");
		WIN32_FIND_DATA data;
		HANDLE hFind;
		NOU::boolean firstFolder = true;
		
		if ((hFind = FindFirstFile(pattern.rawStr(), &data)) != INVALID_HANDLE_VALUE) {
			do 
			{ 
				if (data.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
				{
					v.emplaceBack(data.cFileName);
				}
			} 
			while (FindNextFile(hFind, &data) != 0);
			FindClose(hFind);
		}
		return v;
        #elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX

		struct dirent
		{
			ino_t m_ino; 
			off_t m_off;
			unsigned short m_reclean;
			unsigned char m_types;
				char m_name[256]; 

		};

		static void list_dir(const char *path)
		{
			struct dirent *entry;
			DIR *dir = opendir(path);
			if (dir == NULL)
			{
				return;
			}

			while ((entry = readdir(dir)) != NULL) 
			{
				std::cout << (entry->m_name);
			}

			closedir(dir);
	}
		
        #endif
	}

	NOU_DAT_ALG::Vector<Folder> Folder::listFiles() const
	{
      #if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
		NOU_DAT_ALG::Vector<Folder> v;
		NOU::NOU_DAT_ALG::String8 pattern(m_path.getAbsolutePath().rawStr());
		pattern.append("\\*");
		WIN32_FIND_DATA data;
		HANDLE hFind;
		NOU::boolean firstFolder = true;
		
		if ((hFind = FindFirstFile(pattern.rawStr(), &data)) != INVALID_HANDLE_VALUE) {
			do
			{
				if (data.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
				{
					v.emplaceBack(data.cFileName);
				}

			} while (FindNextFile(hFind, &data) != 0);
			FindClose(hFind);
		}
		return v;

       #elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
	
       #endif
	}
}



	

	


