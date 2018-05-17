#include "nostrautils\lang\Lang.hpp"
#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include "nostrautils\file_mngt\INIfile.hpp"

namespace NOU::NOU_LANG
{
	const NOU::NOU_FILE_MNGT::INIFile::NouString Lang::defaultLanguage("en-GB");
	NOU::NOU_FILE_MNGT::INIFile::NouString Lang::activeLanguage = Lang::defaultLanguage;


	void Lang::setActive(const NouString & tag)
	{
		Lang::activeLanguage = tag;
	}


	Lang::NouString Lang::getActive()
	{
		return Lang::activeLanguage;
	}


	boolean Lang::loadFile(const NouString & filename)
	{
		if (Lang::activeLanguage.size() == 0) {
			Lang::setActive(Lang::defaultLanguage);
		}

		NOU::NOU_FILE_MNGT::INIFile inifile = NOU::NOU_FILE_MNGT::INIFile(filename);

		if (!inifile.read()) {
			return false;
		}

		if (Lang::m_data.containsKey(Lang::activeLanguage)) {
			Lang::m_data.remove(Lang::activeLanguage);
		}

		Lang::m_data.map(Lang::activeLanguage, inifile);
	}


	Lang::NouString Lang::_(const NouString & token)
	{
		// Check if the language is registered
		if (!Lang::m_data.containsKey(Lang::activeLanguage)) {
			// If the current language is not the default language, temporarily override it.
			if (Lang::activeLanguage != Lang::defaultLanguage) {
				Lang::NouString originalLanguage = Lang::activeLanguage;
				Lang::setActive(Lang::defaultLanguage);
				Lang::NouString translation = Lang::_(token);
				Lang::setActive(originalLanguage);

				return translation;
			}

			// Cannot find translation for this token...
			Lang::NouString translation = "*";

			translation += Lang::activeLanguage;
			translation += "::";
			translation += token;
			translation += "*";

			return translation;
		}

		// Get the language file
		NOU::NOU_FILE_MNGT::INIFile inifile = Lang::m_data.get(Lang::activeLanguage);

		// Check if token exists
		if (!inifile.keyExists(token)) {
			// If the current language is not the default language, temporarily override it.
			if (Lang::activeLanguage != Lang::defaultLanguage) {
				Lang::NouString originalLanguage = Lang::activeLanguage;
				Lang::setActive(Lang::defaultLanguage);
				Lang::NouString translation = Lang::_(token);
				Lang::setActive(originalLanguage);

				return translation;
			}

			// Cannot find translation for this token...
			Lang::NouString translation = "*";

			translation += Lang::activeLanguage;
			translation += "::";
			translation += token;
			translation += "*";

			return translation;
		}

		return inifile.getString(token);
	}


	Lang::NouString Lang::_(const NouString & token, const int32 count)
	{
		NouString countToken = token;

		switch (count)
		{
			case 0:
				countToken += "_0";
				break;

			case 1:
			case -1:
				countToken += "_1";
				break;

			default:
				countToken += "_N";
				break;
		}

		return Lang::_(countToken);
	}


	Lang::NouString Lang::_(const NouString & token, const boolean state)
	{
		NouString stateToken = token;

		switch (state)
		{
			case true:
				stateToken += "_TRUE";
				break;

			case false:
				stateToken += "_FALSE";
				break;
		}

		return Lang::_(stateToken);
	}
}