#ifndef	NOU_THREAD_THREAD_MANAGER_HPP
#define	NOU_THREAD_THREAD_MANAGER_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\core\ErrorHandler.hpp"

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

	public:
		using ThreadType = int; //temporary thread type

		NOU_DAT_ALG::Vector<ThreadType> m_threads;
		NOU_DAT_ALG::Vector<NOU_CORE::ErrorHandler> m_handlers;
	};
}

#endif