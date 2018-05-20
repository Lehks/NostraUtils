#include "nostrautils/core/Logging.hpp"
#include "nostrautils/dat_alg/Utils.hpp"
#include "nostrautils/core/StdIncludes.hpp"

namespace NOU::NOU_CORE
{
	const Event::StringType Event::FATAL	= "Fatal";
	const Event::StringType Event::ERROR	= "Error";
	const Event::StringType Event::WARNING	= "Warning";
	const Event::StringType Event::INFO		= "Info";
	const Event::StringType Event::DEBUG	= "Debug";
	const Event::StringType Event::TRACE	= "Trace";
	const Event::StringType Event::UNKNOWN	= "Unknown";

	typename Event::TimeStamp::TimeType Event::TimeStamp::getSeconds() const
	{
		return m_seconds;
	}

	typename Event::TimeStamp::TimeType Event::TimeStamp::getMinutes() const
	{
		return m_minutes;
	}

	typename Event::TimeStamp::TimeType Event::TimeStamp::getHours() const
	{
		return m_hours;
	}

	typename Event::TimeStamp::TimeType Event::TimeStamp::getDay() const
	{
		return m_day;
	}

	typename Event::TimeStamp::TimeType Event::TimeStamp::getMonth() const
	{
		return m_month + 1; //Months would otherwise start at 0 and end at 11
	}

	typename Event::TimeStamp::TimeType Event::TimeStamp::getYear() const
	{
		return m_year + 1900; //the struct tm provides the years after the year 1900
	}

	Event::Event(EventLevelCodes eventLevel, const StringType& eventMsg) :
		m_eventLevel(eventLevel),
		m_eventMsg(eventMsg),
		m_timeStamp(getTime())
	{}

	typename Event::TimeStamp Event::getTime()
	{
#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
		using tmType = tm;
#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
		using tmType = tm*;
#endif

		time_t  currTime;
		tmType  currTm;
		tm     *tmPtr;

		time(&currTime);

#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
		gmtime_s(&currTm, &currTime);
		tmPtr = &currTm;
#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
		currTm = gmtime(&currTime);
		tmPtr = currTm;
#endif

		TimeStamp ret;

		ret.m_seconds = tmPtr->tm_sec;
		ret.m_minutes = tmPtr->tm_min;
		ret.m_hours   = tmPtr->tm_hour;
		ret.m_day     = tmPtr->tm_mday;
		ret.m_month   = tmPtr->tm_mon;
		ret.m_year    = tmPtr->tm_year;

		return ret;
	}

	const EventLevelCodes Event::getEventLevel() const
	{
		return m_eventLevel;
	}

	const Event::StringType& Event::getEventMsg() const
	{
		return m_eventMsg;
	}

	const typename Event::TimeStamp& Event::getTimeStamp() const
	{
		return m_timeStamp;
	}

	Event::StringType enumToString(EventLevelCodes eventLevel)
	{
		switch (eventLevel)
		{
		case EventLevelCodes::FATAL:
			return Event::FATAL;
			break;
		case EventLevelCodes::ERROR:
			return Event::ERROR;
			break;
		case EventLevelCodes::WARNING:
			return Event::WARNING;
			break;
		case EventLevelCodes::INFO:
			return Event::INFO;
			break;
		case EventLevelCodes::DEBUG:
			return Event::DEBUG;
			break;
		case EventLevelCodes::TRACE:
			return Event::TRACE;
			break;
		default:
			return Event::UNKNOWN;
		}
	}

	void ConsoleLogger::write(const Event& event)
	{
		NOU::NOU_DAT_ALG::String8 error = Logger::print(event);
		std::cout << error.rawStr() << std::endl;
	}

