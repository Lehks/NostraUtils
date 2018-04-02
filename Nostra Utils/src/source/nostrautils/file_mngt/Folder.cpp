#include "nostrautils/file_mngt/Folder.hpp"

#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
#include <Windows.h>
#include <stdlib.h>
#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
#include <unistd.h>
#endif

namespace NOU::NOU_FILE_MNGT
{
	Folder::Folder(const NOU::NOU_DAT_ALG::StringView<char8>& m_name, const NOU::NOU_DAT_ALG::StringView<char8>& m_path) :
		m_path(m_path),
		m_name(m_name)
	{}

	void Folder::create(const char * m_path)
	{
		if (!CreateDirectory(m_path, NULL))
		{
			return;
		}
	}

	

	bool Folder::exists(const NOU::NOU_FILE_MNGT::Path &p)
	{
		if()
		return true;
		
	}

	void Folder::read_directory(const NOU::NOU_DAT_ALG::String8& name, NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> & v)
	{
		NOU::NOU_DAT_ALG::String8 pattern(name);
		pattern.append("\\*");
		WIN32_FIND_DATA data;
		HANDLE hFind;
		if ((hFind = FindFirstFile(pattern.rawStr(), &data)) != INVALID_HANDLE_VALUE) {
			do {
				v.emplaceBack(data.cFileName);
			} while (FindNextFile(hFind, &data) != 0);
			FindClose(hFind);
		}
	}


}