#ifndef NOU_DAT_ALG_STRING_HPP
#define	NOU_DAT_ALG_STRING_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\ErrorHandler.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\StringView.hpp"
#include "nostrautils\dat_alg\Vector.hpp"

#include <iostream>
#include <stdlib.h>


/** \file Vector.hpp
\author  Dennis Franz
\author	 Lukas Reichmann
\since   0.0.1
\version 0.0.1
\brief   This file provides a String implementation.
*/

namespace NOU::NOU_DAT_ALG
{


	template<typename CHAR_TYPE = char8>
	class NOU_CLASS String final : public StringView<CHAR_TYPE>
	{
	public:
		using CharType = typename StringView<CHAR_TYPE>::CharType;
		using ConstCharType = typename StringView<CHAR_TYPE>::ConstCharType;

		using StringIterator = VectorIterator<CharType>;
		using StringReverseIterator = VectorReverseIterator<CharType>;

	private:

		/**
		\tparam IT The input type.
		\param i   The integer to convert.
		\return    The converted string.

		\brief Converts a any signed integer into a string.
		*/
		template<typename IT>
		static String genericIntToString(IT i);

		/**
		\tparam IT The input type.
		\param i   The integer to convert.
		\return    The converted string.

		\brief Converts a any unsigned integer into a string.
		*/
		template<typename IT>
		static String genericUintToString(IT i);

		/**
		\tparam IT The input type.
		\param f   The float to convert.
		\return    The converted string.

		\brief Converts a any floating point type number into a string.
		*/
		template<typename IT>
		static String genericFloatToString(IT f);

		/**
		\brief The vector that stores the single characters of the string.
		*/
		Vector<CharType> m_data;

		/**
		\param size The new size (without the null-terminator).

		\brief Since the size is stored in StringView's m_size and \c m_data's internal size, both need to be set when
		the string changes size. This method sets both sizes.
		*/
		void setSize(sizeType size);

	public:
		/**
		\param b The boolean to convert.
		\return  Either \"true\" or \"false\".

		\brief Converts the passed boolean into a string.
		*/
		static String booleanToString(boolean b);

		/**
		\param i The number to convert.
		\return  The passed number as string.

		\brief Converts the passed number into a string.
		*/
		static String intToString(int32 i);
		/**
		\param i The number to convert.
		\return  The passed number as string.

		\brief Converts the passed number into a string.
		*/
		static String intToString(int64 i);

		/**
		\param i The number to convert.
		\return  The passed number as string.

		\brief Converts the passed number into a string.
		*/
		static String intToString(uint32 i);

		/**
		\param i The number to convert.
		\return  The passed number as string.

		\brief Converts the passed number into a string.
		*/
		static String intToString(uint64 i);

		/**
		\param f The number to convert.
		\return  The passed number as string.

		\brief Converts the passed number into a string.
		*/
		static String floatToString(float32 f);

		/**
		\param f The number to convert.
		\return  The passed number as string.

		\brief Converts the passed number into a string.
		*/
		static String floatToString(float64 f);

		/**
		\param str The initial value of the string.

		\brief Constructs a new instance that is filled with the characters from the passed string view.
		*/
		String(const StringView<CHAR_TYPE> &str = "");

		/**
		\param c The initial value of the string.

		\brief Constructs a new instance that is filled with the one character that was passed.
		*/
		String(CharType c);
		/**
		\param c Another String.

		\brief Copy Constructor.
		*/
		String(const String &other);
		/**
		\param c Another String.

		\brief Move Constructor.
		*/
		String(String &&other);

		/**
		\param i The integer to convert and use as initial value.

		\brief Constructs a new instance that is filled with the string representation of the passed integer.
		*/
		String(int32 i);

		/**
		\param i The integer to convert and use as initial value.

		\brief Constructs a new instance that is filled with the string representation of the passed integer.
		*/
		String(int64 i);

		/**
		\param i The integer to convert and use as initial value.

		\brief Constructs a new instance that is filled with the string representation of the passed integer.
		*/
		String(uint32 i);

		/**
		\param i The floating point number to convert and use as initial value.

		\brief Constructs a new instance that is filled with the string representation of the passed floating
		point number.
		*/
		String(uint64 i);

		/**
		\param f The floating point number to convert and use as initial value.

		\brief Constructs a new instance that is filled with the string representation of the passed floating
		point number.
		*/
		String(float32 f);

		/**
		\param f The integer to convert and use as initial value.

		\brief Constructs a new instance that is filled with the string representation of the passed integer.
		*/
		String(float64 f);

		/**
		\param index The index of the character that will be returned.
		\return      The character at the provided index.

		\brief Returns the character at the passed index.
		*/
		CharType& at(sizeType index);

		/**
		\param index The index at which the character will be inserted.
		\param c     The character to insert.
		\return      A reference to the instance itself.

		\brief Inserts the provided character at the provided index.
		*/
		String& insert(sizeType index, CharType c);

		/**
		\param index The index at which the string will be inserted.
		\param str   The string to insert.
		\return      A reference to the instance itself.

		\brief Inserts the provided string at the provided index.
		*/
		String& insert(sizeType index, const StringView<CHAR_TYPE> &str);

		/**
		\param index The index at which the number will be inserted.
		\param nr    The number to insert.
		\return      A reference to the instance itself.

		\brief Inserts the provided number at the provided index.
		*/
		String& insert(sizeType index, int32 nr);

		/**
		\param index The index at which the number will be inserted.
		\param nr    The number to insert.
		\return      A reference to the instance itself.

		\brief Inserts the provided number at the provided index.
		*/
		String& insert(sizeType index, int64 nr);

