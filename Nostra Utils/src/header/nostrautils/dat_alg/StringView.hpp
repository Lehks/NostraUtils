#ifndef NOU_DAT_ALG_STRING_VIEW_HPP
#define	NOU_DAT_ALG_STRING_VIEW_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/core/ErrorHandler.hpp"
#include "nostrautils/core/Meta.hpp"
#include "nostrautils/core/Utils.hpp"
#include "nostrautils/dat_alg/Comparator.hpp"
#include "nostrautils/dat_alg/Vector.hpp"
#include "nostrautils/dat_alg/Utils.hpp"

/** \file StringView.hpp
\author	 Lukas Reichmann
\since   1.0.0
\version 1.0.0
\brief   This file provides the StringView which is an interface between \link nostra::utils::dat_alg::String 
         String\endlink and C-Strings.

\see nostra::utils::dat_alg::StringView
*/

namespace NOU::NOU_DAT_ALG
{
	/**
	\tparam CHAR_TYPE The type of the single characters that are stored in a string (this type will not 
	directly be used internally, but a version of this type that is always \c const).

	\brief A read-only representation of a string literal or nostra::utils::data_alg::String that is used to provide a 
	unified interface to work with either type.

	\details
	A read-only representation of a string literal or nostra::utils::data_alg::String that is used to provide a unified
	interface to work with either type.

	This class is supposed to be very lightweight, so converting from a string literal to a string view is 
	always possible without major overhead (no dynamic allocations, but just trivial copies).

	Since a string view is truly read-only, the content of the represented string can not be changed, nor can 
	a new string be assigned to an existing instance of this class.

	\note Despite nostra::utils::data_alg::String being a child class of nostra::utils::data_alg::StringView, from a logical point of
	view, they are not related any more than nostra::utils::data_alg::StringView is related to a string literal. The only reason
	for this inheritance to exists, is that both classes share some functionality and not having this inheritance would
	lead to the same code existing twice.

	\par Lifetime
	The lifetime of an instance of string view is limited by the source of the underlying string.
	- If the source is a string literal, the lifetime is unlimited, since those have a static storage duration.
	- If the source is a nostra::utils::data_alg::String, the string view is only usable as long as the source instance exists
	(since the buffer of the string is deallocated when the string is destructed).

	\par Why are there the two attributes m_string and m_dataPtr?
	Since a string view needs to be able to work with both a string literal and a nostra::utils::data_alg::String, both of these
	attributes are required for the string view to be "up to date" at any time (in the lifetime of the underlying
	string). The attribute m_dataPtr is required because nostra::utils::data_alg::String may reallocate its buffer to
	store more characters, which invalidates the pointer to the now old buffer. A pointer to a pointer is always up to
	date, since it points to the variable that points to the buffer (and the address of that variable never changes).
	*/
	template<typename CHAR_TYPE = char>
	class NOU_CLASS StringView 
	{
	public:

		/**
		\brief The same as ConstCharType, but without the const. This type is used by nostra::utils::data_alg::String.
		*/
		using CharType = NOU_CORE::removeConst_t<CHAR_TYPE>;

		/**
		\brief The type that is used to store the single characters. Since a string view is read only, this type is
		always const.
		*/
		using ConstCharType = const CharType;

		using StringConstIterator = VectorConstIterator<ConstCharType>;
		using StringReverseConstIterator = VectorReverseConstIterator<ConstCharType>;

		/**
		\brief The character that is used to separate the decimal places from the remaining digits by stringToFloat32()
		and stringToFloat64() by default.
		*/
		static constexpr ConstCharType DECIMAL_PLACE_SEPARATOR = '.'; ///\todo Localize

		/**
		\brief The character that is used to identify a negative number when converting a string to a number.
		*/
		static constexpr ConstCharType MINUS_CHAR = '-'; ///\todo Localize

		/**
		\brief The null terminating character.
		*/
		static constexpr ConstCharType NULL_TERMINATOR = 0;

		/**
		\brief An invalid index that is used to mark special indices (the usage differs from the context).
		*/
		static constexpr sizeType NULL_INDEX = -1;

	private:
		
	//Re-enable later w/ error handling
		/**
		\tparam OT The output type.
		\param str The string to convert.
		\return    The converted number.
	
		\brief Converts a string into any signed integer.
		*/
		template<typename OT>
		static OT genericStringToInt(const StringView &str);
	
