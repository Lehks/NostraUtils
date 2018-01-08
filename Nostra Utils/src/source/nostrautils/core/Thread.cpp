#include "nostrautils\core\Thread.hpp"

namespace NOU::NOU_CORE
{
	const std::thread& Thread::getUnderlyingThread() const
	{
		return m_thread;
	}

	std::thread& Thread::getUnderlyingThread()
	{
		return m_thread;
	}
}