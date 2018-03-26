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
			static std::unordered_map<NouString, NOU::NOU_FILE_MNGT::INIFile> m_data;
			static NouString current_language;
			Lang();

		public:
			static void setCurrent(const NouString & tag);
			static NouString getCurrent();
			static void loadFile(const NouString & filename);
			static NouString _(const NouString & token);
	};
}
#endif