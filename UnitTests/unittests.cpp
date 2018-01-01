
#include "stdafx.h"
#include "CppUnitTest.h"

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Utils.hpp"
#include "nostrautils\core\Version.hpp"
#include "nostrautils\core\Meta.hpp"
#include "nostrautils\dat_alg\Comparator.hpp"
#include "nostrautils\mem_mngt\Pointer.hpp"

#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TypeSizes)
		{
			Assert::IsTrue(sizeof(NOU::int8)   >= 1);
			Assert::IsTrue(sizeof(NOU::uint8)  >= 1);
			Assert::IsTrue(sizeof(NOU::int16)  >= 2);
			Assert::IsTrue(sizeof(NOU::uint16) >= 2);
			Assert::IsTrue(sizeof(NOU::int32)  >= 4);
			Assert::IsTrue(sizeof(NOU::uint32) >= 4);
			Assert::IsTrue(sizeof(NOU::int64)  >= 8);
			Assert::IsTrue(sizeof(NOU::uint64) >= 8);

			Assert::IsTrue(sizeof(NOU::char8)  >= 1);
			Assert::IsTrue(sizeof(NOU::char16) >= 2);
			Assert::IsTrue(sizeof(NOU::char32) >= 4);

			/*
			  sizeof(long double) >= 4 / 8 to sort out those compilers that do not have a float that is 
			  32 / 64 bit wide
			*/
			Assert::IsTrue(sizeof(NOU::float32) == 4 && sizeof(long double) >= 4);
			Assert::IsTrue(sizeof(NOU::float64) == 8 && sizeof(long double) >= 8);
		}

		TEST_METHOD(Versions)
		{
			NOU::uint32 major0 = 0;
			NOU::uint32 minor0 = 0;
			NOU::uint32 patch0 = 0;
			NOU::uint32 version0 = NOU_MAKE_VERSION(major0, minor0, patch0);

			Assert::AreEqual(NOU_VERSION_MAJOR(version0), major0);
			Assert::AreEqual(NOU_VERSION_MINOR(version0), minor0);
			Assert::AreEqual(NOU_VERSION_PATCH(version0), patch0);

			NOU::uint32 major1 = 5;
			NOU::uint32 minor1 = 23;
			NOU::uint32 patch1 = 9187;
			NOU::uint32 version1 = NOU_MAKE_VERSION(major1, minor1, patch1);

			Assert::AreEqual(NOU_VERSION_MAJOR(version1), major1);
			Assert::AreEqual(NOU_VERSION_MINOR(version1), minor1);
			Assert::AreEqual(NOU_VERSION_PATCH(version1), patch1);

			NOU::uint32 major2 = NOU_VERSION_MAJOR_MAX;
			NOU::uint32 minor2 = NOU_VERSION_MINOR_MAX;
			NOU::uint32 patch2 = NOU_VERSION_PATCH_MAX;
			NOU::uint32 version2 = NOU_MAKE_VERSION(major2, minor2, patch2);

			Assert::AreEqual(NOU_VERSION_MAJOR(version2), major2);
			Assert::AreEqual(NOU_VERSION_MINOR(version2), minor2);
			Assert::AreEqual(NOU_VERSION_PATCH(version2), patch2);

			NOU::uint32 major3 = NOU_VERSION_MAJOR_MAX + 5; //overflow on purpose
			NOU::uint32 minor3 = NOU_VERSION_MINOR_MAX + 5;
			NOU::uint32 patch3 = NOU_VERSION_PATCH_MAX + 5;
			NOU::NOU_CORE::Version version3(major2, minor2, patch2);

			//compare with normal, not overflown values
			Assert::AreEqual(version3.getMajor(), NOU_VERSION_MAJOR_MAX);
			Assert::AreEqual(version3.getMinor(), NOU_VERSION_MINOR_MAX);
			Assert::AreEqual(version3.getPatch(), NOU_VERSION_PATCH_MAX);

			NOU::NOU_CORE::Version version4 = version3;

			Assert::IsTrue(version3 == version4);
			Assert::IsFalse(version3 != version4);
			Assert::IsFalse(version3 > version4);
			Assert::IsFalse(version3 < version4);
			Assert::IsTrue(version3 >= version4);
			Assert::IsTrue(version3 <= version4);

			NOU::NOU_CORE::Version version5(1, 2, 3);
			NOU::NOU_CORE::Version version6(1, 2, 4);

			Assert::IsFalse(version5 == version6);
			Assert::IsTrue(version5 != version6);
			Assert::IsFalse(version5 > version6);
			Assert::IsTrue(version5 < version6);
			Assert::IsFalse(version5 >= version6);
			Assert::IsTrue(version5 <= version6);

			NOU::NOU_CORE::Version version7(1, 2, 3);
			NOU::NOU_CORE::Version version8(1, 3, 3);

			Assert::IsFalse(version7 == version8);
			Assert::IsTrue(version7 != version8);
			Assert::IsFalse(version7 > version8);
			Assert::IsTrue(version7 < version8);
			Assert::IsFalse(version7 >= version8);
			Assert::IsTrue(version7 <= version8);

			NOU::NOU_CORE::Version version9(1, 2, 3);
			NOU::NOU_CORE::Version version10(2, 2, 4);

			Assert::IsFalse(version9 == version10);
			Assert::IsTrue(version9 != version10);
			Assert::IsFalse(version9 > version10);
			Assert::IsTrue(version9 < version10);
			Assert::IsFalse(version9 >= version10);
			Assert::IsTrue(version9 <= version10);

			NOU::NOU_CORE::Version version11(5, 9, 4);
			NOU::NOU_CORE::Version version12(1, 10, 4);
			
			Assert::IsFalse(version11 == version12);
			Assert::IsTrue(version11 != version12);
			Assert::IsTrue(version11 > version12);
			Assert::IsFalse(version11 < version12);
			Assert::IsTrue(version11 >= version12);
			Assert::IsFalse(version11 <= version12);

		}

		TEST_METHOD(Clamp)
		{
			Assert::AreEqual(NOU::NOU_CORE::clamp(2, 1, 3), 2); //in interval
			Assert::AreEqual(NOU::NOU_CORE::clamp(2, 2, 3), 2); //on min border
			Assert::AreEqual(NOU::NOU_CORE::clamp(2, 3, 3), 3); //on max border
			Assert::AreEqual(NOU::NOU_CORE::clamp(1, 2, 3), 2); //smaller than min
			Assert::AreEqual(NOU::NOU_CORE::clamp(4, 3, 3), 3); //greater than max
		}

		TEST_METHOD(Comparator)
		{
			//int as dummy type
			Assert::IsTrue(std::is_same_v<NOU::NOU_DAT_ALG::Comparator<int>, 
												decltype(&NOU::NOU_DAT_ALG::genericComparator<int>)>);

			Assert::IsTrue(std::is_same_v<NOU::NOU_DAT_ALG::Comparator<int>,
												decltype(&NOU::NOU_DAT_ALG::genericInvertedComparator<int>)>);

			Assert::IsTrue(NOU::NOU_DAT_ALG::invert(NOU::NOU_DAT_ALG::CompareResult::BIGGER) ==
				NOU::NOU_DAT_ALG::CompareResult::SMALLER);
			Assert::IsTrue(NOU::NOU_DAT_ALG::invert(NOU::NOU_DAT_ALG::CompareResult::EQUAL) ==
				NOU::NOU_DAT_ALG::CompareResult::EQUAL);
			Assert::IsTrue(NOU::NOU_DAT_ALG::invert(NOU::NOU_DAT_ALG::CompareResult::SMALLER) ==
				NOU::NOU_DAT_ALG::CompareResult::BIGGER);

			Assert::IsTrue(NOU::NOU_DAT_ALG::genericComparator(1, 5) ==
				NOU::NOU_DAT_ALG::CompareResult::SMALLER);

			Assert::IsTrue(NOU::NOU_DAT_ALG::genericComparator(5, 5) ==
				NOU::NOU_DAT_ALG::CompareResult::EQUAL);

			Assert::IsTrue(NOU::NOU_DAT_ALG::genericComparator(5, 1) ==
				NOU::NOU_DAT_ALG::CompareResult::BIGGER);




			Assert::IsTrue(NOU::NOU_DAT_ALG::genericComparator('A', 'a') == 
				NOU::NOU_DAT_ALG::CompareResult::EQUAL);

			Assert::IsTrue(NOU::NOU_DAT_ALG::genericComparator('a', 'A') ==
				NOU::NOU_DAT_ALG::CompareResult::EQUAL);

			Assert::IsTrue(NOU::NOU_DAT_ALG::genericComparator('a', 'b') ==
				NOU::NOU_DAT_ALG::CompareResult::SMALLER);

			Assert::IsTrue(NOU::NOU_DAT_ALG::genericComparator('A', 'b') ==
				NOU::NOU_DAT_ALG::CompareResult::SMALLER);

		}

		TEST_METHOD(UniquePtr)
		{
			//use string for testing.
			std::string *rawPtr = new std::string("Hello World!");
			std::string *rawPtr1 = new std::string("Hello World! 1");

			NOU::NOU_MEM_MNGT::UniquePtr<std::string> uPtr = rawPtr;
			NOU::NOU_MEM_MNGT::UniquePtr<std::string> uPtr1 = rawPtr1;

			Assert::IsTrue(uPtr.rawPtr() == rawPtr);
			Assert::IsTrue(uPtr[0] == rawPtr[0]);
			Assert::IsTrue(uPtr->size() == rawPtr->size()); //check -> operator
			Assert::IsTrue(*uPtr == *rawPtr);
			Assert::IsTrue(uPtr);
			Assert::IsFalse(NOU::NOU_MEM_MNGT::UniquePtr<std::string>()); //nullptr
			Assert::IsTrue((uPtr <= uPtr1) == (rawPtr <= rawPtr1));
			Assert::IsTrue((uPtr >= uPtr1) == (rawPtr >= rawPtr1));
			Assert::IsTrue((uPtr < uPtr1) == (rawPtr < rawPtr1));
			Assert::IsTrue((uPtr > uPtr1) == (rawPtr > rawPtr1));
			Assert::IsTrue((uPtr == uPtr1) == (rawPtr == rawPtr1));
			Assert::IsTrue((uPtr != uPtr1) == (rawPtr != rawPtr1));

			Assert::IsTrue(uPtr.deleter() == &NOU::NOU_MEM_MNGT::defaultDeleter<std::string>);

			uPtr = std::move(uPtr1);

			Assert::IsTrue(uPtr1.rawPtr() == nullptr);

			Assert::IsTrue(uPtr.rawPtr() == rawPtr1);

			struct TestDeleter
			{
				void operator () (int* i)
				{
					delete i;
				}
			};

			NOU::NOU_MEM_MNGT::UniquePtr<int, TestDeleter> uPtr2(new int, TestDeleter());

			Assert::
		}

		TEST_METHOD(AreSame)
		{
			Assert::IsTrue(NOU::NOU_CORE::AreSame<int, int>::value);
			Assert::IsFalse(NOU::NOU_CORE::AreSame<double, int>::value);
			Assert::IsFalse(NOU::NOU_CORE::AreSame<int, double>::value);
			Assert::IsTrue(NOU::NOU_CORE::AreSame<int, int, int>::value);
			Assert::IsFalse(NOU::NOU_CORE::AreSame<int, int, double>::value);
			Assert::IsFalse(NOU::NOU_CORE::AreSame<int, double, double>::value);
			Assert::IsFalse(NOU::NOU_CORE::AreSame<int, double, double, int>::value);
			Assert::IsTrue(NOU::NOU_CORE::AreSame<int, int, int, int>::value);
			Assert::IsTrue(NOU::NOU_CORE::AreSame<double, double, double, double, double>::value);
			Assert::IsFalse(NOU::NOU_CORE::AreSame<int, int, int, int, int, int, double>::value);
		}
	};
}