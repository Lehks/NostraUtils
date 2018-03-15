#ifndef	NOU_THREAD_TASK_QUEUE_HPP
#define NOU_THREAD_TASK_QUEUE_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Meta.hpp"
#include "nostrautils\core\Utils.hpp"
#include "nostrautils\core\ErrorHandler.hpp"
#include "nostrautils\thread\ThreadManager.hpp"
#include "nostrautils\thread\Task.hpp"
#include "nostrautils\dat_alg\Uninitialized.hpp"
#include "nostrautils\dat_alg\FastQueue.hpp"
#include <type_traits>

namespace NOU::NOU_THREAD
{
	/**
	\brief A namespace that contains a collection of several accumulators that are meant to be used with 
	       TaskQueue.
	*/
	namespace  TaskQueueAccumulators
	{
		/**
		\tparam R The type of the results that will be accumulated.

		\brief The type of a function that can be used as an accumulator.
		*/
		template<typename R>
		using FunctionPtr = R(*)(R&&, R&&);

		/**
		\tparam R The type of the results that will be accumulated.

		\param previous The result from the previous accumulation.
		\param current  The result from the last task that was executed.

		\return \p current

		\brief An accumulator that returns \p current.
		*/
		template<typename R>
		static R forward(R &&previous, R &&current);

		/**
		\tparam R The type of the results that will be accumulated.

		\param previous The result from the previous accumulation.
		\param current  The result from the last task that was executed.

		\return \p previous + \p current

		\brief Returns the result of an addition of \p previous and \p current.

		\note
		\p R needs to have the operator + overloaded.
		*/
		template<typename R>
		static R addition(R &&previous, R &&current);

		/**
		\tparam R The type of the results that will be accumulated.

		\param previous The result from the previous accumulation.
		\param current  The result from the last task that was executed.

		\return \p current + \p previous

		\brief Returns the result of an addition of \p previous and \p current.

		\note
		\p R needs to have the operator + overloaded.
		*/
		template<typename R>
		static R additionInverted(R &&previous, R &&current);

		/**
		\tparam R The type of the results that will be accumulated.

		\param previous The result from the previous accumulation.
		\param current  The result from the last task that was executed.

		\return \p previous - \p current

		\brief Returns the result of an subtraction of \p previous and \p current.

		\note
		\p R needs to have the operator - overloaded.
		*/
		template<typename R>
		static R subtract(R &&previous, R &&current);

		/**
		\tparam R The type of the results that will be accumulated.

		\param previous The result from the previous accumulation.
		\param current  The result from the last task that was executed.

		\return \p current - \p previous

		\brief Returns the result of an subtraction of \p previous and \p current.

		\note
		\p R needs to have the operator - overloaded.
		*/
		template<typename R>
		static R subtractInverted(R &&previous, R &&current);

		/**
		\tparam R The type of the results that will be accumulated.

		\param previous The result from the previous accumulation.
		\param current  The result from the last task that was executed.

		\return \p previous * \p current

		\brief Returns the result of an multiplication of \p previous and \p current.

		\note
		\p R needs to have the operator * overloaded.
		*/
		template<typename R>
		static R multiplicate(R &&previous, R &&current);

		/**
		\tparam R The type of the results that will be accumulated.

		\param previous The result from the previous accumulation.
		\param current  The result from the last task that was executed.

		\return \p current * \p previous

		\brief Returns the result of an multiplication of \p previous and \p current.

		\note
		\p R needs to have the operator * overloaded.
		*/
		template<typename R>
		static R multiplicateInverted(R &&previous, R &&current);

		/**
		\tparam R The type of the results that will be accumulated.

		\param previous The result from the previous accumulation.
		\param current  The result from the last task that was executed.

		\return \p previous / \p current

		\brief Returns the result of an division of \p previous and \p current.

		\note
		\p R needs to have the operator / overloaded.
		*/
		template<typename R>
		static R divide(R &&previous, R &&current);

		/**
		\tparam R The type of the results that will be accumulated.

		\param previous The result from the previous accumulation.
		\param current  The result from the last task that was executed.

		\return \p current / \p previous

		\brief Returns the result of an division of \p previous and \p current.

		\note
		\p R needs to have the operator / overloaded.
		*/
		template<typename R>
		static R divideInverted(R &&previous, R &&current);

		/**
		\tparam R The type of the results that will be accumulated.

		\tparam FUNC The member function to call.

		\param previous The result from the previous accumulation.
		\param current  The result from the last task that was executed.

		\return <tt> previous.*FUNC(current) </tt>

		\brief Returns the result of a call to the member function \p FUNC with \p previous being the callee
			   and \p current the parameter.
		*/
		template<typename R, R(R::*FUNC)(R&&)>
		static R memberFunction(R &&previous, R &&current);

		/**
		\tparam R The type of the results that will be accumulated.

		\tparam FUNC The member function to call.

		\param previous The result from the previous accumulation.
		\param current  The result from the last task that was executed.

		\return <tt> current.*FUNC(previous) </tt>

		\brief Returns the result of a call to the member function \p FUNC with \p current being the callee
			   and \p previous the parameter.
		*/
		template<typename R, R(R::*FUNC)(R&&)>
		static R memberFunctionInverted(R &&previous, R &&current);
	};

