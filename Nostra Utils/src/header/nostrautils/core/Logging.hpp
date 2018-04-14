#ifndef NOU_CORE_LOGGING_HPP
#define NOU_CORE_LOGGING_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/core/Meta.hpp"
#include "nostrautils/dat_alg/StringView.hpp"
#include "nostrautils/dat_alg/Vector.hpp"
#include "nostrautils/thread/Threads.hpp"
#include "nostrautils/file_mngt/File.hpp"
#include "nostrautils/file_mngt/Path.hpp"

#include <chrono>
#include <iostream>

/**
\file core/Logging.hpp

\author	 Lukas Gross
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
		   Trace:	Detailed tracing of the application during runtime, especially for tracking errors.
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

		/**
		\brief A constant string that stores one of the event level codes.
		*/
		const static StringType FATAL;

		/**
		\brief A constant string that stores one of the event level codes.
		*/
		const static StringType ERROR;

		/**
		\brief A constant string that stores one of the event level codes.
		*/
		const static StringType WARNING;

		/**
		\brief A constant string that stores one of the event level codes.
		*/
		const static StringType INFO;

		/**
		\brief A constant string that stores one of the event level codes.
		*/
		const static StringType DEBUG;

		/**
		\brief A constant string that stores one of the event level codes.
		*/
		const static StringType TRACE;

		/**
		\brief A constant string that stores one of the event level codes.
		*/
		const static StringType UNKNOWN;

		/**
		\brief A class that provides custom time functionality. It is used for displaying date and time.
		*/
		class NOU_CLASS TimeStamp
		{
			friend class Event;

		public:

			/**
			\brief Defines the type as a uint32.

			\details uint32 is defines as a uint32_t.
			*/
			using TimeType = uint32;

		private:
			/**
			\brief Attribute that stores the second.
			*/
			TimeType m_seconds;

			/**
			\brief Attribute that stores the minute.
			*/
			TimeType m_minutes;

			/**
			\brief Attribute that stores the hour.
			*/
			TimeType m_hours;

			/**
			\brief Attribute that stores the day.
			*/
			TimeType m_day;

			/**
			\brief Attribute that stores the month.
			*/
			TimeType m_month;

			/**
			\brief Attribute that stores the year.
			*/
			TimeType m_year;

		public:

			/**
			\return The second.

			\brief Returns the second.
			*/
			TimeType getSeconds() const;

			/**
			\return The minute.

			\brief Returns the minute.
			*/
			TimeType getMinutes() const;

			/**
			\return The hour.

			\brief Returns the hour.
			*/
			TimeType getHours() const;

			/**
			\return The day.

			\brief Returns the day.
			*/
			TimeType getDay() const;

			/**
			\return The month.

			\brief Returns the month.
			*/
			TimeType getMonth() const;

			/**
			\return The years.

			\brief Returns the year.
			*/
			TimeType getYear() const;
		};

	private:

		/**
		\brief The attribute, which stores the event level as a enum type.
		*/
		EventLevelCodes m_eventLevel;

		/**
		\brief The attribute, which stores the event message as a StringType.
		*/
		StringType m_eventMsg;

		/**
		\brief The attribute, which stores the time the event happened / The event object was created.
		*/
		TimeStamp m_timeStamp;

		/**
		\brief Returns the current time.
		*/
		static TimeStamp getTime();

	public:

		/**
		\param eventLevel	The level of the created element.

		\param eventMsg		The message of the created element.

		\brief				Constructs a new event.
		*/
		Event(EventLevelCodes eventLevel, const StringType& eventMsg);

		/**
		\return The event level.

		\brief	Returns the event level of the event object.
		*/
		const StringType getEventLevel() const;

		/**
		\return A reference to the event message.

		\brief	Returns the event message of the event object.
		*/
		const StringType& getEventMsg() const;

		/**
		\return	A reference to the time stamp.

		\brief	Returns the time stamp when the event happened.
		*/
		const TimeStamp& getTimeStamp() const;
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
		\brief The destructor of the ILogger interface. It is defined as default.
		*/
		virtual ~ILogger() = default;

		/**
		\brief Alias for the NOU::NOU_DAT_ALG::StringView8.
		*/
		using StringType = Event::StringType;

	private:
		/**
		\param event	A const referenced object of the event class.
		\param filename	The name of the file where the log will be written to.
		
		\brief			A pure virtual class whose behavior will be overridden in derived classes.
		*/
		virtual void write(const Event& event, StringType filename) = 0;
	};

	/**
	\param eventLevel	A enum of the event level.
	
	\return				Returns the enum as a string.

	\brief				Returns the enum value as a string value.
	*/
	NOU_FUNC Event::StringType enumToString(EventLevelCodes eventLevel);

	/**
	\brief A derived class of the ILogger interface. Used for writing logs to the console.
	*/
	class NOU_CLASS ConsoleLogger : public ILogger
	{
	private:

		/**
		\param event	A const reference to an event object.
		\param filename	The name of the file where the log will be written to.

		\brief			A overridden function of the write() in the ILogger interface. Writes the log entry 
						to the console.
		*/
		void write(const Event& event, StringType filename) override
		{
			std::cout 
				<< "[" << event.getTimeStamp().getYear() << "/" << event.getTimeStamp().getMonth() << "/" 
				<< event.getTimeStamp().getDay() << " " << event.getTimeStamp().getHours() << ":" 
				<< event.getTimeStamp().getMinutes() << ":" << event.getTimeStamp().getSeconds() << "] " 
			
				<< event.getEventLevel().rawStr() << ": "
				<< event.getEventMsg().rawStr() << "\n" 
				<< 
			std::endl;
		}
	};

	/**
	\brief A derived class of the ILogger interface. Used for writing logs to a file.
	*/
	class NOU_CLASS FileLogger : public ILogger
	{
	private:

		/**
		\param event	A const reference to an event object.
		\param filename	The name of the file where the log will be written to.

		\brief			A overridden function of the write() in the ILogger interface. Writes the log entry
						to a log file.
		*/
		void write(const Event& event, StringType filename) override
		{
			NOU::NOU_DAT_ALG::String8 absPath = NOU::NOU_FILE_MNGT::Path::currentWorkingDirectory().getAbsolutePath();
			absPath.append("/").append(filename);
			
			NOU::NOU_FILE_MNGT::File file(absPath);

			if (file.open(NOU::NOU_FILE_MNGT::AccessMode::APPEND) == true)
			{
				NOU::NOU_DAT_ALG::String8 error;
				error.append("[").append(event.getTimeStamp().getYear()).append("/").
					append(event.getTimeStamp().getMonth()).append("/").append(event.getTimeStamp().getDay()).
					append(" ").append(event.getTimeStamp().getHours()).append(":").
					append(event.getTimeStamp().getMinutes()).append(":").
					append(event.getTimeStamp().getSeconds());

				if (event.getTimeStamp().getSeconds() == 0)
					error.append("0");
#
				error.append("] ").
					append(event.getEventLevel()).append(": ").
					append(event.getEventMsg()).append("\n");
				
				file.write(error);
				file.close();
			}
			else
			{
				NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::CANNOT_OPEN_FILE,
					"Could not open log file.");
			}
		}
	};

	/**
	\brief A class for storing the different logger and writing logs to all of them.
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
		NOU::NOU_MEM_MNGT::GenericAllocationCallback<ILogger*> s_allocator;

		/**
		\brief Creates a new vector from ILogger pointers.
		*/
		NOU::NOU_DAT_ALG::Vector<ILogger*> s_logger;

		/**
		\param event	A const reference to an event object.
		\param filename	The name of the file where the log will be written to.

		\brief			Calls the write function for every objects in s_logger.
		*/
		void logAll(Event &&events, StringType filename);

		/**
		\param logger	The logger to write the event to.
		\param event	The event to write.
		\param filename	The name of the file where the log will be written to.

		\brief			Calls <tt>logger->write(event)</tt>. This is required for the task queue.
		*/
		static void callLoggingTarget(ILogger *logger, Event event, StringType filename);

		/**
		\brief		A TaskQueue for all multi-threaded tasks.
		\details	A task in the TaskQueue logs an error to one of the logging targets. Those tasks are
					executed in parallel.
		*/
		NOU::NOU_THREAD::TaskQueue<void, decltype(&callLoggingTarget),
			NOU::NOU_THREAD::TaskQueueAccumulators::FunctionPtr
			<NOU::NOU_THREAD::TaskQueueAccumulators::Void>, ILogger*, Event, StringType>
			taskQueue;

	public:

		/**
		\param log	A reference to an ILogger object.

		\brief		Pushes an logger to s_logger.
		*/
		void pushLogger(ILogger &log);

		/**
		\param level	A enum value, which represents the level of the event.
		\param msg		A const reference to the message, which specifies the event.
		\param filename	The name of the file where the log will be written to. The default value is log.txt.

		\brief			Creates a new event object from the level and msg parameters and calls the logAll() 
						with this event object.
		*/
		void write(EventLevelCodes level, const StringType &msg, StringType filename = "log.txt");
	};
/**
\brief This macro is a convenience macro for writing logs to the logger. This macro automatically
passes the level and message.
*/
#ifndef NOU_WRITE_LOG
#define NOU_WRITE_LOG(logger, level, msg, filename) logger.write(level, msg, filename)
#endif

/**
\brief This macro is a convenience macro, that behaves exactly like NOU_WRITE_LOG, but only if NOU_DEBUG is
defined. Otherwise, it will do nothing.
*/
#ifndef NOU_WRITE_DEBUG_LOG
#    ifdef  NOU_DEBUG
#        define NOU_WRITE_DEBUG_LOG(logger, level, msg, filename) NOU_WRITE_LOG(logger, level, msg, filename)
#    else
#        define NOU_WRITE_DEBUG_LOG(logger, level, msg, filename)
#    endif
#endif
}
#endif