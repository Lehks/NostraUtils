#include "nostrautils\lang\Lang.hpp"
#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include "nostrautils\file_mngt\INIfile.hpp"

namespace NOU::NOU_LANG
{
	using NouString = NOU::NOU_FILE_MNGT::NouString;

	void Lang::setCurrent(const NouString & tag)
	{
		Lang::current_language.clear().append(tag);
	}


	NouString Lang::getCurrent()
	{
		return Lang::current_language;
	}


	void Lang::loadFile(const NouString & filename)
	{

	}


	NouString Lang::_(const NouString & token)
	{
		// Check if there are any languages
		if (Lang::current_language.size() == 0) {
			return NouString("*").append(token).append("*");
		}

		// Check if 
		if (m_data.find(Lang::current_language) == m_data.end()) {
			return NouString("*").append(token).append("*");
		}
	}
}