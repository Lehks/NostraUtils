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

namespace NOU::NOU_THREAD
{
	class ThreadManager;

	NOU_FUNC ThreadManager& getThreadManager();

	class NOU_CLASS ThreadManager
	{
	//Parts responsible for creating the singleton
	private:
		static ThreadManager s_instance;

		ThreadManager();
		ThreadManager(const ThreadManager&) = delete;
		ThreadManager(ThreadManager&&) = delete;

	public:
		static ThreadManager& getInstance();
	//End of singleton parts

		struct ThreadHandlerBundle
		{
			/**
			\brief The thread that is used by this bundle.
			*/
			ThreadWrapper m_thread;

			/**
			\brief The error handler that is currently in use by this bundle.
			*/
			NOU_CORE::ErrorHandler *m_handler;
		
			/**
			\param thread The thread that will be used by this bundle.

			\brief Constructs a new instance that uses the passed thread. The error remains unset.
			*/
			ThreadHandlerBundle(ThreadWrapper &&thread);
		};

		/**
		\brief The amount of threads that the manager will work with 
		*/
		uint32 DEFAULT_THREAD_COUNT = 1;

		sizeType DEFAULT_TASK_CAPACITY = 50;

		using ThreadType = ThreadHandlerBundle;

	private:
		template<typename T>
		using AllocatorType = NOU_MEM_MNGT::GenericAllocationCallback<T>; //abbreviation for the allocator

		template<typename T>
		using ObjectPoolPtr = NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::ObjectPool<T>>;

		NOU_DEFINE_PAIR(TaskErrorHandlerPairTempl, task, handler)

		using TaskErrorHandlerPair = TaskErrorHandlerPairTempl<AbstractTask*, NOU_CORE::ErrorHandler*>;

//		using TaskErrorHandlerPair = NOU_DAT_ALG::Pair<AbstractTask*, NOU_CORE::ErrorHandler*>;

		static void threadLoop(boolean *shouldShutdown, TaskErrorHandlerPair *taskHandlerPair);

		//Thread Pool
		AllocatorType<NOU_DAT_ALG::internal::ObjectPoolChunk<ThreadType>> m_threadAllocator;
		ObjectPoolPtr<ThreadType> m_threads;

		//Handler Pool
		AllocatorType<NOU_DAT_ALG::internal::ObjectPoolChunk<NOU_CORE::ErrorHandler>> m_handlerAllocator;
		ObjectPoolPtr<NOU_CORE::ErrorHandler> m_handlers;

		/*
		 * uint64 is the same type as BinaryHeap's priority type, if the priority type ever changes,
		 * this must change too. BinaryHeap::Priority type is not defined at this point, since 
		 * BinaryHeap.hpp is not included.
		 */
		AllocatorType<NOU_DAT_ALG::Pair<uint64, TaskErrorHandlerPair>> m_taskAllocator;
		NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::BinaryHeap<TaskErrorHandlerPair>> m_tasks;

		ObjectPoolPtr<ThreadType> makeThreadPool();
		ObjectPoolPtr<NOU_CORE::ErrorHandler> makeHandlerPool();
		NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::BinaryHeap<TaskErrorHandlerPair>> makeTaskHeap();

		Mutex m_threadPoolAccessMutex;

		void pushTask(AbstractTask *task, int32 priority, NOU_CORE::ErrorHandler *handler = nullptr); //if nullptr, any error handler will be used
		void enqueueTask(AbstractTask *task, int32 priority, NOU_CORE::ErrorHandler *handler);

		void executeTaskWithThread(TaskErrorHandlerPair task, ThreadType &thread);
	public:
		~ThreadManager();

		void giveBackThread(ThreadType &thread);
	};
}

#endif