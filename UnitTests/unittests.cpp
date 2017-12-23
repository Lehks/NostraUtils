
#include "stdafx.h"
#include "CppUnitTest.h"

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Utils.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(FloatTypeSize)
		{
			/*
			  sizeof(long double) >= 4 / 8 to sort out those compilers that do not have a float that is 
			  32 / 64 bit wide
			*/
			Assert::IsTrue(sizeof(NOU::float32) == 4 && sizeof(long double) >= 4);
			Assert::IsTrue(sizeof(NOU::float64) == 8 && sizeof(long double) >= 8);
		}

		TEST_METHOD(minAndMax)
		{
			int i0 = 1;
			int i1 = 5;

			Assert::AreEqual(NOU::NOU_CORE::max(i0, i1), 5);
			Assert::AreEqual(NOU::NOU_CORE::min(i0, i1), 1);
			Assert::AreEqual(NOU::NOU_CORE::max(i1, i0), 5);
			Assert::AreEqual(NOU::NOU_CORE::min(i1, i0), 1);
		}

	};
}