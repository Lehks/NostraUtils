#ifndef NOU_DAT_ALG_BINARYHEAP_HPP
#define NOU_DAT_ALG_BINARYHEAP_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\dat_alg\Utils.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"

namespace NOU::NOU_DAT_ALG
{

	template<typename T>
	class NOU_CLASS BinaryHeap
	{
	public:
		using PriorityTypePart = NOU::uint32;
		using PriorityType = NOU::uint64;

	private:
		boolean										isMinHeap;

		Vector<NOU::NOU_DAT_ALG::Pair<T, PriorityType>>			m_data;
		
		PriorityTypePart m_nextPriorityCounter;

		PriorityTypePart getNextPriorityCounter();
		PriorityType makePriority(PriorityTypePart rawPriority);
		PriorityTypePart getPriority(PriorityType priority) const;

		void checkForLaw(sizeType i = m_data.size());

	public:
		BinaryHeap(boolean isMinHeap = true, NOU::NOU_MEM_MNGT::AllocationCallback<T> &allocator = NOU_MEM_MNGT::GenericAllocationCallback<T>::getInstance());
		BinaryHeap(const BinaryHeap<T> &other);
		BinaryHeap(BinaryHeap<T> && otehr);

		void enqueue(const T& data, PriorityTypePart priority);

		void dequeue();

		void decreaseKey(PriorityType priority, PriorityType newpriority);

		sizeType size() const;
	};

	template<typename T>
	typename BinaryHeap<T>::PriorityTypePart BinaryHeap<T>::getNextPriorityCounter()
	{
		return ++m_nextPriorityCounter;
	}

	template<typename T>
	typename BinaryHeap<T>::PriorityType BinaryHeap<T>::makePriority(PriorityTypePart rawPriority)
	{
		PriorityType ret = rawPriority; //priority left, counter right

		ret |= getNextPriorityCounter() << (sizeof(PriorityTypePart) * 8);

		return ret;
	}

	template<typename T>
	typename BinaryHeap<T>::PriorityTypePart BinaryHeap<T>::getPriority(PriorityType priority) const
	{
		return static_cast<PriorityTypePart>(priority & 0xFFFFFFFF); //0x FFFF FFFF : first 32 bits are 1, remaining bits are 0
	}

	template<typename T>
	void BinaryHeap<T>::checkForLaw(sizeType i)
	{
		if (isMinHeap)
		{
			while (1 > 0)
			{
				sizeType p = static_cast<int>(i - 1) / 2;

				if (getPriority(m_data[i].dataTwo) < getPriority(m_data[p].dataTwo))
				{
					swap(m_data[i], m_data[p]);
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			while (1 > 0)
			{
				sizeType p = static_cast<int>(i - 1) / 2;

				if (getPriority(m_data[i].dataTwo) > getPriority(m_data[p].dataTwo))
				{
					swap(m_data[i], m_data[p]);
				}
				else
				{
					break;
				}
			}
		}
	}

	template<typename T>
	BinaryHeap<T>::BinaryHeap(boolean isMinHeap, NOU::NOU_MEM_MNGT::AllocationCallback<T>& allocator) :
		isMinHeap(isMinHeap),
		m_data(0, allocator),
		m_nextPriorityCounter(-1) //counter still starts at 0
	{}

	template<typename T>
	BinaryHeap<T>::BinaryHeap(const BinaryHeap<T> &other) :
		isMinHeap(other.isMinHeap),
		m_data(other.m_data),
		m_nextPriorityCounter(other.m_nextPriorityCounter)
	{}

	template<typename T>
	BinaryHeap<T>::BinaryHeap(BinaryHeap &&other) :
		isMinHeap(other.isMinHeap),
		m_data(other.m_data),
		m_nextPriorityCounter(other.m_nextPriorityCounter)
	{}

	template<typename T>
	void BinaryHeap<T>::enqueue(const T& data, PriorityTypePart priority)
	{
		
		NOU::NOU_DAT_ALG::Pair<T, PriorityType> p(data, makePriority(priority));

		m_data.pushBack(p);

		checkForLaw();
	}

	template<typename T>
	void BinaryHeap<T>::dequeue()
	{
		m_data.remove(0);

		sizeType i = m_data.size() - 1;

		if (isMinHeap)
		{
			while (1 < n / 2 - 2)
			{
				sizeType l = 2 * i + 1;
				sizeType r = 2 * i + 2;

				sizeType s = l;

				if (getPriority(m_data[r].dataTwo) < getPriority(m_data[l].dataTwo))
					c = r;

				if (getPriority(m_data[r].dataTwo) < getPriority(m_data[l].dataTwo))
				{
					swap(m_data[c], m_data[i]);
					i = c;
				}
				else
				{
					break;
				}

			}
		}
		else
		{
			while (1 < n / 2 - 2)
			{
				sizeType l = 2 * i + 1;
				sizeType r = 2 * i + 2;

				sizeType s = l;

				if (getPriority(m_data[r].dataTwo) > getPriority(m_data[l].dataTwo))
					c = r;

				if (getPriority(m_data[r].dataTwo) > getPriority(m_data[l].dataTwo))
				{
					swap(m_data[c], m_data[i]);
					i = c;
				}
				else
				{
					break;
				}

			}
		}

	}

	template<typename T>
	void BinaryHeap<T>::decreaseKey(PriorityType priority , PriorityType newpriority)
	{
		for (int i = 0; i < m_data.size(); i++)
		{
			if (m_data.at(i).dataTwo == priority)
			{
				m_data.at(i).dataTwo = newpriority;
				checkForLaw(i);
				break;
			}
		}
	}

	template<typename T>
	sizeType BinaryHeap<T>::size() const
	{
		return m_data.size();
	}

}



#endif
