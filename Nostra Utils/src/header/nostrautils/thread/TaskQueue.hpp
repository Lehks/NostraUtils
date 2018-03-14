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

namespace NOU::NOU_THREAD
{
	class NOU_CLASS AbstractTaskQueue
	{
	public:
	private:
		typename ThreadManager::Priority m_nextPriority;
		NOU_CORE::ErrorHandler m_handler;

	protected:
		void pushNextTask(internal::AbstractTask *task);
	};

	template<typename T>
	using AccumFunc = T(*)(T&&, T&&);

	template<typename R, typename I, typename ACCUM = AccumFunc<R>, typename... ARGS>
	class NOU_CLASS TaskQueue
	{
		static_assert(NOU_CORE::IsInvocableR<R, ACCUM, R&&, R&&>::value);
	
	public:
		using Accumulator = ACCUM;
		using Result = R;
		using Task = Task<Result, I, ARGS...>;

		static constexpr sizeType DEFAULT_INITIAL_CAPACITY = 1;

	private:
		Mutex                              m_taskAccess;
		Accumulator                        m_accumulator;
		NOU_DAT_ALG::FastQueue<Task>       m_taskQueue;
		NOU_DAT_ALG::Uninitialized<Task>   m_currentTask;
		NOU_DAT_ALG::Uninitialized<Result> m_result;

	public:
		TaskQueue(sizeType initialCapacity = DEFAULT_INITIAL_CAPACITY);

		TaskQueue& pushTask(Task &&task);
	};

	template<typename T>
	T nullAccum(T &&previous, T &&current);

	template<typename T>
	T addAccum(T &&previous, T &&current);

	template<typename T>
	T addInvAccum(T &&previous, T &&current);

	template<typename T>
	T subAccum(T &&previous, T &&current);

	template<typename T>
	T subInvAccum(T &&previous, T &&current);

	template<typename T>
	T mulAccum(T &&previous, T &&current);

	template<typename T>
	T mulInvAccum(T &&previous, T &&current);

	template<typename T>
	T divAccum(T &&previous, T &&current);

	template<typename T>
	T divInvAccum(T &&previous, T &&current);

	template<typename T, T(T::*FUNC)(T&&)>
	T memFuncAccum(T &&previous, T &&current);

	template<typename T, T(T::*FUNC)(T&&)>
	T memFuncInvAccum(T &&previous, T &&current);

	template<typename R, typename I, typename ACCUM, typename... ARGS>
	TaskQueue<R, I, ACCUM, ARGS...>::TaskQueue(sizeType initialCapacity) :
		m_taskQueue(initialCapacity)
	{}

	template<typename R, typename I, typename ACCUM, typename... ARGS>
	TaskQueue<R, I, ACCUM, ARGS...>& TaskQueue<R, I, ACCUM, ARGS...>::pushTask(Task &&task)
	{
		Lock lock(m_taskAccess);

		/*
		 * If there is currently no task waiting for execution (is currently being executed), schedule the new 
		 * task for execution
		 */
		if (!m_currentTask.isValid())
		{
			m_currentTask = NOU_CORE::move(task);
		}
		else
		{
			m_taskQueue.push(NOU_CORE::move(task));
		}

		return *this;
	}

	template<typename T>
	T nullAccum(T &&previous, T &&current)
	{
		return NOU_CORE::move(current);
	}

	template<typename T>
	T addAccum(T &&previous, T &&current)
	{
		return NOU_CORE::move(previous) + NOU_CORE::move(current);
	}

	template<typename T>
	T addInvAccum(T &&previous, T &&current)
	{
		return addAccum(NOU_CORE::move(current), NOU_CORE::move(previous));
	}

	template<typename T>
	T subAccum(T &&previous, T &&current)
	{
		return NOU_CORE::move(previous) - NOU_CORE::move(current);
	}

	template<typename T>
	T subInvAccum(T &&previous, T &&current)
	{
		return subAccum(NOU_CORE::move(current), NOU_CORE::move(previous));
	}

	template<typename T>
	T mulAccum(T &&previous, T &&current)
	{
		return NOU_CORE::move(previous) * NOU_CORE::move(current);
	}

	template<typename T>
	T mulInvAccum(T &&previous, T &&current)
	{
		return mulAccum(NOU_CORE::move(current), NOU_CORE::move(previous));
	}

	template<typename T>
	T divAccum(T &&previous, T &&current)
	{
		return NOU_CORE::move(previous) / NOU_CORE::move(current);
	}

	template<typename T>
	T divInvAccum(T &&previous, T &&current)
	{
		return divAccum(NOU_CORE::move(current), NOU_CORE::move(previous));
	}

	template<typename T, T (T::*FUNC)(T&&)>
	T memFuncAccum(T &&previous, T &&current)
	{
		return (previous.*FUNC)(NOU_CORE::move(current));
	}

	template<typename T, T(T::*FUNC)(T&&)>
	T memFuncInvAccum(T &&previous, T &&current)
	{
		return (current.*FUNC)(NOU_CORE::move(current));
	}
}

#endif