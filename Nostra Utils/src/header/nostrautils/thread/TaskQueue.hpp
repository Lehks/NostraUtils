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
#include "nostrautils\thread\ConditionVariable.hpp"
#include <type_traits>


/** \file thread\TaskQueue.hpp
\author	 Lukas Reichmann
\since   0.0.1
\version 0.0.1
\brief   This file provides a the class TaskQueue

\see TaskQueue
*/

namespace NOU::NOU_THREAD
{
	/**
	\brief A namespace that contains a collection of several accumulators that are meant to be used with 
	       TaskQueue.
	*/
	namespace TaskQueueAccumulators
	{
		/**
		\brief A dummy type that is used by the specialization of TaskQueue that works with tasks that return
		\p void. 

		\details
		A dummy type that is used by the specialization of TaskQueue that works with tasks that return \p 
		void. See the detailed section of that specialization for further details (unfortunately, it is not 
		possible to have a link to that class here, sorry for the inconvenience).

		\note
		It does not matter as which type \p Void is defined as it only serves as a dummy. However, it must be 
		any type other than \p void.
		*/
		using Void = int;

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

		\brief An accumulator that returns \p current. As this accumulator does the least work, it is a good 
		       choice if no accumulation should happen.
		*/
		template<typename R>
		NOU_FUNC R forward(R &&previous, R &&current);

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
		NOU_FUNC R addition(R &&previous, R &&current);

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
		NOU_FUNC R additionInverted(R &&previous, R &&current);

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
		NOU_FUNC R subtract(R &&previous, R &&current);

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
		NOU_FUNC R subtractInverted(R &&previous, R &&current);

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
		NOU_FUNC R multiply(R &&previous, R &&current);

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
		NOU_FUNC R multiplyInverted(R &&previous, R &&current);

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
		NOU_FUNC R divide(R &&previous, R &&current);

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
		NOU_FUNC R divideInverted(R &&previous, R &&current);

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
		NOU_FUNC R memberFunction(R &&previous, R &&current);

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
		NOU_FUNC R memberFunctionInverted(R &&previous, R &&current);
	};

	/**
	\tparam R     The result type of the tasks that can be pushed to the queue.
	\tparam I     The type of invocable that can be executed by the tasks that can be pushed to the queue. 
	              This must be an invocable according to IsInvocableR<Result, I, ARGS...>.
	\tparam ACCUM The type of the accumulator that will be used by the queue. This must be an invocable 
	              according to IsInvocableR<Result, Accumulator, Result&&, Result&&>.
	\tparam ARGS  The types of the parameters that will be passed to the invocable in the tasks.

	\brief A class that allows to push multiple tasks to the thread manager in a FIFO-Queue order.

	\details
	A class that allows to push multiple tasks to the thread manager in a FIFO-Queue order. 

	All the tasks in a single task queue share the same error handler. Also, the error handler will not be
	emptied after a task has finished execution. This means, that if one tasks produces an error that is not 
	getting handled by that same task, the error will still be present for the next task.

	It is also possible to use all the tasks in the queue to produce a result. This is done using an 
	accumulator. Such an accumulator is a function of the type Result(Result&&, Result&&), with the first 
	parameter being the "old" result (the result that was accumulated after the last task has finished 
	execution) and the second parameter being the result of the task that has just finished execution. The 
	returned value will be the next "old" result. 
	The accumulator is always executed after a task has finished execution. 
	The namespace nostra::utils::thread::TaskQueueAccumulators has a variety of predefined accumulators. If 
	no accumulator is needed, TaskQueueAccumulators::forward is a good choice as it always passes down the 
	latest result (the result of the task that just finished execution). It is not possible to have no 
	accumulator at all.

	\note 
	This documentation is only those tasks that have a return type other than void. For a documentation of the
	specialization that is used when the result type is void, see TaskQueue<void, I, ACCUM, ARGS>. 
	*/
	template<typename R, typename I, typename ACCUM = 
		TaskQueueAccumulators::FunctionPtr<
			NOU_CORE::typeIf_t<
				NOU_CORE::AreSame<R, void>::value, 
					TaskQueueAccumulators::Void, R>>,
		typename... ARGS>
	class NOU_CLASS TaskQueue
	{
	public:
		/**
		\brief The type of the accumulator.
		*/
		using Accumulator = ACCUM;

