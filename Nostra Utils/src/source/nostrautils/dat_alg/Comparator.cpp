#include "nostrautils\dat_alg\Comparator.hpp"
#include "nostrautils\core\Meta.hpp"

namespace NOU::NOU_DAT_ALG
{
	CompareResult invert(CompareResult result)
	{
		//cast to underlying type, invert value, cast back to enum
		return static_cast<CompareResult>(-static_cast<NOU_CORE::UnderlyingType_t<CompareResult>>(result));
	}
	
	template<>
	CompareResult genericComparator<char8>(const char8 &a, const char8 &b)
	{
		char8 lowerCaseCharA = a >= 'A' && a <= 'Z' ? a + 'a' - 'A' : a;
		char8 lowerCaseCharB = b >= 'A' && b <= 'Z' ? b + 'a' - 'A' : b;

		return genericComparator<int32>(lowerCaseCharA, lowerCaseCharB);
	}

	template<>
	CompareResult genericComparator<char16>(const char16 &a, const char16 &b)
	{
		char16 lowerCaseCharA = a >= u'A' && a <= u'Z' ? a + u'a' - u'A' : a;
		char16 lowerCaseCharB = b >= u'A' && b <= u'Z' ? b + u'a' - u'A' : b;

		return genericComparator<int32>(lowerCaseCharA, lowerCaseCharB);
	}

	template<>
	CompareResult genericComparator<char32>(const char32 &a, const char32 &b)
	{
		char32 lowerCaseCharA = a >= U'A' && a <= U'Z' ? a + U'a' - U'A' : a;
		char32 lowerCaseCharB = b >= U'A' && b <= U'Z' ? b + U'a' - U'A' : b;

		return genericComparator<int32>(lowerCaseCharA, lowerCaseCharB);
	}
}