		/**
		\tparam OT The output type.
		\param str The string to convert.
		\return    The converted number.
	
		\brief Converts a string into any unsigned integer.
		*/
		template<typename OT>
		static OT genericStringToUint(const StringView &str);
	
		/**
		\tparam OT                   The output type.
		\param str                   The string to convert.
		\param decimalPlaceSeparator The character that is used to separate the decimal places.
		\return                      The converted number.
	
		\brief Converts a string into any floating point type number.
		*/
		template<typename OT>
		static OT genericStringToFloat(const StringView &str, ConstCharType decimalPlaceSeparator);
	
		/**
		\param multiple The multiplier.
		\return         \f$10^{multiple}\f$

		\brief Returns the \c multiple'th power of 10.
		*/
		static uint64 getMultipleOf10(uint32 multiple);

		/**
		\param place The decimal places (as a negative value &rarr; if a number has 5 decimal places, the parameter
		would be -5).
		\return      \f$1 / (10^{|place|})\f$

		\brief Returns a multiple of 10 that, if multiplied with a number with \p places decimal places will result in a
		number that has no decimal places left.

		\details
		Returns a multiple of 10 that, if multiplied with a number with \p places decimal places will result in a number
		that has no decimal places left.
		E.g:
		\code{.cpp}
		float32 number = 2.123f;
		float32 newNumber = number * getMultiplierForDecPlaces(-3);
		\endcode
		In this example, \p newNumber would have the value 2123.0. The parameter -3 was passed to
		getMultiplierForDecPlaces() because 2.123 has 3 decimal places.
		*/
		static float64 getMultiplierForDecPlaces(int32 place);

		/**
		\brief A pointer to the string that is represented by this string view.
		\note
		This is only used if the instance was instantiated using StringView(ConstCharType*).
		*/
		ConstCharType  *m_string;

	protected:
		/**
		\brief A pointer to a pointer to the string that is represented by this instance (see the detailed description
		of this class on why this is done).
		*/
		ConstCharType **m_dataPtr;

		/**
		\brief The amount of characters in this string.
		*/
		sizeType        m_size;

		/**
		\param dataPtr A pointer to a pointer to the actual data.
		\param size    The size of the string.

		\brief Constructs a new instance using a pointer to a pointer to the actual string and the passed size. This
		constructor is used by nostra::utils::data_alg::String.
		*/
		StringView(ConstCharType ** dataPtr, sizeType size);

	public:
		/**
		\param str0 The first string.
		\param str1 The second string.
		\return     A result according to alphabetical order.

		\brief Compares the two passed strings in alphabetical order. The single characters are compared using
		nostra::utils::data_alg::genericComparator.
		*/
		static CompareResult basicComparator(const StringView &str0, const StringView &str1);

		/**
		\param c The character to check.
		\return  True, if the passed character is a digit, false if not.

		\brief Returns weather a character is a digit or not.
		*/
		constexpr static boolean isDigit(ConstCharType c);

		/**
		\param c The character to check.
		\return  True, if the passed character is a character, false if not.

		\brief Returns weather a character is a character or not.
		*/
		constexpr static boolean isCharacter(ConstCharType c);

		/**
		\param str The string to convert.
		\return    true, if the passed string is \"true\", false if not.

		\brief Converts a string into a nou::boolean.
		*/
		static boolean stringToBoolean(const StringView &str);

		/**
		\param str The string to convert.
		\return    The number that is represented by the passed string.

		\brief Converts a string into a nou::int32. If the method fails, the error register will be set accordingly and
		0 is returned. If the conversion fails, the error register is set to
		ErrorCode::ErrorCode::INVALID_STRING_CONVERSION.
		*/
		static int32   stringToInt32(const StringView &str);

		/**
		\param str The string to convert.
		\return    The number that is represented by the passed string.

		\brief Converts a string into a nou::int64. If the method fails, the error register will be set accordingly and
		0 is returned. If the conversion fails, the error register is set to
		ErrorCode::ErrorCode::INVALID_STRING_CONVERSION.
		*/
		static int64   stringToInt64(const StringView &str);

		/**
		\param str The string to convert.
		\return    The number that is represented by the passed string.

		\brief Converts a string into a nou::uint32. If the method fails, the error register will be set accordingly
		and 0 is returned. If the conversion fails, the error register is set to
		ErrorCode::ErrorCode::INVALID_STRING_CONVERSION.
		*/
		static uint32  stringToUint32(const StringView &str);