	template<typename R, typename I, typename ACCUM = typename TaskQueueAccumulators::FunctionPtr<R>, typename... ARGS>
	class NOU_CLASS TaskQueue
	{
	public:
		using Accumulator = ACCUM;
		using Result = R;
		using Task = Task<Result, I, ARGS...>;
		using ExecutionTask = NOU_THREAD::Task<void, void(*)(TaskQueue*), TaskQueue*>;

		static_assert(NOU_CORE::IsInvocableR<Result, ACCUM, Result&&, Result&&>::value);
		static_assert(NOU_CORE::IsInvocableR<Result, I, ARGS...>::value);

		static constexpr sizeType DEFAULT_INITIAL_CAPACITY = 1;

	private:
		static void executeTask(TaskQueue *taskQueue);

		Mutex                              m_taskQueueMutex;
		Mutex                              m_currentTaskMutex;
		Mutex                              m_resultMutex;
		Accumulator                        m_accumulator;
		NOU_DAT_ALG::FastQueue<Task>       m_taskQueue;
		NOU_DAT_ALG::Uninitialized<Task>   m_currentTask;
		NOU_DAT_ALG::Uninitialized<Result> m_result;
		NOU_CORE::ErrorHandler             m_handler;
		boolean                            m_closed;
		boolean                            m_stopParallelExecution;
		ExecutionTask                      m_executionTask;

		/**
		\pre Lock m_currentTaskMutex and m_taskQueueMutex.
		*/
		void updateExecutingTask();

		void accumulate(Result &&current);

	public:
		TaskQueue(Accumulator &&accumulator, sizeType initialCapacity = DEFAULT_INITIAL_CAPACITY);

		TaskQueue& pushTask(Task &&task);

		/**
		\return The current, temporary result.

		\brief Returns the currently stored, temporary result.

		\details
		Returns the currently stored, temporary result. Unlike getResult(), this method does not force the
		the execution of all tasks that are currently in the queue, but returns the result that was produced
		by the last accumulation.

		\note
		This function may be expensive, as the result will be copied instead of moved or returned by
		reference. This is required because the internally stored result may be overridden at any time by
		a task that has just finished execution.
		*/
		Result getTemporaryResult();

		/**
		\brief Computes the result of all tasks in the queue and returns the accumulated result.

		\details
		Computes the result of all tasks in the queue and returns the accumulated result. If there is
		currently already a task in execution and there are other tasks still waiting in the queue, those
		tasks will be executed in getResult() (by the thread that called that method).

		\attention
		It is dangerous to call getResult() and then push tasks to the queue after that. This is because
		getResult() returns a reference to the result and if one thread accesses the result and another thread
		overwrites it at the same time, the result may be in an inconsistent state when accessed via the
		reference. To prevent pushing tasks to the queue after getResult() has been called, close() can be
		used.

		\warning
		If there is another thread continuously pushing tasks to the queue while another thread called
		getResult(), getResult() will not finish (unless the pushing thread stops pushing tasks). One way to
		avoid that, is using close() (Note that if the other thread keeps pushing after close() has been
		called, the error handler will be filled up with errors if they are not handled).
		*/
		const Result& getResult();

		/**
		\brief Closes the queue. This prevents from any tasks getting pushed to it.

		\details
		Closes the queue. This prevents from any tasks getting pushed to it. This can be useful to ensure that
		getResult() always returns a reference to an object that is in a consistent state. For more
		information on why this is a problem, see detailed section of getResult().

		If a queue has been closed and pushTask() is called anyway, the error handler will be set to
		ErrorCodes::INVALID_STATE.
		*/
		void close();
	};

	namespace TaskQueueAccumulators
	{
		template<typename R>
		R forward(R &&previous, R &&current)
		{
			return NOU_CORE::move(current);
		}

		template<typename R>
		R addition(R &&previous, R &&current)
		{
			return NOU_CORE::move(previous) + NOU_CORE::move(current);
		}

		template<typename R>
		R additionInverted(R &&previous, R &&current)
		{
			return addAccum(NOU_CORE::move(current), NOU_CORE::move(previous));
		}

		template<typename R>
		R subtract(R &&previous, R &&current)
		{
			return NOU_CORE::move(previous) - NOU_CORE::move(current);
		}

		template<typename R>
		R subtractInverted(R &&previous, R &&current)
		{
			return subAccum(NOU_CORE::move(current), NOU_CORE::move(previous));
		}

		template<typename R>
		R multiplicate(R &&previous, R &&current)
		{
			return NOU_CORE::move(previous) * NOU_CORE::move(current);
		}

		template<typename R>
		R multiplicateInverted(R &&previous, R &&current)
		{
			return mulAccum(NOU_CORE::move(current), NOU_CORE::move(previous));
		}

		template<typename R>
		R divide(R &&previous, R &&current)
		{
			return NOU_CORE::move(previous) / NOU_CORE::move(current);
		}

