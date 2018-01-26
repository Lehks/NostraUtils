#ifndef NOU_DAT_ALG_BINARYHEAP_HPP
#define NOU_DAT_ALG_BINARYHEAP_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\dat_alg\Utils.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"

/** \file BinaryHeap.hpp
\author  Dennis Franz
\since   0.0.1
\version 0.0.1
\brief   This file provides a BinaryHeap (Min / Max) implementation.
*/


namespace NOU::NOU_DAT_ALG
{

	/**
	\tparam The type of the elements that will be stored in this BinaryHeap.

	\brief A Min or Max Heap that works with prioritys.

	\details This Binary-Heap can function as an Min or Max Heap with priotitys.
	the priotity is split in 2 parts ( PriorityTypePart(s) ). the first part (right to left) is the unique identifier of the priority,
	we need that because of our search function. The second part is the "standard" id wich will be used for sorting / maintaining the heap law.
	*/
	template<typename T>
	class NOU_CLASS BinaryHeap
	{
	public:
		using PriorityTypePart = NOU::uint64;

		using PriorityType = NOU::uint64;

	private:
		/**
		\brief A boolean that indicates wehter this heap function as a MIN or a MAX heap.
		*/
		boolean													m_isMinHeap;
		/**
		\brief The Vector that stores the Pairs(the data and the priority).
		*/
		Vector<NOU::NOU_DAT_ALG::Pair<T, PriorityType>>			m_data;
		/**
		\brief A counter that provides a uniqe identifiyer for every priority.
		*/
		PriorityTypePart										m_nextPriorityCounter;
		/**
		\return					The actuall counter increased by 1.

		\brief Returns the next counter.
		*/
		PriorityTypePart getNextPriorityCounter();
		/**
		\param rawPriority		The raw priority (priority without the counter).
		\param counter			The counter (default 0: means that the normal count will be increased).
		\return					A full 64bit priority.

		\brief Taks the rawpriority and (just in case of BinaryHeap<T>::decreaseKey a counter).
		*/
		PriorityType makePriority(PriorityTypePart rawPriority, PriorityTypePart counter = 0);
		/**
		\param priority			A Full priority.
		\return					The priority part without the counter.

		\brief	Takes the a full priority and returns the part without the counter.
		*/
		PriorityTypePart getPriority(PriorityType priority) const;
		/**
		\param priority			A Full priority.
		\return					The counter without the priority part.

		\brief Takes the a full priority and returns the part without the priority.
		*/
		PriorityTypePart getPriorityId(PriorityType priority) const;
		/**
		\brief Recreates the law of the heap.
		*/
		void checkForLaw();

	public:
		/**
		\param isMinHeap		A boolean that indicates wether this heap will be a min or a max heap.
		\param allocator		An allocator reference for the internal Vector.

		\brief "Standard" constructor.
		*/
		BinaryHeap(boolean isMinHeap = true, NOU::NOU_MEM_MNGT::AllocationCallback<NOU::NOU_DAT_ALG::Pair<T, PriorityType>> &allocator = NOU_MEM_MNGT::GenericAllocationCallback<NOU::NOU_DAT_ALG::Pair<T, PriorityType>>::getInstance());
		/**
		\param other			An onther BinaryHeap.

		\brief "Standard" copy constructor.
		*/
		BinaryHeap(const BinaryHeap<T> &other);
		/**
		\param other			An onther BinaryHeap.

		\brief "Standard" move constructor.
		*/
		BinaryHeap(BinaryHeap<T> && otehr);
		/**
		\param data				The data that will be one part of the Pair wich gets inserted in the vector.
		\param priority			Wich is the other part of the Pair thats get inserted in the vector.

		\brief Inserts a Pair of data and priority intothe Vector and checks at the end if the heap law is correct or not.
		*/
		void enqueue(const T& data, PriorityTypePart priority);
		/**
		\brief Deletes the root of the heap.
		*/
		void dequeue();
		/**
		\param is				The id that is searched.
		\param newpriority		The new priority that will be replace the old one.

		\brief This Function searchs the heap for the given id and replace its old id of the element with the new one.
		*/
		void decreaseKey(PriorityTypePart id, PriorityTypePart newpriority);
		/**
		\brief Returns the size of the heap (not the heigth !).
		*/
		sizeType size() const;
		/**
		\param index			An index.

		\brief Returns the data part of the object at the given index.
		*/
		T& at(sizeType index);
		/**
		\param index			An index.

		\brief Returns the FULL priority at the given index.
		*/
		typename BinaryHeap<T>::PriorityType priorityAt(sizeType index);
		/**
		\param index			An index.

		\brief Returns the data part of the object at the given index. (calls BinaryHeap<T>::at)
		*/
		T& operator [] (sizeType index);
	};

	template<typename T>
	typename BinaryHeap<T>::PriorityTypePart BinaryHeap<T>::getNextPriorityCounter()
	{
		return ++m_nextPriorityCounter;
	}

