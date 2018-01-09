#ifndef NOU_CORE_LOGGING_HPP
#define NOU_CORE_LOGGING_HPP

#define _CRT_SECURE_NO_WARNINGS //Only because compiler warnings by the ctime header.

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Meta.hpp"
#include "nostrautils\dat_alg\StringView.hpp"

#include <chrono>

#undef _CRT_SECURE_NO_WARNINGS


namespace NOU::NOU_CORE
{
	class NOU_CLASS Logger
	{
	public:

		using StringType = NOU::NOU_DAT_ALG::StringView8;
	
	private:

		StringType m_date;

	public:

		template<typename T>
		void write(StringType eventLevel, StringType event, T stream);

		StringType getTime();
	};

	template<typename T> 
	void Logger::write(StringType eventLevel, StringType eventMsg, T stream)
	{
		m_date = getTime();
		*stream << m_date.rawStr() << eventLevel.rawStr() << ": " << eventMsg.rawStr()<< "\n\n";
	}
}

#endif