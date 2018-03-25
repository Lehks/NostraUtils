#ifndef NOU_FILE_MNGT_PATH_HPP
#define NOU_FILE_MNGT_PATH_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\dat_alg\StringView.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include "nostrautils\dat_alg\LazyEvaluationProperty.hpp"


namespace NOU::NOU_FILE_MNGT
{
	class NOU_CLASS Path
	{
	public:
		constexpr static char8 PATH_SEPARATOR_WINDOWS = '\\';
		constexpr static char8 PATH_SEPARATOR_UNIX_LINUX = '/';

		constexpr static char8 FILE_NAME_EXTENSION_SEPARATOR = '.';
#if NOU_OS == NOU_OS_WINDOWS
		constexpr static char8 PATH_SEPARATOR = PATH_SEPARATOR_WINDOWS;
#elif NOU_OS == NOU_OS_UNIX ||  NOU_OS == NOU_OS_LINUX ||  NOU_OS == NOU_OS_MAC
		constexpr static char8 PATH_SEPARATOR = PATH_SEPARATOR_UNIX_LINUX;
#endif

	private:
		static NOU_DAT_ALG::String8 makeAbsolutePath(const NOU_DAT_ALG::StringView8 &path);

		static NOU_DAT_ALG::String8 evaluateName(const NOU_DAT_ALG::StringView8 &path);
		static NOU_DAT_ALG::String8 evaluateExtension(const NOU_DAT_ALG::StringView8 &path);
		static NOU_DAT_ALG::String8 evaluateNameAndExtension(const NOU_DAT_ALG::StringView8 &path);
		static NOU_DAT_ALG::String8 evaluateRelativePath(const NOU_DAT_ALG::StringView8 &path);
		static NOU_DAT_ALG::String8 evaluateParentPath(const NOU_DAT_ALG::StringView8 &path);



		NOU_DAT_ALG::String8										m_absolutePath;


		template<typename FUNC>
		using LazyEvalProp = NOU_DAT_ALG::LazyEvaluationProperty<NOU_DAT_ALG::String8, FUNC, const NOU_DAT_ALG::StringView8&>;

		mutable LazyEvalProp<decltype(&evaluateName)>				m_name;
		mutable LazyEvalProp<decltype(&evaluateExtension)>			m_extension;
		mutable LazyEvalProp<decltype(&evaluateNameAndExtension)>	m_nameAndExtension;
		mutable LazyEvalProp<decltype(&evaluateRelativePath)>		m_relativePath;
		mutable LazyEvalProp<decltype(&evaluateParentPath)>			m_parentPath;
	public:
		static Path currentWorkingDirectory();

		Path(NOU::NOU_DAT_ALG::StringView8::ConstCharType *path);
		Path(const NOU::NOU_DAT_ALG::StringView8 & path);

		const NOU::NOU_DAT_ALG::StringView8& getName() const;
		const NOU::NOU_DAT_ALG::StringView8& getFileExtension() const;
		const NOU::NOU_DAT_ALG::StringView8& getNameAndExtension() const;
		const NOU::NOU_DAT_ALG::StringView8& getRelativePath() const;
		const NOU::NOU_DAT_ALG::StringView8& getAbsolutePath() const;
		const NOU::NOU_DAT_ALG::StringView8& getParentPath() const;

		boolean operator == (const Path &other) const;
		boolean operator != (const Path &other) const;
	};
}

#endif
