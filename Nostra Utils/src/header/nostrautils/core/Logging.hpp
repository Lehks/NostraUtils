#ifndef NOU_CORE_LOGGING_HPP
#define NOU_CORE_LOGGING_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/core/Meta.hpp"

#include "nostrautils/dat_alg/StringView.hpp"
#include "nostrautils/dat_alg/String.hpp"
#include "nostrautils/dat_alg/Vector.hpp"

#include "nostrautils/file_mngt/File.hpp"
#include "nostrautils/file_mngt/Path.hpp"

#include "nostrautils/thread/Threads.hpp"

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
		   Unknown:	All errors that do not fall under one of the other categories are unknown errors.
	*/
	enum class EventLevelCodes
	{
		FATAL		= 0,

		ERROR		= 1,

		WARNING		= 2,

		INFO		= 3,

		DEBUG		= 4,

		TRACE		= 5,

		UNKNOWN		= 6
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
		
		\brief			A pure virtual class whose behavior will be overridden in derived classes.
		*/
		virtual void write(const Event& event) = 0;
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

		\brief			A overridden function of the write() in the ILogger interface. Writes the log entry 
						to the console.
		*/
		void write(const Event& event) override;
	};

	/**
	\brief A derived class of the ILogger interface. Used for writing logs to a file.
	*/
	class NOU_CLASS FileLogger : public ILogger
	{
	private:

		/**
		\brief			The path of the file
		*/
		NOU_FILE_MNGT::Path m_path;

		/**
		\param event	A const reference to an event object.

		\brief			A overridden function of the write() in the ILogger interface. Writes the log entry
						to a log file.
		*/
		void write(const Event& event) override;

	public:
		/**
		\param path		The path to the file that the log will be written to.

		\brief			Constructs a new instance that will write the log to the passed file.
		*/
		FileLogger(const NOU_FILE_MNGT::Path &path);
	};


	/**
	\brief		A class for storing the different logger and writing logs to all of them.
	
	\details	To create a new Logger you need to call the get() and store the result in a Logger.
				e.g.:	Logger& log = Logger::get();

				The get() will create a new Logger object. If there is already a Logger object it won't 
				create a new one and you will get the already created one.

				This ensures that there is only one Logger object at all time.

				After that you need to push a logging target to the logger you created.
				e.g.:	log.pushLogger<ConsoleLogger>(); //This will push a ConsoleLogger

				If you want to specify a file, where your logs should be written to, you can use the
				fileLogger and pass the name of the file.
				e.g.:	log.pushLogger<FileLogger>("logFile.txt");

				And at end you can tell the logger to write a log.
				e.g.:	NOU_LOG_ERROR("Invalid object type.");

				This example will write an error of the ERROR level. You can change the event level 
				by using a different macro. All macros start with NOU_LOG_ and end with the event level.

				All macros are:

				-NOU_LOG_FATAL()
				-NOU_LOG_ERROR()
				-NOU_LOG_WARNING()
				-NOU_LOG_INFO()
				-NOU_LOG_DEBUG()
				-NOU_LOG_TRACE()
	*/
	class Logger
	{
	public:

		/**
		\brief		Alias for the NOU::NOU_DAT_ALG::StringView8.
		*/
		using StringType = Event::StringType;

		/**
		\return		The logger object.

		\brief		Creates a Logger object and returns it.

		\details	This function is implemented as a singleton.
		*/
		NOU_FUNC static Logger& get();

		/**
		\brief			Destructor of the Logger.
		*/
		~Logger();

		/**
		\param	event	An event.

		\return			The error string.

		\brief			Returns a custom formated error string.
		*/
		NOU_FUNC static NOU::NOU_DAT_ALG::String8 print(const Event& event);

	private:

		/**
		\brief			Default constructor of the Logger.
		*/
		NOU_FUNC Logger() = default;

		/**
		\brief			Deleted copy constructor of the Logger.
		*/
		NOU_FUNC Logger(const Logger& other) = delete;

		/**
		\brief			Creates a new vector from ILogger pointers.
		*/
		NOU::NOU_DAT_ALG::Vector<ILogger*> m_logger;

		/**
		\param events	An event object.

		\brief			Calls the write function for every objects in m_logger.
		*/
		NOU_FUNC void logAll(Event &&events);

		/**
		\param logger	The logger to write the event to.
		\param event	The event to write.

		\brief			Calls <tt>logger.write(event)</tt>. This is required for the task queue.
		*/
		NOU_FUNC static void callLoggingTarget(ILogger *logger, Event event);

		/**
		\brief		A TaskQueue for all multi-threaded tasks.

		\details	A task in the TaskQueue logs an error to one of the logging targets. Those tasks are
					executed in parallel.
		*/
		NOU::NOU_THREAD::TaskQueue<void, decltype(&callLoggingTarget),
			NOU::NOU_THREAD::TaskQueueAccumulators::FunctionPtr
			<NOU::NOU_THREAD::TaskQueueAccumulators::Void>, ILogger*, Event>
			m_taskQueue;

	public:

		/**
		\tparam T		The type of the Logger.
		\tparam ARGS	The arguments.
		\param log		A reference to an ILogger object.

		\brief			Pushes an logger to m_logger.
		*/
		template<typename T, typename ...ARGS>
		void pushLogger(ARGS&&... log);

		/**
		\param level	A enum value, which represents the level of the event.
		\param msg		A const reference to the message, which specifies the event.

		\brief			Creates a new event object from the level and msg parameters and calls the logAll() 
						with this event object.
		*/
		NOU_FUNC void write(EventLevelCodes level, const StringType &msg);
	
		/**
		\brief Holds the execution of the thread that the method is called from until the logger is done
		       writing to all of the logging targets.

		\attention
		This method can 
		1. only be called once
		2. converts the logger into an invalid state; it is not possible to write messages to the logger once 
		   this method was called.
		*/
		NOU_FUNC void wait();
	};

	template<typename T, typename ...ARGS>
	void Logger::pushLogger(ARGS&&... args)
	{
		m_logger.pushBack(new T(NOU_CORE::forward<ARGS>(args)...));
	}

