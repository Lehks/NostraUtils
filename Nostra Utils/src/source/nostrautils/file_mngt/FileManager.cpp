#include "nostrautils\file_mngt\FileManager.hpp"

namespace NOU::NOU_FILE_MNGT
{

	FileManager::FileManager()
	{
		m_storedFiles = 0;
		m_storedFolders = 0;
		m_openedFileCount = 0;
	}

	boolean FileManager::removeFromOpenedFiles(File file)
	{
		NOU::NOU_DAT_ALG::StringView<char8> name = file.getName();

		for (sizeType i = 0; i < m_openedFileCount; i++)
		{
			if (m_openedFiles[i].getName() == name)
			{
				m_openedFiles.remove(i);
				m_openedFileCount--;
				return true;
			}
		}

		return false;
	}

	FileManager FileManager::getInstance()
	{
		static FileManager instance;

		return instance;
	}

	boolean FileManager::addFile(const NOU::NOU_DAT_ALG::StringView<char8>& name, const NOU::NOU_DAT_ALG::StringView<char8>& path)
	{
		m_fileStorage.emplaceBack(name, path);
		m_storedFiles++;
		return true;
	}

	boolean FileManager::openFile(File file)
	{
		NOU::NOU_DAT_ALG::StringView<char8> name = file.getName();

		for (sizeType i = 0; i < m_storedFiles; i++)
		{
			if (m_fileStorage[i].getName() == name)
			{
				m_fileStorage[i].open();
				m_openedFiles.pushBack(m_fileStorage[i]);
				m_openedFileCount++;
				return true;
			}
		}

		return false;
	}

	boolean FileManager::closeFile(File file)
	{
		NOU::NOU_DAT_ALG::StringView<char8> name = file.getName();

		for (sizeType i = 0; i < m_storedFiles; i++)
		{
			if (m_fileStorage[i].getName() == name)
			{
				m_fileStorage[i].close();
				removeFromOpenedFiles(m_fileStorage[i]);
				return true;
			}
		}

		return false;
	}

	File FileManager::getFile(const NOU::NOU_DAT_ALG::StringView<char8>& name)
	{
		for (sizeType i = 0; i < m_storedFiles; i++)
		{
			if (m_fileStorage[i].getName() == name)
			{
				return m_fileStorage[i];
			}
		}

		//ERROR;
	}

	boolean FileManager::removeFile(File file)
	{
		NOU::NOU_DAT_ALG::StringView<char8> name = file.getName();

		for (sizeType i = 0; i < m_storedFiles; i++)
		{
			if (m_fileStorage[i].getName() == name)
			{
				if (file.isCurrentlyOpen())
				{
					file.close();
					removeFromOpenedFiles(m_fileStorage[i]);
				}

				m_fileStorage[i].~File;
				return true;
			}
		}
	}

	NOU::NOU_DAT_ALG::StringView<char8> FileManager::getFileName(File file)
	{
		return file.getName();
	}

	NOU::NOU_DAT_ALG::StringView<char8> FileManager::getFilePath(File file)
	{
		return file.getPath();
	}

	NOU::NOU_DAT_ALG::StringView<char8> FileManager::getAbsoluteFilePath(File file)
	{
		return file.getAbsolutePath();
	}



}