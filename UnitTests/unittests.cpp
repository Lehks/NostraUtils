
#include "stdafx.h"
#include "CppUnitTest.h"

#include "nostrautils\core\StdIncludes.hpp"

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
			NOU::uint32 version0 = NOU_MAKE_VERISON(major0, minor0, patch0);

			Assert::AreEqual(NOU_VERSION_MAJOR(version0), major0);
			Assert::AreEqual(NOU_VERSION_MINOR(version0), minor0);
			Assert::AreEqual(NOU_VERSION_PATCH(version0), patch0);

			NOU::uint32 major1 = 5;
			NOU::uint32 minor1 = 23;
			NOU::uint32 patch1 = 9187;
			NOU::uint32 version1 = NOU_MAKE_VERISON(major1, minor1, patch1);

			Assert::AreEqual(NOU_VERSION_MAJOR(version1), major1);
			Assert::AreEqual(NOU_VERSION_MINOR(version1), minor1);
			Assert::AreEqual(NOU_VERSION_PATCH(version1), patch1);

			NOU::uint32 major2 = NOU_VERSION_MAJOR_MAX;
			NOU::uint32 minor2 = NOU_VERSION_MINOR_MAX;
			NOU::uint32 patch2 = NOU_VERSION_PATCH_MAX;
			NOU::uint32 version2 = NOU_MAKE_VERISON(major2, minor2, patch2);

			Assert::AreEqual(NOU_VERSION_MAJOR(version2), major2);
			Assert::AreEqual(NOU_VERSION_MINOR(version2), minor2);
			Assert::AreEqual(NOU_VERSION_PATCH(version2), patch2);
		}
	};
}