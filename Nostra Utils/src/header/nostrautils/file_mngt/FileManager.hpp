#ifndef NOU_FILE_MNGT_FILEMANAGER_HPP
#define NOU_FILE_MNGT_FILEMANAGER_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include <stdlib.h>

namespace NOU::NOU_FILE_MNGT
{

	class NOU_CLASS FileManager
	{
	private	:
		FileManager();
	public:
		static FileManager getInstance();

		boolean createFile(const NOU::NOU_DAT_ALG::StringView<char8> &name, const NOU::NOU_DAT_ALG::StringView<char8> &mode);

		boolean openFile(const NOU::NOU_DAT_ALG::StringView<char8> &name, const NOU::NOU_DAT_ALG::StringView<char8> &mode);

		boolean deleteFile(const NOU::NOU_DAT_ALG::StringView<char8> &name);

		boolean createFolder(NOU::NOU_DAT_ALG::String<char8> path, NOU::NOU_DAT_ALG::String<char8> name);

		boolean openFolder(NOU::NOU_DAT_ALG::String<char8> fullpath);

		boolean deleteFolder(NOU::NOU_DAT_ALG::String<char8> fullpath);


	};

}

#endif