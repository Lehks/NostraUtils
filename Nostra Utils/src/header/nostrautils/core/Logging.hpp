#ifndef NOU_CORE_LOGGING_HPP
#define NOU_CORE_LOGGING_HPP

#define _CRT_SECURE_NO_WARNINGS //Only because compiler warnings by the chrono header because a warning
								//about ctime.

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Meta.hpp"
#include "nostrautils\dat_alg\StringView.hpp"
#include "nostrautils\dat_alg\Vector.hpp"

#include <chrono>
#include <iostream>
#undef _CRT_SECURE_NO_WARNINGS


/**
\file core/Logging.hpp

\author	 Lukas Groﬂ
\version 0.0.1
\since	 1.0.0

\brief A file that contains the nostra::utils::core::Logging class.
*/

namespace NOU::NOU_CORE
{
	

	/**
	\brief Defines the Logger class.
	*/
	class NOU_CLASS ILogger
	{
	public:

		virtual ~ILogger() = default;

		/**
		\brief Alias for the NOU::NOU_DAT_ALG::StringView8.
		*/
		using StringType = NOU::NOU_DAT_ALG::StringView8;

		/**
		\brief Returns the current local time.
		*/
		StringType getTime();

		static void writeLog(StringType eventLevel, StringType eventMsg, ILogger &log);

	private:
		/**
		\param eventLevel The level on which an logged event happend.

		\param event A event or a message.
		
		\brief Writes a log to the defined destination. The eventLevel can be:
			Fatal: Error, which results in the termination of the application.
			Error: Runtime error, which obstruct the application or unexpected errors.
			Warning: Call of an deprecated interface, wrong call of a interface, user error or inconvenient 
					 application state.
			Info: Runtime information like start/stop of the application, user login/logout, transactions.
			Debug: Information about the application execution. Usually only used during development or
				   debugging errors.
			Trace: Detailled tracing of the application during runtime, especially for tracking errors.
		*/
		virtual void write(StringType eventLevel, StringType event) = 0;
	};

	class NOU_CLASS ConsoleLogger : public ILogger
	{
	private:

		/**
		\brief The timestamp at which a logging entry was created.
		*/
		StringType m_date;

	public:

		void write(StringType eventLevel, StringType eventMsg) override
		{
			m_date = getTime();

			std::cout << m_date.rawStr() << eventLevel.rawStr() << ": " 
				<< eventMsg.rawStr() << "\n" << std::endl;
		}

	};

	class NOU_CLASS Logger
	{

	public:

		/**
		\brief Alias for the NOU::NOU_DAT_ALG::StringView8.
		*/
		using StringType = NOU::NOU_DAT_ALG::StringView8;

	private:
		static NOU::NOU_MEM_MNGT::GenericAllocationCallback<ILogger*> s_allocator;

		static NOU::NOU_DAT_ALG::Vector<ILogger*> s_logger;

	public:
		
		static void pushLogger(ILogger &log);

		static void logAll(StringType eventLevel, StringType eventMsg);

	};

	class NOU_CLASS EventLevelCodes
	{
	public:
		enum EventLevel : typename sizeType
		{
			FATAL = 0,

			ERROR = 1,

			WARNING = 2,

			INFO = 3,

			DEBUG = 4,

			TRACE = 5

		};

		static Logger::StringType getLevel(sizeType lvl);
	};
}

#endif