		/**
		\brief The result type.
		*/
		using Result = R;

		/**
		\brief The type of task that can be processed by this task queue.
		*/
		using Task = Task<Result, I, ARGS...>;

		static_assert(NOU_CORE::IsInvocableR<Result, I, ARGS...>::value);
		static_assert(NOU_CORE::IsInvocableR<Result, Accumulator, Result&&, Result&&>::value);

		/**
		\brief The capacity that the queue has by default.
		*/
		static constexpr sizeType DEFAULT_INITIAL_CAPACITY = 1;

	private:
		/**
		\brief The type of a wrapper task that is used to execute the tasks pushed to the queue.

		\details
		For details on why this wrapper task is required, see the detailed section of executeTask().
		*/
		using ExecutionTask = NOU_THREAD::Task<void, void(*)(TaskQueue*), TaskQueue*>;

		/**
		\brief A function that executes the tasks in the queue.

		\details
		This function is required, because the task queue has to do some additional stuff before and after 
		executing the tasks that were pushed to the queue (like accumulating the result and executing the next
		task).
		*/
		static void executeTask(TaskQueue *taskQueue);

		/**
		\brief The mutex that is used to lock the access to m_taskQueue.
		*/
		Mutex                              m_taskQueueMutex;

		/**
		\brief The mutex that is used to lock the access to m_currentTask.
		*/
		Mutex                              m_currentTaskMutex;

		/**
		\brief The mutex that is used to lock the access to m_result.
		*/
		Mutex                              m_resultMutex;

		/**
		\brief A mutex that is used to synchronize the method getResult() with the execution task.
		*/
		Mutex                              m_getResultMutex;

		/**
		\brief A state that is used to synchronize the method getResult() with the execution task.
		*/
		boolean                            m_isExecuting;

		/**
		\brief A condition variable that is used to synchronize the method getResult() with the execution 
		       task.
		*/
		ConditionVariable                  m_getResultVariable;

		/**
		\brief The accumulator that will be used to accumulate the results of the tasks.
		*/
		Accumulator                        m_accumulator;

		/**
		\brief The queue that stores the tasks that will be executed.
		*/
		NOU_DAT_ALG::FastQueue<Task>       m_taskQueue;

		/**
		\brief The task that is currently in execution (or will be executed next).

		\details
		The task that is currently in execution (or will be executed next). This is required because for the 
		duration of the execution the task is not allowed to change it's position in the memory (which might 
		happen if the task is still in the queue and the queue has to do reallocations).
		*/
		NOU_DAT_ALG::Uninitialized<Task>   m_currentTask;

		/**
		\brief The current result.
		*/
		NOU_DAT_ALG::Uninitialized<Result> m_result;

		/**
		\brief The error handler that will be used by this task queue.
		*/
		NOU_CORE::ErrorHandler             m_handler;

		/**
		\brief True if the queue is closed, false if not.
		*/
		boolean                            m_closed;

		/**
		\brief True if the next tasks should still be executed in a different thread, false if not.

		\details
		True if the next tasks should still be executed in a different thread, false if not. This is used by
		getResult() to stop the queue from pushing the tasks to the thread manager because it will execute the
		tasks immediately in the thread that getResult() was called from.
		*/
		boolean                            m_stopParallelExecution;

		/**
		\brief The task that will actually be pushed to the thread manager to execute the tasks that were 
		pushed to the queue.

		\details
		The task that will actually be pushed to the thread manager to execute the tasks that were pushed to 
		the queue. For details on why this is required, see the detailed section of executeTask().
		*/
		ExecutionTask                      m_executionTask;

