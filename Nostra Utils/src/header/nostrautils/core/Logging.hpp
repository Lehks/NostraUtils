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
	enum class EventLevelCodes
	{

		FATAL = 0,

		ERROR = 1,

		WARNING = 2,

		INFO = 3,

		DEBUG = 4,

		TRACE = 5
	};

	class NOU_CLASS Event
	{
	public:
		using StringType = NOU::NOU_DAT_ALG::StringView8;
	private:
		EventLevelCodes m_eventLevel;

		StringType m_eventMsg;
	public:
		Event(EventLevelCodes eventLevel, StringType eventMsg);

		const StringType getEventLevel() const;
		const StringType& getEventMsg() const;
	};

	class Logger;

	/**
	\brief Defines the Logger class.
	*/
	class NOU_CLASS ILogger
	{
		friend class Logger;

	public:

		virtual ~ILogger() = default;

		/**
		\brief Alias for the NOU::NOU_DAT_ALG::StringView8.
		*/
		using StringType = Event::StringType;

		/**
		\brief Returns the current local time.
		*/
		StringType getTime();

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
		virtual void write(const Event& event) = 0;
	};

	NOU_FUNC Event::StringType enumToString(EventLevelCodes eventLevel);

	class NOU_CLASS ConsoleLogger : public ILogger
	{
	private:

		/**
		\brief The timestamp at which a logging entry was created.
		*/
		StringType m_date;

		void write(const Event& event) override
		{
			m_date = getTime();
			std::cout << m_date.rawStr() << event.getEventLevel().rawStr() << ": "
				<< event.getEventMsg().rawStr() << "\n" << std::endl;
		}
	};

	class NOU_CLASS Logger
	{
	public:

		/**
		\brief Alias for the NOU::NOU_DAT_ALG::StringView8.
		*/
		using StringType = Event::StringType;

	private:
		static NOU::NOU_MEM_MNGT::GenericAllocationCallback<ILogger*> s_allocator;

		static NOU::NOU_DAT_ALG::Vector<ILogger*> s_logger;

		static void logAll(const Event& event);
	public:
		
		static void pushLogger(ILogger &log);


		static void write(EventLevelCodes level, const StringType &msg);
	};
}
#endif