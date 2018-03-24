#include "nostrautils\file_mngt\FileManager.hpp"

namespace NOU::NOU_FILE_MNGT
{

	FileManager::FileManager()
	{
		m_storedFiles = 0;
		m_storedFolders = 0;
	}

	FileManager FileManager::getInstance()
	{
		static FileManager instance;

		return instance;
	}

	boolean FileManager::addFile(const NOU::NOU_DAT_ALG::StringView<char8>& name, const NOU::NOU_DAT_ALG::StringView<char8>& path)
	{


		return boolean();
	}

	boolean FileManager::openFile(File file)
	{
		return ;
	}

	boolean FileManager::closeFile(File file)
	{
		return boolean();
	}

	void FileManager::writeFile(byte b)
	{
	}

	byte FileManager::readFile(File file)
	{
		return byte();
	}

	boolean FileManager::removeFile(File file)
	{
		return boolean();
	}

	NOU::NOU_DAT_ALG::StringView<char8> FileManager::getFileName(File file)
	{
		return NOU::NOU_DAT_ALG::StringView<char8>();
	}

	NOU::NOU_DAT_ALG::StringView<char8> FileManager::getFilePath(File file)
	{
		return NOU::NOU_DAT_ALG::StringView<char8>();
	}

	NOU::NOU_DAT_ALG::StringView<char8> FileManager::getAbsoluteFilePath(File file)
	{
		return NOU::NOU_DAT_ALG::StringView<char8>();
	}



}