		/**
		\param str The string to convert.
		\return    The number that is represented by the passed string.

		\brief Converts a string into a nou::uint64. If the method fails, the error register will be set accordingly
		and 0 is returned. If the conversion fails, the error register is set to
		ErrorCode::ErrorCode::INVALID_STRING_CONVERSION.
		*/
		static uint64  stringToUint64(const StringView &str);

		/**
		\param str                   The string to convert.
		\param decimalPlaceSeparator The character that is used to separate the decimal places.
		\return                      The number that is represented by the passed string.

		\brief Converts a string into a nou::float32. If the method fails, the error register will be set accordingly
		and 0.0 is returned. If the conversion fails, the error register is set to
		ErrorCode::ErrorCode::INVALID_STRING_CONVERSION.
		*/
		static float32 stringToFloat32(const StringView &str, ConstCharType decimalPlaceSeparator 
			= DECIMAL_PLACE_SEPARATOR); ///TODO fix

		/**
		\param str                   The string to convert.
		\param decimalPlaceSeparator The character that is used to separate the decimal places.
		\return                      The number that is represented by the passed string.

		\brief Converts a string into a nou::float64. If the method fails, the error register will be set accordingly
		and 0.0 is returned. If the conversion fails, the error register is set to
		ErrorCode::ErrorCode::INVALID_STRING_CONVERSION.
		*/
		static float64 stringToFloat64(const StringView &str, ConstCharType decimalPlaceSeparator = DECIMAL_PLACE_SEPARATOR);

		/**
		\param str The string to convert.
		\return    The number that is represented by the passed string.

		\brief Converts a string into a nou::int64. If the method fails, the error register will be set accordingly and
		0 is returned.
		*/
		StringView(ConstCharType *str = "");

		/**
		\param other The StringView to copy the data from.

		\brief Copies a the contents of a StringView.
		*/
		///\todo check if correct constructors are getting called.
		StringView(const StringView &other); 

		virtual ~StringView() = default;

		/**
		\param str        The substring to find.
		\param startIndex The first index at which the method will look for a matching substring.
		\return           The first index at which the substring was found, or NULL_INDEX,
		if the substring was not found. This value is always either
		NULL_INDEX, or \>= \p startIndex.

		\brief Returns the index of the first occurrence of \p str in the string represented by this string view that is
		at or after the index \p startIndex.
		*/
		sizeType find(const StringView &str, sizeType startIndex = 0) const;

		/**
		\param c          The character to find.
		\param startIndex The first index at which the method will look for the character.
		\return           The first index at which the character was found, or NULL_INDEX,
		if the character was not found. This value is always either
		NULL_INDEX, or \>= \p startIndex.

		\brief Returns the index of the first occurrence of \p c in the string represented by this string view that is at
		or after the index \p startIndex.
		*/
		sizeType find(CharType c, sizeType startIndex = 0) const;

		/**
		\param c The character to find.
		\return  The index at which the character \p c occurs for the first time in the string, or
		NULL_INDEX, if it is not present in the string.

		\brief Returns the first character that is \p c.
		*/
		sizeType firstIndexOf(ConstCharType c) const;

		/**
		\param c The character to find.
		\return  The index at which the character \p c occurs for the last time in the string, or
		NULL_INDEX, if it is not present in the string.

		\brief Returns the last character that is \p c.
		*/
		sizeType lastIndexOf(ConstCharType c) const;

		/**
		\param c The character to exclude.
		\return  The index of the first character that is not \p c, or NULL_INDEX, if the
		entire string only consists of that character.

		\brief Returns the first character that is not \p c.
		*/
		sizeType firstIndexOfNot(ConstCharType c) const;

		/**
		\param c The character to exclude.
		\return  The index of the last character that is not \p c, or NULL_INDEX, if the
		entire string only consists of that character.

		\brief Returns the last character that is not \p c.
		*/
		sizeType lastIndexOfNot(ConstCharType c) const;

		/**
		\param c The character to check.
		\return  True, if the string starts with \p c, false if not.

		\brief   Checks weather the string starts with the passed character.
		*/
		boolean startsWith(ConstCharType c) const;

		/**
		\param str The string to check.
		\return    True, if the string starts with \p str, false if not.

		\brief   Checks weather the string starts with the passed string.
		*/
		boolean startsWith(const StringView &str) const;

		/**
		\param c The character to check.
		\return  True, if the string ends with \p c, false if not.

		\brief   Checks weather the string ends with the passed character.
		*/
		boolean endsWith(ConstCharType c) const;

