#ifndef	NOU_THREAD_THREAD_MANAGER_HPP
#define	NOU_THREAD_THREAD_MANAGER_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\Pointer.hpp"
#include "nostrautils\core\ErrorHandler.hpp"
#include "nostrautils\dat_alg\Utils.hpp"
#include "nostrautils\thread\ThreadWrapper.hpp"
#include "nostrautils\thread\Task.hpp"
#include "nostrautils\thread\Mutex.hpp"
#include "nostrautils\thread\ConditionVariable.hpp"

#include <iostream>

///\cond
namespace NOU::NOU_DAT_ALG
{
	namespace internal
	{
		template<typename T>
		class ObjectPoolChunk;
	}

	template<typename T>
	class ObjectPool;

	template<typename T>
	class BinaryHeap;

}
///\endcond

#define private public

namespace NOU::NOU_THREAD
{
	class ThreadManager;

	NOU_FUNC ThreadManager& getThreadManager();

	class NOU_CLASS ThreadManager
	{
	//Parts responsible for creating the singleton
	private:
	//	static ThreadManager s_instance;

		ThreadManager();
		ThreadManager(const ThreadManager&) = delete;
		ThreadManager(ThreadManager&&) = delete;

	public:
		static ThreadManager& getInstance();
	//End of singleton parts

		/*
		* Since BinaryHeap.hpp can not be included at this point, uint32 is used instead of
		* BinaryHeap::PriorityTypePart. If the type of BinaryHeap::PriorityTypePart is ever changed, this
		* must be changed too. The constructor of ThreadManager contains a static_assert to check
		* whether the types still match.
		*/
		using Priority = uint32;

		class TaskInformation
		{
			friend class ThreadManager;

		private:
			constexpr static Priority INVALID_ID = -1;

			Priority m_id;

			/*
			 * should only be constructed by ThreadManager (which is possible b/c ThreadManager is a friend of 
			 * TaskInformation).
			 */
			explicit TaskInformation(Priority id);

		public:
			TaskInformation();
		};

		//TaskInformation needs access to m_tasks to check whether a task is in it or not
		friend class TaskInformation;

		/**
		\brief The amount of threads that the manager will work with 
		*/
		uint32 DEFAULT_THREAD_COUNT = 1;

		sizeType DEFAULT_TASK_CAPACITY = 50;

	private:
		template<typename T>
		using ObjectPoolPtr = NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::ObjectPool<T>>;

		NOU_DEFINE_PAIR(TaskErrorHandlerPairTempl, task, handler)

		using TaskErrorHandlerPair = TaskErrorHandlerPairTempl<AbstractTask*, NOU_CORE::ErrorHandler*>;

		struct ThreadDataBundle
		{
			ThreadWrapper thread;
			TaskErrorHandlerPair taskHandlerPair;
			Mutex mutex;
			ConditionVariable variable;
			boolean taskReady;

			ThreadDataBundle(ThreadWrapper &&thread);

			ThreadDataBundle(ThreadDataBundle&& tdb);
		};

		static void threadLoop(ThreadManager *threadManager, ThreadDataBundle **threadData, 
			Mutex *startupMutex, ConditionVariable *startupVariable, boolean *startupDone);

		boolean m_shouldShutdown;

		//Thread Pool
		ObjectPoolPtr<ThreadDataBundle> m_threads;

		//Handler Pool
		ObjectPoolPtr<NOU_CORE::ErrorHandler> m_handlers;

		//Task queue
		NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::BinaryHeap<TaskErrorHandlerPair>> m_tasks;

		ObjectPoolPtr<ThreadDataBundle> makeThreadPool();
		ObjectPoolPtr<NOU_CORE::ErrorHandler> makeHandlerPool();
		NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::BinaryHeap<TaskErrorHandlerPair>> makeTaskHeap();

		Mutex m_threadPoolAccessMutex;
		Mutex m_taskHeapAccessMutex;

		/**
		\pre pushTask() or locking m_taskHeapAccessMutex
		*/
		TaskInformation enqueueTask(AbstractTask *task, int32 priority, NOU_CORE::ErrorHandler *handler);

		/**
		\pre pushTask() or locking m_threadPoolAccessMutex
		*/
		boolean addThread();

		void executeTaskWithThread(TaskErrorHandlerPair task, ThreadDataBundle &threadData);

		void giveBackThread(ThreadDataBundle &thread);
		void giveBackHandler(NOU_CORE::ErrorHandler &handler);
	public:
		~ThreadManager();

		//if handler == nullptr, an error handler from the handler pool will be used
		TaskInformation pushTask(AbstractTask *task, Priority priority, NOU_CORE::ErrorHandler *handler
			= nullptr); 
		boolean removeTask(const TaskInformation &taskInfo);
	};
}

#endif