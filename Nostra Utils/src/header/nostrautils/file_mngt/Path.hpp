#ifndef NOU_FILE_MNGT_PATH_HPP
#define NOU_FILE_MNGT_PATH_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/dat_alg/StringView.hpp"
#include "nostrautils/dat_alg/String.hpp"
#include "nostrautils/dat_alg/LazyEvaluationProperty.hpp"

/** \file Vector.hpp
\author  Dennis Franz
\since   0.0.1
\version 0.0.1
\brief   This file provides a Path implementation.
*/

namespace NOU::NOU_FILE_MNGT
{
	/**
	\brief A path class for different path operations on different operating systems.
	*/
	class NOU_CLASS Path
	{
	public:
		/**
		\brief Special Path Separator for Windows.
		*/
		constexpr static char8 PATH_SEPARATOR_WINDOWS = '\\';
		/**
		\brief Special Path Separator for UNIX systems.
		*/
		constexpr static char8 PATH_SEPARATOR_UNIX_LINUX = '/';
		/**
		\brief File name extension separator (all systems) is  simply a dot.
		*/
		constexpr static char8 FILE_NAME_EXTENSION_SEPARATOR = '.';

		/**
		\brief This OS specific call checks on which system this library is running and
		sets the specific path separator to an unified PATH_SEPARATOR char variable.

		/see PATH_SEPARATOR_WINDOWS
		/see PATH_SEPARATOR_UNIX_LINUX
		*/
#if NOU_OS == NOU_OS_WINDOWS
		constexpr static char8 PATH_SEPARATOR = PATH_SEPARATOR_WINDOWS;
#elif NOU_OS == NOU_OS_UNIX ||  NOU_OS == NOU_OS_LINUX ||  NOU_OS == NOU_OS_MAC
		constexpr static char8 PATH_SEPARATOR = PATH_SEPARATOR_UNIX_LINUX;
#endif

	private:
		/**
		\param const path		a constant path.

		\return String8			the absolutePath of the file.

		\brief This method generates (if it is eg. an relative path) the absolute path.

		/see nostra:dat_alg::LazyEvaluationProperty.hpp
		*/
		static NOU_DAT_ALG::String8 makeAbsolutePath(const NOU_DAT_ALG::StringView8 &path);
		/**
		\param const path		a constant path.

		\return String8			the name of the file.

		\brief This method "calculates" the value of the name of the Path's when it is needed and saves it for later usage.
		If there is no name at the end of the path it returns an empty string.

		/see nostra:dat_alg::LazyEvaluationProperty.hpp
		*/
		static NOU_DAT_ALG::String8 evaluateName(const NOU_DAT_ALG::StringView8 &path);
		/**
		\param const path		a constant path.

		\return String8			the file extension of the file.

		\brief This method "calculates" the value of the file extension when it is needed and saves it for later usage.
		if there is no file at the end of the path it return an empty string.

		/see nostra:dat_alg::LazyEvaluationProperty.hpp
		*/
		static NOU_DAT_ALG::String8 evaluateExtension(const NOU_DAT_ALG::StringView8 &path);
		/**
		\param const path		a constant path.

		\return String8			the name and the extension of the file.

		\brief This method "calculates" the value of the file extension when it is needed and saves it for later usage.
		if there is no file at the end of the path it return an empty string.

		/see nostra:dat_alg::LazyEvaluationProperty.hpp
		*/
		static NOU_DAT_ALG::String8 evaluateNameAndExtension(const NOU_DAT_ALG::StringView8 &path);
		/**
		\param const path		a constant path.

		\return String8			the relative path of the file.

		\brief This method "calculates" the value of the file extension when it is needed and saves it for later usage.
		the relative path is a path from the current working directory to the paths location.
		
		\details
		If there is no path given only the drive given in the path name and the library is running on windows then there will be
		the absolute path will be returned. This happens also if your directory is on another drive then the value of the path.
		If you are running of UNIX systems only the first mentioned point will count.

		/see nostra:dat_alg::LazyEvaluationProperty.hpp
		*/
		static NOU_DAT_ALG::String8 evaluateRelativePath(const NOU_DAT_ALG::StringView8 &path);
		/**
		\param const path		a constant path.

		\return String8			the parent path of the file.

		\brief This method "calculates" the value of the parent path when it is needed and saves it for later usage.
		
		\details
		If there is only the drive given in the path name an empty string will be returned.As with the evaluateRelativePath() method 
		this counts only for windows usage. If you are on UNIX systems the root directory will be returned.

		/see nostra:dat_alg::LazyEvaluationProperty.hpp
		*/
		static NOU_DAT_ALG::String8 evaluateParentPath(const NOU_DAT_ALG::StringView8 &path);