		/**
		\param str The string to check.
		\return    True, if the string ends with \p str, false if not.

		\brief   Checks weather the string ends with the passed string.
		*/
		boolean endsWith(const StringView &str) const;

		/**
		\param index The index of the character that will be returned.
		\return      The character at the provided index.

		\brief Returns the character at the passed index.
		*/
		ConstCharType at(sizeType index) const;

		/**
		\return The size of the string.

		\brief Returns the size of the string (or more precise, the amount of characters that come before the first
		null-character in the string).
		*/
		sizeType size() const;

		/**
		\return The underlying string in its raw form.

		\brief Returns the string in its raw form which is a pointer to the string itself.

		\details
		Returns the string in its raw form which is a pointer to the string itself. If the template type is \c char,
		this will return a simple C-string.

		This method exists mainly for compatibility with functions or methods that take in pointers to a string.

		\note
		If the source of the string is nostra::utils::data_alg::String, the lifetime of the returned string
		is even more limited than the lifetime of a string view, since the raw string will be invalidated
		as soon as the original instance of nostra::utils::data_alg::String reallocates its buffer.
		The lifetime of the string if the string view was created from a string literal remains unchanged.
		*/
		ConstCharType* rawStr() const;

		/**
		\param str        The string to compare this string to.
		\param comparator The comparator that is used to compare the strings.
		\return           The result that was produced by the passed comparator.

		\brief Compares this string to the passed one using the provided comparator.
		*/
		CompareResult compareTo(const StringView &str, Comparator<StringView> comparator 
			= basicComparator) const;

		/**
		\param start The start of the interval of the characters that will be in the substring. The character at this
		index will included in the substring.
		\param end   The end of the interval of the characters that will be in the substring. The character at this
		index will excluded in the substring. If this is equal to NULL_INDEX,
		the size of the string will be used.
		\return      A string view that starts at the index \p start of this instance and has a size of \p end -
		\p start.

		\brief Returns a string view that contains a substring of this instance with the characters in the interval
		\f$\left[start, end\right[\f$. <b>Important:</b> See detailed section before first usage! This method is
		not exactly the same as nostra::utils::data_alg::String::substring().

		\details
		Returns a string view that contains a substring of this instance with the characters in the interval
		\f$\left[start, end\right[\f$.

		\note
		The returned string view will have the same lifetime as its origin string view.

		\warning
		A string view that is returned by this method should only be used by methods and functions that use the method
		size() to determine the end of a string and not by those relying on a null terminator (this is due to a string
		view being read-only by design and therefore the inability to set a new null terminator).
		*/
		StringView logicalSubstring(sizeType start, sizeType end = NULL_INDEX) const;

		/**
		\return A StringConstIterator that points to the first character in the string.
		\brief  Returns a StringConstIterator that points to the first character in the string.
		*/
		StringConstIterator begin() const;

		/**
		\return A StringConstIterator that points to the character after the last character in the string.
		\brief  Returns a StringConstIterator that points to the character after the last character in the string.
		*/
		StringConstIterator end() const;

		/**
		\param index The index at which this iterator will start.
		\return      A StringConstIterator that points to the character at the passed index.
		\brief       Returns a StringConstIterator that points to the character at the passed index.
		*/
		StringConstIterator indexIterator(sizeType index) const;

		/**
		\param index The index at which this iterator will start.
		\return      A StringReverseConstIterator that points to the character at the passed index.
		\brief       Returns a StringReverseConstIterator that points to the character at the passed index.
		*/
		StringReverseConstIterator indexRIterator(sizeType index) const;

		/**
		\return A StringReverseConstIterator that points to the last character in the string.
		\brief  Returns a StringReverseConstIterator that points to the last character in the string.
		*/
		StringReverseConstIterator rbegin() const;

		/**
		\return A StringReverseConstIterator that points to the character before the first character in the string.
		\brief  Returns a StringReverseConstIterator that points to the character before the first character in the
		string.
		*/
		StringReverseConstIterator rend() const;

		/**
		\param other The string view to copy the data from.

		\brief Copies the data from the other StringView to this one.
		*/
		///\todo Check if correct operator is getting called
		virtual StringView& operator = (const StringView &other);

		/**
		\param str The string to compare to.
		\return    True, if the strings are equal, false if not.

		\brief Compares this string with the passed one, using compareTo() with the default comparator.
		*/
		boolean operator == (const StringView &str) const;

