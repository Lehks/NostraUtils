#ifndef	NOU_MEM_MNGT_INI_PARSER_HPP
#define	NOU_MEM_MNGT_INI_PARSER_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include <unordered_map>
#include <string>

namespace NOU::NOU_FILE_MNGT
{
	class NOU_CLASS IniParser
	{
		private:
			std::unordered_map<std::string, std::string> m_data;
			std::string m_filename;

		public:
			IniParser(std::string &filename);
			~IniParser();
			boolean parse();
			std::string getValue(std::string &key) const;
	};
}
#endif
