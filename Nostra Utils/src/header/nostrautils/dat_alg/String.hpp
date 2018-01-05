#ifndef NOU_DAT_ALG_STRING_HPP
#define	NOU_DAT_ALG_STRING_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\StringView.hpp"
#include "nostrautils\dat_alg\Vector.hpp"

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
		\param additionalCapactiy The minimum additional capacity that this string has after calling
		this method.

		\brief Expands the capacity of the string in a way that it is guaranteed that after
		this method the string has at least a capacity of the old capacity + \p additionalCapactiy.
		This method behaves exactly like gul::container::Vector::expandIfNeeded().
		*/
		void expandIfNeeded(sizeType additionalCapactiy);

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
		\param replacement The strint that will be used to replace the substring that is marked by \p start and \p end.
		\return            A reference to the instance itself.

		\brief Replaces the substring that is marked by \p start and \p end and replaces it with \p replacement.
		*/
		String& replace(sizeType start, sizeType end, const StringView<CHAR_TYPE> &replacement);

		/**
		\tparam SELECTOR The type of the selector that will be used to select the characters to replace. This must be a
		selector according to gul::functional::assertSelector<SELECTOR,
		gul::container::String::CharType>().
		\tparam SUPPLIER The type of the supplier that will be used to make the replacement characters. This must be a
		supplier according to gul::functional::assertSelector<SUPPLIER,
		gul::container::String::CharType, gul::container::String::ConstCharType&>().
		\param selector  A selector of the type SELECTOR that will be used to select the characters to replace. The
		character that will be passed to the selector is the character that is currently checked
		weather it should be replaced.
		\param supplier  A supplier of the type SUPPLIER that will be used to make the character replacements. The
		character that is passed to the supplier is the character that will be replaced by the
		character that will be returned by the supplier.
		\return          A reference to the instance itself.

		\brief Replaces all characters that will be selected by the selector with the characters that will be made by
		the supplier.
		*/
		template<typename SELECTOR, typename SUPPLIER>
		String& replaceAll(SELECTOR selector, SUPPLIER supplier);

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

		\brief Overrides all the characters in the interval \f$\left[start, end\right[\f$ with the chracter \p c.
		*/
		String& fillRange(CharType c, sizeType start, sizeType end);

		/**
		\param start The start of the interval that will be removed. The character at this index will be included.
		\param end   The end of the interval that will be removed. The character at this index will be excluded. If
		this is equal to InitValues::SIZE_T_GENERAL_SPECIAL_INDEX, the size of the string will be used.
		\return      A reference to the instance itself.

		\brief Removes the characters in the interval \f$\left[start, end\right[\f$. This operation is the exact oposite
		to preserve().
		*/
		String& remove(sizeType start, sizeType end = NULL_INDEX);

		/**
		\tparam SELECTOR The type of the selector that will be used to select the characters that should be removed.
		\param selector  The selector that used to select the characters to remove.
		\return      A reference to the instance itself.

		\brief Removes all the characters that will be selected by the selector.
		*/
		template<typename SELECTOR>
		String& removeAll(SELECTOR selector);

		/**
		\param start The start of the interval that will be preserved. The character at this index will be included.
		\param end   The end of the interval that will be preserved. The character at this index will be excluded. If
		this is equal to InitValues::SIZE_T_GENERAL_SPECIAL_INDEX, the size of the string will be used.
		\return      A reference to the instance itself.

		\brief Removes all characters, except those in the interval \f$\left[start, end\right[\f$. This operation is the
		exact oposite to remove(sizeType, sizeType).
		*/
		String& preserve(sizeType start, sizeType end = NULL_INDEX);

		/**
		\param separator The seperator at which the strings will be split. This character not be part of any of the
		returned strings.
		\return          A vector that holds all the substrings that were created.

		\brief Splits the string into substrings that start and end with the passed character (this passed character
		will not be part of the substrings).

		\details
		Splits the string into substrings that start and end with the passed character (this passed character will not
		be part of the substrings).

		Example:
		The string
		\code{.cpp}
		"Important data:A date:Other important data"
		\endcode
		and
		\p separator = ':'
		will result in the substrings
		\code{.cpp}
		"Important data", "A date" and "Other important data"
		\endcode
		*/
		Vector<String> split(CharType separator) const;

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
		\return A reference to the instance itselft.

		\brief Converts all characters in the string to their lower case equivalent.
		*/
		String& toLowerCase();

		/**
		\return A reference to the instance itselft.

		\brief Converts all characters in the string to their upper case equivalent.
		*/
		String& toUpperCase();

		/**
		\return A reference to the instance itselft.

		\brief Removes all whitespaces (characters with numeric values 0x9 and 0x29) at the end and front of the string.

		\details
		Removes all whitespaces (characters with numeric values 0x9 and 0x29) at the end and front of the string.

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
		\return A reference to the instance itselft.

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
	String<CHAR_TYPE>::String(const StringView<CHAR_TYPE> &str) :
		m_data(str.size()),
		StringView<CHAR_TYPE>(m_data.data(), str.size())
	{
		for (sizeType i = 0; i < str.size(); i++)
		{
			m_data.pushBack(str.at(i));
		}

		setSize(str.size());
	}
	template<typename CHAR_TYPE>
	void String<CHAR_TYPE>::setSize(sizeType size)
	{
		m_size = size;
	}
}


#endif