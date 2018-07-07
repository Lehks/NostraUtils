#ifndef	NOU_THREAD_THREAD_MANAGER_HPP
#define	NOU_THREAD_THREAD_MANAGER_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/mem_mngt/Pointer.hpp"
#include "nostrautils/core/ErrorHandler.hpp"
#include "nostrautils/dat_alg/Utils.hpp"
#include "nostrautils/thread/ThreadWrapper.hpp"
#include "nostrautils/thread/Task.hpp"
#include "nostrautils/thread/Mutex.hpp"
#include "nostrautils/thread/ConditionVariable.hpp"
#include  "nostrautils/dat_alg/FwdDcl.hpp"

#include <iostream>

/**
\file thread/ThreadManager.hpp

\author  Lukas Reichmann
\version 1.0.1
\since   1.0.0

\brief A file that contains the thread management system of NOU.
*/



namespace NOU::NOU_THREAD
{
	///\cond
	class ThreadManager;
	///\endcond

	/**
	\brief The main way to obtain the thread manager.

	\return The thread manager instance (stored on static memory).
	*/
	NOU_FUNC ThreadManager& getThreadManager();

	/**
	\brief The thread management system that is used by Nostra.

	\details
	The thread management system that is used by Nostra. This class is designed as a singleton and no new 
	thread managers can be constructed by a user. To obtain a reference to an already pre-constructed thread
	manager, getThreadManager() should be used.

	To execute functionality in a different thread, the thread manager uses the Task class.

	\see getThreadManager()
	\see Task
	\see AsyncTaskResult
	\see TaskQueue
	*/
	class ThreadManager
	{
	//Parts responsible for creating the singleton
	private:
	//	static ThreadManager s_instance;

		/**
		\brief The default constructor.

		\warning
		This constructor must always be called from the main thread.
		*/
		NOU_FUNC ThreadManager();

		/**
		\brief Not copy-able.
		*/
		ThreadManager(const ThreadManager&) = delete;

		/**
		\brief Not move-able.
		*/
		ThreadManager(ThreadManager&&) = delete;

	public:
		/**
		\brief Another way to obtain the thread manager instance.

		\details 
		Another way to obtain the thread manager instance. getThreadManager() is the preferred way, simply
		because it is shorter to write.

		However, this method also stores the instance of the thread manager as a local static variable.

		\warning
		The first time that this method is called must be done from the main thread.
		*/
		NOU_FUNC static ThreadManager& get();
	//End of singleton parts

		/**
		\brief The type that is used for the prioritization of different tasks.
		*/
		/*
		* Since BinaryHeap.hpp can not be included at this point, uint32 is used instead of
		* BinaryHeap::PriorityTypePart. If the type of BinaryHeap::PriorityTypePart is ever changed, this
		* must be changed too. The constructor of ThreadManager contains a static_assert to check
		* whether the types still match.
		*/
		using Priority = uint32;

		/**
		\brief A handle-type class that is used to uniquely identify a task that was pushed to the thread
		       manager.

		\details
		A handle-type class that is used to uniquely identify a task that was pushed to the thread manager.
		An instance of this class can be used to e.g. remove a task from the thread manger.
		*/
		class TaskInformation
		{
			friend class ThreadManager;

		private:
			/**
			\brief An ID that always identifies an instance of this class as an invalid handle (aka. if an 
			       instance stores this ID, it will never be on the task heap).
			*/
			constexpr static Priority INVALID_ID = -1;

			/**
			\brief The ID of the task in the task heap.
			*/
			Priority m_id;

			/**
			\param id The ID of the instance.

			\brief Constructs a new instance from the passed id.
			*/
			/*
			 * should only be constructed by ThreadManager (which is possible b/c ThreadManager is a friend of 
			 * TaskInformation).
			 */
			NOU_FUNC explicit TaskInformation(Priority id);

		public:
			/**
			\brief Constructs a new instance with an invalid ID.
			*/
			NOU_FUNC TaskInformation();
		};

		//TaskInformation needs access to m_tasks to check whether a task is in it or not
		friend class TaskInformation;

		/**
		\brief The amount of threads that the manager will work with if ThreadWrapper::maxThreads() returns 0.
		*/
		constexpr static uint32 DEFAULT_THREAD_COUNT = 2;

		/**
		\brief The initial capacity of the task heap.
		*/
		constexpr static sizeType DEFAULT_TASK_CAPACITY = 50;

	private:
		/**
		\tparam The type of elements that is stored in the object pool.

		\brief An abbreviation for a unique pointer to an object pool.
		*/
		template<typename T>
		using ObjectPoolPtr = NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::ObjectPool<T, 
			NOU_MEM_MNGT::GenericAllocationCallback>>;

		NOU_DEFINE_PAIR(TaskErrorHandlerPairTempl, task, handler)