		/**
		\param str The string to compare to.
		\return    True, if the strings are unequal, false if not.

		\brief Compares this string with the passed one, using compareTo() with the default comparator.
		*/
		boolean operator != (const StringView &str) const;

		/**
		\param str The string to compare to.
		\return    True, if this string is bigger than the passed one.

		\brief Compares this string with the passed one, using compareTo() with the default comparator.
		*/
		boolean operator > (const StringView &str) const;

		/**
		\param str The string to compare to.
		\return    True, if this string is smaller than the passed one.

		\brief Compares this string with the passed one, using compareTo() with the default comparator.
		*/
		boolean operator < (const StringView &str) const;

		/**
		\param str The string to compare to.
		\return    True, if this string is bigger than or equal to the passed one.

		\brief Compares this string with the passed one, using compareTo() with the default comparator.
		*/
		boolean operator >= (const StringView &str) const;

		/**
		\param str The string to compare to.
		\return    True, if this string is smaller than or equal to the passed one.

		\brief Compares this string with the passed one, using compareTo() with the default comparator.
		*/
		boolean operator <= (const StringView &str) const;

		/**
		\param index The index of the character that will be returned.
		\return      The character at the provided index

		\brief Returns the character at the passed index. This is equal to at().
		*/
		ConstCharType operator [] (sizeType index) const;
	};

	/**
	\brief An alias name for a StringView that uses a nostra::utils::char8;
	*/
	using StringView8 = StringView<char8>;

	/**
	\brief An alias name for a StringView that uses a nostra::utils::char16;
	*/
	using StringView16 = StringView<char16>;

	/**
	\brief An alias name for a StringView that uses a nostra::utils::char32;
	*/
	using StringView32 = StringView<char32>;

	template<typename CHAR_TYPE>
	constexpr typename StringView<CHAR_TYPE>::ConstCharType StringView<CHAR_TYPE>::DECIMAL_PLACE_SEPARATOR;

	template<typename CHAR_TYPE>
	constexpr typename StringView<CHAR_TYPE>::ConstCharType StringView<CHAR_TYPE>::MINUS_CHAR;
	
	template<typename CHAR_TYPE>
	constexpr typename StringView<CHAR_TYPE>::ConstCharType StringView<CHAR_TYPE>::NULL_TERMINATOR;
	
	template<typename CHAR_TYPE>
	constexpr sizeType StringView<CHAR_TYPE>::NULL_INDEX;

