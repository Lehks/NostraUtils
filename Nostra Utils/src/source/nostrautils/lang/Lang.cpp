#include "nostrautils\lang\Lang.hpp"
#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include "nostrautils\file_mngt\INIfile.hpp"

namespace NOU::NOU_LANG
{
	using NouString = NOU::NOU_FILE_MNGT::NouString;

	const NouString Lang::default_language("en-GB");
	NouString Lang::active_language = Lang::default_language;

	void Lang::setActive(const NouString & tag)
	{
		Lang::active_language.clear().append(tag);
	}


	NouString Lang::getActive()
	{
		return Lang::active_language;
	}


	boolean Lang::loadFile(const NouString & filename)
	{
		if (Lang::active_language.size() == 0) {
			Lang::setActive(Lang::default_language);
		}

		NOU::NOU_FILE_MNGT::INIFile inifile = NOU::NOU_FILE_MNGT::INIFile(filename);

		if (!inifile.read()) {
			return false;
		}

		if (Lang::m_data.count(Lang::active_language) > 0) {
			Lang::m_data.erase(Lang::active_language);
		}

		Lang::m_data.insert(std::make_pair(Lang::active_language, inifile));
	}


	NouString Lang::_(const NouString & token)
	{
		std::unordered_map<NouString, NOU::NOU_FILE_MNGT::INIFile>::const_iterator inifile;

		// Check if there are any languages
		if (Lang::active_language.size() == 0) {
			Lang::setActive(Lang::default_language);
		}

		// Check if the current language is actually registered
		inifile = m_data.find(Lang::active_language);

		if (inifile == m_data.end()) {
			return NouString("*").append(Lang::active_language).append("::").append(token).append("*");
		}

		// Return translated string if exists
		if (inifile->second.keyExists(token)) {
			return inifile->second.getString(token);
		}

		// As fallback, return default language translation
		NouString tmp_language = Lang::active_language;
		NouString translation;

		Lang::setActive(Lang::default_language);
		translation.append(Lang::_(token));
		Lang::setActive(tmp_language);

		return translation;
	}


	NouString Lang::_(const NouString & token, const int32 count)
	{
		NouString count_token;

		count_token.append(token);

		switch (count)
		{
			case 0:
				count_token.append("_0");
				break;

			case 1:
			case -1:
				count_token.append("_1");
				break;

			default:
				count_token.append("_N");
				break;
		}

		return Lang::_(count_token);
	}


	NouString Lang::_(const NouString & token, const boolean state)
	{
		NouString state_token;

		state_token.append(token);

		switch (state)
		{
			case true:
				state_token.append("_TRUE");
				break;

			case false:
				state_token.append("_FALSE");
				break;
		}

		return Lang::_(state_token);
	}
}