#include "nostrautils\file_mngt\Path.hpp"
#include <iostream>


#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
#include <Windows.h>
#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
#include <unistd.h>
#endif

namespace NOU::NOU_FILE_MNGT
{
	NOU_DAT_ALG::String8 Path::makeAbsolutePath(const NOU_DAT_ALG::StringView8 &path)
	{
		NOU_DAT_ALG::String8 ret = path;

#if NOU_OS == NOU_OS_WINDOWS

		//replace all / with \ 
		ret.replace(PATH_SEPARATOR_UNIX_LINUX, PATH_SEPARATOR_WINDOWS);

		//if path starts not with *:\, it is a relative path (* is any character, like C)
		if (!(path.at(1) == ':' && path.at(2) == PATH_SEPARATOR_WINDOWS)) 
		{
			Path cwd = currentWorkingDirectory();

			ret.insert(0, cwd.getAbsolutePath());

			if(!path.startsWith(PATH_SEPARATOR))
				ret.insert(cwd.getAbsolutePath().size(), PATH_SEPARATOR);
		}

#elif NOU_OS == NOU_OS_LINUX || NOU_OS == NOU_OS_UNIX || NOU_OS == NOU_OS_MAC

		//replace all \ with /
		ret.replace(PATH_SEPARATOR_WINDOWS, PATH_SEPARATOR_UNIX_LINUX);

		if (!path.startsWith(PATH_SEPARATOR_UNIX_LINUX)) //if path starts not with /, it is a relative path
		{
			Path cwd = currentWorkingDirectory();

			ret.insert(0, cwd.getAbsolutePath());
			ret.insert(cwd.getAbsolutePath().size(), PATH_SEPARATOR);
		}
#endif

		return ret;
	}

	NOU_DAT_ALG::String8 Path::evaluateName(const NOU_DAT_ALG::StringView8 &path)
	{
		sizeType nameExtensionSeparator = path.lastIndexOf(FILE_NAME_EXTENSION_SEPARATOR);
		sizeType lastPathSeparator = path.lastIndexOf(PATH_SEPARATOR) + 1;

		//if there is no extension
		if (nameExtensionSeparator == NOU_DAT_ALG::StringView8::NULL_INDEX)
			nameExtensionSeparator = path.size();

		//if not in a folder
		if (lastPathSeparator == NOU_DAT_ALG::StringView8::NULL_INDEX)
			lastPathSeparator = 0;

		//if the separator is in the name of a folder on the path to the file
		if (lastPathSeparator > nameExtensionSeparator)
		{
			nameExtensionSeparator = path.size();
		}

		return NOU_DAT_ALG::String8(path.logicalSubstring(lastPathSeparator, nameExtensionSeparator));
	}

	NOU_DAT_ALG::String8 Path::evaluateExtension(const NOU_DAT_ALG::StringView8 &path)
	{
		sizeType nameExtensionSeparator = path.lastIndexOf(FILE_NAME_EXTENSION_SEPARATOR);
		sizeType lastPathSeparator = path.lastIndexOf(PATH_SEPARATOR);

		//if there is no file extension
		if (nameExtensionSeparator == NOU_DAT_ALG::StringView8::NULL_INDEX)
		{
			return ""; 
		}

		if (lastPathSeparator > nameExtensionSeparator && lastPathSeparator != NOU_DAT_ALG::StringView8::NULL_INDEX)
		{
			return "";
		}

		return NOU_DAT_ALG::String8(path.logicalSubstring(nameExtensionSeparator + 1, path.size()));
	}

	NOU_DAT_ALG::String8 Path::evaluateNameAndExtension(const NOU_DAT_ALG::StringView8 &path)
	{
		sizeType lastPathSeparator = path.lastIndexOf(PATH_SEPARATOR);

		if (lastPathSeparator == NOU_DAT_ALG::StringView8::NULL_INDEX)
			return path;

		return NOU_DAT_ALG::String8(path.logicalSubstring(lastPathSeparator + 1, path.size()));
	}

	NOU_DAT_ALG::String8 Path::evaluateRelativePath(const NOU_DAT_ALG::StringView8 &path)
	{		
		// "\\testfile.exe";
		// "testdir\\testfile.test";
		// "\\test.dir\\testfile.test";
		// "test.dir\\testfile";
		// "testfile.test\\";
		// "testfile";
		// "test.tar.gz";
		return NOU_DAT_ALG::String8();
	}

	NOU_DAT_ALG::String8 Path::evaluateParentPath(const NOU_DAT_ALG::StringView8 &path)
	{
		return path;
	}

	Path Path::currentWorkingDirectory()
	{
#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
		TCHAR path[MAX_PATH];

		GetCurrentDirectory(MAX_PATH, path);

		return Path(path);
#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
		char cwd[1024];

		char *getcwd(char *cwd, sizeof(cwd));

		return Path(cwd);
#endif
	}

	Path::Path(NOU::NOU_DAT_ALG::StringView8::ConstCharType *path) :
		Path(NOU_DAT_ALG::StringView8(path))
	{}

	Path::Path(const NOU_DAT_ALG::StringView8 &path) :
		m_absolutePath(makeAbsolutePath(path)),
		m_extension(evaluateExtension),
		m_nameAndExtension(evaluateNameAndExtension),
		m_relativePath(evaluateRelativePath),
		m_parentPath(evaluateParentPath),
		m_name(&evaluateName)
	{}

	const NOU_DAT_ALG::StringView8& Path::getName() const
	{
		return m_name.get(m_absolutePath);
	}

	const NOU::NOU_DAT_ALG::StringView8 & Path::getFileExtension() const
	{
		return m_extension.get(m_absolutePath);
	}

	const NOU::NOU_DAT_ALG::StringView8 & Path::getNameAndExtension() const
	{
		return m_nameAndExtension.get(m_absolutePath);
	}

	const NOU::NOU_DAT_ALG::StringView8 & Path::getRelativePath() const
	{
		return m_relativePath.get(m_absolutePath);
	}

	const NOU::NOU_DAT_ALG::StringView8 & Path::getAbsolutePath() const
	{
		return m_absolutePath;
	}

	const NOU::NOU_DAT_ALG::StringView8 & Path::getParentPath() const
	{
		return m_parentPath.get(m_absolutePath);
	}

	boolean Path::operator == (const Path &other) const
	{
		return m_absolutePath == other.m_absolutePath;
	}

	boolean Path::operator != (const Path &other) const
	{
		return !(*this == other);
	}
}