#ifndef NOU_DAT_ALG_POINTER_HPP
#define NOU_DAT_ALG_POINTER_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\Utils.hpp"

namespace NOU::NOU_MEM_MNGT
{
	/**
	\tparam T The type of object to delete.

	\brief An aliasname for a deleter that is used by the various smart pointer types.
	*/
	template<typename T>
	using Deleter = void(*)(T*);

	template<typename T>
	NOU_FUNC void defaultDeleter(T *t);

	template<typename T>
	NOU_FUNC void defaultArrayDeleter(T *t);

	template<typename T>
	NOU_FUNC void uninitializedDeleter(T *t);

	template<typename T>
	class SmartPtrTempl
	{
	public:
		using Type = T;

	private:
		T*      m_ptr;
		Deleter m_deleter; //not called!

	public:
		SmartPtrTempl(T *ptr);

		T* rawPtr();
		const T* rawPtr() const;

		Deleter deleter() const;

		T& operator [] (sizeType index);
		const T& operator [] (sizeType index) const;

		T* operator -> ();
		const T* operator -> () const;

		T& operator * ();
		const T& operator * () const;

		T** operator & ();
		const T** operator & () const;

		boolean operator boolean () const;


	};

	template<typename T>
	class NOU_CLASS UniquePtr final
	{
	
	};


	template<typename T>
	void defaultDeleter(T *t)
	{
		delete t;
	}

	template<typename T>
	void defaultArrayDeleter(T *t)
	{
		delete[] t
	}

	template<typename T>
	void uninitializedDeleter(T *t)
	{
		deallocateUninitialized(t);
	}
}

#endif