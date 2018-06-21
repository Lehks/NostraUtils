#include "nostrautils/file_mngt/Path.hpp"
#include <iostream>


#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
#include <Windows.h>
#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
#include <unistd.h>
#include <pwd.h>
#endif

namespace NOU::NOU_FILE_MNGT
{
	constexpr char8 Path::PATH_SEPARATOR_WINDOWS;
	constexpr char8 Path::PATH_SEPARATOR_UNIX_LINUX;
	constexpr char8 Path::FILE_NAME_EXTENSION_SEPARATOR;
	constexpr char8 Path::PATH_SEPARATOR;

	NOU_DAT_ALG::String8 Path::makeAbsolutePath(const NOU_DAT_ALG::StringView8 &path)
	{
		NOU_DAT_ALG::String8 ret = path;

#if NOU_OS == NOU_OS_WINDOWS

		//replace all / with \ 
        ret.replace(PATH_SEPARATOR_UNIX_LINUX, PATH_SEPARATOR_WINDOWS);


        //if path starts not with *:\ , it is a relative path (* is any character, like C)
        if (ret[1] != ':')
		{
			if (!ret.startsWith(PATH_SEPARATOR))
				ret.insert(0, PATH_SEPARATOR);

			Path cwd = currentWorkingDirectory();

			ret.insert(0, cwd.getAbsolutePath());
		}

#elif NOU_OS == NOU_OS_LINUX || NOU_OS == NOU_OS_UNIX || NOU_OS == NOU_OS_MAC

		//replace all \ with /
		ret.replace(PATH_SEPARATOR_WINDOWS, PATH_SEPARATOR_UNIX_LINUX);

        if(ret.startsWith('~'))
        {
            struct passwd *pw = getpwuid(getuid());

            if (ret.at(1) != '/')
            {
                ret.insert(1,'/');
            }

            NOU::NOU_DAT_ALG::String8 str(pw->pw_dir);

            return str + ret.substring(1,ret.size() +1);
        }

		if (!ret.startsWith(PATH_SEPARATOR_UNIX_LINUX))
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
		Path cwd = currentWorkingDirectory();

		NOU::NOU_DAT_ALG::String8 str = path;

#if NOU_OS == NOU_OS_WINDOWS
		if (!cwd.getAbsolutePath().startsWith(path.at(0)))
		{
			return path;
		}
#endif

		if (path == cwd.getAbsolutePath())
			return ".";

		if (str.substring(0, cwd.getAbsolutePath().size()) == cwd.getAbsolutePath())
		{
			sizeType lastPathSeparator = cwd.getAbsolutePath().size();
			return NOU_DAT_ALG::String8(path.logicalSubstring(lastPathSeparator + 1, path.size()));
		}


		sizeType prevIndex = 0;
		sizeType nextIndex = cwd.getAbsolutePath().find(PATH_SEPARATOR, prevIndex);

		while (nextIndex != NOU_DAT_ALG::StringView8::NULL_INDEX)
		{

			if (cwd.getAbsolutePath().logicalSubstring(prevIndex + 1, nextIndex) != path.logicalSubstring(prevIndex + 1, nextIndex))
			{
				NOU_DAT_ALG::String8 str;
				sizeType separatorCounter = 0;
				sizeType firstIndexOfDifference = prevIndex;

				while (nextIndex != NOU_DAT_ALG::StringView8::NULL_INDEX)
				{
					prevIndex = nextIndex;
					nextIndex = cwd.getAbsolutePath().find(PATH_SEPARATOR, prevIndex + 1);

					separatorCounter++;
				}

				for (sizeType i = 0; i < separatorCounter; i++)
				{
					str.append("..").append(PATH_SEPARATOR);
				}

				str.append(path.logicalSubstring(firstIndexOfDifference + 1, path.size()));

				return str;
			}

			prevIndex = nextIndex;
			nextIndex = cwd.getAbsolutePath().find(PATH_SEPARATOR, prevIndex);
		}		

		return NOU_DAT_ALG::String8(path.logicalSubstring(prevIndex +1 , path.size()));
	}

	NOU_DAT_ALG::String8 Path::evaluateParentPath(const NOU_DAT_ALG::StringView8 &path)
	{
		sizeType nameExtensionSeparator = path.lastIndexOf(FILE_NAME_EXTENSION_SEPARATOR);
		sizeType lastPathSeparator = path.lastIndexOf(PATH_SEPARATOR);

		if (lastPathSeparator < 2)
		{
			return "";
		}

		if (path.endsWith(PATH_SEPARATOR))
		{
			return evaluateParentPath(path.logicalSubstring(0, lastPathSeparator - 1));
		}

		return NOU_DAT_ALG::String8(path.logicalSubstring(0, lastPathSeparator));
	}

	Path Path::currentWorkingDirectory()
	{
#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
		TCHAR path[MAX_PATH];

		GetCurrentDirectory(MAX_PATH, path);

		return Path(path);
#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
		char cwd[1024];

#if NOU_COMPILER == NOU_COMPILER_CLANG
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused" 
#endif

		*getcwd(cwd, sizeof(cwd));

#if NOU_COMPILER == NOU_COMPILER_CLANG
#pragma clang diagnostic pop
#endif

		return Path(cwd);
#endif
	}

