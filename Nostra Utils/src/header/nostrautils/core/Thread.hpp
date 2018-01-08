#ifndef NOU_CORE_THREAD_HPP
#define	NOU_CORE_THREAD_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\dat_alg\FastQueue.hpp"
#include "nostrautils\dat_alg\ContainerInterfaces.hpp"

#include <thread>

namespace NOU::NOU_CORE
{
	///\cond
	class Thread;
	///\endcond
	
	using Task = void(*)(void*);


	class TaskQueue : public NOU_DAT_ALG::Queue<Task>
	{
	private:
		NOU_DAT_ALG::FastQueue<Task> m_tasks;

	public:
		void push(const Task &task);

		const Task& peek() const override;
		Task& peek() override;
	
		Task pop() override;

		void allowParallelExecution();
	};

	class Thread
	{
	public:
		using UnderlyingType = std::thread;

	private:
		UnderlyingType m_thread;
		//error handler ref

	public:
		const UnderlyingType& getUnderlyingThread() const;
		UnderlyingType& getUnderlyingThread();

		void sleepUntilWoken();
		void wakeUp();
	};

	class ThreadManager
	{

	};
}

#endif