		/**
		\brief A pair of an AbstractTask* and NOU_CORE::ErrorHandler*.
		*/
		using TaskErrorHandlerPair = TaskErrorHandlerPairTempl<internal::AbstractTask*, 
			NOU_CORE::ErrorHandler*>;

		/**
		\brief The data that is always bundled together with a thread.
		*/
		struct ThreadDataBundle
		{
			/**
			\brief The thread handle.
			*/
			ThreadWrapper        m_thread;

			/**
			\brief A pair of the task that will be executed by the thread \p m_thread and the error handler 
			       that will be used during execution.
			*/
			TaskErrorHandlerPair m_taskHandlerPair;

			/**
			\brief The mutex that is used (together with \p m_variable and \p m_taskRead) to make the thread 
			       wait for a new task when no task is available.
			*/
			Mutex                m_mutex;

			/**
			\brief The mutex that is used (together with \p m_mutex and \p m_taskRead) to make the thread
			wait for a new task when no task is available.
			*/
			ConditionVariable    m_variable;

			/**
			\brief The mutex that is used (together with \p m_mutex and \p m_variable) to make the thread
			wait for a new task when no task is available.
			*/
			boolean              m_taskReady;

			/**
			\param thread The thread that is stored by this bundle.

			\brief Constructs a new instance with the passed thread.
			*/
			ThreadDataBundle(ThreadWrapper &&thread);

			/**
			\param tdb The instance to move from.

			\brief Moves the data from \p tdb to the instance that is being constructed by the constructor.
			*/
			ThreadDataBundle(ThreadDataBundle&& tdb);
		};

		/**
		\param threadManager   The thread manager (both phases)
		\param threadData	   The thread data bundle (loop phase)
		\param startupMutex	   The startup mutex to synchronize the startup with the function that starts the 
		                       thread. (startup phase)
		\param startupVariable The startup variable to synchronize the startup with the function that starts 
		                       the thread. (startup phase)
		\param startupDone	   A boolean that is used by \p startupVariable to synchronize the startup with 
		                       the function that starts the thread. (startup phase)

		\brief The method that will be executed by the single threads that are managed by the thread 
		       manager.

		\details
		The method that will be executed by the single threads that are managed by the thread manager. This
		method has two phases: 
		<ul>
			<li>
				The startup phase: All of the data required by the method is being set. This phase uses \p 
				threadData, \p startupMutex \p startupVariable and \p startupDone. These parameters must not 
				be used after the startup phase as they will be invalidated after it.
			</li>
			<li>
				The loop phase: The method will loop until the thread manager tells it to stop and shut down. 
				During this loop the method will :
				<ul>
					<li>Wait for a new task to execute</li>
					<li>Execute that task</li>
				</ul>
			</li>
		</ul> 
		*/
		NOU_FUNC static void threadLoop(ThreadManager *threadManager, ThreadDataBundle **threadData,
			Mutex *startupMutex, ConditionVariable *startupVariable, boolean *startupDone);

		/**
		\brief True, if the thread manager is in the shutdown process. If this value is set to true, the 
		       running threads will stop execution as soon as possible.
		*/
		boolean m_shouldShutdown;

		/**
		\brief The pool that is used to store the threads. This pool can store no more than 
		       ThreadWrapper::maxThreads() (or DEFAULT_THREAD_COUNT) if maxThreads() returns 0.
		*/
		ObjectPoolPtr<ThreadDataBundle> m_threads;

		/**
		\brief The pool that is used to store the error handlers. This pool can store no more than
		ThreadWrapper::maxThreads() (or DEFAULT_THREAD_COUNT) if maxThreads() returns 0.
		*/
		ObjectPoolPtr<NOU_CORE::ErrorHandler> m_handlers;

		/**
		\brief The heap that stores the tasks that will be executed by the thread manager sooner or later.
		*/
		NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::BinaryHeap<TaskErrorHandlerPair>> m_tasks;

		/**
		\brief A map that stores the ID of the different threads with the error handler that is currently
		associated with that thread.
		*/
		NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::HashMap<typename ThreadWrapper::ID, 
			NOU_CORE::ErrorHandler*>> m_handlersMap;

		/**
		\brief Creates the value for \p m_threads.
		*/
		ObjectPoolPtr<ThreadDataBundle> makeThreadPool();

		/**
		\brief Creates the value for \p m_handlers.
		*/
		ObjectPoolPtr<NOU_CORE::ErrorHandler> makeHandlerPool();

		/**
		\brief Creates the value for \p m_tasks.
		*/
		NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::BinaryHeap<TaskErrorHandlerPair>> makeTaskHeap();

		/**
		\brief Creates the value for \p m_handlersMap.
		*/
		NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::HashMap<typename ThreadWrapper::ID, 
			NOU_CORE::ErrorHandler*>> makeHandlersMap();

		/**
		\brief The mutex that is used to control the access to \p m_threads.
		*/
		Mutex m_threadPoolAccessMutex;

