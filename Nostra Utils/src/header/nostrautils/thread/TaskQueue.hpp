#ifndef	NOU_THREAD_TASK_QUEUE_HPP
#define NOU_THREAD_TASK_QUEUE_HPP

#include "nostrautils\thread\ThreadManager.hpp"
#include "nostrautils\thread\Task.hpp"
#include "nostrautils\dat_alg\FastQueue.hpp"
#include "nostrautils\core\Utils.hpp"

namespace NOU::NOU_THREAD
{
	template<typename ACCUM, typename R, typename I, typename... ARGS>
	class TaskQueue final
	{
	public:
		using Accumulator = ACCUM;
		using TaskType = Task<R, I, ARGS...>;
		using ResultType = typename TaskType::ResultType;
		using TaskId = uint64;

	private:
		NOU_DAT_ALG::FastQueue<TaskType> m_queue;
		TaskId m_nextId;

	public:
		TaskQueue();

		TaskQueue(const TaskQueue&) = delete;
		TaskQueue(TaskQueue&&) = delete;
		TaskQueue() = default; //notify thread mngr of deletion ?

		TaskId pushTask(TaskType &&task);

		void removeTask(TaskId);

		ResultType& getResult();
		const ResultType& getResult() const;
		
		ResultType& getCurrentResult();
		const ResultType& getCurrentResult() const;

		void setAccumulator(Accumulator &&accumulator);
		const Accumulator& getAccumulator() const;
	};

	template<typename ACCUM, typename R, typename I, typename... ARGS>
	typename TaskQueue<ACCUM, R, I, ARGS...>::TaskId TaskQueue<ACCUM, R, I, ARGS...>::
		pushTask(TaskQueue<ACCUM, R, I, ARGS...>::TaskType &&task)
	{
		m_queue.pushBack(NOU_CORE::forward<TaskType>(task));
	}
}

#endif