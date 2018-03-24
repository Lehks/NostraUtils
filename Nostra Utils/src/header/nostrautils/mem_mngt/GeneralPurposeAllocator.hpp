#ifndef NOU_MEM_MNGT_GENERAL_PURPOSE_ALLOCATOR_HPP
#define NOU_MEM_MNGT_GENERAL_PURPOSE_ALLOCATOR_HPP

//USELESS SHIT ON THE WAY

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Utils.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\BinarySearch.hpp"
#include "nostrautils\mem_mngt\Utils.hpp"

/**
\file dat_alg/GeneralPurposeAllocator.hpp

\author  Lukas Gross
\version 0.0.1
\since   1.0.0

\brief A file that contains the nostra::utils::dat_alg::GeneralPurposeAllocator class.
*/
namespace NOU::NOU_MEM_MNGT
{
	namespace internal
	{
		/**
		\tparam T The type of the parameters

		\param multipleOf The value you want a multiple of.

		\param value Your current value.

		\return A multiple of your value and your multipleOf.

		\brief Returns the next multiple of your multipleOf where your value fits in.

		\details e.g. You have a value (e.g. 10) and want to know if it fits in another value
				 (e.g. 8). The 10 does not fit in the 8. So you double the 8 and the 10 fits in the 16.
				 Then your return value will be 16, because 10 fits in the 16 which is a multiple of 8.
		*/
		template <typename T>
		T nextMultiple(T multipleOf, T value)
		{
			T multiple = value + multipleOf - 1;
			multiple -= (multiple % multipleOf);
			return multiple;
		}

		/**
		\brief This class defines the chunks of the allocator.
		*/
		class GeneralPurposeAllocatorFreeChunk
		{
		public:
			/**
			\brief A byte pointer to the address of the chunk.
			*/
			byte* m_addr;

			/**
			\brief The size of the chunks.
			*/
			sizeType m_size;

			/**
			\param addr A byte pointer to the address of the free chunks

			\param size The size of the free chunks.

			\brief Constructs a new free chunk object.
			*/
			GeneralPurposeAllocatorFreeChunk(byte* addr, sizeType size);

			/**
			\param other A const reference to a GeneralPurposeAllocatorFreeChunk.

			\return True if the chunks touch each other and false if not.

			\brief Checks if the address of the chunk and the passed chunk touches each other.
			*/
			boolean touches(const GeneralPurposeAllocatorFreeChunk& other) const;

			/**
			\param other A const reference to a GeneralPurposeAllocatorFreeChunk.

			\return True if the address of the chunk is bigger than the address of the passed chunk.
					False if not.

			\brief Overloads the > operator.
			*/
			boolean operator>(const GeneralPurposeAllocatorFreeChunk& other) const;

			/**
			\param other A const reference to a GeneralPurposeAllocatorFreeChunk.

			\return True if the address of the chunk is smaller than the address of the passed chunk.
					False if not.

			\brief Overloads the < operator.
			*/
			boolean operator<(const GeneralPurposeAllocatorFreeChunk& other) const;

			/**
			\param other A const reference to a GeneralPurposeAllocatorFreeChunk.

			\return True if the address of the chunk is bigger or equal to the address of the passed chunk.
					False if not.

			\brief Overloads the >= operator.
			*/
			boolean operator>=(const GeneralPurposeAllocatorFreeChunk& other) const;

			/**
			\param other A const reference to a GeneralPurposeAllocatorFreeChunk.

			\return True if the address of the chunk is smaller or equal to the address of the passed chunk.
					False if not.

			\brief Overloads the <= operator.
			*/
			boolean operator<=(const GeneralPurposeAllocatorFreeChunk& other) const;

			/**
			\param other A const reference to a GeneralPurposeAllocatorFreeChunk.
					
			\return True if the address of the chunk is equal to the address of the passed chunk.
					False if not.

			\brief Overloads the == operator.
			*/
			boolean operator==(const GeneralPurposeAllocatorFreeChunk& other) const;


			/**
			\tparam T The return type.

			\param arguments All passed parameters.

			\return A pointer to the allocated object or a null-pointer if the element could not be allocated.

			\brief Allocates a new Object with all passed elements.
			*/
			template <typename T, typename... arguments>
			T* allocateObject(sizeType amountofObjects = 1, arguments&&... args);
		};
	}

