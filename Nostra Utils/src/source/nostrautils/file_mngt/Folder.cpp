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

	

	bool Folder::exists()
	{
		return true;
	}

}