		/**
		\param index The index at which the number will be inserted.
		\param nr    The number to insert.
		\return      A reference to the instance itself.

		\brief Inserts the provided number at the provided index.
		*/
		String& insert(sizeType index, uint32 nr);

		/**
		\param index The index at which the number will be inserted.
		\param nr    The number to insert.
		\return      A reference to the instance itself.

		\brief Inserts the provided number at the provided index.
		*/
		String& insert(sizeType index, uint64 nr);

		/**
		\param index The index at which the number will be inserted.
		\param nr    The number to insert.
		\return      A reference to the instance itself.

		\brief Inserts the provided number at the provided index.
		*/
		String& insert(sizeType index, float32 nr);

		/**
		\param index The index at which the number will be inserted.
		\param nr    The number to insert.
		\return      A reference to the instance itself.

		\brief Inserts the provided number at the provided index.
		*/
		String& insert(sizeType index, float64 nr);

		/**
		\param c The character to append.
		\return  A reference to the instance itself.

		\brief Appends the provided character.
		*/
		String& append(CharType c);

		/**
		\param str The string to append.
		\return    A reference to the instance itself.

		\brief Appends the provided string.
		*/
		String& append(const StringView<CHAR_TYPE> &str);

		/**
		\param nr The number to append.
		\return   A reference to the instance itself.

		\brief Appends the provided number.
		*/
		String& append(int32 nr);

		/**
		\param nr The number to append.
		\return   A reference to the instance itself.

		\brief Appends the provided number.
		*/
		String& append(int64 nr);

		/**
		\param nr The number to append.
		\return   A reference to the instance itself.

		\brief Appends the provided number.
		*/
		String& append(uint32 nr);

		/**
		\param nr The number to append.
		\return   A reference to the instance itself.

		\brief Appends the provided number.
		*/
		String& append(uint64 nr);

		/**
		\param nr The number to append.
		\return   A reference to the instance itself.

		\brief Appends the provided number.
		*/
		String& append(float32 nr);

		/**
		\param nr The number to append.
		\return   A reference to the instance itself.

		\brief Appends the provided number.
		*/
		String& append(float64 nr);

		/**
		\param b The value that determines weather the character will be appended or not.
		\param c The character to append.
		\return  A reference to the instance itself.

		\brief Appends the provided character if the passed boolean is \c true.
		*/
		String& appendIf(boolean b, CharType c);

		/**
		\param b   The value that determines weather the string will be appended or not.
		\param str The string to append.
		\return    A reference to the instance itself.

		\brief Appends the provided string if the passed boolean is \c true.
		*/
		String& appendIf(boolean b, const StringView<CHAR_TYPE> &str);

		/**
		\param b  The value that determines weather the number will be appended or not.
		\param nr The number to append.
		\return   A reference to the instance itself.

		\brief Appends the provided  if the passed boolean is \c true.
		*/
		String& appendIf(boolean b, int32 nr);

		/**
		\param b  The value that determines weather the number will be appended or not.
		\param nr The number to append.
		\return   A reference to the instance itself.

		\brief Appends the provided  if the passed boolean is \c true.
		*/
		String& appendIf(boolean b, int64 nr);

		/**
		\param b  The value that determines weather the number will be appended or not.
		\param nr The number to append.
		\return   A reference to the instance itself.

		\brief Appends the provided  if the passed boolean is \c true.
		*/
		String& appendIf(boolean b, uint32 nr);

		/**
		\param b  The value that determines weather the number will be appended or not.
		\param nr The number to append.
		\return   A reference to the instance itself.

		\brief Appends the provided  if the passed boolean is \c true.
		*/
		String& appendIf(boolean b, uint64 nr);

		/**
		\param b  The value that determines weather the number will be appended or not.
		\param nr The number to append.
		\return   A reference to the instance itself.

		\brief Appends the provided  if the passed boolean is \c true.
		*/
		String& appendIf(boolean b, float32 nr);

		/**
		\param b  The value that determines weather the number will be appended or not.
		\param nr The number to append.
		\return   A reference to the instance itself.

		\brief Appends the provided  if the passed boolean is \c true.
		*/
		String& appendIf(boolean b, float64 nr);
		/**
		\param replacement the character which will be used to replace.
		\param index The index.

		\brief Replaces a single character.
		*/
		void replace(CharType replacement, sizeType index);

		/**
		\param target      The characters that will be replaced with \p replacement.
		\param replacement The characters that will be used to replace the \p target characters.
		\param start       The start of the interval in which the characters will be replaced. The character at this
		index is included.
		\param end         The end of the interval in which the characters will be replaced. The character at this
		index is excluded. If this is equal to InitValues::SIZE_T_GENERAL_SPECIAL_INDEX, the size of
		the string will be used.
		\return            A reference to the instance itself.

		\brief Finds all \p target characters and replaces them with \p replacement in the interval \f$\left[target,
		replacement\right[\f$.
		*/
		String& replace(CharType target, CharType replacement, sizeType start = 0, sizeType end = NULL_INDEX);

		/**
		\param target      The substrings that will be replaced with \p replacement.
		\param replacement The substrings that will be used to replace the \p target substrings.
		\param start       The start of the interval in which the characters will be replaced. The substrings at this
		index are included.
		\param end         The end of the interval in which the characters will be replaced. The substrings at this
		index are excluded (they are even excluded if the substring started within the valid
		interval, but end at or after this index). If this is equal to
		InitValues::SIZE_T_GENERAL_SPECIAL_INDEX, the size of the string will be used.
		\return            A reference to the instance itself.

		\brief Finds all \p target substrings and replaces them with \p replacement in the interval \f$\left[target,
		replacement\right[\f$.
		*/
		String& replace(const StringView<CHAR_TYPE> &target, const StringView<CHAR_TYPE> &replacement, sizeType start = 0, sizeType end = NULL_INDEX);

