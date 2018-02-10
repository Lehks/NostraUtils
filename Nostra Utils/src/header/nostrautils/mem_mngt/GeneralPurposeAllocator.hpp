#ifndef NOU_MEM_MNGT_GENERAL_PURPOSE_ALLOCATOR_HPP
#define NOU_MEM_MNGT_GENERAL_PURPOSE_ALLOCATOR_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Utils.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\BinarySearch.hpp"
#include "nostrautils\mem_mngt\Utils.hpp"

namespace NOU::NOU_MEM_MNGT
{
	namespace INTERNAL
	{
		template <typename T>
		T nextMultiple(T multipleOf, T value)
		{
			T multiple = value + multipleOf - 1;
			multiple -= (multiple % multipleOf);
			return multiple;
		}

		class GeneralPurposeAllocatorFreeChunk
		{
		public:
			byte* m_addr;

			sizeType m_size;

			GeneralPurposeAllocatorFreeChunk(byte* addr, sizeType size);

			boolean touches(const GeneralPurposeAllocatorFreeChunk& other) const;

			boolean operator>(const GeneralPurposeAllocatorFreeChunk& other) const;

			boolean operator<(const GeneralPurposeAllocatorFreeChunk& other) const;

			boolean operator>=(const GeneralPurposeAllocatorFreeChunk& other) const;

			boolean operator<=(const GeneralPurposeAllocatorFreeChunk& other) const;

			boolean operator==(const GeneralPurposeAllocatorFreeChunk& other) const;

			template <typename T, typename... arguments>
			T* allocateObject(sizeType amountofObjects = 1, arguments&&... args);
		};
	}

	class GeneralPurposeAllocator
	{
	public:

		template <typename T>
		class GeneralPurposeAllocatorPointer
		{
			friend class GeneralPurposeAllocator;

		private:

			T * m_pdata;

			sizeType m_size;

		public:
			GeneralPurposeAllocatorPointer(T* pdata, sizeType size);

			T* operator->();

			const T* operator->() const;

			T& operator*();

			const T& operator*() const;

			T& operator[](int index);

			const T& operator[](int index) const;

			T* getRaw();

			boolean operator==(void* ptr) const;

			boolean operator!=(void* ptr) const;
		};

	private:
		static const sizeType GENERAL_PURPOSE_ALLOCATOR_DEFAULT_SIZE = 1024;

		byte* m_data;

		sizeType m_size;

		NOU_DAT_ALG::Vector<INTERNAL::GeneralPurposeAllocatorFreeChunk> m_freeChunks; 
		///\todo sorting with insert function

	public:
		explicit GeneralPurposeAllocator(sizeType size = GENERAL_PURPOSE_ALLOCATOR_DEFAULT_SIZE);

		GeneralPurposeAllocator(const GeneralPurposeAllocator& other) = delete;
		GeneralPurposeAllocator(GeneralPurposeAllocator&& other) = delete;
		GeneralPurposeAllocator& operator=(const GeneralPurposeAllocator& other) = delete;
		GeneralPurposeAllocator& operator=(GeneralPurposeAllocator&& other) = delete;

		~GeneralPurposeAllocator();

		template <typename T, typename... arguments>
		GeneralPurposeAllocatorPointer<T> allocateObjects(sizeType amountOfObjects = 1, arguments&&... args);

		template <typename T, typename... arguments>
		GeneralPurposeAllocatorPointer<T> allocateObject(arguments&&... args);

		template <typename T>
		void deallocateObjects(GeneralPurposeAllocatorPointer<T> pointer);

		template<typename T>
		void getNeigbors(const T& val, T*& left, T*& right, sizeType insertionIndex);
	};

	INTERNAL::GeneralPurposeAllocatorFreeChunk::GeneralPurposeAllocatorFreeChunk(byte* addr, sizeType size) :
		m_addr(addr),
		m_size(size)
	{
		//do nothing
	}

	boolean INTERNAL::GeneralPurposeAllocatorFreeChunk::touches
	(const GeneralPurposeAllocatorFreeChunk& other) const
	{
		if (m_addr + m_size == other.m_addr)
		{
			return true;
		}

		if (other.m_addr + other.m_size == m_addr)
		{
			return true;
		}

		return false;
	}