		/**
		\brief Stores the absolute value of the path.
		*/
		NOU_DAT_ALG::String8										m_absolutePath;


		template<typename FUNC>
		using LazyEvalProp = NOU_DAT_ALG::LazyEvaluationProperty<NOU_DAT_ALG::String8, FUNC, const NOU_DAT_ALG::StringView8&>;
		/**
		\brief Stores the name of the path's file. This variable can be modified because of the key word mutable.
		*/
		mutable LazyEvalProp<decltype(&evaluateName)>				m_name;
		/**
		\brief Stores the extension of the path's file. This variable can be modified because of the key word mutable.
		*/
		mutable LazyEvalProp<decltype(&evaluateExtension)>			m_extension;
		/**
		\brief Stores the name and extension of the path's file. This variable can be modified because of the key word mutable.
		*/
		mutable LazyEvalProp<decltype(&evaluateNameAndExtension)>	m_nameAndExtension;
		/**
		\brief Stores the relative path to the path. This variable can be modified because of the key word mutable.

		\see evaluateRelativePath().
		*/
		mutable LazyEvalProp<decltype(&evaluateRelativePath)>		m_relativePath;
		/**
		\brief Stores the parent path of the path's file or last folder. This variable can be modified because of the key word mutable.
		*/
		mutable LazyEvalProp<decltype(&evaluateParentPath)>			m_parentPath;
	public:
		/**
		\return path		current working directory.

		\brief Returns a path object with the current working directory.
		*/
		static Path currentWorkingDirectory();
		/**
		\brief Constructor with a char pointer as parameter (calls Path(const NOU::NOU_DAT_ALG::StringView8 & path)) constructor.
		*/
		Path(NOU::NOU_DAT_ALG::StringView8::ConstCharType *path);
		/**
		\brief Constructor with a const StringView8 reference as parameter.
		this constructor will initialize all  LazyEvalProp variables and calls the makeAbsolutePath method as well.

		\see makeAbsolutePath().
		*/
		Path(const NOU::NOU_DAT_ALG::StringView8 & path);
		/**
		\brief This file calls evaluateName().

		\see evaluateName()
		*/
		const NOU::NOU_DAT_ALG::StringView8& getName() const;
		/**
		\brief This file calls evaluateExtension().

		\see evaluateExtension()
		*/
		const NOU::NOU_DAT_ALG::StringView8& getFileExtension() const;
		/**
		\brief This file calls evaluateNameAndExtension().

		\see evaluateNameAndExtension()
		*/
		const NOU::NOU_DAT_ALG::StringView8& getNameAndExtension() const;
		/**
		\brief This file calls evaluateRelativePath().

		\see evaluateRelativePath()
		*/
		const NOU::NOU_DAT_ALG::StringView8& getRelativePath() const;
		/**
		\brief This file returns the absolutePath variable.
		*/
		const NOU::NOU_DAT_ALG::StringView8& getAbsolutePath() const;
		/**
		\brief This file calls evaluateParentPath().

		\see evaluateParentPath()
		*/
		const NOU::NOU_DAT_ALG::StringView8& getParentPath() const;

		/**
		\brief Simple override of the equals operator between path's.
		*/
		boolean operator == (const Path &other) const;
		/**
		\brief Simple override of the not equals operator between path's.
		*/
		boolean operator != (const Path &other) const;
	};
}

#endif
