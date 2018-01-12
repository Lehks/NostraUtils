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
	\brief A enum class, which stores the different event level. 
		   The eventLevel can be:
		   Fatal:	Error, which results in the termination of the application.
		   Error:	Runtime error, which obstruct the application or unexpected errors.
		   Warning: Call of an deprecated interface, wrong call of a interface, user error or inconvenient
				    application state.
		   Info:	Runtime information like start/stop of the application, user login/logout, transactions.
		   Debug:	Information about the application execution. Usually only used during development or
					debugging errors.
		   Trace:	Detailled tracing of the application during runtime, especially for tracking errors.
	*/
	enum class EventLevelCodes
	{

		FATAL		= 0,

		ERROR		= 1,

		WARNING		= 2,

		INFO		= 3,

		DEBUG		= 4,

		TRACE		= 5
	};

	/**
	\brief The event class, which creates a new event from the event level and the event message.
	*/
	class NOU_CLASS Event
	{
	public:

		/**
		\brief Alias for the NOU::NOU_DAT_ALG::StringView8.
		*/
		using StringType = NOU::NOU_DAT_ALG::StringView8;

	private:

		/**
		\brief The attribute, which stores the event level as a enum type.
		*/
		EventLevelCodes m_eventLevel;

		/**
		\brief The attribute, which stores the event message as a StringType.
		*/
		StringType m_eventMsg;

	public:

		/**
		\param eventLevel The level of the created element.

		\param eventMsg The message of the created element.

		\brief Constructs a new event.
		*/
		Event(EventLevelCodes eventLevel, StringType eventMsg);

		/**
		\return Returns the event level.

		\brief Returns the event level of the event object.
		*/
		const StringType getEventLevel() const;

		/**
		\return Returns a reference to the event message.

		\brief Returns the event message of the event object.
		*/
		const StringType& getEventMsg() const;
	};

	///\cond
	class Logger;
	///\endcond

	/**
	\brief A abstract class, which defines the ILogger interface.
	*/
	class NOU_CLASS ILogger
	{
		/**
		\brief Defines the Logger class as a friend of the ILogger class.
		*/
		friend class Logger;

	public:

		/**
		\brief The deconstructor of the ILogger interface. It is defined as default.
		*/
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
		\param event A const referenced object of the event class.
		
		\brief A pure virtual class whose behavior will be overridden in derived classes.
		*/
		virtual void write(const Event& event) = 0;
	};

	/**
	\return Returns the enum as a string.

	\param eventLevel A enum of the event level.

	\brief Returns the enum value as a string value.
	*/
	NOU_FUNC Event::StringType enumToString(EventLevelCodes eventLevel);

	/**
	\brief A derived class of the ILogger interface. Used for writing logs to the console.
	*/
	class NOU_CLASS ConsoleLogger : public ILogger
	{
	private:

		/**
		\brief The timestamp when a logging entry was created.
		*/
		StringType m_date;

		/**
		\param event A const reference to an event object.

		\brief A overriden function of the write() in the ILogger interface. Writes the log entry to the
			   console.
		*/
		void write(const Event& event) override
		{
			m_date = getTime();
			std::cout << m_date.rawStr() << event.getEventLevel().rawStr() << ": "
				<< event.getEventMsg().rawStr() << "\n" << std::endl;
		}
	};
	/**
	\brief A class for storeing the different logger and writing logs to all of them.
	*/
	class NOU_CLASS Logger
	{
	public:

		/**
		\brief Alias for the NOU::NOU_DAT_ALG::StringView8.
		*/
		using StringType = Event::StringType;

	private:

		/**
		\brief Creates a new allocation callback for ILogger pointer.
		*/
		static NOU::NOU_MEM_MNGT::GenericAllocationCallback<ILogger*> s_allocator;

		/**
		\brief Creates a new vector from ILogger pointern.
		*/
		static NOU::NOU_DAT_ALG::Vector<ILogger*> s_logger;

		/**
		\param event A const reference to an event object.

		\brief Calls the write function for every objects in s_logger.
		*/
		static void logAll(const Event& event);

	public:
		
		/**
		\param log A reference to an ILogger object.

		\brief Pushes an logger to s_logger.
		*/
		static void pushLogger(ILogger &log);

		/**
		\param level A enum value, which represents the level of the event.

		\param msg A const reference to the message, which specifies the event.

		\brief Creates a new event object from the level and msg parametern and calls the logAll() with this
			   event object.
		*/
		static void write(EventLevelCodes level, const StringType &msg);
	};
/**
\brief This macro is a convenience macro for writing logs to the logger. This macro automatically
passes the level and message.
*/
#ifndef NOU_WRITE_LOG
#define NOU_WRITE_LOG(logger, level, msg) logger.write(level, msg)
#endif

/**
\brief This macro is a convenience macro, that behaves exactly like NOU_WRITE_LOG, but only if NOU_DEBUG is
defined. Otherwise, it will do nothing.
*/
#ifndef NOU_WRITE_DEBUG_LOG
#    ifdef  NOU_DEBUG
#        define NOU_WRITE_DEBUG_LOG(logger, level, msg) NOU_WRITE_LOG(logger, level, msg)
#    else
#        define NOU_WRITE_DEBUG_LOG(logger, level, msg)
#    endif
#endif
}
#endif