	/**
	\brief Defines the GeneralPurposeAllocator class, which is used to allocate and deallocate objects.
	*/
	class GeneralPurposeAllocator
	{
	public:

		/**
		\tparam T The type of the pointer.

		\brief Defines the GeneralPurposeAllocatorPointer class, which is used for saving a pointer to the
			   allocator.
		*/
		template <typename T>
		class GeneralPurposeAllocatorPointer
		{
			/**
			\brief Defines the GeneralPurposeAllocator as a friend class.
			*/
			friend class GeneralPurposeAllocator;

		private:

			/**
			\brief A pointer of the passed type T. Points to the stored elements.
			*/
			T* m_pdata;

			/**
			\brief The amount of objects which are stored.
			*/
			sizeType m_size;

		public:

			/**
			\param pdata A pointer to the elements where the pointer is pointing to.

			\param size The amount of objects.

			\brief Creates a pointer to the elements in the GeneralPurposeAllocator.
			*/
			GeneralPurposeAllocatorPointer(T* pdata, sizeType size);

			/**
			\return The pointer stored in the GeneralPurposeAllocatorPointer.

			\brief Returns the pointer which is stored in the GeneralPurposeAllocatorPointer.
			*/
			T* operator->();

			/**
			\return The pointer stored in the GeneralPurposeAllocatorPointer.

			\brief Returns a const pointer to the pointer which is stored in the 
				   GeneralPurposeAllocatorPointer.
			*/
			const T* operator->() const;

			/**
			\return A reference to the pointer stored in the GeneralPurposeAllocatorPointer.

			\brief Returns a reference to the pointer which is stored in the GeneralPurposeAllocatorPointer.
			*/
			T& operator*();

			/**
			\return A reference to the pointer stored in the GeneralPurposeAllocatorPointer.

			\brief Returns a const reference to the pointer which is stored in the 
				   GeneralPurposeAllocatorPointer.
			*/
			const T& operator*() const;

			/**
			\param index The index of the element.

			\return A reference to the element.

			\brief Returns a reference of the element at the passed index.
			*/
			T& operator[](int index);

			/**
			\param index The index of the element.

			\return A const reference to the element.

			\brief Returns a const reference of the element at the passed index.
			*/
			const T& operator[](int index) const;

			/**
			\return The pointer which is stored in the GeneralPurposeAllocatorPointer.

			\brief Returns the raw pointer.
			*/
			T* getRaw();

			/**
			\param ptr A void pointer.

			\return True when the pointers are equal and false if not.
			
			\brief Compares the passed pointer with the stored pointer and checks if they are equal.
			*/
			boolean operator==(void* ptr) const;

			/**
			\param ptr A void pointer.

			\return True when the pointers are not equal and false if they are.

			\brief Compares the passed pointer with the stored pointer and checks if they are not equal.
			*/
			boolean operator!=(void* ptr) const;
		};

	private:

		/**
		\brief The default size of the allocator.
		*/
		static const sizeType GENERAL_PURPOSE_ALLOCATOR_DEFAULT_SIZE = 10 * 1024;

		/**
		\brief A byte pointer to the elements
		*/
		byte* m_data;

		/**
		\brief The size of the allocator.
		*/
		sizeType m_size;

		/**
		\brief A vector which stores chunks from the GeneralPurposeAllocatorFreeChunk.
		*/
		NOU_DAT_ALG::Vector<internal::GeneralPurposeAllocatorFreeChunk> m_freeChunks; 
		///\todo sorting with insert function

	public:

		/**
		\param size The size of the gpa. Can be set manually or the default size.

		\brief Creates a new gpa with a passed size or the default size.
		*/
		explicit GeneralPurposeAllocator(sizeType size = GENERAL_PURPOSE_ALLOCATOR_DEFAULT_SIZE);

		GeneralPurposeAllocator(const GeneralPurposeAllocator& other) = delete;
		GeneralPurposeAllocator(GeneralPurposeAllocator&& other) = delete;
		GeneralPurposeAllocator& operator=(const GeneralPurposeAllocator& other) = delete;
		GeneralPurposeAllocator& operator=(GeneralPurposeAllocator&& other) = delete;

		/**
		\brief Destructor of the gpa.
		*/
		~GeneralPurposeAllocator();

