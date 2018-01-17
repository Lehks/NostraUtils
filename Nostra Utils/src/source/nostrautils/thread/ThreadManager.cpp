#include "nostrautils\thread\ThreadManager.hpp"

namespace NOU::NOU_THREAD
{
	NOU_FUNC ThreadManager& getThreadManager()
	{
		return ThreadManager::getInstance();
	}

	ThreadManager& ThreadManager::getInstance()
	{
		return s_instance;
	}
}