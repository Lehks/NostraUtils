
#include "stdafx.h"
#include "CppUnitTest.h"

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Utils.hpp"
#include "nostrautils\core\Version.hpp"
#include "nostrautils\core\Meta.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\core\Utils.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\Utils.hpp"
#include "nostrautils\dat_alg\Comparator.hpp"
#include "nostrautils\mem_mngt\Pointer.hpp"
#include "nostrautils\dat_alg\StringView.hpp"
#include "nostrautils\dat_alg\FastQueue.hpp"

#include "DebugClass.hpp"

#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


//both functions are used in test IsInvocable
void dummyFunc0(int)
{

}

int dummyFunc1(int)
{
	return 1;
}

//used in test UniquePtr
NOU::boolean testVar = false;


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

		TEST_METHOD(Swap)
		{
			NOU::int32 a = 1;
			NOU::int32 b = 2;

			NOU::NOU_DAT_ALG::swap(&a, &b);

			Assert::AreEqual(2,a);
			Assert::AreEqual(1,b);
		}

		TEST_METHOD(Vector)
		{
			NOU::NOU_DAT_ALG::Vector<NOU::int32> vec1(10);

			Assert::AreEqual(static_cast<NOU::sizeType>(0), vec1.size());

			for (NOU::sizeType i = 0; i < 10; i++)
			{
				vec1.pushBack(i);
			}

			Assert::AreEqual(0, vec1[0]);
			Assert::AreEqual(1, vec1[1]);
			Assert::AreEqual(2, vec1[2]);
			Assert::AreEqual(3, vec1[3]);
			Assert::AreEqual(4, vec1[4]);
			Assert::AreEqual(5, vec1[5]);
			Assert::AreEqual(6, vec1[6]);
			Assert::AreEqual(7, vec1[7]);
			Assert::AreEqual(8, vec1[8]);
			Assert::AreEqual(9, vec1[9]);

			Assert::IsFalse(vec1.empty());

			vec1.pushBack(10);
			Assert::AreEqual(10, vec1[10]);

			NOU::NOU_DAT_ALG::Vector<NOU::int32> vec2(11);
			vec2 = vec1;
			Assert::AreEqual(vec2[9], vec1[9]);

			NOU::NOU_DAT_ALG::Vector<NOU::int32> vec3(10);
			vec3 = vec1;
			Assert::AreEqual(vec3[9], vec1[9]);

			vec1.pushFront(15);
			Assert::AreEqual(15, vec1[0]);

			NOU::int32 testinteger = 0;
			testinteger = vec1.popFront();
			Assert::AreEqual(15, testinteger);

			vec2.swap(0,1);
			Assert::AreEqual(0, vec2[1]);

			vec2.remove(0);
			Assert::AreEqual(0, vec2[0]);

			int i = 0;

			for (NOU::NOU_DAT_ALG::VectorIterator<NOU::int32> it = vec2.begin(); it != vec2.end(); it++)
			{
				Assert::AreEqual(*it, vec2[i]);
				i++;
			}

			i = vec2.size() - 1;

			for (NOU::NOU_DAT_ALG::VectorReverseIterator<NOU::int32> it = vec2.rbegin(); it != vec2.rend(); it++)
			{
				Assert::AreEqual(*it, vec2[i]);
				i--;
			}
			
			NOU::NOU_MEM_MNGT::DebugAllocationCallback<NOU::int32> dbgAlloc;

			{

				NOU::NOU_DAT_ALG::Vector<NOU::int32> vec4(1, dbgAlloc);

				vec4.pushBack(5);
				vec4.pushBack(2);
				vec4.remove(1);
				vec4.pushBack(1);
				vec4.pushBack(1);
				vec4.pushBack(1);
				vec4.pushBack(546045);
				vec4.pushBack(909789);
				vec4.pushBack(213301);
				vec4.pushBack(898049);
				vec4.pushBack(132034);
				vec4.pushBack(1);
				vec4.pushBack(1);
				vec4.pushBack(1);
				vec4.remove(0);
				vec4.remove(0);
				vec4.remove(0);
				vec4.remove(0);
				vec4.remove(0);
				vec4.remove(0);
				vec4.remove(0);
				vec4.remove(0);
				vec4.remove(0);
				vec4.remove(0);
				vec4.remove(0);


				vec4.pushBack(4);
			}


			Assert::IsTrue(dbgAlloc.getCounter() == 0);

			Assert::AreEqual(0, vec2.peek());
			Assert::AreEqual(0, vec2.peekFront());

			NOU::DebugClass dg;
			NOU::DebugClass dg1;
			NOU::DebugClass dg2;

			NOU::int64 u = dg.getCounter();

			NOU::NOU_DAT_ALG::Vector<NOU::DebugClass> vec5(1);

			vec5.pushBack(dg);
			u = dg.getCounter();
			vec5.pushBack(dg1);
			vec5.remove(0);
			u = dg.getCounter();
			vec5.pushBack(dg2);
			vec5.remove(1);
			u = dg.getCounter();
			vec5.remove(0);

			u = dg.getCounter();

			Assert::IsTrue(dg.getCounter() == 0);
		}

		TEST_METHOD(Swap)
		{
			NOU::int32 a = 1;
			NOU::int32 b = 2;

			NOU::NOU_DAT_ALG::swap(&a, &b);

			Assert::AreEqual(2,a);
			Assert::AreEqual(1,b);
		}

		TEST_METHOD(Vector)
		{
			NOU::NOU_DAT_ALG::Vector<NOU::int32> vec1(10);

			Assert::AreEqual(static_cast<NOU::sizeType>(0), vec1.size());

			for (NOU::sizeType i = 0; i < 10; i++)
			{
				vec1.pushBack(i);
			}

			Assert::AreEqual(0, vec1[0]);
			Assert::AreEqual(1, vec1[1]);
			Assert::AreEqual(2, vec1[2]);
			Assert::AreEqual(3, vec1[3]);
			Assert::AreEqual(4, vec1[4]);
			Assert::AreEqual(5, vec1[5]);
			Assert::AreEqual(6, vec1[6]);
			Assert::AreEqual(7, vec1[7]);
			Assert::AreEqual(8, vec1[8]);
			Assert::AreEqual(9, vec1[9]);

			Assert::IsFalse(vec1.empty());

			vec1.pushBack(10);
			Assert::AreEqual(10, vec1[10]);

			NOU::NOU_DAT_ALG::Vector<NOU::int32> vec2(11);
			vec2 = vec1;
			Assert::AreEqual(vec2[9], vec1[9]);

			NOU::NOU_DAT_ALG::Vector<NOU::int32> vec3(10);
			vec3 = vec1;
			Assert::AreEqual(vec3[9], vec1[9]);

			vec1.pushFront(15);
			Assert::AreEqual(15, vec1[0]);

			NOU::int32 testinteger = 0;
			testinteger = vec1.popFront();
			Assert::AreEqual(15, testinteger);

			vec2.swap(0,1);
			Assert::AreEqual(0, vec2[1]);

			vec2.remove(0);
			Assert::AreEqual(0, vec2[0]);

			int i = 0;

			NOU::NOU_DAT_ALG::VectorIterator<NOU::int32> iter1 = vec2.begin();
			for (NOU::NOU_DAT_ALG::VectorIterator<NOU::int32> it = vec2.begin(); it != vec2.end(); it++)
			{
				Assert::AreEqual(*it, vec2[i]);
				i++;
			}

			i = vec2.size();

			NOU::NOU_DAT_ALG::VectorReverseIterator<NOU::int32> iter2 = vec2.rbegin();
			for (NOU::NOU_DAT_ALG::VectorReverseIterator<NOU::int32> it = vec2.rbegin(); it != vec2.rend(); it++)
			{
				Assert::AreEqual(*it, vec2[i]);
				i--;
			}
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

			NOU::NOU_MEM_MNGT::UniquePtr<std::string> uPtr(rawPtr, NOU::NOU_MEM_MNGT::defaultDeleter);
			NOU::NOU_MEM_MNGT::UniquePtr<std::string> uPtr1(rawPtr1, NOU::NOU_MEM_MNGT::defaultDeleter);

			Assert::IsTrue(uPtr.rawPtr() == rawPtr);
			Assert::IsTrue(uPtr[0] == rawPtr[0]);
			Assert::IsTrue(uPtr->size() == rawPtr->size()); //check -> operator
			Assert::IsTrue(*uPtr == *rawPtr);
			Assert::IsTrue(uPtr);
			Assert::IsFalse(NOU::NOU_MEM_MNGT::UniquePtr<std::string>(nullptr, 
						NOU::NOU_MEM_MNGT::defaultDeleter));
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
					testVar = true;
					delete i;
				}
			};

			{
				//check if this compiles
				NOU::NOU_MEM_MNGT::UniquePtr<int, TestDeleter> uPtr2(new int, TestDeleter());
				
				//destructor is called here
			}

			Assert::IsTrue(testVar); //if testVar is true, the destructor has been called.

			testVar = false;

			NOU::NOU_MEM_MNGT::UniquePtr<int, TestDeleter> uPtr3(new int, TestDeleter());
			uPtr3 = new int;

			Assert::IsTrue(testVar); //if testVar is true, the destructor has been called.
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

		TEST_METHOD(IsInvocable)
		{
			Assert::IsTrue(NOU::NOU_CORE::IsInvocable<decltype(dummyFunc0), int>::value);
			Assert::IsFalse(NOU::NOU_CORE::IsInvocable<decltype(dummyFunc0), std::string>::value);
			Assert::IsFalse(NOU::NOU_CORE::IsInvocable<int, int>::value);

			Assert::IsTrue(NOU::NOU_CORE::IsInvocableR<int, decltype(dummyFunc1), int>::value);
			Assert::IsFalse(NOU::NOU_CORE::IsInvocableR<int, decltype(dummyFunc1), std::string>::value);
			Assert::IsFalse(NOU::NOU_CORE::IsInvocableR<std::string, decltype(dummyFunc1), int>::value);

			Assert::IsFalse(NOU::NOU_CORE::IsInvocableR<int, int, int>::value);
		}

		TEST_METHOD(FastQueue)
		{
			NOU::NOU_DAT_ALG::FastQueue<int> fq(5);

			Assert::IsTrue(fq.capacity() == 5);
			Assert::IsTrue(&(fq.getAllocationCallback()) == 
				&(NOU::NOU_MEM_MNGT::GenericAllocationCallback<int>::getInstance()));

			Assert::IsTrue(fq.size() == 0);
			Assert::IsTrue(fq.empty());
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

		TEST_METHOD(IsInvocable)
		{
			Assert::IsTrue(NOU::NOU_CORE::IsInvocable<decltype(dummyFunc0), int>::value);
			Assert::IsFalse(NOU::NOU_CORE::IsInvocable<decltype(dummyFunc0), std::string>::value);
			Assert::IsFalse(NOU::NOU_CORE::IsInvocable<int, int>::value);

			Assert::IsTrue(NOU::NOU_CORE::IsInvocableR<int, decltype(dummyFunc1), int>::value);
			Assert::IsFalse(NOU::NOU_CORE::IsInvocableR<int, decltype(dummyFunc1), std::string>::value);
			Assert::IsFalse(NOU::NOU_CORE::IsInvocableR<std::string, decltype(dummyFunc1), int>::value);

			Assert::IsFalse(NOU::NOU_CORE::IsInvocableR<int, int, int>::value);
		}

		TEST_METHOD(DebugAllocationCallback)
		{
			NOU::NOU_MEM_MNGT::DebugAllocationCallback<int> alloc;

			int *iPtr = alloc.allocate(5);

			Assert::IsTrue(alloc.getCounter() == 1);

			alloc.deallocate(iPtr);

			Assert::IsTrue(alloc.getCounter() == 0);
		}
		
		TEST_METHOD(AllocationCallbackDeleter)
		{
			NOU::NOU_MEM_MNGT::DebugAllocationCallback<int> dbgAlloc;
			NOU::NOU_MEM_MNGT::AllocationCallbackRefDeleter<int> deleter0(dbgAlloc);

			int *iPtr0 = dbgAlloc.allocate();

			deleter0(iPtr0); //delete using deleter

			Assert::IsTrue(dbgAlloc.getCounter() == 0);

			auto callback = NOU::NOU_MEM_MNGT::DebugAllocationCallback<int>();
			NOU::NOU_MEM_MNGT::AllocationCallbackDeleter<int, 
				NOU::NOU_MEM_MNGT::DebugAllocationCallback<int>> deleter1(callback);

			int *iPtr1 = deleter1.getAllocator().allocate();

			deleter1(iPtr1); //delete using deleter

			Assert::IsTrue(deleter1.getAllocator().getCounter() == 0);
		}

		TEST_METHOD(StringView)
		{
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8::isCharacter('A'));
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8::isCharacter('Z'));
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8::isCharacter('a'));
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8::isCharacter('z'));

			Assert::IsFalse(NOU::NOU_DAT_ALG::StringView8::isCharacter(' '));
			Assert::IsFalse(NOU::NOU_DAT_ALG::StringView8::isCharacter('3'));
			Assert::IsFalse(NOU::NOU_DAT_ALG::StringView8::isCharacter('%'));
			Assert::IsFalse(NOU::NOU_DAT_ALG::StringView8::isCharacter('-'));

			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8::isDigit('1'));
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8::isDigit('2'));
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8::isDigit('3'));
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8::isDigit('4'));
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8::isDigit('5'));
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8::isDigit('6'));
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8::isDigit('7'));
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8::isDigit('8'));
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8::isDigit('9'));

			Assert::IsFalse(NOU::NOU_DAT_ALG::StringView8::isDigit(' '));
			Assert::IsFalse(NOU::NOU_DAT_ALG::StringView8::isDigit('A'));
			Assert::IsFalse(NOU::NOU_DAT_ALG::StringView8::isDigit('%'));
			Assert::IsFalse(NOU::NOU_DAT_ALG::StringView8::isDigit('-'));

			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8::stringToBoolean("true"));

			Assert::IsFalse(NOU::NOU_DAT_ALG::StringView8::stringToBoolean("false"));
			Assert::IsFalse(NOU::NOU_DAT_ALG::StringView8::stringToBoolean("abcde"));
			Assert::IsFalse(NOU::NOU_DAT_ALG::StringView8::stringToBoolean("12345"));
			Assert::IsFalse(NOU::NOU_DAT_ALG::StringView8::stringToBoolean("!§$%&"));

			NOU::NOU_DAT_ALG::StringView8 sv = "Hello World!";

			Assert::IsTrue(sv[0] == 'H');
			Assert::IsTrue(sv[1] == 'e');
			Assert::IsTrue(sv[2] == 'l');
			Assert::IsTrue(sv[3] == 'l');
			Assert::IsTrue(sv[4] == 'o');
			Assert::IsTrue(sv[5] == ' ');
			Assert::IsTrue(sv[6] == 'W');
			Assert::IsTrue(sv[7] == 'o');
			Assert::IsTrue(sv[8] == 'r');
			Assert::IsTrue(sv[9] == 'l');
			Assert::IsTrue(sv[10] == 'd');
			Assert::IsTrue(sv[11] == '!');

			Assert::IsTrue(sv.size() == 12);

			Assert::IsTrue(sv == "Hello World!");

			Assert::IsTrue(sv.find('e') == 1);
			Assert::IsTrue(sv.find('e', 1) == 1);

			Assert::IsTrue(sv.find('o') == 4);
			Assert::IsTrue(sv.find('o', 5) == 7);
			Assert::IsTrue(sv.find('z') == NOU::NOU_DAT_ALG::StringView8::NULL_INDEX);

			Assert::IsTrue(sv.find("ello") == 1);
			Assert::IsTrue(sv.find("o") == 4);
			Assert::IsTrue(sv.find("o", 5) == 7);
			Assert::IsTrue(sv.find("test") == NOU::NOU_DAT_ALG::StringView8::NULL_INDEX);

			Assert::IsTrue(sv.firstIndexOf('H') == 0);
			Assert::IsTrue(sv.firstIndexOf('o') == 4);
			Assert::IsTrue(sv.firstIndexOf('z') == NOU::NOU_DAT_ALG::StringView8::NULL_INDEX);

			Assert::IsTrue(sv.lastIndexOf('H') == 0);
			Assert::IsTrue(sv.lastIndexOf('o') == 7);
			Assert::IsTrue(sv.lastIndexOf('z') == NOU::NOU_DAT_ALG::StringView8::NULL_INDEX);

			Assert::IsTrue(sv.firstIndexOfNot('H') == 1);
			Assert::IsTrue(sv.firstIndexOfNot('o') == 0);
			Assert::IsTrue(sv.firstIndexOfNot('z') == 0);

			Assert::IsTrue(sv.lastIndexOfNot('H') == 11);
			Assert::IsTrue(sv.lastIndexOfNot('o') == 11);
			Assert::IsTrue(sv.lastIndexOfNot('z') == 11);

			Assert::IsTrue(sv.startsWith('H'));
			Assert::IsFalse(sv.startsWith('g'));

			Assert::IsTrue(sv.startsWith("Hell"));
			Assert::IsFalse(sv.startsWith("World"));

			Assert::IsTrue(sv.endsWith("rld!"));
			Assert::IsFalse(sv.endsWith("World"));

			Assert::IsTrue(sv.compareTo("Abc") 
				== NOU::NOU_DAT_ALG::CompareResult::BIGGER);
			Assert::IsTrue(sv.compareTo("Hello World!")
				== NOU::NOU_DAT_ALG::CompareResult::EQUAL);
			Assert::IsTrue(sv.compareTo("Xyz") 
				== NOU::NOU_DAT_ALG::CompareResult::SMALLER);

			NOU::NOU_DAT_ALG::StringView8 subStr = sv.logicalSubstring(6);

			Assert::IsTrue(subStr.size() == 6);

			Assert::IsTrue(subStr[0] == 'W');
			Assert::IsTrue(subStr[1] == 'o');
			Assert::IsTrue(subStr[2] == 'r');
			Assert::IsTrue(subStr[3] == 'l');
			Assert::IsTrue(subStr[4] == 'd');
			Assert::IsTrue(subStr[5] == '!');

			Assert::IsTrue(sv == "Hello World!");
			Assert::IsTrue(sv != "Hello z World!");
			Assert::IsTrue(sv < "xyz");
			Assert::IsTrue(sv > "abc");
		}

		TEST_METHOD(DebugClass)
		{
			{
				NOU::DebugClass dbgCls0;

				Assert::IsTrue(NOU::DebugClass::getCounter() == 1);

				{
					NOU::DebugClass dbgCls1 = dbgCls0;

					Assert::IsTrue(NOU::DebugClass::getCounter() == 2);
				}

				Assert::IsTrue(NOU::DebugClass::getCounter() == 1);

				NOU::DebugClass dbgCls2 = NOU::NOU_CORE::move(dbgCls0);

				Assert::IsTrue(NOU::DebugClass::getCounter() == 2);
			}

			Assert::IsTrue(NOU::DebugClass::getCounter() == 0);
		}
	};
}