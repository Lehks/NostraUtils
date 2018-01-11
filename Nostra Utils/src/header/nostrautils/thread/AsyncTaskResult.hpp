#ifndef	NOU_THREAD_ASYNC_TASK_RESULT_HPP
#define	NOU_THREAD_ASYNC_TASK_RESULT_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\thread\Task.hpp"

namespace NOU::NOU_THREAD
{
	template<typename T>
	class NOU_FUNC AsyncTaskResult
	{
	public:
		enum class State
		{
			WATINIG,
			EXECUTING_ASYNC,
			EXECUTING_SYNC,
			DONE
		};

		using ResultType = T;

	private:
		Task m_task;
		State m_state;
		ResultType m_result;

		void makeResult();

	public:
		const Task getTask() const;
		State getState() const;
		ResultType& getResult();
	};

	template<typename T>
	void AsyncTaskResult<T>::makeResult()
	{
		//lock here to avoid executing twice

		switch (m_state)
		{
		case State::WATINIG:
			//if true, task is being executed in sync, if false, task is executing async (rework, if sync, will not be set and state will be waiting)
			m_state = m_task->execute() ? State::EXECUTING_SYNC : State::EXECUTING_ASYNC;
			break;

		case State::EXECUTING_ASYNC:
		case State::EXECUTING_SYNC:
			//wait for task to be done
			break;
		}

		m_state = State::DONE;
	}

	template<typename T>
	const Task AsyncTaskResult<T>::getTask() const
	{
		return m_task;
	}

	template<typename T>
	typename AsyncTaskResult<T>::State AsyncTaskResult<T>::getState() const
	{
		return m_state;
	}

	template<typename T>
	typename AsyncTaskResult<T>::ResultType& AsyncTaskResult<T>::getResult()
	{
		makeResult();

		return *static_cast<ResultType*>(m_task->getResult());
	}

}

#endif