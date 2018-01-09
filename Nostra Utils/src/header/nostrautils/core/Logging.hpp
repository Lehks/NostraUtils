#ifndef NOU_CORE_LOGGING_HPP
#define NOU_CORE_LOGGING_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Meta.hpp"
#include "nostrautils\dat_alg\StringView.hpp"

#include <iostream>
#include <ostream>
#include <chrono>

namespace NOU::NOU_CORE
{
	
	class NOU_CLASS Logger
	{
	public:

		using StringType = NOU::NOU_DAT_ALG::StringView8;

		using dateType = std::chrono::high_resolution_clock::time_point;
	
	private:

		dateType m_date;

		StringType m_logLevel;

		StringType m_event;

	public:

		template<typename T>
		void write(StringType& msg, T iostream);
	};

	template<typename T>
	void Logger::write(StringType& msg, T iostream)
	{
		m_date = std::chrono::high_resolution_clock::now();
		iostream << msg << "\n";
	}
}

#endif