#ifndef NOU_LOG_FATAL
#    ifndef NOU_LOG_FATAL_DISABLE
#        define NOU_LOG_FATAL(msg) \
                              NOU::NOU_CORE::Logger::get().write(NOU::NOU_CORE::EventLevelCodes::FATAL, msg);
#    endif
#endif

#ifndef NOU_LOG_ERROR
#    ifndef NOU_LOG_ERROR_DISABLE
#        define NOU_LOG_ERROR(msg) \
                              NOU::NOU_CORE::Logger::get().write(NOU::NOU_CORE::EventLevelCodes::ERROR, msg);   
#    endif
#endif

#ifndef NOU_LOG_WARNING
#    ifndef NOU_LOG_WARNING_DISABLE
#        define NOU_LOG_WARNING(msg) \
                            NOU::NOU_CORE::Logger::get().write(NOU::NOU_CORE::EventLevelCodes::WARNING, msg);   
#    endif
#endif

#ifndef NOU_LOG_INFO
#    ifndef NOU_LOG_INFO_DISABLE
#        define NOU_LOG_INFO(msg) \
                            NOU::NOU_CORE::Logger::get().write(NOU::NOU_CORE::EventLevelCodes::INFO, msg);   
#    endif
#endif

#ifndef NOU_LOG_DEBUG
#    ifndef NOU_LOG_DEBUG_DISABLE
#        define NOU_LOG_DEBUG(msg) \
                            NOU::NOU_CORE::Logger::get().write(NOU::NOU_CORE::EventLevelCodes::DEBUG, msg);   
#    endif
#endif

#ifndef NOU_LOG_TRACE
#    ifndef NOU_LOG_TRACE_DISABLE
#        define NOU_LOG_TRACE(msg) \
                            NOU::NOU_CORE::Logger::get().write(NOU::NOU_CORE::EventLevelCodes::TRACE, msg);   
#    endif
#endif

#ifndef NOU_LOG_UNKNOWN
#    ifndef NOU_LOG_UNKNOWN_DISABLE
#        define NOU_LOG_UNKNOWN(msg) \
                            NOU::NOU_CORE::Logger::get().write(NOU::NOU_CORE::EventLevelCodes::UNKNOWN, msg);   
#    endif
#endif
}

#endif