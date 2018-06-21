#ifndef	NOU_THREAD_ASYNC_TASK_RESULT_HPP
#define	NOU_THREAD_ASYNC_TASK_RESULT_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/thread/Task.hpp"
#include "nostrautils/thread/ThreadManager.hpp"
#include "nostrautils/thread/Mutex.hpp"

/** \file thread\AsyncTaskResult.hpp
\author	 Lukas Reichmann
\since   1.0.0
\version 1.0.1
\brief   This file provides a the class AsyncTaskResult

\see AsyncTaskResult
*/

namespace NOU::NOU_THREAD
{
	/**
	\brief An enumeration that stores that states that a AsyncTaskResult can have.
	*/
	enum class AsyncTaskResultState
	{
		/**
		\brief The task has not been started yet.
		*/
		NOT_STARTED,

		/**
		\brief makeResult() has directly or indirectly been called and the task is currently being
		executed by the thread that called that method.
		*/
		EXECUTING_SYNC,

		/**
		\brief The task is currently being executed by another thread.
		*/
		EXECUTING_ASYNC,

		/**
		\brief The task has finished execution.
		*/
		DONE
	};

	namespace internal
	{
		/**
		\brief A helper class that implements the functionality of AsyncTaskResult that interfaces with the 
		       thread manager.

		\details
		A helper class that implements the functionality of AsyncTaskResult that interfaces with the thread 
		manager.

		To execute the passed task in a different thread, this class uses another task that wraps around the
		passed one. This is, because the thread manager provided no functionality to notify a client about the
		tasks that it executes (hence, it would not be possible to update the status of the task). This
		wrapper does nothing else than executing the task and updating the state before the execution starts
		and after it ends. If the task is being executed 

		\note
		This class is not meant to be used by a user, instead AsyncTaskResult is supposed to be used instead.
		*/
		class AbstractAsyncTaskResult
		{
		public:
			using State = AsyncTaskResultState;

		private:
			/**
			\brief The priority that is used when a task is getting pushed to the thread manager.
			*/
			constexpr static int32 DEFAULT_PRIORITY = 0;

			/**
			\brief A method that executes the task that was passed to it and updates the state of this task
			       result accordingly.

			\details
			Together with the member \p m_executionTask (and everything that comes along with it, this method
			builds a wrapper for a task that will be executed in a different thread).

			A further description why this is needed is given in the details section of the class.
			*/
			NOU_FUNC static void executeTask(AbstractTask *task, AbstractAsyncTaskResult *taskResult, 
				Mutex *mutex);

			/**
			\brief The type of the member \p m_executionTask.

			\details
			Together with the member \p m_executionTask (and everything that comes along with it, this type
			builds a wrapper for a task that will be executed in a different thread).

			A further description why this is needed is given in the details section of the class.
			*/
			using ExecutionTask = Task<void, decltype(&executeTask), AbstractTask*, AbstractAsyncTaskResult*,
				Mutex*>;

			/**
			\brief An alias for ThreadManager::TaskInformation for easier usage.
			*/
			using TaskInfo = typename ThreadManager::TaskInformation;

			/**
			\brief A mutex that is used to synchronize the execution of the task in a different thread with a
			       call to makeResult() while the execution in that thread is still running.
			*/
			Mutex          m_executionMutex;

			/**
			\brief A mutex that is used to lock the access to the member \p m_state.
			*/
			Mutex          m_stateMutex;

			/**
			\brief The task that is meant to be executed in another thread.
			*/
			AbstractTask  *m_task;

			/**
			\brief The current state of the task.
			*/
			//to set this member, only setState() must be used (because of thread safety)
			State          m_state;

			/**
			\brief A task that wraps around \p m_task to execute that task in a different thread.

			\details
			A further description why this is needed is given in the details section of the class.
			*/
			ExecutionTask  m_executionTask;

			/**
			\brief The task information of the task that was pushed to the thread manager.
			*/
			TaskInfo       m_taskInformation;

			/**
			\param state The new state.
			
			\brief Sets the member \p m_state in a thread safe way.
			*/
			NOU_FUNC void setState(State state);

		protected:
			/**
			\param task The task to execute.

			\brief Constructs a new instance with the passed task.
			*/
			NOU_FUNC AbstractAsyncTaskResult(AbstractTask *task);

			/**
			\brief Pushes the task to the thread manager.

			\details
			Pushes the task to the thread manager. This method must be manually executed by any inheriting 
			classes. This is to make sure that all members could be initialized before the task is pushed to
			the thread manager.
			*/
			NOU_FUNC void push();

		public:
			/**
			\return The state of the task.

			\brief Returns the current state of the task.

			\note
			Unless the returned value is State::DONE, it is more of a hint than a definitive state, as e.g.
			if the state is State::EXECUTING_ASYNC, the task may be done executing right after this method has
			returned and before any other methods are getting called.
			*/
			NOU_FUNC State getState() const;

			/**
			\brief Forces the execution of the result. If this method returns, the state will always be 
			       State::DONE and the task will have finished execution.
			*/
			NOU_FUNC void makeResult();

			/**
			\brief Not copy construct-able.
			*/
			AbstractAsyncTaskResult(const AbstractAsyncTaskResult&) = delete;