	template<typename T>
	typename BinaryHeap<T>::PriorityType BinaryHeap<T>::makePriority(PriorityTypePart rawPriority, PriorityTypePart counter)
	{
		PriorityType ret = (rawPriority * 100000000);

		if (counter == 0)
		{
			ret += getNextPriorityCounter();
		}
		else 
		{
			ret += counter;
		}
		return ret;
	}

	template<typename T>
	typename BinaryHeap<T>::PriorityTypePart BinaryHeap<T>::getPriority(PriorityType priority) const
	{
		return (priority / 100000000); 
	}

	template<typename T>
	typename BinaryHeap<T>::PriorityTypePart BinaryHeap<T>::getPriorityId(PriorityType priority) const
	{
		return (priority % 100000000);
	}

	template<typename T>
	void BinaryHeap<T>::checkForLaw()
	{
		sizeType i = m_data.size() - 1;

		if (m_isMinHeap)
		{
			while (i > 0)
			{
				sizeType p = static_cast<sizeType>(i - 1) / 2;

				if (getPriority(m_data[i].dataTwo) < getPriority(m_data[p].dataTwo))
				{
					m_data.swap(i, p);
				}
				else
				{
					break;
				}
				i--;
			}
		}
		else
		{
			while (1 > 0)
			{
				sizeType p = static_cast<sizeType>(i - 1) / 2;

				if (getPriority(m_data[i].dataTwo) > getPriority(m_data[p].dataTwo))
				{
					m_data.swap(i, p);
				}
				else
				{
					break;
				}
				i--;
			}
		}
	}

	template<typename T>
	BinaryHeap<T>::BinaryHeap(boolean isMinHeap, NOU::NOU_MEM_MNGT::AllocationCallback<NOU::NOU_DAT_ALG::Pair<T, PriorityType>> &allocator) :
		m_isMinHeap(isMinHeap),
		m_data(0, allocator),
		m_nextPriorityCounter(-1) //counter still starts at 0
	{}

	template<typename T>
	BinaryHeap<T>::BinaryHeap(const BinaryHeap<T> &other) :
		m_isMinHeap(other.m_isMinHeap),
		m_data(other.m_data),
		m_nextPriorityCounter(other.m_nextPriorityCounter)
	{}

	template<typename T>
	BinaryHeap<T>::BinaryHeap(BinaryHeap &&other) :
		m_isMinHeap(other.m_isMinHeap),
		m_data(other.m_data),
		m_nextPriorityCounter(other.m_nextPriorityCounter)
	{}

	template<typename T>
	void BinaryHeap<T>::enqueue(const T& data, PriorityTypePart priority)
	{
		
		PriorityType pt = makePriority(priority);
		NOU::NOU_DAT_ALG::Pair<T, PriorityType> p(data, pt);

		m_data.pushBack(p);

		checkForLaw();
	}

	template<typename T>
	void BinaryHeap<T>::dequeue()
	{
		m_data.remove(0);

		sizeType i = m_data.size() - 1;
		sizeType b = 0;
		if (m_isMinHeap)
		{
			while (b < (i / 2 - 2))
			{
				sizeType l = 2 * b + 1;			//left child
				sizeType r = 2 * b + 2;			//right child

				sizeType s = l;					//smaller child

				if (getPriority(m_data[r].dataTwo) < getPriority(m_data[l].dataTwo))
					s = r;

				b = static_cast<sizeType>(i - 1) / 2;

				if (getPriority(m_data[s].dataTwo) < getPriority(m_data[b].dataTwo))
				{
					m_data.swap(s, b);
					b = s;
				}
				else
				{
					break;
				}

			}
		}
		else
		{
			while (b < (i / 2 - 2))
			{
				sizeType l = 2 * b + 1;			//left child
				sizeType r = 2 * b + 2;			//right child

				sizeType s = l;					//smaller child

				if (getPriority(m_data[r].dataTwo) > getPriority(m_data[l].dataTwo))
					s = r;

				if (getPriority(m_data[s].dataTwo) > getPriority(m_data[b].dataTwo))
				{
					m_data.swap(s, b);
					b = s;
				}
				else
				{
					break;
				}

			}
		}
	}

	template<typename T>
	void BinaryHeap<T>::decreaseKey(PriorityTypePart id , PriorityTypePart newpriority)
	{
		for (sizeType i = 0; i < m_data.size(); i++)
		{
			if (getPriorityId(m_data[i].dataTwo) == id)
			{
				PriorityType p = makePriority(newpriority, id);
				m_data.at(i).dataTwo = p;
				checkForLaw();
				break;
			}
		}
	}

	template<typename T>
	sizeType BinaryHeap<T>::size() const
	{
		return m_data.size();
	}

	template<typename T>
	T& BinaryHeap<T>::at(sizeType index)
	{
		return m_data.at(index).dataOne;
	}

	template<typename T>
	typename BinaryHeap<T>::PriorityType BinaryHeap<T>::priorityAt(sizeType index)
	{
		return m_data.at(index).dataTwo;
	}

	template<typename T>
	T& BinaryHeap<T>::operator[](sizeType index)
	{
		return at(index);
	}

}



#endif 