	Path::Path(NOU::NOU_DAT_ALG::StringView8::ConstCharType *path) :
		Path(NOU_DAT_ALG::StringView8(path))
	{}

	Path::Path() :
        m_absolutePath(currentWorkingDirectory().getAbsolutePath()),
        m_extension(evaluateExtension),
        m_nameAndExtension(evaluateNameAndExtension),
        m_relativePath(evaluateRelativePath),
        m_parentPath(evaluateParentPath),
        m_name(&evaluateName)
    {}

	Path::Path(const NOU_DAT_ALG::StringView8 &path) :
		m_absolutePath(makeAbsolutePath(path)),
		m_extension(evaluateExtension),
		m_nameAndExtension(evaluateNameAndExtension),
		m_relativePath(evaluateRelativePath),
		m_parentPath(evaluateParentPath),
		m_name(&evaluateName)
	{}

	Path::Path(const Path & other) :
            m_absolutePath(other.m_absolutePath),
            m_extension(other.m_extension),
            m_nameAndExtension(other.m_nameAndExtension),
            m_relativePath(other.m_relativePath),
            m_parentPath(other.m_parentPath),
            m_name(other.m_name)
    {}

    Path::Path(Path &&other) :
            m_absolutePath(NOU_CORE::move(other.m_absolutePath)),
            m_extension(NOU_CORE::move(other.m_extension)),
            m_nameAndExtension(NOU_CORE::move(other.m_nameAndExtension)),
            m_relativePath(NOU_CORE::move(other.m_relativePath)),
            m_parentPath(NOU_CORE::move(other.m_parentPath)),
            m_name(NOU_CORE::move(other.m_name))
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

	Path & Path::operator=(const Path & other)
	{
		m_absolutePath = other.m_absolutePath;

		m_name = other.m_name;
		m_extension = other.m_extension;
		m_nameAndExtension = other.m_nameAndExtension;
		m_parentPath = other.m_parentPath;
		m_relativePath = other.m_relativePath;

		return *this;
	}

	Path & Path::operator=(Path && other)
	{
		m_absolutePath = NOU_CORE::move(other.m_absolutePath);

		m_name = NOU_CORE::move(other.m_name);
		m_extension =NOU_CORE::move( other.m_extension);
		m_nameAndExtension = NOU_CORE::move(other.m_nameAndExtension);
		m_parentPath = NOU_CORE::move(other.m_parentPath);
		m_relativePath = NOU_CORE::move(other.m_relativePath);

		return *this;
	}

	Path Path::operator+(const NOU::NOU_DAT_ALG::StringView8 & other) const
	{
		NOU::NOU_DAT_ALG::String8 strAbsolute = getAbsolutePath();
		NOU::NOU_DAT_ALG::String8 strOther = other;

#if NOU_OS == NOU_OS_WINDOWS
		if (!strAbsolute.endsWith("\\"))
		{
			strAbsolute.append("\\");
		}
#elif NOU_OS == NOU_OS_LINUX || NOU_OS == NOU_OS_UNIX || NOU_OS == NOU_OS_MAC
		if (!strAbsolute.endsWith("/"))
		{
			strAbsolute.append("/");
		}
#endif

		Path newPath(strAbsolute + strOther);

		return newPath;
	}

	Path & Path::operator+=(const Path & other)
	{
#if NOU_OS == NOU_OS_WINDOWS
		if (!m_absolutePath.endsWith("\\"))
		{
			m_absolutePath.append("\\");
		}
#elif NOU_OS == NOU_OS_LINUX || NOU_OS == NOU_OS_UNIX || NOU_OS == NOU_OS_MAC
		if (!m_absolutePath.endsWith("/"))
		{
			m_absolutePath.append("/");
		}
#endif

		m_absolutePath.append(other.m_absolutePath);

		m_name.needsReevaluation();
		m_extension.needsReevaluation();
		m_nameAndExtension.needsReevaluation();
		m_parentPath.needsReevaluation();
		m_relativePath.needsReevaluation();

		return *this;
	}

	Path & Path::operator+=(const NOU::NOU_DAT_ALG::StringView8 & other)
	{
#if NOU_OS == NOU_OS_WINDOWS
		if (!m_absolutePath.endsWith("\\"))
		{
			m_absolutePath.append("\\");
		}
#elif NOU_OS == NOU_OS_LINUX || NOU_OS == NOU_OS_UNIX || NOU_OS == NOU_OS_MAC
		if (!m_absolutePath.endsWith("/"))
		{
			m_absolutePath.append("/");
		}
#endif

		m_absolutePath.append(other);

		m_name.needsReevaluation();
		m_extension.needsReevaluation();
		m_nameAndExtension.needsReevaluation();
		m_parentPath.needsReevaluation();
		m_relativePath.needsReevaluation();

		return *this;
	}
}
