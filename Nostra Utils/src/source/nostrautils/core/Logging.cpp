#include "nostrautils/core/Logging.hpp"

namespace NOU::NOU_CORE
{
	Event::Event(EventLevelCodes eventLevel, StringType eventMsg) :
		m_eventLevel(eventLevel),
		m_eventMsg(eventMsg),
		m_timestamp(getTime())
	{}

	Event::StringType Event::getTime()
	{
		time_t now = time(0);

		StringType localTime = ctime(&now);

		return localTime;
	}

	const Event::StringType Event::getEventLevel() const
	{
		return enumToString(m_eventLevel);
	}

	const Event::StringType& Event::getEventMsg() const
	{
		return m_eventMsg;
	}

	const Event::StringType& Event::getTimestamp() const
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

	//void FileLogger::callLoggingTarget(NOU::NOU_FILE_MNGT::File file, const NOU::NOU_DAT_ALG::String8 error)
	//{
	//	file.write(error);
	//}
	//
	//NOU::NOU_THREAD::TaskQueue<void, decltype(&FileLogger::callLoggingTarget),
	//	NOU::NOU_THREAD::TaskQueueAccumulators::FunctionPtr<NOU::NOU_THREAD::TaskQueueAccumulators::Void>, NOU::NOU_FILE_MNGT::File, NOU::NOU_DAT_ALG::String8>
	//	FileLogger::fileLoggerQueue;
	
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
