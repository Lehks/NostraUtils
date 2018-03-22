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

	boolean FileManager::createFile(const char *name, const char *mode)
	{
		#pragma warning(suppress : 4996)
		File tmp(fopen(name, mode));

		if (!tmp.open)
		{
			return false;
		}

		fclose(tmp);

		return true;
	}

	boolean FileManager::openFile(const char *name, const char *mode)
	{
		return boolean();
	}

	boolean FileManager::deleteFile(NOU::NOU_DAT_ALG::String<char8> fullpath)
	{
		return boolean();
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