#include "nostrautils\file_mngt\Path.hpp"

namespace NOU::NOU_FILE_MNGT
{
	NOU_DAT_ALG::String8 Path::evaluateName(const NOU_DAT_ALG::StringView8 &path)
	{
		return NOU_DAT_ALG::String8(path);
	}

	Path::Path(const NOU_DAT_ALG::StringView8 &path) :
		m_absolutePath(makeAbsolutePath(path)),
		m_name(&evaluateName)
	{}

	const NOU_DAT_ALG::StringView8& Path::getName() const
	{
		return m_name.get(m_absolutePath);
	}
}