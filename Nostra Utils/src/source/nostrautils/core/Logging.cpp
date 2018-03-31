#include "nostrautils/core/Logging.hpp"

namespace NOU::NOU_CORE
{
	Event::Event(EventLevelCodes eventLevel, StringType eventMsg) :
		m_eventLevel(eventLevel),
		m_eventMsg(eventMsg)
	{}

	const Event::StringType Event::getEventLevel() const
	{
		return enumToString(m_eventLevel);
	}

	const Event::StringType& Event::getEventMsg() const
	{
		return m_eventMsg;
	}

	ILogger::StringType ILogger::getTime()
	{
		time_t now = time(0);

		StringType localTime = ctime(&now);

		return localTime;
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
		NOU::NOU_THREAD::TaskQueueAccumulators::FunctionPtr<NOU::NOU_THREAD::TaskQueueAccumulators::Void>, ILogger*, Event>
		Logger::taskQueue;

	void Logger::logAll(Event& events)
	{
		for (sizeType i = 0; i < s_logger.size(); i++)
		{
			taskQueue.pushTask(NOU_THREAD::makeTask(&callLoggingTarget, s_logger[i], events));
		}
	}

	void Logger::callLoggingTarget(ILogger *logger, Event event)
	{
		logger->write(event);
	}

	void Logger::write(EventLevelCodes level, const StringType &msg)
	{
		Event event(level, msg);

		logAll(event);
	}
}
