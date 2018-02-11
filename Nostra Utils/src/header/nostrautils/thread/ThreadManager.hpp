#ifndef	NOU_THREAD_THREAD_MANAGER_HPP
#define	NOU_THREAD_THREAD_MANAGER_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\Pointer.hpp"
#include "nostrautils\core\ErrorHandler.hpp"
#include "nostrautils\thread\ThreadWrapper.hpp"
#include "nostrautils\thread\Task.hpp"
#include "nostrautils\thread\Mutex.hpp"
#include "nostrautils\thread\ConditionVariable.hpp"

///\cond
namespace NOU::NOU_DAT_ALG
{
	template<typename T>
	class ObjectPool;

	template<typename T>
	class BinaryHeap;

	template<typename O, typename T>
	class Pair;
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

		/**
		\brief The amount of threads that the manager will work with 
		*/
		uint32 DEFAULT_THREAD_COUNT = 1;

		sizeType DEFAULT_TASK_CAPACITY = 50;

		using ThreadType = ThreadWrapper;

	private:
		template<typename T>
		using AllocatorType = NOU_MEM_MNGT::GenericAllocationCallback<T>; //abbreviation for the allocator

		template<typename T>
		using ObjectPoolPtr = NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::ObjectPool<T>>;

		static void threadLoop(ThreadManager &manager);

		Mutex m_taskQueueMutex;
		ConditionVariable m_threadLoopVariable;

		ObjectPoolPtr<ThreadType> makeThreadPool();
		ObjectPoolPtr<NOU_CORE::ErrorHandler> makeHandlerPool();
		NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::BinaryHeap<AbstractTask*>> makeTaskHeap();

	public:
		AllocatorType<NOU_DAT_ALG::ObjectPool<ThreadType>::Chunk> m_threadAllocator;
		ObjectPoolPtr<ThreadType> m_threads;

		AllocatorType<NOU_DAT_ALG::ObjectPool<NOU_CORE::ErrorHandler>::Chunk> m_handlerAllocator;
		ObjectPoolPtr<NOU_CORE::ErrorHandler> m_handlers;

		/*
		 * uint64 is the same type as BinaryHeap's priority type, if the priority type ever changes,
		 * this must change too. BinaryHeap::Priority type is not defined at this point, since 
		 * BinaryHeap.hpp is not included.
		 */
		AllocatorType<NOU_DAT_ALG::Pair<uint64, AbstractTask*>> m_taskAllocator;
		NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::BinaryHeap<AbstractTask*>> m_tasks;
	};
}

#endif