		/**
		\tparam T The type of the object which will be allocated.

		\tparam arguments The passed data of the object.

		\param amountOfObjects Defines the amount of objects which will be created. Can be set manually or
			   use the default size.

		\param arguments The data of the object which will be allocated.

		\return A pointer to the allocated Objects.

		\brief Allocates memory in the gpa for the passed object. Allows to allocate the passed object
			   multiple times.
		*/
		template <typename T, typename... arguments>
		GeneralPurposeAllocatorPointer<T> allocateObjects(sizeType amountOfObjects = 1, arguments&&... args);

		/**
		\tparam T The type of the object which will be allocated.

		\tparam arguments The passed data of the object.

		\param arguments The data of the object which will be allocated.

		\return A pointer to the allocated object-

		\brief Allocates memory in the gpa for the passed object. Allows to allocate the passed object
		only ones. For multiple allocations of the same object use the allocateObjects().

		\details Calls the allocateObjects() with the parameter amountOfObjects = 1.
		*/
		template <typename T, typename... arguments>
		GeneralPurposeAllocatorPointer<T> allocateObject(arguments&&... args);

		/**
		\tparam T The type of the object which will be deallocated.

		\param pointer A  pointer to the object which will be deallocated.

		\brief Deallocated the object at the location the pointer points to.
		*/
		template <typename T>
		void deallocateObjects(GeneralPurposeAllocatorPointer<T> pointer);

		/**
		\tparam T The type of the object in the gpa.

		\param left A pointer reference to the left element in the gpa.

		\param right A pointer reference to the right element in the gpa.

		\param insertionIndex The index where the new element will be inserted.

		\brief Saves the left and right element in two passed pointers dependent on the insertion index where
			   you want to insert a new element.
		*/
		template<typename T>
		void getNeigbors(T*& left, T*& right, sizeType insertionIndex);
	};

	internal::GeneralPurposeAllocatorFreeChunk::GeneralPurposeAllocatorFreeChunk(byte* addr, sizeType size) :
		m_addr(addr),
		m_size(size)
	{
		//do nothing
	}

	boolean internal::GeneralPurposeAllocatorFreeChunk::touches
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

	boolean internal::GeneralPurposeAllocatorFreeChunk::operator>
		(const GeneralPurposeAllocatorFreeChunk& other) const
	{
		return m_addr > other.m_addr;
	}

	boolean internal::GeneralPurposeAllocatorFreeChunk::operator<
		(const GeneralPurposeAllocatorFreeChunk& other) const
	{
		return m_addr < other.m_addr;
	}

	boolean internal::GeneralPurposeAllocatorFreeChunk::operator>=
		(const GeneralPurposeAllocatorFreeChunk& other) const
	{
		return m_addr >= other.m_addr;
	}

	boolean internal::GeneralPurposeAllocatorFreeChunk::operator<=
		(const GeneralPurposeAllocatorFreeChunk& other) const
	{
		return m_addr <= other.m_addr;
	}

	boolean internal::GeneralPurposeAllocatorFreeChunk::operator==
		(const GeneralPurposeAllocatorFreeChunk& other) const
	{
		return m_addr == other.m_addr;
	}

	template <typename T, typename... arguments>
	T* internal::GeneralPurposeAllocatorFreeChunk::allocateObject
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
		m_freeChunks.pushBack(internal::GeneralPurposeAllocatorFreeChunk(m_data, m_size));
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

		internal::GeneralPurposeAllocatorFreeChunk gpafc(bytePointer - offset, amountOfBytes + offset);

		sizeType insertionIndex;
		NOU_DAT_ALG::binarySearch(m_freeChunks, gpafc, 0, -1, &insertionIndex);

		internal::GeneralPurposeAllocatorFreeChunk* p_gpafc = &gpafc;
		internal::GeneralPurposeAllocatorFreeChunk* left;
		internal::GeneralPurposeAllocatorFreeChunk* right;

		getNeigbors(left, right, insertionIndex);

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
	void GeneralPurposeAllocator::getNeigbors(T*& left, T*& right, sizeType insertionIndex)
	{
		left = reinterpret_cast<T*>(m_freeChunks.data() + insertionIndex - 1);
		right = reinterpret_cast<T*>(m_freeChunks.data() + insertionIndex);
	}
}

#endif