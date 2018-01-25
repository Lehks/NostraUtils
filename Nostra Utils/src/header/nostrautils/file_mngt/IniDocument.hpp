#ifndef	NOU_MEM_MNGT_INI_DOCUMENT_HPP
#define	NOU_MEM_MNGT_INI_DOCUMENT_HPP

namespace NOU::NOU_FILE_MNGT
{
	class NOU_CLASS IniDocument
	{
		public:
			boolean exists(const std::string &, const std::string & = INI_DEFAULT_SECTION) const;

	}
}
#endif;