#include "nostrautils/thread/ConditionVariable.hpp"

namespace NOU::NOU_THREAD
{
	void ConditionVariable::notifyOne()
	{
		m_variable.notify_one();
	}

	void ConditionVariable::notifyAll()
	{
		m_variable.notify_all();
	}

	void ConditionVariable::wait(UniqueLock &lock)
	{
		m_variable.wait(lock.getUnderlying());
	}
}