		/**
		\pre Lock m_currentTaskMutex and m_taskQueueMutex.

		\brief Checks if the current task is done executing and if it is, schedules the next task for 
		       execution.

		\details
		Checks if the current task is done executing and if it is, schedules the next task for execution. The 
		current task counts as done, as soon <tt> m_currentTask.isValid() </tt> returns false.
		*/
		void updateExecutingTask();

		/**
		\param current The result that was produced and should now be accumulated.

		\brief Accumulates the old result with \p current.
		*/
		void accumulate(Result &&current);

	public:
		/**
		\param accumulator     The accumulator that will be used by the task queue.
		\param initialCapacity The capacity that the internal queue that stores the tasks will have.

		\brief Constructs a new instance with the passed parameters.
		*/
		TaskQueue(Accumulator &&accumulator, sizeType initialCapacity = DEFAULT_INITIAL_CAPACITY);

		/**
		\param task The task to push.

		\brief Pushes a new task to the queue.
		*/
		TaskQueue& pushTask(Task &&task);

		/**
		\return The current, temporary result.

		\brief Returns the currently stored, temporary result.

		\details
		Returns the currently stored, temporary result. Unlike getResult(), this method does not force the
		execution of all tasks that are currently in the queue, but returns the result that was produced by 
		the last accumulation.

		\note
		This function may be expensive, as the result will be copied instead of moved or returned by
		reference. This is required because the internally stored result may be overridden at any time by
		a task that has just finished execution.

		\warning
		If the return type of the task type that this task queue executes is void, this method will return 
		void too. This may be a problem in code like this:
		\code
		auto result = task.getResult(); //task is a AsyncTaskResult in this case.
		\endcode

		Implementation detail:
		It is not actually this method that will change the return type, in fact there is an entire 
		specialization for invocables that return \p void. This specialization is not documented in this
		Doxygen documentation but it behaves exactly like this class does.
		
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

	/**
	\tparam I     The type of invocable that can be executed by the tasks that can be pushed to the queue.
	              This must be an invocable according to IsInvocableR<void, I, ARGS...>.
	\tparam ACCUM A dummy parameter that has no effect (it only has an effect if the result type is not void).
	\tparam ARGS  The types of the parameters that will be passed to the invocable in the tasks.

	\brief A class that allows to push multiple tasks to the thread manager in a FIFO-Queue order.

	\details
	A class that allows to push multiple tasks to the thread manager in a FIFO-Queue order.

	All the tasks in a single task queue share the same error handler. Also, the error handler will not be
	emptied after a task has finished execution. This means, that if one tasks produces an error that is not
	getting handled by that same task, the error will still be present for the next task.

	Since there is no result produced by the tasks in this queue, no accumulation takes place (to enable 
	compatibility with the class that is used when the return type is not void, there are still all the 
	parameters and functionality that would use accumulators, however they do not affect the class at all).

	\note
	This documentation is only those tasks that have the return type void. For a documentation of the class 
	that is used when the result type is not void, see TaskQueue.
	*/
	template<typename I, typename ACCUM, typename... ARGS>
	class NOU_CLASS TaskQueue<void, I, ACCUM, ARGS...>
	{
	public:
		/**
		\brief The type of the accumulator (could be any type).
		*/
		using Accumulator = ACCUM;

		/**
		\brief The result type. For this specialization, it is hard wired to void.
		*/
		using Result = void;

		/**
		\brief The type of task that can be processed by this task queue.
		*/
		using Task = Task<Result, I, ARGS...>;

		static_assert(NOU_CORE::IsInvocableR<Result, I, ARGS...>::value);

		/**
		\brief The capacity that the queue has by default.
		*/
		static constexpr sizeType DEFAULT_INITIAL_CAPACITY = 1;

	private:
		/**
		\brief The type of a wrapper task that is used to execute the tasks pushed to the queue.

		\details
		For details on why this wrapper task is required, see the detailed section of executeTask().
		*/
		using ExecutionTask = NOU_THREAD::Task<void, void(*)(TaskQueue*), TaskQueue*>;

