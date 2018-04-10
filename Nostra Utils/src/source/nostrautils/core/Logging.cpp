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

	const Event::StringType Event::getEventLevel() const
	{
		return enumToString(m_eventLevel);
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

	void Logger::pushLogger(ILogger &log)
	{
		s_logger.pushBack(&log);
	}

	void Logger::logAll(Event&& events)
	{
		for (sizeType i = 0; i < s_logger.size(); i++)
		{
			taskQueue.pushTask(NOU_THREAD::makeTask(&callLoggingTarget, s_logger[i], NOU_CORE::move(events)));
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
}
