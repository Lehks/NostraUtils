
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
#include "nostrautils\core\ErrorHandler.hpp"
#include "nostrautils\dat_alg\Uninitialized.hpp"
#include "nostrautils\dat_alg\BinaryHeap.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include "nostrautils\dat_alg\Hashing.hpp"
#include "nostrautils\dat_alg\BinarySearch.hpp"

#include "DebugClass.hpp"

#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define NOU_CHECK_ERROR_HANDLER Assert::IsTrue(NOU::NOU_CORE::getErrorHandler().getErrorCount() == 0)

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
			Assert::IsTrue(sizeof(NOU::int8) >= 1);
			Assert::IsTrue(sizeof(NOU::uint8) >= 1);
			Assert::IsTrue(sizeof(NOU::int16) >= 2);
			Assert::IsTrue(sizeof(NOU::uint16) >= 2);
			Assert::IsTrue(sizeof(NOU::int32) >= 4);
			Assert::IsTrue(sizeof(NOU::uint32) >= 4);
			Assert::IsTrue(sizeof(NOU::int64) >= 8);
			Assert::IsTrue(sizeof(NOU::uint64) >= 8);

			Assert::IsTrue(sizeof(NOU::char8) >= 1);
			Assert::IsTrue(sizeof(NOU::char16) >= 2);
			Assert::IsTrue(sizeof(NOU::char32) >= 4);

			/*
			  sizeof(long double) >= 4 / 8 to sort out those compilers that do not have a float that is
			  32 / 64 bit wide
			*/
			Assert::IsTrue(sizeof(NOU::float32) == 4 && sizeof(long double) >= 4);
			Assert::IsTrue(sizeof(NOU::float64) == 8 && sizeof(long double) >= 8);

			NOU_CHECK_ERROR_HANDLER;
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

			NOU_CHECK_ERROR_HANDLER;
		}

		TEST_METHOD(Clamp)
		{
			Assert::AreEqual(NOU::NOU_CORE::clamp(2, 1, 3), 2); //in interval
			Assert::AreEqual(NOU::NOU_CORE::clamp(2, 2, 3), 2); //on min border
			Assert::AreEqual(NOU::NOU_CORE::clamp(2, 3, 3), 3); //on max border
			Assert::AreEqual(NOU::NOU_CORE::clamp(1, 2, 3), 2); //smaller than min
			Assert::AreEqual(NOU::NOU_CORE::clamp(4, 3, 3), 3); //greater than max
		
			NOU_CHECK_ERROR_HANDLER;
		}

		TEST_METHOD(Swap)
		{
			NOU::int32 a = 1;
			NOU::int32 b = 2;

			NOU::NOU_DAT_ALG::swap(&a, &b);

			Assert::AreEqual(2,a);
			Assert::AreEqual(1,b);
		
			NOU_CHECK_ERROR_HANDLER;
		}


		struct NOU_CLASS Foo
		{
		public:
			int m_i;
			bool m_b;
			float m_f;

			Foo() = default;
			Foo(Foo &&other)
			{
				m_i = other.m_i;
				m_b = other.m_b;
				m_f = other.m_f;
			}
			Foo(int i, bool b, float f) :
				m_i(i),
				m_b(b),
				m_f(f)
			{}
		};

		struct NotCopiable
		{
			NotCopiable() = default;
			NotCopiable(const NotCopiable&) = delete;
			NotCopiable(NotCopiable&&) = default;
		};

		TEST_METHOD(Vector)
		{
			NOU::NOU_DAT_ALG::Vector<NOU::int32> vec1(10);

			Assert::AreEqual(static_cast<NOU::sizeType>(0), vec1.size());

			for (NOU::int32 i = 0; i < 10; i++)
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

			vec2.swap(0, 1);
			Assert::AreEqual(0, vec2[1]);

			vec2.remove(0);
			Assert::AreEqual(0, vec2[0]);

			NOU::sizeType i = 0;

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


			{
				NOU::NOU_DAT_ALG::Vector<NOU::DebugClass> vec5(1);

				vec5.pushBack(NOU::DebugClass());
				vec5.pushBack(NOU::DebugClass());
				vec5.remove(0);
				vec5.pushBack(NOU::DebugClass());
				vec5.remove(1);
				vec5.remove(0);

				Assert::IsTrue(NOU::DebugClass::getCounter() == 0);

				vec5.push(NOU::DebugClass());
				vec5.push(NOU::DebugClass());
				vec5.push(NOU::DebugClass());
			}

			Assert::AreEqual(0, vec1.peek());
			Assert::AreEqual(0, vec1.peekFront());

			Assert::IsTrue(NOU::DebugClass::getCounter() == 0);

			//Check if this compiles
			NOU::NOU_DAT_ALG::Vector<NotCopiable> vec;
		
			NOU_CHECK_ERROR_HANDLER;
		}

		TEST_METHOD(Comparator)
		{
			//int as dummy type
			Assert::IsTrue(std::is_same_v<NOU::NOU_DAT_ALG::Comparator<int>,
				decltype(&NOU::NOU_DAT_ALG::genericComparator<int>)>);

			Assert::IsTrue(std::is_same_v<NOU::NOU_DAT_ALG::Comparator<int>,
				decltype(&NOU::NOU_DAT_ALG::genericInvertedComparator<int>)>);

			Assert::IsTrue(NOU::NOU_DAT_ALG::invert(-1) == 1);
			Assert::IsTrue(NOU::NOU_DAT_ALG::invert(0) == 0);
			Assert::IsTrue(NOU::NOU_DAT_ALG::invert(1) == -1);

			Assert::IsTrue(NOU::NOU_DAT_ALG::genericComparator(1, 5) < 0);

			Assert::IsTrue(NOU::NOU_DAT_ALG::genericComparator(5, 5) == 0);

			Assert::IsTrue(NOU::NOU_DAT_ALG::genericComparator(5, 1) > 0);


			Assert::IsTrue(NOU::NOU_DAT_ALG::genericComparator<NOU::uint64>(1, 5) < 0);

			Assert::IsTrue(NOU::NOU_DAT_ALG::genericComparator<NOU::uint64>(5, 5) == 0);

			Assert::IsTrue(NOU::NOU_DAT_ALG::genericComparator<NOU::uint64>(5, 1) > 0);




			Assert::IsTrue(NOU::NOU_DAT_ALG::genericComparator('A', 'a') == 0);

			Assert::IsTrue(NOU::NOU_DAT_ALG::genericComparator('a', 'A') == 0);

			Assert::IsTrue(NOU::NOU_DAT_ALG::genericComparator('a', 'b') < 0);

			Assert::IsTrue(NOU::NOU_DAT_ALG::genericComparator('A', 'b') < 0);
		


			Assert::IsTrue(NOU::NOU_DAT_ALG::genericComparator(static_cast<NOU::char16>('A'),
				static_cast<NOU::char16>('a')) == 0);

			Assert::IsTrue(NOU::NOU_DAT_ALG::genericComparator(static_cast<NOU::char16>('a'),
				static_cast<NOU::char16>('A')) == 0);

			Assert::IsTrue(NOU::NOU_DAT_ALG::genericComparator(static_cast<NOU::char16>('a'),
				static_cast<NOU::char16>('b')) < 0);

			Assert::IsTrue(NOU::NOU_DAT_ALG::genericComparator(static_cast<NOU::char16>('A'),
				static_cast<NOU::char16>('b')) < 0);


			Assert::IsTrue(NOU::NOU_DAT_ALG::genericComparator(static_cast<NOU::char32>('A'),
				static_cast<NOU::char32>('a')) == 0);

			Assert::IsTrue(NOU::NOU_DAT_ALG::genericComparator(static_cast<NOU::char32>('a'),
				static_cast<NOU::char32>('A')) == 0);

			Assert::IsTrue(NOU::NOU_DAT_ALG::genericComparator(static_cast<NOU::char32>('a'),
				static_cast<NOU::char32>('b')) < 0);

			Assert::IsTrue(NOU::NOU_DAT_ALG::genericComparator(static_cast<NOU::char32>('A'),
				static_cast<NOU::char32>('b')) < 0);
		
			NOU_CHECK_ERROR_HANDLER;
		}


		struct TestDeleter
		{
			void operator () (int* i)
			{
				testVar = true;
				delete i;
			}
		};

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
		
			NOU_CHECK_ERROR_HANDLER;
		}

		TEST_METHOD(FastQueue)
		{
			while(NOU::NOU_CORE::getErrorHandler().getErrorCount() != 0)
				NOU::NOU_CORE::getErrorHandler().popError();

			NOU::NOU_MEM_MNGT::DebugAllocationCallback<NOU::DebugClass> allocator;

			{
				NOU::NOU_DAT_ALG::FastQueue<NOU::DebugClass> fq(5, allocator);

				Assert::IsTrue(fq.capacity() == 5);
				Assert::IsTrue(&fq.getAllocationCallback() == &allocator);

				Assert::IsTrue(fq.size() == 0);
				Assert::IsTrue(fq.empty());

				fq.push(NOU::DebugClass());
				fq.push(NOU::DebugClass());
				fq.push(NOU::DebugClass());
				fq.push(NOU::DebugClass());

				fq.pop();
				fq.pop();
				fq.pop();
				fq.pop();

				Assert::IsTrue(NOU::DebugClass::getCounter() == 0);

				fq.push(NOU::DebugClass());
				fq.push(NOU::DebugClass());
				fq.push(NOU::DebugClass());
				fq.push(NOU::DebugClass());
				fq.push(NOU::DebugClass());

				fq.clear();

				Assert::IsTrue(NOU::DebugClass::getCounter() == 0);

				fq.push(NOU::DebugClass());
				fq.push(NOU::DebugClass());
				fq.push(NOU::DebugClass());
			}

			Assert::IsTrue(NOU::DebugClass::getCounter() == 0);
			Assert::IsTrue(allocator.getCounter() == 0);

			NOU::NOU_DAT_ALG::FastQueue<int> fq;
		
			fq.push(1);
			fq.push(2);
			fq.push(3);
			fq.push(4);
		
			Assert::IsTrue(fq.peek() == 1);
		
			Assert::IsTrue(fq.pop() == 1);
			Assert::IsTrue(fq.pop() == 2);
			Assert::IsTrue(fq.pop() == 3);
			Assert::IsTrue(fq.pop() == 4);

			Assert::IsTrue(NOU::NOU_CORE::getErrorHandler().getErrorCount() == 0);

			//Check if this compiles
			NOU::NOU_DAT_ALG::FastQueue<NotCopiable>();
		
			NOU_CHECK_ERROR_HANDLER;
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
		
			NOU_CHECK_ERROR_HANDLER;
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
		
			NOU_CHECK_ERROR_HANDLER;
		}

		TEST_METHOD(DebugAllocationCallback)
		{
			NOU::NOU_MEM_MNGT::DebugAllocationCallback<int> alloc;

			int *iPtr = alloc.allocate(5);

			Assert::IsTrue(alloc.getCounter() == 1);

			alloc.deallocate(iPtr);

			Assert::IsTrue(alloc.getCounter() == 0);
		
			NOU_CHECK_ERROR_HANDLER;
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
		
			NOU_CHECK_ERROR_HANDLER;
		}

		TEST_METHOD(StringView)
		{
			Assert::IsTrue(
				NOU::NOU_CORE::BooleanConstant<NOU::NOU_DAT_ALG::StringView8::isCharacter('A')>::value);
			Assert::IsTrue(
				NOU::NOU_CORE::BooleanConstant<NOU::NOU_DAT_ALG::StringView8::isCharacter('Z')>::value);
			Assert::IsTrue(
				NOU::NOU_CORE::BooleanConstant<NOU::NOU_DAT_ALG::StringView8::isCharacter('a')>::value);
			Assert::IsTrue(
				NOU::NOU_CORE::BooleanConstant<NOU::NOU_DAT_ALG::StringView8::isCharacter('z')>::value);

			Assert::IsFalse(
				NOU::NOU_CORE::BooleanConstant<NOU::NOU_DAT_ALG::StringView8::isCharacter(' ')>::value);
			Assert::IsFalse(
				NOU::NOU_CORE::BooleanConstant<NOU::NOU_DAT_ALG::StringView8::isCharacter('3')>::value);
			Assert::IsFalse(
				NOU::NOU_CORE::BooleanConstant<NOU::NOU_DAT_ALG::StringView8::isCharacter('%')>::value);
			Assert::IsFalse(
				NOU::NOU_CORE::BooleanConstant<NOU::NOU_DAT_ALG::StringView8::isCharacter('-')>::value);

			Assert::IsTrue(
				NOU::NOU_CORE::BooleanConstant<NOU::NOU_DAT_ALG::StringView8::isDigit('1')>::value);
			Assert::IsTrue(
				NOU::NOU_CORE::BooleanConstant<NOU::NOU_DAT_ALG::StringView8::isDigit('2')>::value);
			Assert::IsTrue(
				NOU::NOU_CORE::BooleanConstant<NOU::NOU_DAT_ALG::StringView8::isDigit('3')>::value);
			Assert::IsTrue(
				NOU::NOU_CORE::BooleanConstant<NOU::NOU_DAT_ALG::StringView8::isDigit('4')>::value);
			Assert::IsTrue(
				NOU::NOU_CORE::BooleanConstant<NOU::NOU_DAT_ALG::StringView8::isDigit('5')>::value);
			Assert::IsTrue(
				NOU::NOU_CORE::BooleanConstant<NOU::NOU_DAT_ALG::StringView8::isDigit('6')>::value);
			Assert::IsTrue(
				NOU::NOU_CORE::BooleanConstant<NOU::NOU_DAT_ALG::StringView8::isDigit('7')>::value);
			Assert::IsTrue(
				NOU::NOU_CORE::BooleanConstant<NOU::NOU_DAT_ALG::StringView8::isDigit('8')>::value);
			Assert::IsTrue(
				NOU::NOU_CORE::BooleanConstant<NOU::NOU_DAT_ALG::StringView8::isDigit('9')>::value);

			Assert::IsFalse(
				NOU::NOU_CORE::BooleanConstant<NOU::NOU_DAT_ALG::StringView8::isDigit(' ')>::value);
			Assert::IsFalse(
				NOU::NOU_CORE::BooleanConstant<NOU::NOU_DAT_ALG::StringView8::isDigit('A')>::value);
			Assert::IsFalse(
				NOU::NOU_CORE::BooleanConstant<NOU::NOU_DAT_ALG::StringView8::isDigit('%')>::value);
			Assert::IsFalse(
				NOU::NOU_CORE::BooleanConstant<NOU::NOU_DAT_ALG::StringView8::isDigit('-')>::value);

			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<
				NOU::NOU_DAT_ALG::StringView8::stringToBoolean("true")>::value);

			Assert::IsFalse(NOU::NOU_CORE::BooleanConstant<
				NOU::NOU_DAT_ALG::StringView8::stringToBoolean("false")>::value);
			Assert::IsFalse(NOU::NOU_CORE::BooleanConstant<
				NOU::NOU_DAT_ALG::StringView8::stringToBoolean("abcde")>::value);
			Assert::IsFalse(NOU::NOU_CORE::BooleanConstant<
				NOU::NOU_DAT_ALG::StringView8::stringToBoolean("12345")>::value);
			Assert::IsFalse(NOU::NOU_CORE::BooleanConstant<
				NOU::NOU_DAT_ALG::StringView8::stringToBoolean("!§$%&")>::value);

			constexpr NOU::NOU_DAT_ALG::StringView8 sv = "Hello World!";

			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv[0] == 'H'>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv[1] == 'e'>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv[2] == 'l'>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv[3] == 'l'>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv[4] == 'o'>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv[5] == ' '>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv[6] == 'W'>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv[7] == 'o'>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv[8] == 'r'>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv[9] == 'l'>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv[10] == 'd'>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv[11] == '!'>::value);

			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv.size() == 12>::value);

			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<*sv.indexIterator(0) == 'H'>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<*sv.indexIterator(1) == 'e'>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<*sv.indexIterator(2) == 'l'>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<*sv.indexIterator(3) == 'l'>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<*sv.indexIterator(4) == 'o'>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<*sv.indexIterator(5) == ' '>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<*sv.indexIterator(6) == 'W'>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<*sv.indexIterator(7) == 'o'>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<*sv.indexIterator(8) == 'r'>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<*sv.indexIterator(9) == 'l'>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<*sv.indexIterator(10) == 'd'>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<*sv.indexIterator(11) == '!'>::value);

			Assert::IsTrue(
				NOU::NOU_CORE::BooleanConstant<sv == "Hello World!">::value);

			Assert::IsTrue(
				NOU::NOU_CORE::BooleanConstant<sv.find('e') == 1>::value);
			Assert::IsTrue(
				NOU::NOU_CORE::BooleanConstant<sv.find('e', 1) == 1>::value);

			Assert::IsTrue(
				NOU::NOU_CORE::BooleanConstant<sv.find('o') == 4>::value);
			Assert::IsTrue(
				NOU::NOU_CORE::BooleanConstant<sv.find('o', 5) == 7>::value);
			Assert::IsTrue(
				NOU::NOU_CORE::BooleanConstant<sv.find('z') == 
				NOU::NOU_DAT_ALG::StringView8::NULL_INDEX>::value);

			Assert::IsTrue(
				NOU::NOU_CORE::BooleanConstant<sv.find("ello") == 1>::value);
			Assert::IsTrue(
				NOU::NOU_CORE::BooleanConstant<sv.find("o") == 4>::value);
			Assert::IsTrue(
				NOU::NOU_CORE::BooleanConstant<sv.find("o", 5) == 7>::value);
			Assert::IsTrue(
				NOU::NOU_CORE::BooleanConstant<sv.find("test") == 
				NOU::NOU_DAT_ALG::StringView8::NULL_INDEX>::value);

			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv.firstIndexOf('H') == 0>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv.firstIndexOf('o') == 4>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv.firstIndexOf('z') == NOU::NOU_DAT_ALG::StringView8::NULL_INDEX>::value);

			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv.lastIndexOf('H') == 0>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv.lastIndexOf('o') == 7>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv.lastIndexOf('z') == NOU::NOU_DAT_ALG::StringView8::NULL_INDEX>::value);

			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv.firstIndexOfNot('H') == 1>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv.firstIndexOfNot('o') == 0>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv.firstIndexOfNot('z') == 0>::value);

			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv.lastIndexOfNot('H') == 11>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv.lastIndexOfNot('o') == 11>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv.lastIndexOfNot('z') == 11>::value);

			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv.startsWith('H')>::value);
			Assert::IsFalse(NOU::NOU_CORE::BooleanConstant<sv.startsWith('g')>::value);

			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv.startsWith("Hell")>::value);
			Assert::IsFalse(NOU::NOU_CORE::BooleanConstant<sv.startsWith("World")>::value);

			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv.endsWith("rld!")>::value == true);
			Assert::IsFalse(NOU::NOU_CORE::BooleanConstant<sv.endsWith("World")>::value == true);

			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<(sv.compareTo("Abc")
				> 0)>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<(sv.compareTo("Hello World!")
				== 0)>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<(sv.compareTo("Xyz")
				< 0)>::value);

			constexpr NOU::NOU_DAT_ALG::StringView8 subStr = sv.logicalSubstring(6);

			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<subStr.size() == 6>::value);

			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<subStr[0] == 'W'>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<subStr[1] == 'o'>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<subStr[2] == 'r'>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<subStr[3] == 'l'>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<subStr[4] == 'd'>::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<subStr[5] == '!'>::value);

			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv == "Hello World!">::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv != "Hello z World!">::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<sv < "xyz">::value);
			Assert::IsTrue(NOU::NOU_CORE::BooleanConstant<(sv > "abc")>::value);

			NOU::NOU_DAT_ALG::StringView8 sv1 = "Hello World!";
			NOU::NOU_DAT_ALG::StringView8 sv2 = "Bye World!";

			sv1 = sv2;

			Assert::IsTrue(sv1 == sv2);


			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8::stringToUint32("123") == 123);
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8::stringToUint32("9999999") == 9999999);
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8::stringToUint32("0") == 0);

			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8::stringToInt32("123") == 123);
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8::stringToInt32("9999999") == 9999999);
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8::stringToInt32("0") == 0);
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8::stringToInt32("-123") == -123);
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8::stringToInt32("-9999999") == -9999999);
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8::stringToInt32("-0") == -0);

			Assert::IsTrue(NOU::NOU_DAT_ALG::epsilonCompare(NOU::NOU_DAT_ALG::StringView8::stringToFloat32("123"), 123.0f, 0.001f) == 0);
			Assert::IsTrue(NOU::NOU_DAT_ALG::epsilonCompare(NOU::NOU_DAT_ALG::StringView8::stringToFloat32("9999999"), 9999999.0f, 0.001f) == 0);
			Assert::IsTrue(NOU::NOU_DAT_ALG::epsilonCompare(NOU::NOU_DAT_ALG::StringView8::stringToFloat32("0"), 0.0f, 0.001f) == 0);
			Assert::IsTrue(NOU::NOU_DAT_ALG::epsilonCompare(NOU::NOU_DAT_ALG::StringView8::stringToFloat32("123.456"), 123.456f, 0.001f) == 0);
			Assert::IsTrue(NOU::NOU_DAT_ALG::epsilonCompare(NOU::NOU_DAT_ALG::StringView8::stringToFloat32("5.99"), 5.99f, 0.001f) == 0);
			Assert::IsTrue(NOU::NOU_DAT_ALG::epsilonCompare(NOU::NOU_DAT_ALG::StringView8::stringToFloat32("14.5"), 14.5f, 0.001f) == 0);
			Assert::IsTrue(NOU::NOU_DAT_ALG::epsilonCompare(NOU::NOU_DAT_ALG::StringView8::stringToFloat32("-123.456"), -123.456f, 0.001f) == 0);
			Assert::IsTrue(NOU::NOU_DAT_ALG::epsilonCompare(NOU::NOU_DAT_ALG::StringView8::stringToFloat32("-5.99"), -5.99f, 0.001f) == 0);
			Assert::IsTrue(NOU::NOU_DAT_ALG::epsilonCompare(NOU::NOU_DAT_ALG::StringView8::stringToFloat32("-14.5"), -14.5f, 0.001f) == 0);
		
			NOU_CHECK_ERROR_HANDLER;
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

			NOU::DebugClass dbgCls0(1);
			NOU::DebugClass dbgCls1(3);

			Assert::IsTrue(dbgCls0 < dbgCls1);
			Assert::IsFalse(dbgCls0 > dbgCls1);
			Assert::IsTrue(dbgCls0 <= dbgCls1);
			Assert::IsFalse(dbgCls0 >= dbgCls1);
			Assert::IsFalse(dbgCls0 == dbgCls1);
			Assert::IsTrue(dbgCls0 != dbgCls1);

			NOU::DebugClass dbgCls2(1);

			Assert::IsFalse(dbgCls0 < dbgCls2);
			Assert::IsFalse(dbgCls0 > dbgCls2);
			Assert::IsTrue(dbgCls0 <= dbgCls2);
			Assert::IsTrue(dbgCls0 >= dbgCls2);
			Assert::IsTrue(dbgCls0 == dbgCls2);
			Assert::IsFalse(dbgCls0 != dbgCls2);

			Assert::IsTrue(dbgCls0.get() == 1);
			Assert::IsTrue(dbgCls1.get() == 3);
			Assert::IsTrue(dbgCls2.get() == 1);

			NOU::DebugClass dbgCls3 = dbgCls0;
			NOU::DebugClass dbgCls4 = NOU::NOU_CORE::move(dbgCls1);

			Assert::IsTrue(dbgCls3.get() == 1);
			Assert::IsTrue(dbgCls4.get() == 3);
		
			NOU_CHECK_ERROR_HANDLER;
		}

		TEST_METHOD(IsDefaultConstructible)
		{
			struct NotDefaultConstructible
			{
				NotDefaultConstructible(int)
				{

				}
			};

			Assert::IsTrue(NOU::NOU_CORE::IsDefaultConstructible<int>::value);
			Assert::IsTrue(NOU::NOU_CORE::IsDefaultConstructible
				<NOU::NOU_MEM_MNGT::GenericAllocationCallback<int>>::value);
			Assert::IsFalse(NOU::NOU_CORE::IsDefaultConstructible<NotDefaultConstructible>::value);
		
			NOU_CHECK_ERROR_HANDLER;
		}

		TEST_METHOD(ErrorHandler)
		{
			NOU::NOU_CORE::ErrorHandler handler;

			Assert::IsTrue(handler.getErrorCount() == 0);

			NOU_PUSH_ERROR(handler, NOU::NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS, "The index was out of "
				"bounds.");

			Assert::IsTrue(handler.getErrorCount() == 1);

			//validate that the error in the handler is the one that was supposed to be pushed
			Assert::IsTrue(handler.peekError().getID() == NOU::NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS);
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8(handler.peekError().getFnName()) == NOU_FUNC_NAME);
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8(handler.peekError().getFile()) == __FILE__);
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8(handler.peekError().getMsg()) == 
				"The index was out of bounds.");
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8(handler.peekError().getName()) == 
				"INDEX_OUT_OF_BOUNDS");
		
			auto errorPeek = handler.peekError();
			auto errorPop = handler.popError();

			//validate that the popped error is the same one as the peeked error.
			Assert::IsTrue(errorPeek.getID() == errorPop.getID());
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8(errorPeek.getFnName()) == errorPop.getFnName());
			Assert::IsTrue(errorPeek.getLine() == errorPop.getLine());
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8(errorPeek.getFile()) == errorPop.getFile());
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8(errorPeek.getMsg()) == errorPop.getMsg());
			Assert::IsTrue(NOU::NOU_DAT_ALG::StringView8(errorPeek.getName()) == errorPop.getName());

			Assert::IsTrue(handler.getErrorCount() == 0);

			NOU_PUSH_ERROR(handler, NOU::NOU_CORE::ErrorCodes::UNKNOWN_ERROR, "Some message");
			NOU_PUSH_ERROR(handler, NOU::NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS, "Some other message");

			Assert::IsTrue(handler.getErrorCount() == 2);

			//validate that the order in which the errors are popped is correct
			Assert::IsTrue(handler.popError().getID() == NOU::NOU_CORE::ErrorCodes::UNKNOWN_ERROR);
			Assert::IsTrue(handler.popError().getID() == NOU::NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS);
			
			Assert::IsTrue(handler.getErrorCount() == 0);

			NOU::NOU_CORE::ErrorHandler::ErrorType error = 50000;

			//push some invalid error code
			NOU_PUSH_ERROR(handler, error, "Some invalid code");

			Assert::IsTrue(handler.peekError().getID() == NOU::NOU_CORE::ErrorCodes::UNKNOWN_ERROR);
			Assert::IsTrue(handler.peekError().getActualID() == error);
		
			NOU_CHECK_ERROR_HANDLER;
		}

		TEST_METHOD(EpsilonCompare)
		{
			Assert::IsTrue(NOU::NOU_DAT_ALG::epsilonCompare(122.456, 123.457, 0.1) <  0);
			Assert::IsTrue(NOU::NOU_DAT_ALG::epsilonCompare(123.456, 123.457, 0.1) == 0);
			Assert::IsTrue(NOU::NOU_DAT_ALG::epsilonCompare(124.456, 123.457, 0.1) > 0);

			NOU_CHECK_ERROR_HANDLER;
		}

		TEST_METHOD(InvokeResult)
		{
			Assert::IsTrue(NOU::NOU_CORE::AreSame<void, NOU::NOU_CORE::InvokeResult_t<
				decltype(dummyFunc0), int>>::value);
			Assert::IsTrue(NOU::NOU_CORE::AreSame<int, NOU::NOU_CORE::InvokeResult_t<
				decltype(dummyFunc1), int>>::value);
		
			NOU_CHECK_ERROR_HANDLER;
		}

		TEST_METHOD(Uninitialized)
		{
			{
				NOU::NOU_DAT_ALG::Uninitialized<NOU::DebugClass> ui;

				Assert::IsFalse(ui.isValid());

				Assert::IsTrue(NOU::DebugClass::getCounter() == 0);

				ui = NOU::DebugClass(5);

				Assert::IsTrue(ui.isValid());

				Assert::IsTrue(ui->get() == 5);

				Assert::IsTrue(NOU::DebugClass::getCounter() == 1);

				ui = NOU::DebugClass(10);

				Assert::IsTrue(ui.isValid());

				Assert::IsTrue(ui->get() == 10);

				Assert::IsTrue(NOU::DebugClass::getCounter() == 1);
			}

			Assert::IsTrue(NOU::DebugClass::getCounter() == 0);
		
			NOU_CHECK_ERROR_HANDLER;
		}

		TEST_METHOD(String)
		{
			NOU::NOU_DAT_ALG::String<NOU::char8> str;

			str.append('a');
			Assert::AreEqual(str[0], 'a');

			str.append("Hallo");
			Assert::AreEqual(str[1], 'H');

			str.insert(0, 'A');
			Assert::AreEqual(str[0], 'A');

			str.appendIf(1, 'T');
			Assert::AreEqual(str[str.size() - 1], 'T');

			str.append(1);
			Assert::AreEqual(str[str.size() - 1], '1');

			str.append(-1);
			Assert::AreEqual(str[str.size() - 2], '-');
			Assert::AreEqual(str[str.size() - 1], '1');

			NOU::sizeType i = 0; // becasue of NULLTERMINATOR
			str.clear();
			Assert::AreEqual(str.size(), i);

			str.append("Hallo Welt");
			str.replace('l', 'V', 0, str.size() - 1);
			Assert::AreEqual(str[2], 'V');
			Assert::AreEqual(str[3], 'V');
			Assert::AreEqual(str[8], 'V');

			str.clear();
			str.append(17.025);
			Assert::AreEqual(str[0], '1');
			Assert::AreEqual(str[1], '7');
			Assert::AreEqual(str[2], '.');
			Assert::AreEqual(str[3], '0');
			Assert::AreEqual(str[4], '2');
			Assert::AreEqual(str[5], '5');

			str.remove(2, str.size());
			Assert::AreEqual(str[0], '1');
			Assert::AreEqual(str[1], '7');
			Assert::AreNotEqual(str[0], '.');

			NOU::NOU_DAT_ALG::String<NOU::char8> substr;

			substr.append(str.substring(0, 1));
			Assert::AreEqual(str[0], '1');

			substr.clear();
			substr.append(str.copy());
			Assert::AreEqual(str[0], '1');
			Assert::AreEqual(str[1], '7');
			substr.clear();
			str.clear();
			substr.append("AAAAA");
			str.append("Hallo");
		
			NOU_CHECK_ERROR_HANDLER;
		}

		TEST_METHOD(BinaryHeap)
		{
			NOU::NOU_DAT_ALG::BinaryHeap<NOU::int32> b;

			b.enqueue(10, 1);
			b.enqueue(11, 2);
			b.enqueue(12, 3);
			b.enqueue(13, 4);
			b.enqueue(14, 1);
			b.enqueue(15, 4);

			Assert::IsTrue(b.at(0) == 10);
			Assert::IsTrue(b.at(1) == 14);
			Assert::IsTrue(b.at(2) == 12);
			Assert::IsTrue(b.at(3) == 13);
			Assert::IsTrue(b.at(4) == 11);
			Assert::IsTrue(b.at(5) == 15);


			b.dequeue();

			Assert::IsTrue(b.at(0) == 14);
			Assert::IsTrue(b.at(1) == 12);
			Assert::IsTrue(b.at(2) == 13);
			Assert::IsTrue(b.at(3) == 11);
			Assert::IsTrue(b.at(4) == 15);
			
			b.decreaseKey(2, 2);
			
			Assert::IsTrue(b.at(0) == 14);
			Assert::IsTrue(b.at(1) == 12);
			Assert::IsTrue(b.at(2) == 13);
			Assert::IsTrue(b.at(3) == 11);
			Assert::IsTrue(b.at(4) == 15);
		
			NOU_CHECK_ERROR_HANDLER;
		}


		TEST_METHOD(Hashfunction)
		{
			NOU::sizeType testInt = 42;
			NOU::sizeType hashSize = 5;
			NOU::sizeType test;
			test = NOU::NOU_DAT_ALG::hashObj(&testInt, hashSize);
			testInt = 9234978;
			Assert::AreEqual(test, NOU::NOU_DAT_ALG::hashObj(&testInt, hashSize));

			testInt = 42;
			test = NOU::NOU_DAT_ALG::hashObj(&testInt);
			testInt = 9234978;
			Assert::AreEqual(test, NOU::NOU_DAT_ALG::hashObj(&testInt));

		}

		TEST_METHOD(BinarySearch)
		{
			NOU::NOU_DAT_ALG::Vector<NOU::sizeType> vec;
			vec.pushBack(1);
			vec.pushBack(5);
			vec.pushBack(13);
			vec.pushBack(18);
			vec.pushBack(21);
			vec.pushBack(43);
			vec.pushBack(92);

			NOU::sizeType search_vals[] = { 1, 5, 19, 21, 92, 43, 103, 0};

			
			Assert::IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec.data(), search_vals[0], 0, vec.size() - 1) == 0);
			Assert::IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec.data(), search_vals[1], 0, vec.size() - 1) == 1);
			Assert::IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec.data(), search_vals[2], 0, vec.size() - 1) == -1);
			Assert::IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec.data(), search_vals[3], 0, vec.size() - 1) == 4);
			Assert::IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec.data(), search_vals[4], 0, vec.size() - 1) == 6);
			Assert::IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec.data(), search_vals[5], 0, vec.size() - 1) == 5);
			Assert::IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec.data(), search_vals[6], 0, vec.size() - 1) == -1);

			//Assert::IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec, search_vals[0], 0, -1) == 0);
			//Assert::IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec, search_vals[1], 0, -1) == 1);
			//Assert::IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec, search_vals[2], 0, -1) == -1);
			//Assert::IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec, search_vals[3], 0, -1) == 4);
			//Assert::IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec, search_vals[4], 0, -1) == 6);
			//Assert::IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec, search_vals[5], 0, -1) == 5);
			//Assert::IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec, search_vals[6], 0, -1) == -1);

			NOU::sizeType insertionIndex;

			NOU::NOU_DAT_ALG::binarySearch(vec.data(), search_vals[2], 0, vec.size() - 1, &insertionIndex);
			Assert::IsTrue(insertionIndex == 4);
			NOU::NOU_DAT_ALG::binarySearch(vec.data(), search_vals[6], 0, vec.size() - 1, &insertionIndex);
			Assert::IsTrue(insertionIndex == 7);
			NOU::NOU_DAT_ALG::binarySearch(vec.data(), search_vals[7], 0, vec.size() - 1, &insertionIndex);
			Assert::IsTrue(insertionIndex == 0);
		}
	};
}