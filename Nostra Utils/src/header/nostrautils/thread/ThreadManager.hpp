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

			ThreadDataBundle(ThreadWrapper &&thread);

			ThreadDataBundle(ThreadDataBundle&& tdb);
		};

		static void threadLoop(ThreadManager *threadManager, ThreadDataBundle **threadData, 
			Mutex *startupMutex, ConditionVariable *startupVariable);

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

		void enqueueTask(AbstractTask *task, int32 priority, NOU_CORE::ErrorHandler *handler);

		boolean addThread();

		void executeTaskWithThread(TaskErrorHandlerPair task, ThreadDataBundle &thread);
	public:
		~ThreadManager();

		//if handler == nullptr, an error handler from the handler pool will be used
		void pushTask(AbstractTask *task, int32 priority, NOU_CORE::ErrorHandler *handler = nullptr); 
		void giveBackThread(ThreadDataBundle &thread);
	};
}

#endif