	///\todo Re-enable and exchange error handling
	template<typename CHAR_TYPE>
	template<typename OT>
	OT StringView<CHAR_TYPE>::genericStringToInt(const StringView &str)
	{
		if (str.size() == 0)
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_STRING_CONVERSION, "String is empty.");
			return 0;
		}

		boolean isNegative = false;
		OT ret = 0;

		sizeType i = 0;

		if (str[i] == MINUS_CHAR)
		{
			isNegative = true;
			i++;
		}

		for (; i < str.size(); i++)
		{
			if (isDigit(str[i]))
				ret += (str[i] - '0') * static_cast<OT>(getMultipleOf10(static_cast<uint32>(str.size() - i - 1)));
			else
			{
				NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_STRING_CONVERSION, "Invalid character found.");
				return 0;
			}
		}

		if (isNegative)
			ret = -ret;

		return ret;
	}

	template<typename CHAR_TYPE>
	template<typename OT>
	OT StringView<CHAR_TYPE>::genericStringToUint(const StringView &str)
	{
		OT ret = 0;

		for (sizeType i = 0; i < str.m_size; i++)
			if (isDigit(str[i]))
				ret += (str[i] - '0') * static_cast<OT>(getMultipleOf10(static_cast<uint32>(str.size() - i - 1)));
			else
			{
				NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_STRING_CONVERSION, "Invalid character found.");
				return 0;
			}

		return ret;
	}

	template<typename CHAR_TYPE>
	template<typename OT>
	OT StringView<CHAR_TYPE>::genericStringToFloat(const StringView &str, ConstCharType decimalPlaceSeparator)
	{
		sizeType preDecPointNumbers = 0;
		boolean isNegative = false;
		OT ret = 0;
		sizeType i = 0;
		int32 foundDecimalPoint = false; //Also stores the amount of places that the loop is behind the decimal point

		if (str[i] == MINUS_CHAR)
		{
			isNegative = true;
			i++;
		}

		for (; i < str.size(); i++)
		{
			if (isDigit(str[i]))
			{
				if (foundDecimalPoint)
					ret += (str[i] - '0') * static_cast<OT>(getMultiplierForDecPlaces(foundDecimalPoint--));
				else
				{
					preDecPointNumbers++;
					ret += (str[i] - '0') * getMultipleOf10(static_cast<uint32_t>(str.size() - preDecPointNumbers));
				}
			}
			else
			{
				if (str[i] == decimalPlaceSeparator && !foundDecimalPoint)
				{
					foundDecimalPoint = -1;

					ret /= getMultipleOf10(static_cast<uint32_t>(str.size() - preDecPointNumbers));
				}
				else
				{
					NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_STRING_CONVERSION, "Invalid character found.");
					return 0;
				}
			}
		}

		if (isNegative)
			ret = -ret;

		return ret;
	}

	template<typename CHAR_TYPE>
	uint64 StringView<CHAR_TYPE>::getMultipleOf10(uint32 multiple)
	{
		if (multiple == 0)
			return 1;
		else if (multiple == 1)
			return 10;
		else if (multiple == 2)
			return 100;
		else if (multiple == 3)
			return 1000;
		else if (multiple == 4)
			return 10000;
		else if (multiple == 5)
			return 100000;
		else if (multiple == 6)
			return 1000000;
		else if (multiple == 7)
			return 10000000;
		else if (multiple == 8)
			return 100000000;
		else if (multiple == 9)
			return 1000000000;
		else if (multiple == 10)
			return 10000000000;
		else if (multiple == 11)
			return 100000000000;
		else if (multiple == 12)
			return 1000000000000;
		else if (multiple == 13)
			return 10000000000000;
		else if (multiple == 14)
			return 100000000000000;
		else if (multiple == 15)
			return 1000000000000000;
		else if (multiple == 16)
			return 10000000000000000;
		else if (multiple == 17)
			return 100000000000000000;

		return -1;
	}

	template<typename CHAR_TYPE>
	float64 StringView<CHAR_TYPE>::getMultiplierForDecPlaces(int32 place)
	{
		if (place == -1)
			return 1.0 / 10;
		else if (place == -2)
			return 1.0 / 100;
		else if (place == -3)
			return 1.0 / 1000;
		else if (place == -4)
			return 1.0 / 10000;
		else if (place == -5)
			return 1.0 / 100000;
		else if (place == -6)
			return 1.0 / 1000000;
		else if (place == -6)
			return 1.0 / 10000000;
		else if (place == -7)
			return 1.0 / 100000000;
		else if (place == -8)
			return 1.0 / 1000000000;
		else if (place == -9)
			return 1.0 / 100000000000;
		else if (place == -10)
			return 1.0 / 1000000000000;
		else if (place == -11)
			return 1.0 / 10000000000000;
		else if (place == -12)
			return 1.0 / 100000000000000;
		else if (place == -13)
			return 1.0 / 1000000000000000;
		else if (place == -14)
			return 1.0 / 10000000000000000;
		else if (place == -15)
			return 1.0 / 100000000000000000;

		return 1;
	}

	template<typename CHAR_TYPE>
	CompareResult StringView<CHAR_TYPE>::basicComparator(const StringView &str0, 
		const StringView &str1)
	{
		if (str0.rawStr() == str1.rawStr()) //the underlying strings are the same objects (since the ptr's are the same)
			return 0;

		//the size of the smaller string (stored to avoid recalculating this value each iteration)
		sizeType smallerSize = NOU_CORE::min(str0.size(), str1.size());

		for (sizeType i = 0; i < smallerSize; i++)
		{
			CompareResult charCompareResult = genericComparator<CharType>(str0[i], str1[i]);

			if (charCompareResult != 0)
				return charCompareResult;
		}

		//one string starts with the other one, now the order depends on their length
		return genericComparator<sizeType>(str0.size(), str1.size());
	}

	template<typename CHAR_TYPE>
	constexpr boolean StringView<CHAR_TYPE>::isDigit(ConstCharType c)
	{
		return c >= '0' && c <= '9';
	}

	template<typename CHAR_TYPE>
	constexpr boolean StringView<CHAR_TYPE>::isCharacter(ConstCharType c)
	{
		return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
	}

	template<typename CHAR_TYPE>
	 boolean StringView<CHAR_TYPE>::stringToBoolean(const StringView &str)
	{
		return str == "true";
	}

	template<typename CHAR_TYPE>
	int32 StringView<CHAR_TYPE>::stringToInt32(const StringView &str)
	{
		return genericStringToInt<int32>(str);
	}

	template<typename CHAR_TYPE>
	int64 StringView<CHAR_TYPE>::stringToInt64(const StringView &str)
	{
		return genericStringToInt<int64>(str);
	}

	template<typename CHAR_TYPE>
	uint32 StringView<CHAR_TYPE>::stringToUint32(const StringView &str)
	{
		return genericStringToInt<uint32>(str);
	}

	template<typename CHAR_TYPE>
	uint64 StringView<CHAR_TYPE>::stringToUint64(const StringView &str)
	{
		return genericStringToUint<uint64>(str);
	}

	template<typename CHAR_TYPE>
	float32 StringView<CHAR_TYPE>::stringToFloat32(const StringView &str, 
		ConstCharType decimalPlaceSeparator)
	{
		return genericStringToFloat<float32>(str, decimalPlaceSeparator);
	}

	template<typename CHAR_TYPE>
	float64 StringView<CHAR_TYPE>::stringToFloat64(const StringView &str, 
		ConstCharType decimalPlaceSeparator)
	{
		return genericStringToFloat<float64>(str, decimalPlaceSeparator);
	}

	template<typename CHAR_TYPE>
	StringView<CHAR_TYPE>::StringView(ConstCharType ** dataPtr, sizeType size) :
		m_dataPtr(dataPtr),
		m_size(size),
		m_string(nullptr)
	{}

	template<typename CHAR_TYPE>
	StringView<CHAR_TYPE>::StringView(ConstCharType *str) :
		m_string(str),
		m_dataPtr(&m_string),
		m_size(stringlen<ConstCharType>(str))
	{}

	template<typename CHAR_TYPE>
	StringView<CHAR_TYPE>::StringView(const StringView &other) :
		m_string(other.m_string),
		m_dataPtr(m_string == nullptr ? other.m_dataPtr : &m_string),
		m_size(other.m_size)
	{}

	template<typename CHAR_TYPE>
	sizeType StringView<CHAR_TYPE>::find(const StringView &str, sizeType startIndex) const
	{
		//- str.size() + 1, b/c there needs to be at least str.size() space for the substring
		for (sizeType i = startIndex; i < (size() - str.size() + 1); i++)
		{
			if (at(i) == str.at(0))
			{
				sizeType j = 1;

				for (; j < str.size(); j++)
				{
					if (at(i + j) != str.at(j))
						break; //substring not found, stop loop right here
				}

				//If j == str.size() - 1, the inner loop has finished without being broken
				if (j == str.size())
					return i;
			}
		}

		return NULL_INDEX;
	}

	template<typename CHAR_TYPE>
	sizeType StringView<CHAR_TYPE>::find(CharType c, sizeType startIndex) const
	{
		for (sizeType i = startIndex; i < size(); ++i)
			if (at(i) == c)
				return i;

		return NULL_INDEX;
	}

	template<typename CHAR_TYPE>
	sizeType StringView<CHAR_TYPE>::firstIndexOf(ConstCharType c) const
	{
		for (sizeType i = 0; i < size(); i++)
			if (at(i) == c)
				return i;

		return NULL_INDEX;
	}

	template<typename CHAR_TYPE>
	sizeType StringView<CHAR_TYPE>::lastIndexOf(ConstCharType c) const
	{
		for (sizeType i = size() - 1; i != -1; i--)
			if (at(i) == c)
				return i;

		return NULL_INDEX;
	}

	template<typename CHAR_TYPE>
	sizeType StringView<CHAR_TYPE>::firstIndexOfNot(ConstCharType c) const
	{
		for (sizeType i = 0; i < size(); i++)
			if (at(i) != c)
				return i;

		return NULL_INDEX;
	}

	template<typename CHAR_TYPE>
	sizeType StringView<CHAR_TYPE>::lastIndexOfNot(ConstCharType c) const
	{
		for (sizeType i = size() - 1; i != -1; i--)
			if (at(i) != c)
				return i;

		return NULL_INDEX;
	}

	template<typename CHAR_TYPE>
	boolean StringView<CHAR_TYPE>::startsWith(ConstCharType c) const
	{
		return (size() > 0) && (at(0) == c);
	}

	template<typename CHAR_TYPE>
	boolean StringView<CHAR_TYPE>::startsWith(const StringView &str) const
	{
		if (str.size() > size())
			return false;

		for (sizeType i = 0; i < str.size(); i++)
			if (str.at(i) != at(i))
				return false;

		return true;
	}

	template<typename CHAR_TYPE>
	boolean StringView<CHAR_TYPE>::endsWith(ConstCharType c) const
	{
		return (size() > 0) && (at(size() - 1) == c);
	}

	template<typename CHAR_TYPE>
	boolean StringView<CHAR_TYPE>::endsWith(const StringView &str) const
	{
		if (str.size() > size())
			return false;

		for (sizeType i = size() - 1; i >= size() - str.size(); i--)
			if (str.at(i - size() + str.size()) != at(i))
				return false;

		return true;
	}

	template<typename CHAR_TYPE>
	auto StringView<CHAR_TYPE>::at(sizeType index) const -> ConstCharType
	{
		return (*m_dataPtr)[index];
	}

	template<typename CHAR_TYPE>
	sizeType StringView<CHAR_TYPE>::size() const
	{
		return m_size;
	}

	template<typename CHAR_TYPE>
	auto StringView<CHAR_TYPE>::rawStr() const -> ConstCharType*
	{
		return *m_dataPtr;
	}

	template<typename CHAR_TYPE>
	CompareResult StringView<CHAR_TYPE>::compareTo(const StringView &str, 
		Comparator<StringView> comparator) const
	{
		return comparator(*this, str);
	}

	template<typename CHAR_TYPE>
	StringView<CHAR_TYPE> StringView<CHAR_TYPE>::logicalSubstring(sizeType start, 
		sizeType end) const
	{
		if (end == NULL_INDEX)
			end = size();

		StringView<CHAR_TYPE> ret((*m_dataPtr) + start); //init ret with correct start index.

		ret.m_size = end - start;

		return ret;
	}

	template<typename CHAR_TYPE>
	auto StringView<CHAR_TYPE>::begin() const -> StringConstIterator
	{
		return indexIterator(0);
	}

	template<typename CHAR_TYPE>
	auto StringView<CHAR_TYPE>::end() const -> StringConstIterator
	{
		return indexIterator(size());
	}

	template<typename CHAR_TYPE>
	auto StringView<CHAR_TYPE>::indexIterator(sizeType index) const -> StringConstIterator
	{
		return StringConstIterator(index, m_dataPtr);
	}

	template<typename CHAR_TYPE>
	auto StringView<CHAR_TYPE>::indexRIterator(sizeType index) const -> StringReverseConstIterator
	{
		return StringReverseConstIterator(index, m_dataPtr);
	}

	template<typename CHAR_TYPE>
	auto StringView<CHAR_TYPE>::rbegin() const -> StringReverseConstIterator
	{
		return indexRIterator(size() - 1);
	}

	template<typename CHAR_TYPE>
	auto StringView<CHAR_TYPE>::rend() const -> StringReverseConstIterator
	{
		return indexRIterator(-1);
	}

	template<typename CHAR_TYPE>
	StringView<CHAR_TYPE>& StringView<CHAR_TYPE>::operator = (const StringView<CHAR_TYPE> &other)
	{
		m_string = other.m_string;
		m_dataPtr = m_string == nullptr ? other.m_dataPtr : &m_string;
		m_size = other.m_size;

		return *this;
	}

	template<typename CHAR_TYPE>
	boolean StringView<CHAR_TYPE>::operator == (const StringView &str) const
	{
		return compareTo(str) == 0;
	}

	template<typename CHAR_TYPE>
	boolean StringView<CHAR_TYPE>::operator != (const StringView &str) const
	{
		return !(*this == str);
	}

	template<typename CHAR_TYPE>
	boolean StringView<CHAR_TYPE>::operator > (const StringView &str) const
	{
		return compareTo(str) > 0;
	}

	template<typename CHAR_TYPE>
	boolean StringView<CHAR_TYPE>::operator < (const StringView &str) const
	{
		return compareTo(str) < 0;
	}

	template<typename CHAR_TYPE>
	boolean StringView<CHAR_TYPE>::operator >= (const StringView &str) const
	{
		return compareTo(str) >= 0;
	}

	template<typename CHAR_TYPE>
	boolean StringView<CHAR_TYPE>::operator <= (const StringView &str) const
	{
		return compareTo(str) <= 0;
	}

	template<typename CHAR_TYPE>
	auto StringView<CHAR_TYPE>::operator [] (sizeType index) const -> ConstCharType
	{
		return at(index);
	}
}

#endif