		/**
		\param start       The start of the interval of the substring that will be replaced. The character at this
		index is part of the substring.
		\param end         The end of the interval of the substring that will be replaced. The character at this index
		is not part of the substring.
		\param replacement The string that will be used to replace the substring that is marked by \p start and \p end.
		\return            A reference to the instance itself.

		\brief Replaces the substring that is marked by \p start and \p end and replaces it with \p replacement.
		*/
		String& replace(sizeType start, sizeType end, const StringView<CHAR_TYPE> &replacement);

		/**
		\param target      The target string that the substring will be inserted to.
		\param start       The start of the interval that will be copied. The character at this index will be included.
		\param end         The end of the interval that will be copied. The character at this index will be excluded. If
		this is equal to InitValues::SIZE_T_GENERAL_SPECIAL_INDEX, the size of the string will be
		used.
		\param insertIndex The index at which the substring will be inserted in \p target.

		\brief Inserts the substring that is in the interval \f$\left[start, end\right[\f$ of this instance to \p target
		at the index \p insertIndex. This method is the opposite of copySubstringHere() in terms of from where
		the source substring is pulled and where it is inserted.
		*/
		void copySubstringTo(String &target, sizeType start, sizeType end = NULL_INDEX,
			sizeType insertIndex = 0) const;

		/**
		\param src         The target to copy the substring from.
		\param start       The start of the interval that will be copied. The character at this index will be included.
		\param end         The end of the interval that will be copied. The character at this index will be excluded. If
		this is equal to InitValues::SIZE_T_GENERAL_SPECIAL_INDEX, the size of the string will be
		used.
		\param insertIndex The index at which the substring will be inserted.
		\return            A reference to the instance itself.

		\brief Inserts the substring that is in the interval \f$\left[start, end\right[\f$ of \p source into this
		instance at the index \p insertIndex. This method is the opposite of copySubstringTo() in terms of from
		where the source substring is pulled and where it is inserted.
		*/
		String& copySubstringHere(const StringView<CHAR_TYPE> &src, sizeType start,
			sizeType end = NULL_INDEX, sizeType insertIndex = 0);

		/**
		\param c     The character that will be used to fill the range.
		\param start The start of the interval of characters that will be overridden. The character at this index will
		be included.
		\param end   The end of the interval of characters that will be overridden. The character at this index will  be
		excluded.
		\return      A reference to the instance itself.

		\brief Overrides all the characters in the interval \f$\left[start, end\right[\f$ with the character \p c.
		*/
		String& fillRange(CharType c, sizeType start, sizeType end);

		/**
		\param start The start of the interval that will be removed. The character at this index will be included.
		\param end   The end of the interval that will be removed. The character at this index will be excluded. If
		this is equal to InitValues::SIZE_T_GENERAL_SPECIAL_INDEX, the size of the string will be used.
		\return      A reference to the instance itself.

		\brief Removes the characters in the interval \f$\left[start, end\right[\f$. This operation is the exact opposite
		to preserve().
		*/
		String& remove(sizeType start, sizeType end = NULL_INDEX);

		/**
		\param start The start of the interval that will be preserved. The character at this index will be included.
		\param end   The end of the interval that will be preserved. The character at this index will be excluded. If
		this is equal to InitValues::SIZE_T_GENERAL_SPECIAL_INDEX, the size of the string will be used.
		\return      A reference to the instance itself.

		\brief Removes all characters, except those in the interval \f$\left[start, end\right[\f$. This operation is the
		exact opposite to remove(sizeType, sizeType).
		*/
		String& preserve(sizeType start, sizeType end = NULL_INDEX);

		/**
		\param start The start of the interval of the characters that will be in the substring. The character at this
		index will included in the substring.
		\param end   The end of the interval of the characters that will be in the substring. The character at this
		index will excluded in the substring. If this is equal to InitValues::SIZE_T_GENERAL_SPECIAL_INDEX,
		the size of the string will be used.
		\return      A string view that starts at the index \p start of this instance and has a size of \p end -
		\p start.

		\brief Returns a string that contains the characters in the interval \f$\left[start, end\right[\f$.
		*/
		String substring(sizeType start, sizeType end = NULL_INDEX) const;

		/**
		\return A copy of this string.
		\brief  Returns an exact copy of this string. This method can be used to write code in a single line.
		*/
		String copy() const;

		/**
		\param c The character to concatenate this string with.
		\return  A new string that contains the contents of this string and the passed character.

		\brief Concatenates the current string and the passed character into a new string.
		*/
		String concat(CharType c) const;

		/**
		\param str The string to concatenate this string with.
		\return    A new string that contains the contents of this string and the passed string.

		\brief Concatenates the current string and the passed string into a new string.
		*/
		String concat(const StringView<CHAR_TYPE> &str) const;

		/**
		\param i The integer to concatenate this string with.
		\return  A new string that contains the contents of this string and the passed integer.

		\brief Concatenates the current string and the passed integer into a new string.
		*/
		String concat(int32 i) const;

		/**
		\param i The integer to concatenate this string with.
		\return  A new string that contains the contents of this string and the passed integer.

		\brief Concatenates the current string and the passed integer into a new string.
		*/
		String concat(int64 i) const;

