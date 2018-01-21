#ifndef	NOU_THREAD_TASK_QUEUE_HPP
#define NOU_THREAD_TASK_QUEUE_HPP

#include "nostrautils\thread\ThreadManager.hpp"
#include "nostrautils\thread\Task.hpp"
#include "nostrautils\dat_alg\FastQueue.hpp"
#include "nostrautils\core\Utils.hpp"
#include "nostrautils\dat_alg\Uninitialized.hpp"

namespace NOU::NOU_THREAD
{
	template<typename ACCUM, typename R, typename I, typename... ARGS>
	class TaskQueue final
	{
		static_assert(NOU_CORE::IsInvocableR<R, ACCUM, const R&, const R&>::value);

	public:
		using Accumulator = ACCUM;
		using TaskType = Task<R, I, ARGS...>;
		using ResultType = typename TaskType::ResultType;

	private:
		Accumulator m_accumulator;
		NOU_DAT_ALG::FastQueue<Task> m_queue;
		TaskId m_nextId;
		NOU_DAT_ALG::Uninitialized<ResultType> m_result;

	public:
		TaskQueue();

		TaskQueue(const TaskQueue&) = delete;
		TaskQueue(TaskQueue&&) = delete;
		TaskQueue() = default; //notify thread mngr of deletion ?

		void pushTask(TaskType &&task);

		ResultType& getResult();
		const ResultType& getResult() const;
		
		ResultType& getCurrentResult();
		const ResultType& getCurrentResult() const;

		void setAccumulator(Accumulator &&accumulator);
		const Accumulator& getAccumulator() const;
	};

	template<typename ACCUM, typename R, typename I, typename... ARGS>
	void TaskQueue<ACCUM, R, I, ARGS...>::pushTask(TaskType &&task)
	{
		m_queue.pushBack(NOU_CORE::forward<TaskType>(task));
	}

	template<typename ACCUM, typename R, typename I, typename... ARGS>
	typename TaskQueue<ACCUM, R, I, ARGS...>::ResultType& TaskQueue<ACCUM, R, I, ARGS...>::getResult()
	{
		//wait for queue to be finished
		return *m_result;
	}

	template<typename ACCUM, typename R, typename I, typename... ARGS>
	const typename TaskQueue<ACCUM, R, I, ARGS...>::ResultType& 
		TaskQueue<ACCUM, R, I, ARGS...>::getResult() const
	{
		//wait for queue to be finished
		return *m_result;
	}

	template<typename ACCUM, typename R, typename I, typename... ARGS>
	typename TaskQueue<ACCUM, R, I, ARGS...>::ResultType& TaskQueue<ACCUM, R, I, ARGS...>::getCurrentResult()
	{
		return *m_result;
	}

	template<typename ACCUM, typename R, typename I, typename... ARGS>
	const typename TaskQueue<ACCUM, R, I, ARGS...>::ResultType&
		TaskQueue<ACCUM, R, I, ARGS...>::getCurrentResult() const
	{
		return *m_result;
	}
}

#endif