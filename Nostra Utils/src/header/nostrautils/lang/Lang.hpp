#ifndef	NOU_LANG_LANG_HPP
#define	NOU_LANG_LANG_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include "nostrautils\file_mngt\INIfile.hpp"


namespace NOU::NOU_LANG
{
	using NouString = NOU::NOU_FILE_MNGT::NouString;

	class NOU_CLASS Lang
	{
		private:
			/**
			\brief Key value pairs, with the values being the language tags, and the values being the inifiles.
			*/
			static std::unordered_map<NouString, NOU::NOU_FILE_MNGT::INIFile> m_data;

			/**
			\brief Currently active language tag.
			*/
			static NouString active_language;

			/**
			\brief The default language tag (en-GB).
			*/
			static const NouString default_language;

			/**
			\brief Do not allow instances of this class. Use Lang::_(); instead.
			*/
			Lang();

		public:
			/**
			\param The language tag to set.

			\brief Switches to a different language.
			*/
			static void setActive(const NouString & tag);

			/**
			\brief Returns the tag of the current language.
			*/
			static NouString getActive();

			/**
			\param The full path to the target ini file.

			\brief Loads the given ini file as the current language content.
			*/
			static boolean loadFile(const NouString & filename);

			/**
			\param The token which should be translated.

			\brief Attemps to translate the given token into the current language.
			*/
			static NouString _(const NouString & token);

			/**
			\param The token which should be translated.
			\param Item counter.
			\brief Attemps to translate the given token into the current language.
			       Depending on the number, it will append "_0", "_1" or "_N" to the token.
			*/
			static NouString _(const NouString & token, const int32 count);

			/**
			\param The token which should be translated.
			\param Boolean flag.
			\brief Attemps to translate the given token into the current language.
			Depending on the flag, it will append "_TRUE" or "_FALSE" to the token.
			*/
			static NouString _(const NouString & token, const boolean state);
	};
}
#endif