	boolean INTERNAL::GeneralPurposeAllocatorFreeChunk::operator>
		(const GeneralPurposeAllocatorFreeChunk& other) const
	{
		return m_addr > other.m_addr;
	}

	boolean INTERNAL::GeneralPurposeAllocatorFreeChunk::operator<
		(const GeneralPurposeAllocatorFreeChunk& other) const
	{
		return m_addr < other.m_addr;
	}

	boolean INTERNAL::GeneralPurposeAllocatorFreeChunk::operator>=
		(const GeneralPurposeAllocatorFreeChunk& other) const
	{
		return m_addr >= other.m_addr;
	}

	boolean INTERNAL::GeneralPurposeAllocatorFreeChunk::operator<=
		(const GeneralPurposeAllocatorFreeChunk& other) const
	{
		return m_addr <= other.m_addr;
	}

	boolean INTERNAL::GeneralPurposeAllocatorFreeChunk::operator==
		(const GeneralPurposeAllocatorFreeChunk& other) const
	{
		return m_addr == other.m_addr;
	}

	template <typename T, typename... arguments>
	T* INTERNAL::GeneralPurposeAllocatorFreeChunk::allocateObject
	(sizeType amountofObjects, arguments&&... args)
	{
		static_assert(alignof(T) <= 128, "Max alignment of 128 was exceeded!");
		byte* allocationLocation = (byte*)nextMultiple(alignof(T), ((sizeType)m_addr) + 1);
		sizeType amountOfBytes = amountofObjects * sizeof(T);
		byte* newAddr = allocationLocation + amountOfBytes;

		if (newAddr <= m_addr + m_size)
		{
			byte offset = (byte)(allocationLocation - m_addr);
			allocationLocation[-1] = offset;

			T* returnPointer = reinterpret_cast<T*>(allocationLocation);
			m_size -= newAddr - m_addr;
			m_addr = newAddr;

			for (sizeType i = 0; i < amountofObjects; i++)
			{
				T* object = addressof(returnPointer[i]);
				new(object) T(NOU_CORE::forward<arguments>(args)...);
			}

			return returnPointer;
		}
		else
		{
			return nullptr;
		}
	}

	template <typename T>
	GeneralPurposeAllocator::GeneralPurposeAllocatorPointer<T>::GeneralPurposeAllocatorPointer(T* pdata, 
		sizeType size) :
		m_pdata(pdata),
		m_size(size)
	{
		//do nothing
	}

	template <typename T>
	T* GeneralPurposeAllocator::GeneralPurposeAllocatorPointer<T>::operator->()
	{
		return m_pdata;
	}

	template <typename T>
	const T* GeneralPurposeAllocator::GeneralPurposeAllocatorPointer<T>::operator->() const
	{
		return m_pdata;
	}

	template <typename T>
	T& GeneralPurposeAllocator::GeneralPurposeAllocatorPointer<T>::operator*()
	{
		return *m_pdata;
	}

	template <typename T>
	const T& GeneralPurposeAllocator::GeneralPurposeAllocatorPointer<T>::operator*() const
	{
		return *m_pdata;
	}

	template <typename T>
	T& GeneralPurposeAllocator::GeneralPurposeAllocatorPointer<T>::operator[](int index)
	{
		return *(m_pdata + index);
	}

	template <typename T>
	const T& GeneralPurposeAllocator::GeneralPurposeAllocatorPointer<T>::operator[](int index) const
	{
		return *(m_pdata + index);
	}

	template <typename T>
	T* GeneralPurposeAllocator::GeneralPurposeAllocatorPointer<T>::getRaw()
	{
		return m_pdata;
	}

	template <typename T>
	boolean GeneralPurposeAllocator::GeneralPurposeAllocatorPointer<T>::operator==(void* ptr) const
	{
		return m_pdata == ptr;
	}

