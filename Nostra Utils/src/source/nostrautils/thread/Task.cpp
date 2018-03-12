#include "nostrautils\thread\Task.hpp"

namespace NOU::NOU_THREAD
{
	AbstractTask::AbstractTask() :
		m_state(State::NOT_STARTED)
	{}

	void AbstractTask::reset()
	{
		if (m_state == State::DONE)
			m_state = State::NOT_STARTED;
	}

	typename AbstractTask::State AbstractTask::getState() const
	{
		return m_state;
	}
}