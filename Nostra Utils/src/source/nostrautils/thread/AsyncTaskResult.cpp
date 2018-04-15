#include "nostrautils/thread/AsyncTaskResult.hpp"

namespace NOU { namespace NOU_THREAD
{
	void internal::AbstractAsyncTaskResult::executeTask(AbstractTask *task, 
		AbstractAsyncTaskResult *taskResult, Mutex *mutex)
	{
		Lock lock(*mutex);

		taskResult->setState(State::EXECUTING_ASYNC);

		task->execute();

		taskResult->setState(State::DONE);
	}

	void internal::AbstractAsyncTaskResult::setState(State state)
	{
		Lock lock(m_stateMutex);

		m_state = state;
	}

	internal::AbstractAsyncTaskResult::AbstractAsyncTaskResult(AbstractTask *task) :
		m_task(task),
		m_state(State::NOT_STARTED),
		m_executionTask(makeTask(&executeTask, m_task, this, &m_executionMutex))
	{}

	void internal::AbstractAsyncTaskResult::push()
	{
		getThreadManager().pushTask(&m_executionTask, 0);
	}

	typename internal::AbstractAsyncTaskResult::State internal::AbstractAsyncTaskResult::getState() const
	{
		return m_state;
	}

	void internal::AbstractAsyncTaskResult::makeResult()
	{
		//Remove task here to avoid race conditions (removeTask() will lock the task heap).
		getThreadManager().removeTask(m_taskInformation);
		
		/* 
		 * Lock mutex to wait until the task has finished execution (since the task was already removed, it 
		 * won't be started after this point, so executeTask() will not be blocked)
		 */
		Lock lock(m_executionMutex);

		/*
		 * If it has not been executed yet.
		 * m_state == State::NOT_STARTED is the best option, b/c:
		 * - removeTask() also returns false if the task was already executed (aka. the task was already 
		 *   removed which is why it could not be removed again)
		 * - m_state == State::DONE works better, but it fails as soon as the task is started twice from two 
		 *   different threads (in the case that the task was started again while the first execution is still
		 *   running)
		 */
		if (m_state == State::NOT_STARTED)
		{
			//Execute the task within the calling thread

			setState(State::EXECUTING_SYNC);

			m_task->execute();

			setState(State::DONE);
		}
	}
} //Namespace NOU_DAT_ALG
} //Namespace NOU