		/**
		\brief A function that executes the tasks in the queue.

		\details
		This function is required, because the task queue has to do some additional stuff before and after
		executing the tasks that were pushed to the queue (like executing the next task).
		*/
		static void executeTask(TaskQueue *taskQueue);

		/**
		\brief The mutex that is used to lock the access to m_taskQueue.
		*/
		Mutex                              m_taskQueueMutex;

		/**
		\brief The mutex that is used to lock the access to m_currentTask.
		*/
		Mutex                              m_currentTaskMutex;

		/**
		\brief A mutex that is used to synchronize the method getResult() with the execution task.
		*/
		Mutex                              m_getResultMutex;

		/**
		\brief A state that is used to synchronize the method getResult() with the execution task.
		*/
		boolean                            m_isExecuting;

		/**
		\brief A condition variable that is used to synchronize the method getResult() with the execution 
		       task.
		*/
		ConditionVariable                  m_getResultVariable;

		/**
		\brief The queue that stores the tasks that will be executed.
		*/
		NOU_DAT_ALG::FastQueue<Task>       m_taskQueue;

		/**
		\brief The task that is currently in execution (or will be executed next).

		\details
		The task that is currently in execution (or will be executed next). This is required because for the
		duration of the execution the task is not allowed to change it's position in the memory (which might
		happen if the task is still in the queue and the queue has to do reallocations).
		*/
		NOU_DAT_ALG::Uninitialized<Task>   m_currentTask;

		/**
		\brief The error handler that will be used by this task queue.
		*/
		NOU_CORE::ErrorHandler             m_handler;

		/**
		\brief True if the queue is closed, false if not.
		*/
		boolean                            m_closed;

		/**
		\brief True if the next tasks should still be executed in a different thread, false if not.

		\details
		True if the next tasks should still be executed in a different thread, false if not. This is used by
		getResult() to stop the queue from pushing the tasks to the thread manager because it will execute the
		tasks immediately in the thread that getResult() was called from.
		*/
		boolean                            m_stopParallelExecution;

		/**
		\brief The task that will actually be pushed to the thread manager to execute the tasks that were
		pushed to the queue.

		\details
		The task that will actually be pushed to the thread manager to execute the tasks that were pushed to
		the queue. For details on why this is required, see the detailed section of executeTask().
		*/
		ExecutionTask                      m_executionTask;

		/**
		\pre Lock m_currentTaskMutex and m_taskQueueMutex.

		\brief Checks if the current task is done executing and if it is, schedules the next task for
		execution.

		\details
		Checks if the current task is done executing and if it is, schedules the next task for execution. The
		current task counts as done, as soon <tt> m_currentTask.isValid() </tt> returns false.
		*/
		void updateExecutingTask();

	public:
		/**
		\param accumulator     A dummy parameter without any effect. This is just here for compatibility with 
		                       the class that uses any non-void type as result type.
		\param initialCapacity The capacity that the internal queue that stores the tasks will have.

		\brief Constructs a new instance with the passed parameters.
		*/
		TaskQueue(Accumulator &&accumulator, sizeType initialCapacity = DEFAULT_INITIAL_CAPACITY);

		/**
		\param initialCapacity The capacity that the internal queue that stores the tasks will have.

		\brief Constructs a new instance with the passed initial capacity.
		*/
		TaskQueue(sizeType initialCapacity = DEFAULT_INITIAL_CAPACITY);

		TaskQueue& pushTask(Task &&task);

		/**
		\brief Since there is no result being produced, this method has no effect and only server 
		       compatibility purposes.
		*/
		void getTemporaryResult();

