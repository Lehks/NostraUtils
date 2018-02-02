#ifndef NOU_MEM_MNGT_GENERAL_PURPOSE_ALLOCATOR_HPP
#define NOU_MEM_MNGT_GENERAL_PURPOSE_ALLOCATOR_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Utils.hpp"
#include "nostrautils\mem_mngt\Utils.hpp"

namespace NOU::NOU_MEM_MNGT
{
	namespace NOU::NOU_MEM_MNGT::INTERNAL
	{
		template <typename T>
		T nextMultiple(T multipleOf, T value)
		{
			T multiple = value + multipleOf - 1;
			multiple -= (multiple % multipleOf);
			return multiple;
		}

		class GeneralPurposeAllocatoFreeChunk
		{
		public:
			byte* m_addr;
			sizeType m_size;

			GeneralPurposeAllocatoFreeChunk(byte* addr, sizeType size) :
				m_addr(addr),
				m_size(size)
			{
				//do nothing
			}

			boolean touches(const GeneralPurposeAllocatoFreeChunk& other) const
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

			boolean operator>(const GeneralPurposeAllocatoFreeChunk& other) const
			{
				return m_addr > other.m_addr;
			}

			boolean operator<(const GeneralPurposeAllocatoFreeChunk& other) const
			{
				return m_addr < other.m_addr;
			}

			boolean operator>=(const GeneralPurposeAllocatoFreeChunk& other) const
			{
				return m_addr >= other.m_addr;
			}

			boolean operator<=(const GeneralPurposeAllocatoFreeChunk& other) const
			{
				return m_addr <= other.m_addr;
			}

			boolean operator==(const GeneralPurposeAllocatoFreeChunk& other) const
			{
				return m_addr == other.m_addr;
			}

			template <typename T, typename... arguments>
			T* allocateObject(sizeType amountofObjects = 1, arguments&&... args)
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
						T* object = NOU_MEM_MNGT::addressof(returnPointer[i]);
						new(object) T(NOU_CORE::forward<arguments>(args)...);
					}

					return returnPointer;
				}
				else
				{
					return nullptr;
				}
			}
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
			GeneralPurposeAllocatorPointer(T* pdata, sizeType size) :
				m_pdata(pdata),
				m_size(size)
			{
				//do nothing
			}

			T* operator->()
			{
				return m_pdata;
			}

			const T* operator->() const
			{
				return m_pdata;
			}

			T& operator*()
			{
				return *m_pdata;
			}

			const T& operator*() const
			{
				return *m_pdata;
			}

			T& operator[](int index)
			{
				return *(m_pdata + index);
			}

			const T& operator[](int index) const
			{
				return *(m_pdata + index);
			}

			T* getRaw()
			{
				return m_pdata;
			}

			boolean operator==(void* ptr) const
			{
				return m_pdata == ptr;
			}

			boolean operator!=(void ptr) const
			{
				return m_pdata != ptr;
			}
		};

	};
}

#endif