		/**
		\param i The integer to concatenate this string with.
		\return  A new string that contains the contents of this string and the passed integer.

		\brief Concatenates the current string and the passed integer into a new string.
		*/
		String concat(uint32 i) const;

		/**
		\param i The integer to concatenate this string with.
		\return  A new string that contains the contents of this string and the passed integer.

		\brief Concatenates the current string and the passed integer into a new string.
		*/
		String concat(uint64 i) const;

		/**
		\param f The float to concatenate this string with.
		\return  A new string that contains the contents of this string and the passed float.

		\brief Concatenates the current string and the passed float into a new string.
		*/
		String concat(float32 f) const;

		/**
		\param f The float to concatenate this string with.
		\return  A new string that contains the contents of this string and the passed float.

		\brief Concatenates the current string and the passed float into a new string.
		*/
		String concat(float64 f) const;

		/**
		\param b The value that determines weather the number will be concatenated or not.
		\param c The character to concatenate this string with.
		\return  A new string that contains the contents of this string and the passed character.

		\brief Concatenates the current string and the passed character into a new string, but only if \p b is \c true.
		*/
		String concatIf(boolean b, CharType c) const;

		/**
		\param b   The value that determines weather the number will be concatenated or not.
		\param str The string to concatenate this string with.
		\return    A new string that contains the contents of this string and the passed string.

		\brief Concatenates the current string and the passed string into a new string, but only if \p b is \c true.
		*/
		String concatIf(boolean b, const StringView<CHAR_TYPE> &str) const;

		/**
		\param b The value that determines weather the number will be concatenated or not.
		\param i The integer to concatenate this string with.
		\return  A new string that contains the contents of this string and the passed integer.

		\brief Concatenates the current string and the passed integer into a new string, but only if \p b is \c true.
		*/
		String concatIf(boolean b, int32 i) const;

		/**
		\param b The value that determines weather the number will be concatenated or not.
		\param i The integer to concatenate this string with.
		\return  A new string that contains the contents of this string and the passed integer.

		\brief Concatenates the current string and the passed integer into a new string, but only if \p b is \c true.
		*/
		String concatIf(boolean b, int64 i) const;

		/**
		\param b The value that determines weather the number will be concatenated or not.
		\param i The integer to concatenate this string with.
		\return  A new string that contains the contents of this string and the passed integer.

		\brief Concatenates the current string and the passed integer into a new string, but only if \p b is \c true.
		*/
		String concatIf(boolean b, uint32 i) const;

		/**
		\param b The value that determines weather the number will be concatenated or not.
		\param i The integer to concatenate this string with.
		\return  A new string that contains the contents of this string and the passed integer.

		\brief Concatenates the current string and the passed integer into a new string, but only if \p b is \c true.
		*/
		String concatIf(boolean b, uint64 i) const;

		/**
		\param b The value that determines weather the number will be concatenated or not.
		\param f The float to concatenate this string with.
		\return  A new string that contains the contents of this string and the passed float.

		\brief Concatenates the current string and the passed float into a new string, but only if \p b is \c true.
		*/
		String concatIf(boolean b, float32 f) const;

		/**
		\param b The value that determines weather the number will be concatenated or not.
		\param f The float to concatenate this string with.
		\return  A new string that contains the contents of this string and the passed float.

		\brief Concatenates the current string and the passed float into a new string, but only if \p b is \c true.
		*/
		String concatIf(boolean b, float64 f) const;

		/**
		\return The vector that is internally used.

		\brief Returns the vector that is internally used. If the string is needed as a pointer (e.g. as C-string, if
		\c CHAR_TYPE is \c char), rawString() is a better method to obtain such pointer.
		*/
		const Vector<CharType>& data() const;

		/**
		\return A reference to the instance itself.

		\brief Converts all characters in the string to their lower case equivalent.
		*/
		String& toLowerCase();

		/**
		\return A reference to the instance itself.

		\brief Converts all characters in the string to their upper case equivalent.
		*/
		String& toUpperCase();

		/**
		\return A reference to the instance itself.

		\brief Removes all white spaces (characters with numeric values 0x9 and 0x29) at the end and front of the string.

		\details
		Removes all white spaces (characters with numeric values 0x9 and 0x29) at the end and front of the string.

		Example:
		The string
		\code{.cpp}
		"   test   "
		\endcode
		would result in
		\code{.cpp}
		"test"
		\endcode
		*/
		String& trim();

		/**
		\return A reference to the instance itself.

		\brief Clears the string from all characters and sets the size to 0.
		*/
		String& clear();
		/**
		\return A StringIterator that points to the first character in the string.
		\brief  Returns a StringIterator that points to the first character in the string.
		*/
		StringIterator begin();

		/**
		\return A StringIterator that points to the character after the last character in the string.
		\brief  Returns a StringIterator that points to the character after the last character in the string.
		*/
		StringIterator end();

		/**
		\param index The index at which this iterator will start.
		\return      A StringIterator that points to the character at the passed index.
		\brief       Returns a StringIterator that points to the character at the passed index.
		*/
		StringIterator indexIterator(sizeType index);

		/**
		\param index The index at which this iterator will start.
		\return      A StringReverseIterator that points to the character at the passed index.
		\brief       Returns a StringReverseIterator that points to the character at the passed index.
		*/
		StringReverseIterator indexRIterator(sizeType index);

		/**
		\return A StringReverseIterator that points to the last character in the string.
		\brief  Returns a StringReverseIterator that points to the last character in the string.
		*/
		StringReverseIterator rbegin();