		/**
		\brief Executes all the remaining tasks in the queue.

		\details
		Executes all the remaining tasks in the queue. If there is currently already a task in execution and 
		there are other tasks still waiting in the queue, those tasks will be executed in getResult() (by the 
		thread that called that method).

		\warning
		If there is another thread continuously pushing tasks to the queue while another thread called
		getResult(), getResult() will not finish (unless the pushing thread stops pushing tasks). One way to
		avoid that, is using close() (Note that if the other thread keeps pushing after close() has been
		called, the error handler will be filled up with errors if they are not handled).
		*/
		void getResult();

		/**
		\brief Closes the queue. This prevents from any tasks getting pushed to it.

		\details
		Closes the queue. This prevents from any tasks getting pushed to it. In this specialization, this 
		method serves no purpose, as it is usually used to make getResult() return a reference to an object in
		a consistent state (getResult() returns nothing in this specialization).

		If a queue has been closed and pushTask() is called anyway, the error handler will be set to
		ErrorCodes::INVALID_STATE.
		*/
		void close();
	};

	///\cond

	namespace TaskQueueAccumulators
	{
		template<typename R>
		NOU_FUNC R forward(R &&previous, R &&current)
		{
			return NOU_CORE::move(current);
		}

		template<typename R>
		NOU_FUNC R addition(R &&previous, R &&current)
		{
			return NOU_CORE::move(previous) + NOU_CORE::move(current);
		}

		template<typename R>
		NOU_FUNC R additionInverted(R &&previous, R &&current)
		{
			return addAccum(NOU_CORE::move(current), NOU_CORE::move(previous));
		}

		template<typename R>
		NOU_FUNC R subtract(R &&previous, R &&current)
		{
			return NOU_CORE::move(previous) - NOU_CORE::move(current);
		}

		template<typename R>
		NOU_FUNC R subtractInverted(R &&previous, R &&current)
		{
			return subAccum(NOU_CORE::move(current), NOU_CORE::move(previous));
		}

		template<typename R>
		NOU_FUNC R multiply(R &&previous, R &&current)
		{
			return NOU_CORE::move(previous) * NOU_CORE::move(current);
		}

		template<typename R>
		NOU_FUNC R multiplyInverted(R &&previous, R &&current)
		{
			return mulAccum(NOU_CORE::move(current), NOU_CORE::move(previous));
		}

		template<typename R>
		NOU_FUNC R divide(R &&previous, R &&current)
		{
			return NOU_CORE::move(previous) / NOU_CORE::move(current);
		}

		template<typename R>
		NOU_FUNC R divideInverted(R &&previous, R &&current)
		{
			return divAccum(NOU_CORE::move(current), NOU_CORE::move(previous));
		}

		template<typename R, R(R::*FUNC)(R&&)>
		NOU_FUNC R memberFunction(R &&previous, R &&current)
		{
			return (previous.*FUNC)(NOU_CORE::move(current));
		}

		template<typename R, R(R::*FUNC)(R&&)>
		NOU_FUNC R memberFunctionInverted(R &&previous, R &&current)
		{
			return (current.*FUNC)(NOU_CORE::move(previous));
		}
	}

	template<typename R, typename I, typename ACCUM, typename... ARGS>
	void TaskQueue<R, I, ACCUM, ARGS...>::executeTask(TaskQueue<R, I, ACCUM, ARGS...> *taskQueue)
	{
		taskQueue->m_isExecuting = true;

		NOU_DAT_ALG::Uninitialized<Task> tempTask;

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

		boolean stopParalleExecution;

		{
			Lock lock(taskQueue->m_getResultMutex);
			stopParalleExecution = taskQueue->m_stopParallelExecution;
		}

		if (!stopParalleExecution)
		{
			Lock taskQueueLock(taskQueue->m_taskQueueMutex);
			Lock currentTaskLock(taskQueue->m_currentTaskMutex);

			taskQueue->m_currentTask.destroy();

			taskQueue->updateExecutingTask();
		}
		else
		{
			taskQueue->m_getResultVariable.notifyAll();
		}

		taskQueue->m_isExecuting = false;
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
		{
			Lock lock(m_getResultMutex);
			m_stopParallelExecution = true;
		}

		{
			Mutex mutex;
			UniqueLock lock(mutex);
			m_getResultVariable.wait(lock, [this]() { return !(this->m_isExecuting); });
		}

		{
			Lock lock(m_taskQueueMutex);

			while (m_taskQueue.size() != 0)
			{
				Task task = m_taskQueue.popFront();
				task.execute();

				accumulate(task.moveResult());
			}
		}

		{
			Lock lock(m_getResultMutex);
			m_stopParallelExecution = false;
		}

		return *m_result;
	}

