#include "nostrautils\file_mngt\FileManager.hpp"

namespace NOU::NOU_FILE_MNGT
{
	/*
	FileManager::FileManager()
	{
		m_storedFiles = 0;
		m_storedFolders = 0;
		m_openedFileCount = 0;
	}

	boolean FileManager::removeFromOpenedFiles(const File &file)
	{
		NOU::NOU_DAT_ALG::StringView<char8> path = file.getPath();

		for (sizeType i = 0; i < m_openedFileCount; i++)
		{
			if (m_openedFiles[i].getPath() == path)
			{
				m_openedFiles.remove(i);
				m_openedFileCount--;
				return true;
			}
		}

		return false;
	}

	FileManager& FileManager::getInstance()
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

	boolean FileManager::openFile(const File &file)
	{
		NOU::NOU_DAT_ALG::StringView<char8> path = file.getPath();

		for (sizeType i = 0; i < m_storedFiles; i++)
		{
			if (m_fileStorage[i].getPath() == path)
			{
				m_fileStorage[i].open();
				m_openedFiles.pushBack(m_fileStorage[i]);
				m_openedFileCount++;
				return true;
			}
		}

		return false;
	}

	boolean FileManager::closeFile(const File &file)
	{
		NOU::NOU_DAT_ALG::StringView<char8> path = file.getPath();

		for (sizeType i = 0; i < m_storedFiles; i++)
		{
			if (m_fileStorage[i].getPath() == path)
			{
				m_fileStorage[i].close();
				removeFromOpenedFiles(m_fileStorage[i]);
				return true;
			}
		}

		return false;
	}

	File FileManager::getFile(const NOU::NOU_DAT_ALG::StringView<char8>& path)
	{
		for (sizeType i = 0; i < m_storedFiles; i++)
		{
			if (m_fileStorage[i].getPath() == path)
			{
				return m_fileStorage[i];
			}
		}

		//ERROR;
	}

	boolean FileManager::removeFile(const File &file)
	{
		NOU::NOU_DAT_ALG::StringView<char8> path = file.getPath();

		for (sizeType i = 0; i < m_storedFiles; i++)
		{
			if (m_fileStorage[i].getPath() == path)
			{
				if (file.isCurrentlyOpen())
				{
					file.close();
					removeFromOpenedFiles(m_fileStorage[i]);
				}

				m_fileStorage[i].~File();
				return true;
			}
		}
	}

	const NOU::NOU_DAT_ALG::StringView<char8>& FileManager::getFileName(const File &file)  const
	{
		return file.getName();
	}

	const NOU::NOU_DAT_ALG::StringView<char8>& FileManager::getFilePath(const File &file) const
	{
		return file.getPath();
	}

	const NOU::NOU_DAT_ALG::StringView<char8>& FileManager::getAbsoluteFilePath(const File &file)  const
	{
		return file.getAbsolutePath();
	}


	*/
}