		/**
		\return A StringReverseIterator that points to the character before the first character in the string.
		\brief  Returns a StringReverseIterator that points to the character before the first character in the
		string.
		*/
		StringReverseIterator rend();

		/**
		\param c The character to concatenate.
		\return  \code{.cpp}this->concat(c)\endcode

		\brief Calls concat(CharType).
		*/
		String operator + (CharType c) const;

		/**
		\param str The string to concatenate.
		\return    \code{.cpp}this->concat(str)\endcode

		\brief Calls concat(const StringView&).
		*/
		String operator + (const StringView<CHAR_TYPE> &str) const;

		/**
		\param i The integer to concatenate.
		\return  \code{.cpp}this->concat(i)\endcode

		\brief Calls concat(int32).
		*/
		String operator + (int32 i) const;

		/**
		\param i The integer to concatenate.
		\return  \code{.cpp}this->concat(i)\endcode

		\brief Calls concat(int64).
		*/
		String operator + (int64 i) const;

		/**
		\param i The integer to concatenate.
		\return  \code{.cpp}this->concat(i)\endcode

		\brief Calls concat(uint32).
		*/
		String operator + (uint32 i) const;

		/**
		\param i The integer to concatenate.
		\return \code{.cpp}this->concat(i)\endcode

		\brief Calls concat(uint64).
		*/
		String operator + (uint64 i) const;

		/**
		\param f The float to concatenate.
		\return  \code{.cpp}this->concat(f)\endcode

		\brief Calls concat(float32).
		*/
		String operator + (float32 f) const;

		/**
		\param f The float to concatenate.
		\return  \code{.cpp}this->concat(f)\endcode

		\brief Calls concat(float64).
		*/
		String operator + (float64 f) const;

		/**
		\param c The integer to append.
		\return  \code{.cpp}this->append(c)\endcode

		\brief Calls append(CharType).
		*/
		String& operator += (CharType c);

		/**
		\param str The integer to append.
		\return    \code{.cpp}this->append(str)\endcode

		\brief Calls append(const StringView&).
		*/
		String& operator += (const StringView<CHAR_TYPE> &str);

		/**
		\param i The integer to append.
		\return  \code{.cpp}this->append(i)\endcode

		\brief Calls append(int32).
		*/
		String& operator += (int32 i);

		/**
		\param i The integer to append.
		\return  \code{.cpp}this->append(i)\endcode

		\brief Calls append(int64).
		*/
		String& operator += (int64 i);

		/**
		\param i The integer to append.
		\return  \code{.cpp}this->append(i)\endcode

		\brief Calls append(uint32).
		*/
		String& operator += (uint32 i);

		/**
		\param i The integer to append.
		\return  \code{.cpp}this->append(i)\endcode

		\brief Calls append(uint64).
		*/
		String& operator += (uint64 i);

		/**
		\param f The float to append.
		\return  \code{.cpp}this->append(f)\endcode

		\brief Calls append(float32).
		*/
		String& operator += (float32 f);

		/**
		\param f The float to append.
		\return  \code{.cpp}this->append(f)\endcode

		\brief Calls append(float64).
		*/
		String& operator += (float64 f);

		/**
		\param index The index of the character that will be returned.
		\return      The character at the provided index

		\brief Returns the character at the passed index. This is equal to at().
		*/
		CharType& operator [] (sizeType index);
	};

	template<typename CHAR_TYPE>
	template<typename IT>
	String<CHAR_TYPE> String<CHAR_TYPE>::genericIntToString(IT i)			
	{
		
		String<CHAR_TYPE> str;
		IT temp = i;

		if (i < 0)
		{
			i = i * (-1); //ABS MATH
		}

		while (i != 0)
		{
			char8 c = (i % 10) + '0';
			str.insert(0, c);
			i = i / 10;
		}

		if (temp < 0)
		{
			str.insert(0, "-");
		}

		return str;

	}
	template<typename CHAR_TYPE>
	template<typename IT>
	String<CHAR_TYPE> String<CHAR_TYPE>::genericUintToString(IT i)			
	{
		String<CHAR_TYPE> str;

		while (i != 0)
		{
			char8 c = (i % 10) + '0';
			str.insert(0, c);
			i = i / 10;
		}

		return str;
	}
	template<typename CHAR_TYPE>
	template<typename IT>
	String<CHAR_TYPE> String<CHAR_TYPE>::genericFloatToString(IT f)	
	{

		IT tempFloat = f;
		NOU::uint32 integ_part = (int)f;
		NOU::uint32 integPartdigitCount = integ_part;
		NOU::uint32 i = 0;
		NOU::uint32 zerocounter = 0;

		while (integPartdigitCount != 0)
		{
			integPartdigitCount = integPartdigitCount / 10;
			i++;
		}

		i = 17 - i;

		String<CHAR_TYPE> str;
		String<CHAR_TYPE> int_part;

		int_part.append(genericIntToString(integ_part));
		str.append(int_part);
		str.append('.');

		tempFloat = f - integ_part;

		if (tempFloat == 0)
		{
			str.insert(0, '0');
			return str;
		}

		while (i > 0)
		{
			tempFloat *= 10;
			if (static_cast<NOU::uint32>(tempFloat) == 0)
			{
				zerocounter++;
			}
			i--;
		}

		NOU::int64 tempint = static_cast<NOU::uint64>(tempFloat);
		tempint = tempint / 10;

		if (tempint % 10 >= 5)
		{
			NOU::int64 lastdigit = tempint % 10;
			tempint += (10 - lastdigit);
		}

		sizeType endOfString = str.size();

		while (tempint != 0)
		{
			if (tempint % 10 != 0)
			{
				char8 c = (tempint % 10) + '0';
				str.insert(endOfString, c);
			}
			else if (str[str.size() - 1] != '.')
			{
				str.insert(endOfString, '0');
			}
			tempint = tempint / 10;
		}

		for (sizeType z = 0; z < zerocounter; z++)
		{
			str.insert(endOfString, '0');
		}

		return str;
	}

