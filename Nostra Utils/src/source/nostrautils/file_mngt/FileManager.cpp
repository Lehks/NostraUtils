#include "nostrautils\file_mngt\FileManager.hpp"

namespace NOU::NOU_FILE_MNGT
{

	FileManager FileManager::getInstance()
	{
		static FileManager instance;

		return instance;
	}

	boolean FileManager::createFile(NOU::NOU_DAT_ALG::String<char8> path, NOU::NOU_DAT_ALG::String<char8> name)
	{
		fopen();
		return boolean();
	}

	boolean FileManager::openFile(NOU::NOU_DAT_ALG::String<char8> fullpath)
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
