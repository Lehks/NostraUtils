#ifndef NOU_FILE_MNGT_FILEMANAGER_HPP
#define NOU_FILE_MNGT_FILEMANAGER_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\file_mngt\File.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include <stdlib.h>

namespace NOU::NOU_FILE_MNGT
{
	class NOU_CLASS FileManager
	{
	private	:

		NOU::NOU_DAT_ALG::Vector<File> m_fileStorage;
		NOU::NOU_DAT_ALG::Vector<File> m_folderStorage;
		NOU::NOU_DAT_ALG::Vector<File> m_openedFiles;

		sizeType m_storedFiles;
		sizeType m_openedFileCount;
		sizeType m_storedFolders;

		FileManager();

		boolean removeFromOpenedFiles(File file);
	public:
		static FileManager getInstance();

		boolean addFile(const NOU::NOU_DAT_ALG::StringView<char8> &name, const NOU::NOU_DAT_ALG::StringView<char8> &path);

		boolean openFile(File file);

		boolean closeFile(File file);

		File getFile(const NOU::NOU_DAT_ALG::StringView<char8> &name);

		boolean removeFile(File file);

		NOU::NOU_DAT_ALG::StringView<char8> getFileName(File file);

		NOU::NOU_DAT_ALG::StringView<char8> getFilePath(File file);

		NOU::NOU_DAT_ALG::StringView<char8> getAbsoluteFilePath(File file);
	};

}

#endif