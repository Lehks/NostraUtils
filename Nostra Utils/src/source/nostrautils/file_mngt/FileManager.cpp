#include "nostrautils\file_mngt\FileManager.hpp"
#include "nostrautils\file_mngt\File.hpp"

namespace NOU::NOU_FILE_MNGT
{

	FileManager::FileManager()
	{

	}

	FileManager FileManager::getInstance()
	{
		static FileManager instance;

		return instance;
	}

	boolean FileManager::createFile(const NOU::NOU_DAT_ALG::StringView<char8> &name, const NOU::NOU_DAT_ALG::StringView<char8> &mode)
	{
		File tmp(name, mode);
		boolean hasError = tmp().open(name, mode);

		if (!tmp.open())
		{
			return false;
		}

		tmp.close();

		return true;
	}

	boolean FileManager::openFile(const NOU::NOU_DAT_ALG::StringView<char8> &name, const NOU::NOU_DAT_ALG::StringView<char8> &mode)
	{
		File tmp(fopen(name, mode));

		if (!tmp.open)
		{
			return false;
		}

		return true;
	}

	boolean FileManager::deleteFile(const NOU::NOU_DAT_ALG::StringView<char8> &name)
	{
		int ret;

		ret = remove(filename);

		if (ret == 0) 
		{
			return true;
		}

		return false;
	}

	boolean FileManager::createFolder(NOU::NOU_DAT_ALG::String<char8> path, NOU::NOU_DAT_ALG::String<char8> name)
	{
		return boolean();
	}

	boolean FileManager::openFolder(NOU::NOU_DAT_ALG::String<char8> fullpath)
	{
		return boolean();
	}

	boolean FileManager::deleteFolder(NOU::NOU_DAT_ALG::String<char8> fullpath)
	{
		return boolean();
	}

}