	template<typename R, typename I, typename ACCUM, typename... ARGS>
	void TaskQueue<R, I, ACCUM, ARGS...>::close()
	{
		m_closed = true;
	}




	template<typename I, typename ACCUM, typename... ARGS>
	void TaskQueue<void, I, ACCUM, ARGS...>::executeTask(TaskQueue<void, I, ACCUM, ARGS...> *taskQueue)
	{
		taskQueue->m_isExecuting = true;

		NOU_DAT_ALG::Uninitialized<Task> tempTask;

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

		boolean stopParallelExecution;

		{
			Lock lock(taskQueue->m_getResultMutex);
			stopParallelExecution = taskQueue->m_stopParallelExecution;
		}

		if (!stopParallelExecution)
		{
			Lock taskQueueLock(taskQueue->m_taskQueueMutex);
			Lock currentTaskLock(taskQueue->m_currentTaskMutex);

			taskQueue->m_currentTask.destroy();

			taskQueue->updateExecutingTask();
		}
		else
		{
			taskQueue->m_getResultVariable.notifyAll();
		}

		taskQueue->m_isExecuting = false;
	}

	template<typename I, typename ACCUM, typename... ARGS>
	TaskQueue<void, I, ACCUM, ARGS...>::TaskQueue(Accumulator &&accumulator, sizeType initialCapacity) :
		TaskQueue(initialCapacity)
	{}

	template<typename I, typename ACCUM, typename... ARGS>
	TaskQueue<void, I, ACCUM, ARGS...>::TaskQueue(sizeType initialCapacity) :
		m_taskQueue(initialCapacity),
		m_closed(false),
		m_stopParallelExecution(false),
		m_executionTask(&executeTask, this)
	{}

	template<typename I, typename ACCUM, typename... ARGS>
	void TaskQueue<void, I, ACCUM, ARGS...>::updateExecutingTask()
	{
		if (!m_currentTask.isValid() && m_taskQueue.size() > 0)
		{
			m_currentTask = m_taskQueue.popFront();
			getThreadManager().pushTask(&m_executionTask, 0, &m_handler);
		}
	}

	template<typename I, typename ACCUM, typename... ARGS>
	TaskQueue<void, I, ACCUM, ARGS...>& TaskQueue<void, I, ACCUM, ARGS...>::pushTask(Task &&task)
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

	template<typename I, typename ACCUM, typename... ARGS>
	void TaskQueue<void, I, ACCUM, ARGS...>::getTemporaryResult()
	{}

	template<typename I, typename ACCUM, typename... ARGS>
	void TaskQueue<void, I, ACCUM, ARGS...>::getResult()
	{
		{
			Lock lock(m_getResultMutex);
			m_stopParallelExecution = true;
		}

		{
			Mutex mutex;
			UniqueLock lock(mutex);
			m_getResultVariable.wait(lock, [this]() { return !(this->m_isExecuting); });
		}

		{
			Lock lock(m_taskQueueMutex);

			while (m_taskQueue.size() != 0)
			{
				Task task = m_taskQueue.popFront();
				task.execute();
			}
		}

		{
			Lock lock(m_getResultMutex);
			m_stopParallelExecution = false;
		}
	}

	template<typename I, typename ACCUM, typename... ARGS>
	void TaskQueue<void, I, ACCUM, ARGS...>::close()
	{
		m_closed = true;
	}

///\endcond
}

#endif