		template<typename R>
		R divideInverted(R &&previous, R &&current)
		{
			return divAccum(NOU_CORE::move(current), NOU_CORE::move(previous));
		}

		template<typename R, R(R::*FUNC)(R&&)>
		R memberFunction(R &&previous, R &&current)
		{
			return (previous.*FUNC)(NOU_CORE::move(current));
		}

		template<typename R, R(R::*FUNC)(R&&)>
		R memberFunctionInverted(R &&previous, R &&current)
		{
			return (current.*FUNC)(NOU_CORE::move(previous));
		}
	}

	template<typename R, typename I, typename ACCUM, typename... ARGS>
	void TaskQueue<R, I, ACCUM, ARGS...>::executeTask(TaskQueue<R, I, ACCUM, ARGS...> *taskQueue)
	{
		Uninitialized<Task> tempTask;

		{
			/*
			* To avoid having to lock m_currentTaskMutex for the entire runtime of the task, move that task
			* here locally (locking is only required while the task is getting moved).
			*
			* Also, it is important to move ONLY the task, not the entire m_currentTask Uninitialized
			* (m_currentTask) will be used again.
			* (NOU_CORE::move(*taskQueue->m_currentTask) moves the task itself,
			* NOU_CORE::move(taskQueue->m_currentTask) would move the entire Uninitialized)
			*/
			Lock lock(taskQueue->m_currentTaskMutex);
			tempTask = NOU_CORE::move(*taskQueue->m_currentTask);
		}

		tempTask->execute();
		Result result = tempTask->moveResult();

		{
			Lock lock(taskQueue->m_resultMutex);

			taskQueue->accumulate(NOU_CORE::move(result));
		}

		if (!taskQueue->m_stopParallelExecution)
		{
			Lock taskQueueLock(taskQueue->m_taskQueueMutex);
			Lock currentTaskLock(taskQueue->m_currentTaskMutex);

			taskQueue->m_currentTask.destroy();

			taskQueue->updateExecutingTask();
		}
	}

	template<typename R, typename I, typename ACCUM, typename... ARGS>
	TaskQueue<R, I, ACCUM, ARGS...>::TaskQueue(Accumulator &&accumulator, sizeType initialCapacity) :
		m_accumulator(NOU_CORE::move(accumulator)),
		m_taskQueue(initialCapacity),
		m_closed(false),
		m_stopParallelExecution(false),
		m_executionTask(&executeTask, this)
	{}

	template<typename R, typename I, typename ACCUM, typename... ARGS>
	void TaskQueue<R, I, ACCUM, ARGS...>::updateExecutingTask()
	{
		if (!m_currentTask.isValid() && m_taskQueue.size() > 0)
		{
			m_currentTask = m_taskQueue.popFront();
			getThreadManager().pushTask(&m_executionTask, 0, &m_handler);
		}
	}

	template<typename R, typename I, typename ACCUM, typename... ARGS>
	void TaskQueue<R, I, ACCUM, ARGS...>::accumulate(Result &&current)
	{
		/*
		* if there was already a result, accumulate that old result with the new one, if there was no result
		* yet, set the new result as the result (accumulation will be done by the following tasks)
		*/
		if (m_result.isValid())
		{
			//accumulate old results into a new one
			m_result = m_accumulator(NOU_CORE::move(*m_result), NOU_CORE::move(current));
		}
		else
		{
			m_result = NOU_CORE::move(current);
		}
	}

	template<typename R, typename I, typename ACCUM, typename... ARGS>
	TaskQueue<R, I, ACCUM, ARGS...>& TaskQueue<R, I, ACCUM, ARGS...>::pushTask(Task &&task)
	{
		if (m_closed)
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_STATE, 
				"The queue has been closed.");
		}
		else
		{
			Lock taskQueueMutex(m_taskQueueMutex);

			m_taskQueue.push(NOU_CORE::move(task));

			{
				Lock currentTaskLock(m_currentTaskMutex);
				updateExecutingTask();
			}
		}

		return *this;
	}

	template<typename R, typename I, typename ACCUM, typename... ARGS>
	typename TaskQueue<R, I, ACCUM, ARGS...>::Result TaskQueue<R, I, ACCUM, ARGS...>::getTemporaryResult()
	{
		Lock lock(m_resultMutex);

		Result ret = *m_result;

		return ret;
	}

	template<typename R, typename I, typename ACCUM, typename... ARGS>
	const typename TaskQueue<R, I, ACCUM, ARGS...>::Result& 
		TaskQueue<R, I, ACCUM, ARGS...>::getResult()
	{
		m_stopParallelExecution = true;

		//wait for current task to finish execution

		{
			Lock lock(m_taskQueueMutex);

			while (m_taskQueue.size() != 0)
			{
				Task task = m_taskQueue.popFront();
				task.execute();

				accumulate(task.moveResult());
			}
		}

		m_stopParallelExecution = false;

		return *m_result;
	}

	template<typename R, typename I, typename ACCUM, typename... ARGS>
	void TaskQueue<R, I, ACCUM, ARGS...>::close()
	{
		m_closed = true;
	}
}

#endif