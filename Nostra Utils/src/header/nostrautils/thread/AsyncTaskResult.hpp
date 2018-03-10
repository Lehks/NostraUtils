#ifndef	NOU_THREAD_ASYNC_TASK_RESULT_HPP
#define	NOU_THREAD_ASYNC_TASK_RESULT_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\thread\Task.hpp"
#include "nostrautils\thread\ThreadManager.hpp"
#include "nostrautils\thread\Mutex.hpp"

namespace NOU::NOU_THREAD
{
	class NOU_CLASS AbstractAsyncTaskResult
	{
	public:
		enum class State
		{
			NOT_STARTED,
			EXECUTING_SYNC,
			EXECUTING_ASYNC,
			DONE
		};

	private:
		constexpr static int32 DEFAULT_PRIORITY = 0;

		static void executeTask(AbstractTask *task, AbstractAsyncTaskResult *taskResult, Mutex *mutex);

		using ExecutionTask = Task<void, decltype(&executeTask), AbstractTask*, AbstractAsyncTaskResult*,
			Mutex*>;
		using TaskInfo = typename ThreadManager::TaskInformation;

		Mutex          m_executionMutex;
		Mutex          m_stateMutex;
		ExecutionTask  m_executionTask;
		AbstractTask  *m_task;
		TaskInfo       m_taskInformation;
		State          m_state;
		
		void setState(State state);

	protected:
		AbstractAsyncTaskResult(AbstractTask *task);

	public:
		State getState() const;

		void makeResult();

		AbstractAsyncTaskResult(const AbstractAsyncTaskResult&) = delete;
		AbstractAsyncTaskResult(AbstractAsyncTaskResult&&) = delete;
	};

	template<typename R, typename I, typename... ARGS>
	class NOU_CLASS AsyncTaskResult : public AbstractAsyncTaskResult
	{	
	public:
		using Task = Task<R, I, ARGS...>;

	private:
		Task m_task;

	public:
		explicit AsyncTaskResult(Task &&task);
		explicit AsyncTaskResult(I &&invocable, ARGS&&... args);

		const R& getResult();

		AsyncTaskResult(const AsyncTaskResult&) = delete;
		AsyncTaskResult(AsyncTaskResult&&) = delete;
	};



	template<typename I, typename... ARGS>
	class NOU_CLASS AsyncTaskResult<void, I, ARGS...> : public AbstractAsyncTaskResult
	{
	public:
		using Task = Task<void, I, ARGS...>;

	private:
		Task m_task;

	public:
		explicit AsyncTaskResult(Task &&task);
		explicit AsyncTaskResult(I &&invocable, ARGS&&... args);

		void getResult();

		AsyncTaskResult(const AsyncTaskResult&) = delete;
		AsyncTaskResult(AsyncTaskResult&&) = delete;
	};



	template<typename R, typename I, typename... ARGS>
	AsyncTaskResult<R, I, ARGS...>::AsyncTaskResult(Task &&task) :
		AbstractAsyncTaskResult(&m_task),
		m_task(NOU_CORE::move(task))
	{}

	template<typename R, typename I, typename... ARGS>
	AsyncTaskResult<R, I, ARGS...>::AsyncTaskResult(I &&invocable, ARGS&&... args) :
		AbstractAsyncTaskResult(&m_task),
		m_task(makeTask(NOU_CORE::forward<I>(invocable), NOU_CORE::forward<ARGS>(args)...))
	{}

	template<typename R, typename I, typename... ARGS>
	const R& AsyncTaskResult<R, I, ARGS...>::getResult()
	{
		makeResult();

		return m_task.getResult();
	}



	template<typename I, typename... ARGS>
	AsyncTaskResult<void, I, ARGS...>::AsyncTaskResult(Task &&task) :
		AbstractAsyncTaskResult(&m_task),
		m_task(NOU_CORE::move(task))
	{}

	template<typename I, typename... ARGS>
	AsyncTaskResult<void, I, ARGS...>::AsyncTaskResult(I &&invocable, ARGS&&... args) :
		AbstractAsyncTaskResult(&m_task),
		m_task(makeTask(NOU_CORE::forward<I>(invocable), NOU_CORE::forward<ARGS>(args)...))
	{}

	template<typename I, typename... ARGS>
	void AsyncTaskResult<void, I, ARGS...>::getResult()
	{
		makeResult();
	}
}

#endif