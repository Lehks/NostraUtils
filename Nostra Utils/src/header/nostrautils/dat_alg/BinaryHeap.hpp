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
	private:
		NOU::NOU_MEM_MNGT::AllocationCallback<T>	&m_allocator;
		NOU::boolean								isMinHeap;
		Vector<Pair>								m_data;
	public:
		BinaryHeap<T>(boolean isMinHeap = true, NOU::NOU_MEM_MNGT::AllocationCallback<T> &allocator = NOU_MEM_MNGT::GenericAllocationCallback<T>::getInstance());

		template<typename O>
		void enqueue(const T& data, const O& priority);

		template<typename O>
		void dequeue();

		sizeType size() const;
	};

	template<typename T>
	BinaryHeap<T>::BinaryHeap(boolean isMinHeap = true, NOU::NOU_MEM_MNGT::AllocationCallback<T>& allocator = NOU_MEM_MNGT::GenericAllocationCallback<T>::getInstance()) :
		isMinHeap(isMinHeap),
		m_allocator(allocator),
		m_data(0)
	{}

	template<typename T>
	template<typename O>
	void BinaryHeap<T>::enqueue(const T& data, const O& priority)
	{
		NOU::NOU_DAT_ALG::Pair<T,O> p(data, priority);

		m_data.pushBack(p);

		sizeType i = m_data.size() - 1;
		while (1 > 0)
		{
			sizeType a = (i - 1) / 2;

			if (m_data[i].dataTwo < m_data[p].dataTwo)
			{
				swap(m_data[i], m_data[p]);
			}
			else
			{
				break;
			}
		}
	}

	template<typename T>
	template<typename O>
	void BinaryHeap<T>::dequeue()
	{
		m_data.remove(0);

		sizeType i = m_data.size() - 1;
		while (1 < n / 2 - 2)
		{
			sizeType l = 2 * i + 1;
			sizeType r = 2 * i + 2;

			sizeType s = l;

			if (m_data[r].dataTwo < m_data[l].dataTwo)
				c = r;
			
			if (m_data[c].dataTwo < m_data[i].dataTwo)
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


	template<typename T>
	sizeType BinaryHeap<T>::size() const
	{
		return m_data.size();
	}

}



#endif