	template<typename CHAR_TYPE>
	void String<CHAR_TYPE>::setSize(sizeType size)
	{
		StringView<CHAR_TYPE>::m_size = size;
	}

	template<typename CHAR_TYPE>
	inline String<CHAR_TYPE> String<CHAR_TYPE>::booleanToString(boolean b)					
	{
		String<CHAR_TYPE> str;

		if (b)
			str.append("true");
		else
			str.append("false");

		return str;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::intToString(int32 i)					
	{
		return genericIntToString(i);
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::intToString(int64 i)					
	{
		return genericIntToString(i);
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::intToString(uint32 i)					
	{
		return genericIntToString(i);
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::intToString(uint64 i)					
	{
		return genericIntToString(i);
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::floatToString(float32 f)					
	{
		return genericFloatToString(f);
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::floatToString(float64 f)					
	{
		return  genericFloatToString(f);
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>::String(const StringView<CHAR_TYPE> &str) :
		m_data(str.size()),
		StringView<CHAR_TYPE>(const_cast<ConstCharType **>(&m_data.data()), str.size())
	{
		for (sizeType i = 0; i < str.size(); i++)
		{
			m_data.pushBack(str.at(i));
		}

		m_data.pushBack(NOU::NOU_DAT_ALG::StringView<CHAR_TYPE>::NULL_TERMINATOR);


		setSize(str.size() - 1);
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>::String(CharType c) :
		m_data(1),
		StringView<CHAR_TYPE>(const_cast<ConstCharType **>(&m_data.data()), 1)
	{

		m_data.pushBack(c);

		m_data.pushBack(NOU::NOU_DAT_ALG::StringView<CHAR_TYPE>::NULL_TERMINATOR);


		setSize(m_data.size() - 1);
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>::String(const String<CHAR_TYPE> &other) :
		m_data(other.m_data),
		StringView<CHAR_TYPE>(const_cast<ConstCharType **>(&m_data.data()), other.size())
	{}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>::String(String<CHAR_TYPE> &&other) :
		m_data(NOU_CORE::forward<decltype(m_data)>(other.m_data)),
		StringView<CHAR_TYPE>(const_cast<ConstCharType **>(&m_data.data()), other.size())
	{}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>::String(int32 i) : 
		String(NOU_CORE::move(intToString(i)))
	{}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>::String(int64 i)	:
		String(NOU_CORE::move(intToString(i)))
	{}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>::String(uint32 i)	 :
		String(NOU_CORE::move(intToString(i)))
	{}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>::String(uint64 i)	:
		String(NOU_CORE::move(intToString(i)))
	{}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>::String(float32 f) :	
		String(NOU_CORE::move(floatToString(f)))
	{}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>::String(float64 f) :	
		String(NOU_CORE::move(floatToString(f)))
	{}

	template<typename CHAR_TYPE>
	typename String<CHAR_TYPE>::CharType& String<CHAR_TYPE>::at(sizeType index)
	{
		return m_data.at(index);
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::insert(sizeType index, CharType c)
	{
		NOU_COND_PUSH_ERROR((index > m_data.size() - 1),
			NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS, "An index was out of bounds.");

		m_data.insert(c, index);
		setSize(m_data.size() - 1);
		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::insert(sizeType index, const StringView<CHAR_TYPE>& str)
	{

		for (sizeType i = 0; i < str.size(); i++)
		{
			insert(index + i, str[i]);

		}
		setSize(m_data.size() - 1);
		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::insert(sizeType index, int32 nr)
	{

		insert(index, intToString(nr));
		setSize(m_data.size() - 1);
		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::insert(sizeType index, int64 nr)
	{
		insert(index, intToString(nr));
		setSize(m_data.size() - 1);
		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::insert(sizeType index, uint32 nr)
	{
		insert(index, intToString(nr));
		setSize(m_data.size() - 1);
		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::insert(sizeType index, uint64 nr)
	{
		insert(index, intToString(nr));
		setSize(m_data.size() - 1);
		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::insert(sizeType index, float32 nr)
	{
		insert(index, floatToString(nr));
		setSize(m_data.size() - 1);
		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::insert(sizeType index, float64 nr)
	{
		insert(index, floatToString(nr));
		setSize(m_data.size() - 1);
		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::append(CharType c)
	{
		insert(m_data.size() - 1, c);
		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::append(const StringView<CHAR_TYPE>& str)
	{

		insert(m_data.size() - 1, str);
		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::append(int32 nr)
	{
		insert(m_data.size() - 1, intToString(nr));
		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::append(int64 nr)
	{
		insert(m_data.size() - 1, intToString(nr));
		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::append(uint32 nr)
	{
		insert(m_data.size() - 1, intToString(nr));
		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::append(uint64 nr)
	{
		insert(m_data.size() - 1, intToString(nr));
		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::append(float32 nr)
	{
		insert(m_data.size() - 1, floatToString(nr));
		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::append(float64 nr)
	{
		insert(m_data.size() - 1, floatToString(nr));
		return *this;
	}

	template<typename CHAR_TYPE>
	void String<CHAR_TYPE>::replace(CharType replacement, sizeType)
	{

		m_data.at(i) = replacement;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::replace(CharType target, CharType replacement, sizeType start, sizeType end)
	{
		NOU_COND_PUSH_ERROR((start > m_data.size() - 1 || end > m_data.size() - 1), 
			NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS, "An index was out of bounds.");

		for (sizeType i = start; i < end; i++)
		{
			if (target == m_data.at(i))
			{
				m_data.replace(replacement, i);
			}
		}

		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::replace(const StringView<CHAR_TYPE>& target, const StringView<CHAR_TYPE>& replacement, sizeType start, sizeType end)
	{
		NOU_COND_PUSH_ERROR((start > m_data.size() - 1 || end > m_data.size() - 1),
			NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS, "An index was out of bounds.");

		for (sizeType i = start; i < end; i++)
		{
			if (target == m_data.at(i))
			{
				m_data.replace(replacement, i);
			}
		}

		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::replace(sizeType start, sizeType end, const StringView<CHAR_TYPE>& replacement)
	{
		NOU_COND_PUSH_ERROR((start > m_data.size() - 1 || end > m_data.size() - 1),
			NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS, "An index was out of bounds.");

		for (sizeType i = start; i <end; i++)
		{
			m_data.replace(replacement, i);
		}

		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::appendIf(boolean b, CharType c)
	{
		if (b)
			append(c);

		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::appendIf(boolean b, const StringView<CHAR_TYPE>& str)
	{
		if (b)
			append(str);

		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::appendIf(boolean b, int32 nr)
	{
		if (b)
			append(intToString(nr));

		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::appendIf(boolean b, int64 nr)
	{
		if (b)
			append(intToString(nr));

		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::appendIf(boolean b, uint32 nr)
	{
		if (b)
			append(intToString(nr));

		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::appendIf(boolean b, uint64 nr)
	{
		if (b)
			appendk(intToString(nr));

		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::appendIf(boolean b, float32 nr)
	{
		if (b)
			append(FloatToString(nr));

		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::appendIf(boolean b, float64 nr)
	{
		if (b)
			append(FloatToString(nr));

		return *this;
	}

	template<typename CHAR_TYPE>
	void String<CHAR_TYPE>::copySubstringTo(String & target, sizeType start, sizeType end, sizeType insertIndex) const
	{
		target.insert(insertIndex, substring(start, end));
		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::copySubstringHere(const StringView<CHAR_TYPE>& src, sizeType start, sizeType end, sizeType insertIndex)
	{
		m_data.insert(insertIndex, src.logicalSubstring(start, end))
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::fillRange(CharType c, sizeType start, sizeType end)
	{
		NOU_COND_PUSH_ERROR((start > m_data.size() - 1),
			NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS, "An index was out of bounds.");

		else if (start <= m_data.capacity() && end > m_data.capacity())
		{
			m_data.expandCapacity(end - m_data.capacity());
		}

		for (sizeType i = start; i < end; i++)
		{
			m_data.replace(c, i);
		}

		setSize(m_data.size() - 1);
		return *this;

	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::remove(sizeType start, sizeType end)
	{
		for (sizeType i = start; i < end; i++)
		{
			m_data.remove(i);
		}

		setSize(m_data.size() - 1);
		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::preserve(sizeType start, sizeType end)
	{
		NOU_COND_PUSH_ERROR((start > m_data.size() - 1 || end > m_data.size() - 1),
			NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS, "An index was out of bounds.");

		for (sizeType i = 0; i < m_data.size() - 1; i++)
		{
			if (i == start)
				i = end;

			m_data.remove(i);
		}

		setSize(m_data.size() - 1);
		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::substring(sizeType start, sizeType end) const
	{
		String<CHAR_TYPE> strnew;

		for (sizeType i = start; i < end; i++)
		{
			strnew.m_data.at(i) = m_data.at(i);
		}
		strnew.setSize(strnew.m_data.size() - 1);

		return strnew;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::copy() const
	{
		String<CHAR_TYPE> strnew;

		for (sizeType i = 0; i < m_data.size()-1; i++)
		{
			strnew.append(m_data[i]);
		}

		return strnew;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::concat(CharType c) const
	{
		String<CHAR_TYPE> strnew;
		append(c);
		return copy();
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::concat(const StringView<CHAR_TYPE>& str) const
	{
		String<CHAR_TYPE> strnew;
		append(str);
		return copy();
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::concat(int32 i) const
	{
		String<CHAR_TYPE> strnew;
		append(i);
		return copy();
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::concat(int64 i) const
	{
		String<CHAR_TYPE> strnew;
		append(i);
		return copy();
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::concat(uint32 i) const
	{
		String<CHAR_TYPE> strnew;
		append(i);
		return copy();
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::concat(uint64 i) const
	{
		String<CHAR_TYPE> strnew;
		append(i);
		return copy();
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::concat(float32 f) const
	{
		String<CHAR_TYPE> strnew;
		append(f);
		return copy();
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::concat(float64 f) const
	{
		String<CHAR_TYPE> strnew;
		append(f);
		return copy();
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::concatIf(boolean b, CharType c) const
	{
		String<CHAR_TYPE> strnew;
		appendIf(b, c);
		return copy();
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::concatIf(boolean b, const StringView<CHAR_TYPE>& str) const
	{
		String<CHAR_TYPE> strnew;
		appendIf(b, str);
		return copy();
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::concatIf(boolean b, int32 i) const
	{
		String<CHAR_TYPE> strnew;
		appendIf(b, i);
		return copy();
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::concatIf(boolean b, int64 i) const
	{
		String<CHAR_TYPE> strnew;
		appendIf(b, i);
		return copy();
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::concatIf(boolean b, uint32 i) const
	{
		String<CHAR_TYPE> strnew;
		appendIf(b, i);
		return copy();
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::concatIf(boolean b, uint64 i) const
	{
		String<CHAR_TYPE> strnew;
		appendIf(b, i);
		return copy();
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::concatIf(boolean b, float32 f) const
	{
		String<CHAR_TYPE> strnew;
		appendIf(b, f);
		return copy();
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::concatIf(boolean b, float64 f) const
	{
		String<CHAR_TYPE> strnew;
		appendIf(b, f);
		return copy();
	}

	template<typename CHAR_TYPE>
	const Vector<typename String<CHAR_TYPE>::CharType>& String<CHAR_TYPE>::data() const
	{
		return m_data; 
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::toLowerCase()
	{
		for (sizeType i = 0; i < m_data.size() - 1; i++)
		{
			if (m_data.at(i) >= '\u0040' && m_data.at(i) <= '\u005A') // \u0040 (A) upper letter unicode, \u005A upper letter unicode (Z) 
			{
				String<CHAR_TYPE>::CharType c = m_data.at(i) + 32;  // adds +32 to convert the upper case letter \u0040 - \u005A to lower case letter \u0060 - \u007A
				m_data.replace(c, i);								// example: A (\u0040) toLowerCase = a (\u0060)
			}
		}

		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::toUpperCase()
	{
		for (sizeType i = 0; i < m_data.size() - 1; i++)
		{
			if (m_data.at(i) >= '\u0060' && m_data.at(i) <= '\u007A') //same just vice versa toLowerCase.
			{
				String<CHAR_TYPE>::CharType c = m_data.at(i) - 32; 
				m_data.replace(c, i);
			}
		}

		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::trim()
	{
		sizeType endofstring = m_data.size() - 2;

		while (m_data.at(endofstring) == '\u0020' || m_data.at(endofstring) == '\u000A')
		{
			m_data.remove(endofstring);
			endofstring--;
		}

		sizeType startofstring = 0;

		while (m_data.at(startofstring) == '\u0020' || m_data.at(startofstring) == '\u000A')
		{
			m_data.remove(startofstring);
			startofstring++;

		}
		setSize(m_data.size() - 1);
		return *this;
	}

	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::clear()
	{
		m_data.clear();
		setSize(m_data.size());
		m_data.pushBack(NOU::NOU_DAT_ALG::StringView<CHAR_TYPE>::NULL_TERMINATOR);
		setSize(m_data.size() - 1);
		return *this;
	}

	template<typename CHAR_TYPE>
	typename String<CHAR_TYPE>::StringIterator String<CHAR_TYPE>::begin()
	{
		return m_data.begin();
	}

	template<typename CHAR_TYPE>
	typename String<CHAR_TYPE>::StringIterator String<CHAR_TYPE>::end()
	{
		return m_data.end();
	}

	template<typename CHAR_TYPE>
	typename String<CHAR_TYPE>::StringIterator String<CHAR_TYPE>::indexIterator(sizeType index)
	{
		return m_data.indexIterator(index);
	}

	template<typename CHAR_TYPE>
	typename String<CHAR_TYPE>::StringReverseIterator String<CHAR_TYPE>::indexRIterator(sizeType index)
	{
		return m_data.rindexIterator(index);
	}

	template<typename CHAR_TYPE>
	typename String<CHAR_TYPE>::StringReverseIterator String<CHAR_TYPE>::rbegin()
	{
		return m_data.rbegin();
	}

	template<typename CHAR_TYPE>
	typename String<CHAR_TYPE>::StringReverseIterator String<CHAR_TYPE>::rend()
	{
		return m_data.rend();
	}
	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::operator+(CharType c) const
	{
		return concat(c);
	}
	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::operator+(const StringView<CHAR_TYPE>& str) const
	{
		return concat(str);
	}
	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::operator+(int32 i) const
	{
		return concat(i);
	}
	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::operator+(int64 i) const
	{
		return concat(i);
	}
	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::operator+(uint32 i) const
	{
		return concat(i);
	}
	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::operator+(uint64 i) const
	{
		return concat(i);
	}
	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::operator+(float32 f) const
	{
		return concat(f);
	}
	template<typename CHAR_TYPE>
	String<CHAR_TYPE> String<CHAR_TYPE>::operator+(float64 f) const
	{
		return concat(f);
	}
	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::operator+=(CharType c)
	{
		append(c);
		return *this;
	}
	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::operator+=(const StringView<CHAR_TYPE>& str)
	{
		append(str);
		return *this;
	}
	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::operator+=(int32 i)
	{
		append(i);
		return *this;
	}
	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::operator+=(int64 i)
	{
		append(i);
		return *this;
	}
	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::operator+=(uint32 i)
	{
		append(i);
		return *this;
	}
	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::operator+=(uint64 i)
	{
		append(i);
		return *this;
	}
	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::operator+=(float32 f)
	{
		append(f);
		return *this;
	}
	template<typename CHAR_TYPE>
	String<CHAR_TYPE>& String<CHAR_TYPE>::operator+=(float64 f)
	{
		append(f);
		return *this;
	}
	template<typename CHAR_TYPE>
	typename String<CHAR_TYPE>::CharType& String<CHAR_TYPE>::operator [] (sizeType index)
	{
		return m_data.at(index);
	}
}


#endif