	template <typename T>
	boolean GeneralPurposeAllocator::GeneralPurposeAllocatorPointer<T>::operator!=(void* ptr) const
	{
		return m_pdata != ptr;
	}

	GeneralPurposeAllocator::GeneralPurposeAllocator(sizeType size) :
		m_size(size)
	{
		m_data = new byte[m_size];
		m_freeChunks.pushBack(INTERNAL::GeneralPurposeAllocatorFreeChunk(m_data, m_size));
	}

	GeneralPurposeAllocator::~GeneralPurposeAllocator()
	{
		if (m_data != nullptr)
		{
			delete[] m_data;
			m_data = nullptr;
		}
	}

	template <typename T, typename... arguments>
	GeneralPurposeAllocator::GeneralPurposeAllocatorPointer<T> 
		GeneralPurposeAllocator::allocateObjects(sizeType amountOfObjects, arguments&&... args)
	{
		static_assert(alignof(T) <= 128, "Max alignment of 128 was exceeded!");
		for (sizeType i = 0; i < m_freeChunks.size(); i++)
		{
			T* data = m_freeChunks[i].allocateObject<T>(amountOfObjects, 
				NOU_CORE::forward<arguments>(args)...);
			if (data != nullptr)
			{
				if (m_freeChunks[i].m_size == 0)
				{
					m_freeChunks.remove(i);
				}
				return GeneralPurposeAllocatorPointer<T>(data, amountOfObjects);
			}
		}

		return GeneralPurposeAllocatorPointer<T>(nullptr, 0);///\todo better error handling???
	}

	template<typename T, typename... arguments>
	GeneralPurposeAllocator::GeneralPurposeAllocatorPointer<T> 
		GeneralPurposeAllocator::allocateObject(arguments&&...args)
	{
		return allocateObjects<T>(1, NOU_CORE::forward<arguments>(args)...);
	}

	template <typename T>
	void GeneralPurposeAllocator::deallocateObjects(GeneralPurposeAllocatorPointer<T> pointer)
	{
		for (sizeType i = 0; i < pointer.m_size; i++)
		{
			addressof(pointer.m_pdata[i])->~T();
		}

		byte* bytePointer = reinterpret_cast<byte*>(pointer.m_pdata);
		sizeType amountOfBytes = sizeof(T) * pointer.m_size;
		byte offset = bytePointer[-1];

		INTERNAL::GeneralPurposeAllocatorFreeChunk gpafc(bytePointer - offset, amountOfBytes + offset);

		sizeType insertionIndex;
		NOU_DAT_ALG::binarySearch(m_freeChunks, gpafc, 0, -1, &insertionIndex);

		INTERNAL::GeneralPurposeAllocatorFreeChunk* p_gpafc = &gpafc;
		INTERNAL::GeneralPurposeAllocatorFreeChunk* left;
		INTERNAL::GeneralPurposeAllocatorFreeChunk* right;

		getNeigbors(*p_gpafc, left, right, insertionIndex);

		boolean didMerge = false;

		if (left->m_addr != m_freeChunks.at(-1).m_addr)
		{
			if (left->touches(*p_gpafc))
			{
				left->m_size += p_gpafc->m_size;
				p_gpafc = left;
				didMerge = true;
			}
		}

		if(right->m_addr != m_freeChunks.at(m_freeChunks.size()).m_addr)
		{ 
			if (right->touches(*p_gpafc))
			{
				if (didMerge)
				{
					p_gpafc->m_size += right->m_size;
					m_freeChunks.remove(insertionIndex);
				}
				else
				{
					right->m_size += p_gpafc->m_size;
					right->m_addr = p_gpafc->m_addr;
				}

				didMerge = true;
			}
		}

		if (!didMerge)
		{
			m_freeChunks.pushBack(gpafc);
		}
	}

	template<typename T>
	void GeneralPurposeAllocator::getNeigbors(const T& val, T*& left, T*& right, sizeType insertionIndex)
	{
		left = reinterpret_cast<T*>(m_freeChunks.data() + insertionIndex - 1);
		right = reinterpret_cast<T*>(m_freeChunks.data() + insertionIndex);
	}
}

#endif