		/**
		\brief The mutex that is used to control the access to \p m_threads.
		*/
		Mutex m_taskHeapAccessMutex;

		/**
		\param task     The task to enqueue.
		\param priority The priority to enqueue the task with.
		\param handler  The handler to enqueue the task with.

		\brief Enqueues the passed task with the passed priority and error handler in the task heap.

		\pre pushTask() or locking m_taskHeapAccessMutex
		*/
		NOU_FUNC TaskInformation enqueueTask(internal::AbstractTask *task, int32 priority,
			NOU_CORE::ErrorHandler *handler);

		/**
		\return True, if the adding was successful, false if not.

		\brief If possible, adds a new thread to the thread pool. This is not possible if the thread pool is 
		       already full.

		\pre pushTask() or locking m_threadPoolAccessMutex
		*/
		NOU_FUNC boolean addThread();

		/**
		\param task       The task to execute.
		\param threadData The ThreadDataBundle to execute the task with.

		\brief Executes the passed task with the passed thread.

		\warning 
		The passed thread must not be in the thread pool and it must not already execute another task when
		this method is called.
		*/
		NOU_FUNC void executeTaskWithThread(TaskErrorHandlerPair task, ThreadDataBundle &threadData);

		/**
		\param thread The thread to give back.

		\brief Returns a thread to the thread pool or executes the next task.

		\details
		Returns a thread to the thread or executes the next task. If there is currently a task in the task 
		heap, instead of actually giving back the thread, it will simply tell the thread to execute that task.
		*/
		NOU_FUNC void giveBackThread(ThreadDataBundle &thread);

		/**
		\brief Returns the passed handler to the handler pool.
		*/
		NOU_FUNC void giveBackHandler(NOU_CORE::ErrorHandler &handler);
	public:
		/**
		\brief Destructs the thread manager and shuts down all the threads that are currently running.
		*/
		NOU_FUNC ~ThreadManager();

		/**
		\param task     The task to push.
		\param priority The priority of the task.
		\param handler  The handler that is used by the task during execution. If a nullptr is passed, an
		                error handler will be provided by the thread manager (it is not possible to access 
						such a provided error handler after the task has been completed).

		\brief Pushes a task to the thread manager.

		\warning 
		This method is supposed to be used a sort of a "back end" for functionality (like AsyncTaskResult).

		\note
		If there is no thread available at the point of calling this method and it is possible for the thread
		manager to create another thread, then the thread manager will do so. However, creating a thread is
		not light-weight (there have several dynamic allocations to be done) and it should not be done in a 
		time critical context. To manually create more threads than the thread manager would on its own, 
		prepareThread() can be used.
		*/	
		NOU_FUNC TaskInformation pushTask(internal::AbstractTask *task, Priority priority,
			NOU_CORE::ErrorHandler *handler = nullptr); 

		/**
		\param taskInfo The task information that was returned by pushTask().

		\brief Removes a task from the thread manager.

		\warning 
		As pushTask(), this method is supposed to be used a sort of a "back end" for functionality.
		*/
		NOU_FUNC boolean removeTask(const TaskInformation &taskInfo);

		/**
		\return The maximum amount of threads that is available if no threads are idling.

		\brief Returns the maximum amount of threads that is available if no threads are idling.
		*/
		NOU_FUNC sizeType maximumAvailableThreads() const;

		/**
		\return The amount of threads that are currently idling (this includes threads that were not created 
		        yet, but that could be created if needed).

		\brief Returns the amount of threads that are currently idling (this includes threads that were not 
		       created yet, but that could be created if needed).

		\note
		The returned value can be viewed as more of a hint, since after the method has returned, another 
		thread might e.g. finish execution and change the value that is returned by the method.
		*/
		//no need to be const, thread manger is always obtainable as non-const reference
		NOU_FUNC sizeType currentlyAvailableThreads();

		/**
		\return The amount of threads that are prepared and idling.

		\brief Returns the amount of threads that are prepared and idling.

		\note 
		The returned value can be viewed as more of a hint, since after the method has returned, another 
		thread might prepare an additional thread.
		*/
		NOU_FUNC sizeType currentlyPreparedThreads();

		/**
		\param id The id of the thread to get the handler of.
		\return The error handler of the thread with the passed ID.

		\brief Returns the error handler of the thread with the passed ID.
		*/
		NOU_FUNC NOU_CORE::ErrorHandler& getErrorHandlerByThreadId(ThreadWrapper::ID id);

		/**
		\param count The amount of threads to prepare.

		\return The amount of threads that were actually prepared.

		\brief Forces the thread manager to try and create new threads that will wait for tasks to execute.

		\details
		Forces the thread manager to try and create new threads that will wait for tasks to execute. This is
		useful if, e.g. multiple tasks should be executed as fast as possible. In that case, it would be 
		possible to prepare the required threads before the time critical execution starts.
		*/
		NOU_FUNC sizeType prepareThread(sizeType count = 1);
	};
}

#endif