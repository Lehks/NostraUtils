#ifndef NOU_MEM_MNGT_GENERAL_PURPOSE_ALLOCATOR_HPP
#define NOU_MEM_MNGT_GENERAL_PURPOSE_ALLOCATOR_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/core/Utils.hpp"
#include "nostrautils/dat_alg/Vector.hpp"
#include "nostrautils/dat_alg/BinarySearch.hpp"
#include "nostrautils/mem_mngt/Utils.hpp"
#include "nostrautils/core/ErrorHandler.hpp"

/**
\file mem_mngt/GeneralPurposeAllocator.hpp

\author  Lukas Gross
\version 1.0.0
\since   1.0.0

\brief A file that contains the nostra::utils::dat_alg::GeneralPurposeAllocator class.
*/
namespace NOU::NOU_MEM_MNGT
{
	namespace internal
	{
		/**
		\tparam T			The type of the parameters
		\param multipleOf	The value you want a multiple of.
		\param value		Your current value.

		\return				A multiple of your value and your multipleOf.

		\brief				Returns the next multiple of your multipleOf where your value fits in.

		\details			e.g. You have a value (e.g. 10) and want to know if it fits in another value
							(e.g. 8). The 10 does not fit in the 8. So you double the 8 and the 10 fits in 
							the 16. Then your return value will be 16, because 10 fits in the 16 which is a 
							multiple of 8.
		*/
		template <typename T>
		T nextMultiple(T multipleOf, T value)
		{
			T multiple = value + multipleOf - 1;
			multiple -= (multiple % multipleOf);
			return multiple;
		}

		/**
		\brief This class defines the free chunks of the allocator.
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
			\param addr	A byte pointer to the address of the free chunks.
			\param size	The size of the free chunks.

			\brief		Constructs a new free chunk object.
			*/
			NOU_FUNC GeneralPurposeAllocatorFreeChunk(byte* addr, sizeType size);

			/**
			\param other	A const reference to a GeneralPurposeAllocatorFreeChunk.

			\return			True if the chunks touch each other and false if not.

			\brief			Checks if the address of the chunk and the passed chunk touches each other.
			*/
			NOU_FUNC boolean touches(const GeneralPurposeAllocatorFreeChunk& other) const;

			/**
			\param other	A const reference to a GeneralPurposeAllocatorFreeChunk.

			\return			True if the address of the chunk is bigger than the address of the passed chunk.
							False if not.

			\brief			Overloads the > operator.
			*/
			NOU_FUNC boolean operator>(const GeneralPurposeAllocatorFreeChunk& other) const;

			/**
			\param other	A const reference to a GeneralPurposeAllocatorFreeChunk.

			\return			True if the address of the chunk is smaller than the address of the passed chunk.
							False if not.

			\brief			Overloads the < operator.
			*/
			NOU_FUNC boolean operator<(const GeneralPurposeAllocatorFreeChunk& other) const;

			/**
			\param other	A const reference to a GeneralPurposeAllocatorFreeChunk.

			\return			True if the address of the chunk is bigger or equal to the address of the passed 
							chunk. False if not.

			\brief			Overloads the >= operator.
			*/
			NOU_FUNC boolean operator>=(const GeneralPurposeAllocatorFreeChunk& other) const;

			/**
			\param other	A const reference to a GeneralPurposeAllocatorFreeChunk.

			\return			True if the address of the chunk is smaller or equal to the address of the passed
							chunk. False if not.

			\brief			Overloads the <= operator.
			*/
			NOU_FUNC boolean operator<=(const GeneralPurposeAllocatorFreeChunk& other) const;

			/**
			\param other	A const reference to a GeneralPurposeAllocatorFreeChunk.
					
			\return			True if the address of the chunk is equal to the address of the passed chunk.
							False if not.

			\brief			Overloads the == operator.
			*/
			NOU_FUNC boolean operator==(const GeneralPurposeAllocatorFreeChunk& other) const;


