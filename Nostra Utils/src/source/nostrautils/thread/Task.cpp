#include "nostrautils\thread\Task.hpp"

namespace NOU::NOU_THREAD
{
	internal::AbstractTask::AbstractTask() :
		m_state(State::NOT_STARTED)
	{}

	void internal::AbstractTask::reset()
	{
		if (m_state == State::DONE)
			m_state = State::NOT_STARTED;
	}

	typename internal::AbstractTask::State internal::AbstractTask::getState() const
	{
		return m_state;
	}
}