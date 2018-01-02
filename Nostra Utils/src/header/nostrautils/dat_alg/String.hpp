#ifndef NOU_DAT_ALG_STRING_HPP
#define	NOU_DAT_ALG_STRING_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"

namespace NOU::NOU_DAT_ALG
{


	///\cond
	class StringIterator;

	class StringReverseIterator;
	///\endcond

	using StringConstIterator = const StringIterator;

	using StringReverseConstIterator = const StringReverseIterator;


	class NOU_CLASS String 
	{
	private:
		static const sizeType							NPOS = -1;
		NOU::NOU_MEM_MNGT::AllocationCallback<char>		&m_allocator;
		sizeType										m_size;
		sizeType										m_capacity;
		char*											*m_str;

		char*											alloc(sizeType amount);
		void											free(char *str);
		void											reallocateData(sizeType capacity);

	public:
		/**
		\param Main Constructor.
		*/
		String(NOU::NOU_MEM_MNGT::AllocationCallback<char> &allocator = NOU_MEM_MNGT::GenericAllocationCallback<char>::getInstance());
		/**
		\param Substring Constructor.
		*/
		String(const String &str, sizeType pos, sizeType len = NPOS, NOU::NOU_MEM_MNGT::AllocationCallback<char> &allocator = NOU_MEM_MNGT::GenericAllocationCallback<char>::getInstance());
		/**
		\param C-String Constructor.
		*/
		String(const char* s, NOU::NOU_MEM_MNGT::AllocationCallback<char> &allocator = NOU_MEM_MNGT::GenericAllocationCallback<char>::getInstance());
		/**
		\param Copy Constructor.
		*/
		String(const String &str);
		/**
		\param Move Constructor.
		*/
		String(String &&str) noexcept;
		/**
		\param Destructor.
		*/
		~String();

		String& operator= (const String &str);
		String& operator= (const char* s);
		String& operator= (char c);
		String& operator= (String &&str) noexcept;

		StringIterator begin();
		StringIterator end();
		StringIterator indexIterator(sizeType index);
		StringConstIterator begin() const;
		StringConstIterator end() const;
		StringConstIterator indexIterator(sizeType index) const;
		StringReverseIterator rbegin();
		StringReverseIterator rend();
		StringReverseIterator rindexIterator(sizeType index);
		StringReverseConstIterator rbegin() const;
		StringReverseConstIterator rend() const;
		StringReverseConstIterator rindexIterator(sizeType index) const;

		sizeType size();
		sizeType capacity();
		void resize(sizeType index);
		void clear() noexcept;
		boolean empty();

		String& operator+= (const String &str);
		String& operator+= (const char* s);
		String& operator+= (char c);
		String& append(const String &str);
		String& append(const String &str, sizeType subpos, sizeType sublen = NPOS);
		String& append(const char* s);
		void push_back(char c);
		String& assign(const String &str);
		String& assign(const String &str, sizeType subpos, sizeType sublen = NPOS);
		String& assign(const char* s);
		String& insert(sizeType pos, const String &str);
		String& insert(sizeType pos, const String &str, sizeType subpos, sizeType sublen = NPOS);
		String& insert(sizeType pos, const char* s);
		String& erase(sizeType pos = 0, sizeType len = NPOS);
		StringIterator erase(StringConstIterator p);
		StringIterator erase(StringConstIterator first, StringConstIterator last);
		String& replace(sizeType pos, sizeType len, const String &str);
		String& replace(StringConstIterator i1, StringConstIterator i2, const String &str);
		String& replace(sizeType pos, sizeType len, const String &str, sizeType subpos, sizeType sublen = NPOS);
		String& replace(sizeType pos, sizeType len, const char* s);
		String& replace(StringConstIterator i1, StringConstIterator i2, const char* s);
		void swap(String &str);
		void pop_back();
	};

	class NOU_CLASS StringIterator
	{
		friend class String;

	private:
		char               **m_dataPtr;
		mutable sizeType   m_index; //mutable to allow operator ++ to be const

	public:
		StringIterator(sizeType index, const char **strPtr);
		char& operator * ();
		const char& operator * () const;
		char* operator -> ();
		const char* operator -> () const;
		StringIterator& operator ++ ();
		const StringIterator& operator ++ () const;
		StringIterator operator ++ (int) const;
		boolean operator == (const StringIterator &other) const;
		boolean operator != (const StringIterator &other) const;
	};

	class NOU_CLASS StringReverseIterator
	{
		friend class String;

	private:

		char               **m_dataPtr;
		mutable sizeType   m_index; //mutable to allow operator ++ to be const

	public:
		StringReverseIterator(sizeType index, const char **strPtr);
		char& operator * ();
		const char& operator * () const;
		char* operator -> ();
		const char* operator -> () const;
		StringReverseIterator& operator ++ ();
		const StringReverseIterator& operator ++ () const;
		StringReverseIterator operator ++ (int) const;
		boolean operator == (const StringReverseIterator &other) const;
		boolean operator != (const StringReverseIterator &other) const;
	};
}


#endif