	void FileLogger::write(const Event& event)
	{
		NOU::NOU_FILE_MNGT::File file(m_path);

		if (!file.exists())
		{
			file.createFile();
		}

		if (file.open(NOU::NOU_FILE_MNGT::AccessMode::APPEND) == true)
		{
			NOU::NOU_DAT_ALG::String8 error = Logger::print(event);

			file.write(error);
			file.close();
		}
		else
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::CANNOT_OPEN_FILE,
				"Could not open log file.");
		}
	}

	FileLogger::FileLogger(const NOU_FILE_MNGT::Path &path) :
		m_path(path)
	{}

	void FileLoggerFatal::write(const Event& event)
	{
		if (event.getEventLevel() != EventLevelCodes::FATAL)
			return;

		NOU::NOU_FILE_MNGT::File file(m_path);

		if (!file.exists())
		{
			file.createFile();
		}

		if (file.open(NOU::NOU_FILE_MNGT::AccessMode::APPEND) == true)
		{
			NOU::NOU_DAT_ALG::String8 error = Logger::print(event);

			file.write(error);
			file.close();
		}
		else
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::CANNOT_OPEN_FILE,
				"Could not open log file.");
		}
	}

	FileLoggerFatal::FileLoggerFatal(const NOU_FILE_MNGT::Path &path) :
		m_path(path)
	{}

	void FileLoggerError::write(const Event& event)
	{
		if (event.getEventLevel() != EventLevelCodes::ERROR)
			return;

		NOU::NOU_FILE_MNGT::File file(m_path);

		if (!file.exists())
		{
			file.createFile();
		}

		if (file.open(NOU::NOU_FILE_MNGT::AccessMode::APPEND) == true)
		{
			NOU::NOU_DAT_ALG::String8 error = Logger::print(event);

			file.write(error);
			file.close();
		}
		else
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::CANNOT_OPEN_FILE,
				"Could not open log file.");
		}
	}

	FileLoggerError::FileLoggerError(const NOU_FILE_MNGT::Path &path) :
		m_path(path)
	{}

	void FileLoggerWarning::write(const Event& event)
	{
		if (event.getEventLevel() != EventLevelCodes::WARNING)
			return;

		NOU::NOU_FILE_MNGT::File file(m_path);

		if (!file.exists())
		{
			file.createFile();
		}

		if (file.open(NOU::NOU_FILE_MNGT::AccessMode::APPEND) == true)
		{
			NOU::NOU_DAT_ALG::String8 error = Logger::print(event);

			file.write(error);
			file.close();
		}
		else
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::CANNOT_OPEN_FILE,
				"Could not open log file.");
		}
	}

	FileLoggerWarning::FileLoggerWarning(const NOU_FILE_MNGT::Path &path) :
		m_path(path)
	{}

	void FileLoggerInfo::write(const Event& event)
	{
		if (event.getEventLevel() != EventLevelCodes::INFO)
			return;

		NOU::NOU_FILE_MNGT::File file(m_path);

		if (!file.exists())
		{
			file.createFile();
		}

		if (file.open(NOU::NOU_FILE_MNGT::AccessMode::APPEND) == true)
		{
			NOU::NOU_DAT_ALG::String8 error = Logger::print(event);

			file.write(error);
			file.close();
		}
		else
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::CANNOT_OPEN_FILE,
				"Could not open log file.");
		}
	}

	FileLoggerInfo::FileLoggerInfo(const NOU_FILE_MNGT::Path &path) :
		m_path(path)
	{}

	void FileLoggerDebug::write(const Event& event)
	{
		if (event.getEventLevel() != EventLevelCodes::DEBUG)
			return;

		NOU::NOU_FILE_MNGT::File file(m_path);

		if (!file.exists())
		{
			file.createFile();
		}

		if (file.open(NOU::NOU_FILE_MNGT::AccessMode::APPEND) == true)
		{
			NOU::NOU_DAT_ALG::String8 error = Logger::print(event);

			file.write(error);
			file.close();
		}
		else
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::CANNOT_OPEN_FILE,
				"Could not open log file.");
		}
	}

	FileLoggerDebug::FileLoggerDebug(const NOU_FILE_MNGT::Path &path) :
		m_path(path)
	{}

	void FileLoggerTrace::write(const Event& event)
	{
		if (event.getEventLevel() != EventLevelCodes::TRACE)
			return;

		NOU::NOU_FILE_MNGT::File file(m_path);

		if (!file.exists())
		{
			file.createFile();
		}

		if (file.open(NOU::NOU_FILE_MNGT::AccessMode::APPEND) == true)
		{
			NOU::NOU_DAT_ALG::String8 error = Logger::print(event);

			file.write(error);
			file.close();
		}
		else
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::CANNOT_OPEN_FILE,
				"Could not open log file.");
		}
	}

	FileLoggerTrace::FileLoggerTrace(const NOU_FILE_MNGT::Path &path) :
		m_path(path)
	{}

	void FileLoggerUnknown::write(const Event& event)
	{
		if (event.getEventLevel() != EventLevelCodes::UNKNOWN)
			return;

		NOU::NOU_FILE_MNGT::File file(m_path);

		if (!file.exists())
		{
			file.createFile();
		}

		if (file.open(NOU::NOU_FILE_MNGT::AccessMode::APPEND) == true)
		{
			NOU::NOU_DAT_ALG::String8 error = Logger::print(event);

			file.write(error);
			file.close();
		}
		else
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::CANNOT_OPEN_FILE,
				"Could not open log file.");
		}
	}

	FileLoggerUnknown::FileLoggerUnknown(const NOU_FILE_MNGT::Path &path) :
		m_path(path)
	{}

	Logger& Logger::get()
	{
		static Logger instance;
		return instance;
	}

	Logger::~Logger()
	{
		for (ILogger* element : m_logger)
		{
			delete element;
		}
	}

	NOU::NOU_DAT_ALG::String8 Logger::print(const Event& event)
	{
		NOU::NOU_DAT_ALG::String8 error;

		error.append("[").append(event.getTimeStamp().getYear());
		error.append("/");

		if (event.getTimeStamp().getMonth() < 10)
			error.append("0");
		error.append(event.getTimeStamp().getMonth());
		error.append("/");

		if (event.getTimeStamp().getDay() < 10)
			error.append("0");
		error.append(event.getTimeStamp().getDay());
		error.append(" ");

		if (event.getTimeStamp().getHours() < 10)
			error.append("0");
		error.append(event.getTimeStamp().getHours());
		error.append(":");

		if (event.getTimeStamp().getMinutes() < 10)
			error.append("0");
		error.append(event.getTimeStamp().getMinutes());
		error.append(":");

		if (event.getTimeStamp().getSeconds() < 10)
			error.append("0");
		error.append(event.getTimeStamp().getSeconds());

		error.append("] ");
		error.append(enumToString(event.getEventLevel())).append(": ");
		error.append(event.getEventMsg()).append("\n");

		return error;
	}

	void Logger::logAll(Event&& events)
	{
		for (sizeType i = 0; i < m_logger.size(); i++)
		{
			m_taskQueue.pushTask(NOU_THREAD::makeTask(&callLoggingTarget, m_logger[i], 
				NOU_CORE::move(events)));
		}
	}

	void Logger::callLoggingTarget(ILogger *logger, Event event)
	{
		logger->write(event);
	}

	void Logger::write(EventLevelCodes level, const StringType &msg)
	{
		logAll(Event(level, msg));
	}

	void Logger::wait()
	{
		m_taskQueue.close();
		m_taskQueue.getResult();
	}
}
