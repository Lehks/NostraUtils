#include "nostrautils/core/Logging.hpp"
#include "nostrautils/dat_alg/Utils.hpp"
#include "nostrautils/core/StdIncludes.hpp"

namespace NOU::NOU_CORE
{
	Event::Event(EventLevelCodes eventLevel, const StringType& eventMsg) :
		m_eventLevel(eventLevel),
		m_eventMsg(eventMsg),
		m_timestamp(getTime())
	{}

	NOU::NOU_DAT_ALG::String8 Event::getTime()
	{

#ifdef NOU_OS_LIBRARY_WIN_H
		time_t curr_time;
		tm  curr_tm;
		char date_string[20];
		struct tm buff;

		time(&curr_time);
		localtime_s(&curr_tm, &curr_time);
		strftime(date_string, 20, "%Y/%m/%d %T", &curr_tm);

		NOU::NOU_DAT_ALG::String8 localTime = date_string;

#elif NOU_OS_LIBRARY_POSIX
		time_t curr_time;
		tm * curr_tm;
		char date_string[20];

		time(&curr_time);
		curr_tm = localtime(&curr_time);
		strftime(date_string, 20, "%Y/%m/%d %T", curr_tm);

		NOU::NOU_DAT_ALG::String8 localTime = date_string;
#endif

		return localTime.rawStr();
	}

	const Event::StringType& Event::getEventLevel() const
	{
		return enumToString(m_eventLevel);
	}

	const Event::StringType& Event::getEventMsg() const
	{
		return m_eventMsg;
	}

	const NOU::NOU_DAT_ALG::String8& Event::getTimestamp() const
	{
		return m_timestamp;
	}

	Event::StringType enumToString(EventLevelCodes eventLevel)
	{
		switch (eventLevel)
		{
		case EventLevelCodes::FATAL:
			return "Fatal";
			break;
		case EventLevelCodes::ERROR:
			return "Error";
			break;
		case EventLevelCodes::WARNING:
			return "Warning";
			break;
		case EventLevelCodes::INFO:
			return "Info";
			break;
		case EventLevelCodes::DEBUG:
			return "Debug";
			break;
		case EventLevelCodes::TRACE:
			return "Debug";
			break;
		default:
			return "Unknown";
		}
	}
	
	NOU::NOU_MEM_MNGT::GenericAllocationCallback<ILogger*> Logger::s_allocator;
	NOU::NOU_DAT_ALG::Vector<ILogger*> Logger::s_logger(1, s_allocator);

	void Logger::pushLogger(ILogger &log)
	{
		s_logger.pushBack(&log);
	}

	NOU::NOU_THREAD::TaskQueue<void, decltype(&Logger::callLoggingTarget),
		NOU::NOU_THREAD::TaskQueueAccumulators::FunctionPtr<NOU::NOU_THREAD::TaskQueueAccumulators::Void>, ILogger*, const Event>
		Logger::taskQueue;


	void Logger::logAll(const Event& events)
	{
		for (sizeType i = 0; i < s_logger.size(); i++)
		{
			taskQueue.pushTask(NOU_THREAD::makeTask(&callLoggingTarget, s_logger[i], events));
		}
	}

	void Logger::callLoggingTarget(ILogger *logger, const Event event)
	{
		logger->write(event);
	}

	void Logger::write(EventLevelCodes level, const StringType &msg)
	{
		Event event(level, msg);

		logAll(event);
	}
}