			/**
			\tparam	T				The return type.
			\tparam ARGS			The passed data of the object.
			\param	args			All passed parameters.
			\param	amountOfObjects	Defines the amount of objects which will be created. Can be set manually or
									use the default size.

			\return					A pointer to the allocated object or a null-pointer if the element could 
									not be allocated.

			\brief					Allocates a new Object with all passed elements.
			*/
			template <typename T, typename... ARGS>
			T* allocateObject(sizeType amountOfObjects, ARGS&&... args);
		};
	}

	/**
	\brief		Defines the GeneralPurposeAllocator class, which is used to allocate and deallocate objects.

	\details	The GeneralPurposeAllocator (GPA) cannot increase its size. If the GPA is constructed with the 
				default size or a passed size it can only be increased by creating a new GPA with a bigger size.
	*/
	class GeneralPurposeAllocator
	{
	public:

		/**
		\tparam T	The type of the pointer.

		\brief		Defines the GeneralPurposeAllocatorPointer class, which is used for saving a pointer to the
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
			\param pdata	A pointer to the elements where the pointer is pointing to.
			\param size		The amount of objects.

			\brief			Creates a pointer to the elements in the GeneralPurposeAllocator.
			*/
			GeneralPurposeAllocatorPointer(T* pdata, sizeType size);

			/**
			\return	The pointer stored in the GeneralPurposeAllocatorPointer.

			\brief	Returns the pointer which is stored in the GeneralPurposeAllocatorPointer.
			*/
			T* operator->();

			/**
			\return The pointer stored in the GeneralPurposeAllocatorPointer.

			\brief	Returns a const pointer to the pointer which is stored in the 
					GeneralPurposeAllocatorPointer.
			*/
			const T* operator->() const;

			/**
			\return A reference to the pointer stored in the GeneralPurposeAllocatorPointer.

			\brief	Returns a reference to the pointer which is stored in the GeneralPurposeAllocatorPointer.
			*/
			T& operator*();

			/**
			\return	A reference to the pointer stored in the GeneralPurposeAllocatorPointer.

			\brief	Returns a const reference to the pointer which is stored in the 
					GeneralPurposeAllocatorPointer.
			*/
			const T& operator*() const;

			/**
			\param index	The index of the element.

			\return			A reference to the element.

			\brief			Returns a reference of the element at the passed index.
			*/
			T& operator[](int index);

			/**
			\param index	The index of the element.

			\return			A const reference to the element.

			\brief			Returns a const reference of the element at the passed index.
			*/
			const T& operator[](int index) const;

			/**
			\return	The pointer which is stored in the GeneralPurposeAllocatorPointer.

			\brief	Returns the raw pointer.
			*/
			T* getRaw();

			/**
			\param ptr	A void pointer.

			\return		True when the pointers are equal and false if not.
			
			\brief		Compares the passed pointer with the stored pointer and checks if they are equal.
			*/
			boolean operator==(void* ptr) const;

			/**
			\param ptr	A void pointer.

			\return		True when the pointers are not equal and false if they are.

			\brief		Compares the passed pointer with the stored pointer and checks if they are not equal.
			*/
			boolean operator!=(void* ptr) const;
		};

	private:

		/**
		\brief The default size of the allocator.
		*/
		static const sizeType GENERAL_PURPOSE_ALLOCATOR_DEFAULT_SIZE = 10 * 1024;

		/**
		\brief A byte pointer to the elements.
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
		\param size	The size of the GPA. Can be set manually or the default size.

		\brief		Creates a new GPA with a passed size or the default size.
		*/
		NOU_FUNC explicit GeneralPurposeAllocator(sizeType size = GENERAL_PURPOSE_ALLOCATOR_DEFAULT_SIZE);

		GeneralPurposeAllocator(const GeneralPurposeAllocator& other) = delete;
		GeneralPurposeAllocator(GeneralPurposeAllocator&& other) = delete;
		GeneralPurposeAllocator& operator=(const GeneralPurposeAllocator& other) = delete;
		GeneralPurposeAllocator& operator=(GeneralPurposeAllocator&& other) = delete;

		/**
		\brief Destructor of the GPA.
		*/
		NOU_FUNC ~GeneralPurposeAllocator();

		/**
		\tparam T				The type of the object which will be allocated.
		\tparam ARGS			The passed data of the object.
		\param	amountOfObjects	Defines the amount of objects which will be created. Can be set manually or
								use the default size.
		\param	args			The data of the object which will be allocated.

		\return					A pointer to the allocated Objects. If the GPA exceeded its maximum capacity
								it will return a null-pointer to indicate that the next object cannot be 
								stored.

		\brief					Allocates memory in the GPA for the passed object. Allows to allocate the 
								passed object multiple times.
		*/
		template <typename T, typename... ARGS>
		GeneralPurposeAllocatorPointer<T> allocateObjects(sizeType amountOfObjects, ARGS&&... args);

		/**
		\tparam T			The type of the object which will be allocated.
		\tparam ARGS		The passed data of the object.
		\param	args		The data of the object which will be allocated.

		\return				A pointer to the allocated Objects. If the GPA exceeded its maximum capacity
							it will return a null-pointer to indicate that the next object cannot
							be stored.

		\brief				Allocates memory in the GPA for the passed object. Allows to allocate the passed 
							object only ones. For multiple allocations of the same object use the 
							allocateObjects().

		\details			Calls the allocateObjects() with the parameter amountOfObjects = 1.
		*/
		template <typename T, typename... ARGS>
		GeneralPurposeAllocatorPointer<T> allocateObject(ARGS&&... args);

		/**
		\tparam T		The type of the object which will be deallocated.
		\param pointer	A  pointer to the object which will be deallocated.

		\brief			Deallocated the object at the location the pointer points to.

		\attention		The checks for a double deallocation are only activated if NOU_DEBUG is defined.
		*/
		template <typename T>
		void deallocateObjects(GeneralPurposeAllocatorPointer<T> pointer);

		/**
		\tparam T				The type of the object in the GPA.
		\param left				A pointer reference to the left element in the GPA.
		\param right			A pointer reference to the right element in the GPA.
		\param insertionIndex	The index where the new element will be inserted.

		\brief					Saves the left and right element in two passed pointers dependent on the 
								insertion index where you want to insert a new element.
		*/
		template<typename T>
		void getNeigbors(T*& left, T*& right, int64 insertionIndex);
	};

	template <typename T, typename... ARGS>
	T* internal::GeneralPurposeAllocatorFreeChunk::allocateObject
	(sizeType amountOfObjects, ARGS&&... args)
	{
		static_assert(alignof(T) <= 128, "Max alignment of 128 was exceeded!");

		byte* allocationLocation = reinterpret_cast<byte*>(nextMultiple(alignof(T), ((sizeType)m_addr) + 1));
		sizeType amountOfBytes = amountOfObjects * sizeof(T);
		byte* newAddr = allocationLocation + amountOfBytes;

		if (newAddr <= m_addr + m_size)
		{
			byte offset = (byte)(allocationLocation - m_addr);
			allocationLocation[-1] = offset;

			T* returnPointer = reinterpret_cast<T*>(allocationLocation);
			m_size -= newAddr - m_addr;
			m_addr = newAddr;

			for (sizeType i = 0; i < amountOfObjects; i++)
			{
				T* object = addressof(returnPointer[i]);
				new(object) T(NOU_CORE::forward<ARGS>(args)...);
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

	template <typename T, typename... ARGS>
	GeneralPurposeAllocator::GeneralPurposeAllocatorPointer<T> 
		GeneralPurposeAllocator::allocateObjects(sizeType amountOfObjects, ARGS&&... args)
	{
		static_assert(alignof(T) <= 128, "Max alignment of 128 was exceeded!");
	
		for (sizeType i = 0; i < m_freeChunks.size(); i++)
		{
			T* data = m_freeChunks[i].allocateObject<T>(amountOfObjects,
				NOU_CORE::forward<ARGS>(args)...);
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

	template<typename T, typename... ARGS>
	GeneralPurposeAllocator::GeneralPurposeAllocatorPointer<T> 
		GeneralPurposeAllocator::allocateObject(ARGS&&...args)
	{
		return allocateObjects<T>(1, NOU_CORE::forward<ARGS>(args)...);
	}

	template <typename T>
	void GeneralPurposeAllocator::deallocateObjects(GeneralPurposeAllocatorPointer<T> pointer)
	{
#ifdef NOU_DEBUG
		//data chunk boundary checks
		if (reinterpret_cast<byte*>(pointer.m_pdata) < m_data ||
			reinterpret_cast<byte*>(pointer.m_pdata) + pointer.m_size >= m_data + m_size)
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::BAD_DEALLOCATION,
					"Tried to deallocated an object that does not exist.");
			return;
		}

		//Checks if the pointer is a free chunks->object already deallocated.
		for (internal::GeneralPurposeAllocatorFreeChunk &chunk : m_freeChunks)
		{
			if (!(reinterpret_cast<byte*>(pointer.m_pdata) < chunk.m_addr ||
				reinterpret_cast<byte*>(pointer.m_pdata + pointer.m_size) >= chunk.m_addr + chunk.m_size))
			{
				NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::BAD_DEALLOCATION,
					"Tried to deallocated an object that does not exist.");
				return;
			}
		}

#endif

		for (sizeType i = 0; i < pointer.m_size; i++)
		{
			addressof(pointer.m_pdata[i])->~T();
		}

		byte* bytePointer = reinterpret_cast<byte*>(pointer.m_pdata);
		sizeType amountOfBytes = sizeof(T) * pointer.m_size;
		byte offset = bytePointer[-1];

		internal::GeneralPurposeAllocatorFreeChunk gpafc(bytePointer - offset, amountOfBytes + offset);

		int64 insertionIndex;
		NOU_DAT_ALG::binarySearch(m_freeChunks, gpafc, 0, -1, &insertionIndex);

		internal::GeneralPurposeAllocatorFreeChunk* p_gpafc = &gpafc;
		internal::GeneralPurposeAllocatorFreeChunk* left;
		internal::GeneralPurposeAllocatorFreeChunk* right;

		getNeigbors(left, right, insertionIndex);

		boolean didMerge = false;

		if (left->m_addr != reinterpret_cast<byte*>(m_freeChunks.data() - 1))
		{
			if (left->touches(*p_gpafc))
			{
				left->m_size += p_gpafc->m_size;
				p_gpafc = left;
				didMerge = true;
			}
		}

		if(right->m_addr != reinterpret_cast<byte*>(m_freeChunks.data() + m_freeChunks.size()))
		{ 
			if (right->touches(*p_gpafc))
			{
				if (didMerge)
				{
					p_gpafc->m_size += right->m_size;
					m_freeChunks.remove(static_cast<sizeType>(insertionIndex));
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
	void GeneralPurposeAllocator::getNeigbors(T*& left, T*& right, int64 insertionIndex)
	{
		left = reinterpret_cast<T*>(m_freeChunks.data() + insertionIndex - 1);
		right = reinterpret_cast<T*>(m_freeChunks.data() + insertionIndex);
	}
}

#endif