			/**
			\brief Not move construct-able.
			*/
			AbstractAsyncTaskResult(AbstractAsyncTaskResult&&) = delete;
		};

	}

	/**
	\tparam The type of the return value.
	\tparam The type of the invocable to execute.
	\tparam The parameter types that will be passed to the invocable.

	\brief A class that allows to push single tasks to the thread manager.

	\details
	A class that allows to push single tasks to the thread manager. This class only allows to push single
	tasks, different instances of AsyncTaskResult are not connected.

	Each instance of AsyncTaskResult will get its own error handler provided by the thread manager.
	*/
	template<typename R, typename I, typename... ARGS>
	class AsyncTaskResult : public internal::AbstractAsyncTaskResult
	{	
	public:
		/**
		\brief An abbreviation for internal::AbstractAsyncTaskResult::State for easier use.
		*/
		using State = typename internal::AbstractAsyncTaskResult::State;

		/**
		\brief The type of task that will be executed by instance.
		*/
		using TaskType = Task<R, I, ARGS...>;

	private:
		/**
		\brief The task that will be executed by the instance.
		*/
		TaskType m_task;

	public:
		/**
		\param task The task to execute.

		\brief Constructs a new instance with the passed task.
		*/
		explicit AsyncTaskResult(const TaskType &task);

		/**
		\param task The task to execute.

		\brief Constructs a new instance with the passed task.
		*/
		explicit AsyncTaskResult(TaskType &&task);

		/**
		\param invocable The invocable to execute.
		\param args      The parameters to execute the invocable with.

		\brief Constructs a new instance with the passed invocable and parameters.
		*/
		explicit AsyncTaskResult(I &&invocable, ARGS&&... args);

		/**
		\return The value that was produced by the task.

		\brief Returns the result that was produced by the task. If no result has been produced yet, this
		       method will force the production of that result.

		\warning 
		If \p R is \p void, this method will also have the return type \p void. This may be a problem in code
		like this:
		\code
		auto result = task.getResult(); //task is a AsyncTaskResult in this case.
		\endcode

		Implementation detail:
		It is not actually this method that will change the return type, in fact there is an entire 
		specialization for invocables that return \p void. This specialization is not documented in this 
		Doxygen documentation but it behaves exactly like this class does (with the only difference being the 
		return type of this function).
		*/
		const R& getResult();

		/**
		\brief Not copy construct-able.
		*/
		AsyncTaskResult(const AsyncTaskResult&) = delete;

		/**
		\brief Not move construct-able.
		*/
		AsyncTaskResult(AsyncTaskResult&&) = delete;
	};


	///\cond
	template<typename I, typename... ARGS>
	class AsyncTaskResult<void, I, ARGS...> : public internal::AbstractAsyncTaskResult
	{
	public:
		using State = typename internal::AbstractAsyncTaskResult::State;
		using TaskType = Task<void, I, ARGS...>;

	private:
		TaskType m_task;

	public:
		explicit AsyncTaskResult(const TaskType &task);
		explicit AsyncTaskResult(TaskType &&task);
		explicit AsyncTaskResult(I &&invocable, ARGS&&... args);

		void getResult();

		AsyncTaskResult(const AsyncTaskResult&) = delete;
		AsyncTaskResult(AsyncTaskResult&&) = delete;
	};
	///\endcond


	template<typename R, typename I, typename... ARGS>
	AsyncTaskResult<R, I, ARGS...>::AsyncTaskResult(const TaskType &task) :
		AbstractAsyncTaskResult(&m_task),
		m_task(task)
	{
		push();
	}

	template<typename R, typename I, typename... ARGS>
	AsyncTaskResult<R, I, ARGS...>::AsyncTaskResult(TaskType &&task) :
		AbstractAsyncTaskResult(&m_task),
		m_task(NOU_CORE::move(task))
	{
		push();
	}

	template<typename R, typename I, typename... ARGS>
	AsyncTaskResult<R, I, ARGS...>::AsyncTaskResult(I &&invocable, ARGS&&... args) :
		AsyncTaskResult(makeTask(NOU_CORE::forward<I>(invocable), NOU_CORE::forward<ARGS>(args)...))
	{}

	template<typename R, typename I, typename... ARGS>
	const R& AsyncTaskResult<R, I, ARGS...>::getResult()
	{
		makeResult();

		return m_task.getResult();
	}



	template<typename I, typename... ARGS>
	AsyncTaskResult<void, I, ARGS...>::AsyncTaskResult(const TaskType &task) :
		AbstractAsyncTaskResult(&m_task),
		m_task(task)
	{
		push();
	}

	template<typename I, typename... ARGS>
	AsyncTaskResult<void, I, ARGS...>::AsyncTaskResult(TaskType &&task) :
		AbstractAsyncTaskResult(&m_task),
		m_task(NOU_CORE::move(task))
	{
		push();
	}

	template<typename I, typename... ARGS>
	AsyncTaskResult<void, I, ARGS...>::AsyncTaskResult(I &&invocable, ARGS&&... args) :
		AsyncTaskResult(makeTask(NOU_CORE::forward<I>(invocable), NOU_CORE::forward<ARGS>(args)...))
	{}

	template<typename I, typename... ARGS>
	void AsyncTaskResult<void, I, ARGS...>::getResult()
	{
		makeResult();
	}
}

#endif