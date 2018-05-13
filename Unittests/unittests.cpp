#define CATCH_CONFIG_RUNNER
#include "Catch/catch.hpp"

#define NOU_DEBUG

#include "nostrautils/NostraUtils.hpp"

#include "DebugClass.hpp"

#include <type_traits>
#include <string>
#include <iostream>

#define NOU_CHECK_ERROR_HANDLER 																		 \
				auto errorCount = NOU::NOU_CORE::getErrorHandler().getErrorCount();						 \
				while(NOU::NOU_CORE::getErrorHandler().getErrorCount() > 0)								 \
				{																						 \
					NOU::NOU_CORE::getErrorHandler().popError();										 \
				}																						 \
				IsTrue(errorCount == 0);

void printErrors()
{
    while (NOU::NOU_CORE::getErrorHandler().getErrorCount() != 0)
    {
        std::string msg;
        msg += NOU::NOU_CORE::getErrorHandler().peekError().getName();
        msg += " ";
        msg += std::to_string(NOU::NOU_CORE::getErrorHandler().peekError().getLine());
        msg += " ";
        msg += NOU::NOU_CORE::getErrorHandler().peekError().getFile();
        NOU::NOU_CORE::getErrorHandler().popError();

        std::cout << msg.c_str() << std::endl;
    }
}

#define TEST_METHOD(name) TEST_CASE(NOU_STRINGIFY(name), "[" NOU_STRINGIFY(name) "]")

#define IsTrue(...) REQUIRE(__VA_ARGS__)

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

TEST_METHOD(TypeSizes)
{
IsTrue(sizeof(NOU::int8) >= 1);
IsTrue(sizeof(NOU::uint8) >= 1);
IsTrue(sizeof(NOU::int16) >= 2);
IsTrue(sizeof(NOU::uint16) >= 2);
IsTrue(sizeof(NOU::int32) >= 4);
IsTrue(sizeof(NOU::uint32) >= 4);
IsTrue(sizeof(NOU::int64) >= 8);
IsTrue(sizeof(NOU::uint64) >= 8);

IsTrue(sizeof(NOU::char8) >= 1);
IsTrue(sizeof(NOU::char16) >= 2);
IsTrue(sizeof(NOU::char32) >= 4);

/*
  sizeof(long double) >= 4 / 8 to sort out those compilers that do not have a float that is
  32 / 64 bit wide
*/
bool conditionFloat32 = (sizeof(NOU::float32) == 4 && sizeof(long double) >= 4);
bool conditionFloat64 = (sizeof(NOU::float64) == 8 && sizeof(long double) >= 8);

IsTrue(conditionFloat32);
IsTrue(conditionFloat64);

NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(Versions)
{
NOU::uint32 major0 = 0;
NOU::uint32 minor0 = 0;
NOU::uint32 patch0 = 0;
NOU::uint32 version0 = NOU_MAKE_VERSION(major0, minor0, patch0);

IsTrue(NOU_VERSION_MAJOR(version0) == major0);
IsTrue(NOU_VERSION_MINOR(version0) == minor0);
IsTrue(NOU_VERSION_PATCH(version0) == patch0);

NOU::uint32 major1 = 5;
NOU::uint32 minor1 = 23;
NOU::uint32 patch1 = 9187;
NOU::uint32 version1 = NOU_MAKE_VERSION(major1, minor1, patch1);

IsTrue(NOU_VERSION_MAJOR(version1) == major1);
IsTrue(NOU_VERSION_MINOR(version1) == minor1);
IsTrue(NOU_VERSION_PATCH(version1) == patch1);

NOU::uint32 major2 = NOU_VERSION_MAJOR_MAX;
NOU::uint32 minor2 = NOU_VERSION_MINOR_MAX;
NOU::uint32 patch2 = NOU_VERSION_PATCH_MAX;
NOU::uint32 version2 = NOU_MAKE_VERSION(major2, minor2, patch2);

IsTrue(NOU_VERSION_MAJOR(version2) == major2);
IsTrue(NOU_VERSION_MINOR(version2) == minor2);
IsTrue(NOU_VERSION_PATCH(version2) == patch2);

NOU::uint32 major3 = NOU_VERSION_MAJOR_MAX + 5; //overflow on purpose
NOU::uint32 minor3 = NOU_VERSION_MINOR_MAX + 5;
NOU::uint32 patch3 = NOU_VERSION_PATCH_MAX + 5;
NOU::NOU_CORE::Version version3(major2, minor2, patch2);

//compare with normal, not overflown values
IsTrue(version3.getMajor() == NOU_VERSION_MAJOR_MAX);
IsTrue(version3.getMinor() == NOU_VERSION_MINOR_MAX);
IsTrue(version3.getPatch() == NOU_VERSION_PATCH_MAX);

NOU::NOU_CORE::Version version4 = version3;

IsTrue(version3 == version4);
IsTrue(!(version3 != version4));
IsTrue(!(version3 > version4));
IsTrue(!(version3 < version4));
IsTrue(version3 >= version4);
IsTrue(version3 <= version4);

NOU::NOU_CORE::Version version5(1, 2, 3);
NOU::NOU_CORE::Version version6(1, 2, 4);

IsTrue(!(version5 == version6));
IsTrue(version5 != version6);
IsTrue(!(version5 > version6));
IsTrue(version5 < version6);
IsTrue(!(version5 >= version6));
IsTrue(version5 <= version6);

NOU::NOU_CORE::Version version7(1, 2, 3);
NOU::NOU_CORE::Version version8(1, 3, 3);

IsTrue(!(version7 == version8));
IsTrue(version7 != version8);
IsTrue(!(version7 > version8));
IsTrue(version7 < version8);
IsTrue(!(version7 >= version8));
IsTrue(version7 <= version8);

NOU::NOU_CORE::Version version9(1, 2, 3);
NOU::NOU_CORE::Version version10(2, 2, 4);

IsTrue(!(version9 == version10));
IsTrue(version9 != version10);
IsTrue(!(version9 > version10));
IsTrue(version9 < version10);
IsTrue(!(version9 >= version10));
IsTrue(version9 <= version10);

NOU::NOU_CORE::Version version11(5, 9, 4);
NOU::NOU_CORE::Version version12(1, 10, 4);

IsTrue(!(version11 == version12));
IsTrue(version11 != version12);
IsTrue(version11 > version12);
IsTrue(!(version11 < version12));
IsTrue(version11 >= version12);
IsTrue(!(version11 <= version12));

NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(Clamp)
{
IsTrue(NOU::NOU_CORE::clamp(2, 1, 3) == 2); //in interval
IsTrue(NOU::NOU_CORE::clamp(2, 2, 3) == 2); //on min border
IsTrue(NOU::NOU_CORE::clamp(2, 3, 3) == 3); //on max border
IsTrue(NOU::NOU_CORE::clamp(1, 2, 3) == 2); //smaller than min
IsTrue(NOU::NOU_CORE::clamp(4, 3, 3) == 3); //greater than max

NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(Swap)
{
NOU::int32 a = 1;
NOU::int32 b = 2;

NOU::NOU_DAT_ALG::swap(&a, &b);

IsTrue(2 == a);
IsTrue(1 == b);

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

IsTrue(static_cast<NOU::sizeType>(0) == vec1.size());

for (NOU::int32 i = 0; i < 10; i++)
{
vec1.pushBack(i);
}

IsTrue(0 == vec1[0]);
IsTrue(1 == vec1[1]);
IsTrue(2 == vec1[2]);
IsTrue(3 == vec1[3]);
IsTrue(4 == vec1[4]);
IsTrue(5 == vec1[5]);
IsTrue(6 == vec1[6]);
IsTrue(7 == vec1[7]);
IsTrue(8 == vec1[8]);
IsTrue(9 == vec1[9]);

IsTrue(!vec1.empty());

vec1.pushBack(10);
IsTrue(10 == vec1[10]);

NOU::NOU_DAT_ALG::Vector<NOU::int32> vec2(11);
vec2 = vec1;
IsTrue(vec2[9] == vec1[9]);

NOU::NOU_DAT_ALG::Vector<NOU::int32> vec3(10);
vec3 = vec1;
IsTrue(vec3[9] == vec1[9]);

vec1.pushFront(15);
IsTrue(15 == vec1[0]);

NOU::int32 testinteger = 0;
testinteger = vec1.popFront();
IsTrue(15 == testinteger);

vec2.swap(0, 1);
IsTrue(0 == vec2[1]);

vec2.remove(0);
IsTrue(0 == vec2[0]);

NOU::sizeType i = 0;

for (NOU::NOU_DAT_ALG::VectorIterator<NOU::int32> it = vec2.begin(); it != vec2.end(); it++)
{
IsTrue(*it == vec2[i]);
i++;
}

i = vec2.size() - 1;

for (NOU::NOU_DAT_ALG::VectorReverseIterator<NOU::int32> it = vec2.rbegin(); it != vec2.rend(); it++)
{
IsTrue(*it == vec2[i]);
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


IsTrue(dbgAlloc.getCounter() == 0);

IsTrue(0 == vec2.peek());
IsTrue(0 == vec2.peekFront());


{
NOU::NOU_DAT_ALG::Vector<NOU::DebugClass> vec5(1);

vec5.pushBack(NOU::DebugClass());
vec5.pushBack(NOU::DebugClass());
vec5.remove(0);
vec5.pushBack(NOU::DebugClass());
vec5.remove(1);
vec5.remove(0);

IsTrue(NOU::DebugClass::getCounter() == 0);

vec5.push(NOU::DebugClass());
vec5.push(NOU::DebugClass());
vec5.push(NOU::DebugClass());
}

IsTrue(0 == vec1.peek());
IsTrue(0 == vec1.peekFront());

IsTrue(NOU::DebugClass::getCounter() == 0);

//Check if this compiles
NOU::NOU_DAT_ALG::Vector<NotCopiable> vec;

NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(Comparator)
{
//int as dummy type
IsTrue(std::is_same<NOU::NOU_DAT_ALG::Comparator<int>,
       decltype(&NOU::NOU_DAT_ALG::genericComparator<int>)>::value);

IsTrue(std::is_same<NOU::NOU_DAT_ALG::Comparator<int>,
       decltype(&NOU::NOU_DAT_ALG::genericInvertedComparator<int>)>::value);

IsTrue(NOU::NOU_DAT_ALG::invert(-1) == 1);
IsTrue(NOU::NOU_DAT_ALG::invert(0) == 0);
IsTrue(NOU::NOU_DAT_ALG::invert(1) == -1);

IsTrue(NOU::NOU_DAT_ALG::genericComparator(1, 5) < 0);

IsTrue(NOU::NOU_DAT_ALG::genericComparator(5, 5) == 0);

IsTrue(NOU::NOU_DAT_ALG::genericComparator(5, 1) > 0);


IsTrue(NOU::NOU_DAT_ALG::genericComparator<NOU::uint64>(1, 5) < 0);

IsTrue(NOU::NOU_DAT_ALG::genericComparator<NOU::uint64>(5, 5) == 0);

IsTrue(NOU::NOU_DAT_ALG::genericComparator<NOU::uint64>(5, 1) > 0);




IsTrue(NOU::NOU_DAT_ALG::genericComparator('A', 'a') == 0);

IsTrue(NOU::NOU_DAT_ALG::genericComparator('a', 'A') == 0);

IsTrue(NOU::NOU_DAT_ALG::genericComparator('a', 'b') < 0);

IsTrue(NOU::NOU_DAT_ALG::genericComparator('A', 'b') < 0);



IsTrue(NOU::NOU_DAT_ALG::genericComparator(static_cast<NOU::char16>('A'),
                                           static_cast<NOU::char16>('a')) == 0);

IsTrue(NOU::NOU_DAT_ALG::genericComparator(static_cast<NOU::char16>('a'),
                                           static_cast<NOU::char16>('A')) == 0);

IsTrue(NOU::NOU_DAT_ALG::genericComparator(static_cast<NOU::char16>('a'),
                                           static_cast<NOU::char16>('b')) < 0);

IsTrue(NOU::NOU_DAT_ALG::genericComparator(static_cast<NOU::char16>('A'),
                                           static_cast<NOU::char16>('b')) < 0);


IsTrue(NOU::NOU_DAT_ALG::genericComparator(static_cast<NOU::char32>('A'),
                                           static_cast<NOU::char32>('a')) == 0);

IsTrue(NOU::NOU_DAT_ALG::genericComparator(static_cast<NOU::char32>('a'),
                                           static_cast<NOU::char32>('A')) == 0);

IsTrue(NOU::NOU_DAT_ALG::genericComparator(static_cast<NOU::char32>('a'),
                                           static_cast<NOU::char32>('b')) < 0);

IsTrue(NOU::NOU_DAT_ALG::genericComparator(static_cast<NOU::char32>('A'),
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

IsTrue(uPtr.rawPtr() == rawPtr);
IsTrue(uPtr[0] == rawPtr[0]);
IsTrue(uPtr->size() == rawPtr->size()); //check -> operator
IsTrue(*uPtr == *rawPtr);
IsTrue(uPtr);
IsTrue(!NOU::NOU_MEM_MNGT::UniquePtr<std::string>(nullptr,
                                                  NOU::NOU_MEM_MNGT::defaultDeleter));
IsTrue((uPtr <= uPtr1) == (rawPtr <= rawPtr1));
IsTrue((uPtr >= uPtr1) == (rawPtr >= rawPtr1));
IsTrue((uPtr < uPtr1) == (rawPtr < rawPtr1));
IsTrue((uPtr > uPtr1) == (rawPtr > rawPtr1));
IsTrue((uPtr == uPtr1) == (rawPtr == rawPtr1));
IsTrue((uPtr != uPtr1) == (rawPtr != rawPtr1));

IsTrue(uPtr.deleter() == &NOU::NOU_MEM_MNGT::defaultDeleter<std::string>);

uPtr = std::move(uPtr1);

IsTrue(uPtr1.rawPtr() == nullptr);

IsTrue(uPtr.rawPtr() == rawPtr1);

{
//check if this compiles
NOU::NOU_MEM_MNGT::UniquePtr<int, TestDeleter> uPtr2(new int, TestDeleter());

//destructor is called here
}

IsTrue(testVar); //if testVar is true, the destructor has been called.

testVar = false;

NOU::NOU_MEM_MNGT::UniquePtr<int, TestDeleter> uPtr3(new int, TestDeleter());
uPtr3 = new int;

IsTrue(testVar); //if testVar is true, the destructor has been called.

NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(FastQueue)
{
while (NOU::NOU_CORE::getErrorHandler().getErrorCount() != 0)
NOU::NOU_CORE::getErrorHandler().popError();

NOU::NOU_MEM_MNGT::DebugAllocationCallback<NOU::DebugClass> allocator;

{
NOU::NOU_DAT_ALG::FastQueue<NOU::DebugClass> fq(5, allocator);

IsTrue(fq.capacity() == 5);
IsTrue(&fq.getAllocationCallback() == &allocator);

IsTrue(fq.size() == 0);
IsTrue(fq.empty());

fq.push(NOU::DebugClass());
fq.push(NOU::DebugClass());
fq.push(NOU::DebugClass());
fq.push(NOU::DebugClass());

fq.pop();
fq.pop();
fq.pop();
fq.pop();

IsTrue(NOU::DebugClass::getCounter() == 0);

fq.push(NOU::DebugClass());
fq.push(NOU::DebugClass());
fq.push(NOU::DebugClass());
fq.push(NOU::DebugClass());
fq.push(NOU::DebugClass());

fq.clear();

IsTrue(NOU::DebugClass::getCounter() == 0);

fq.push(NOU::DebugClass());
fq.push(NOU::DebugClass());
fq.push(NOU::DebugClass());
}

IsTrue(NOU::DebugClass::getCounter() == 0);
IsTrue(allocator.getCounter() == 0);

NOU::NOU_DAT_ALG::FastQueue<int> fq;

fq.push(1);
fq.push(2);
fq.push(3);
fq.push(4);

IsTrue(fq.peek() == 1);

IsTrue(fq.pop() == 1);
IsTrue(fq.pop() == 2);
IsTrue(fq.pop() == 3);
IsTrue(fq.pop() == 4);

IsTrue(NOU::NOU_CORE::getErrorHandler().getErrorCount() == 0);

//Check if this compiles
NOU::NOU_DAT_ALG::FastQueue<NotCopiable>();

NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(AreSame)
{
IsTrue(NOU::NOU_CORE::AreSame<int, int>::value);
IsTrue(!NOU::NOU_CORE::AreSame<double, int>::value);
IsTrue(!NOU::NOU_CORE::AreSame<int, double>::value);
IsTrue(NOU::NOU_CORE::AreSame<int, int, int>::value);
IsTrue(!NOU::NOU_CORE::AreSame<int, int, double>::value);
IsTrue(!NOU::NOU_CORE::AreSame<int, double, double>::value);
IsTrue(!NOU::NOU_CORE::AreSame<int, double, double, int>::value);
IsTrue(NOU::NOU_CORE::AreSame<int, int, int, int>::value);
IsTrue(NOU::NOU_CORE::AreSame<double, double, double, double, double>::value);
IsTrue(!NOU::NOU_CORE::AreSame<int, int, int, int, int, int, double>::value);

NOU_CHECK_ERROR_HANDLER;
}

#ifdef NOU_EXISTS_FEATURE_IS_INVOCABLE_R
TEST_METHOD(IsInvocable)
{
	IsTrue(NOU::NOU_CORE::IsInvocable<decltype(dummyFunc0), int>::value);
	IsTrue(!NOU::NOU_CORE::IsInvocable<decltype(dummyFunc0), std::string>::value);
	IsTrue(!NOU::NOU_CORE::IsInvocable<int, int>::value);

	IsTrue(NOU::NOU_CORE::IsInvocableR<int, decltype(dummyFunc1), int>::value);
	IsTrue(!NOU::NOU_CORE::IsInvocableR<int, decltype(dummyFunc1), std::string>::value);
	IsTrue(!NOU::NOU_CORE::IsInvocableR<std::string, decltype(dummyFunc1), int>::value);

	IsTrue(!NOU::NOU_CORE::IsInvocableR<int, int, int>::value);

	NOU_CHECK_ERROR_HANDLER;
}
#endif

TEST_METHOD(DebugAllocationCallback)
{
NOU::NOU_MEM_MNGT::DebugAllocationCallback<int> alloc;

int *iPtr = alloc.allocate(5);

IsTrue(alloc.getCounter() == 1);

alloc.deallocate(iPtr);

IsTrue(alloc.getCounter() == 0);

NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(AllocationCallbackDeleter)
{
NOU::NOU_MEM_MNGT::DebugAllocationCallback<int> dbgAlloc;
NOU::NOU_MEM_MNGT::AllocationCallbackRefDeleter<int> deleter0(dbgAlloc);

int *iPtr0 = dbgAlloc.allocate();

deleter0(iPtr0); //delete using deleter

IsTrue(dbgAlloc.getCounter() == 0);

auto callback = NOU::NOU_MEM_MNGT::DebugAllocationCallback<int>();
NOU::NOU_MEM_MNGT::AllocationCallbackDeleter<int,
        NOU::NOU_MEM_MNGT::DebugAllocationCallback<int>> deleter1(callback);

int *iPtr1 = deleter1.getAllocator().allocate();

deleter1(iPtr1); //delete using deleter

IsTrue(deleter1.getAllocator().getCounter() == 0);

NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(StringView)
{
IsTrue(NOU::NOU_DAT_ALG::StringView8::isCharacter('A'));
IsTrue(NOU::NOU_DAT_ALG::StringView8::isCharacter('Z'));
IsTrue(NOU::NOU_DAT_ALG::StringView8::isCharacter('a'));
IsTrue(NOU::NOU_DAT_ALG::StringView8::isCharacter('z'));

IsTrue(!NOU::NOU_DAT_ALG::StringView8::isCharacter(' '));
IsTrue(!NOU::NOU_DAT_ALG::StringView8::isCharacter('3'));
IsTrue(!NOU::NOU_DAT_ALG::StringView8::isCharacter('%'));
IsTrue(!NOU::NOU_DAT_ALG::StringView8::isCharacter('-'));

IsTrue(NOU::NOU_DAT_ALG::StringView8::isDigit('1'));
IsTrue(NOU::NOU_DAT_ALG::StringView8::isDigit('2'));
IsTrue(NOU::NOU_DAT_ALG::StringView8::isDigit('3'));
IsTrue(NOU::NOU_DAT_ALG::StringView8::isDigit('4'));
IsTrue(NOU::NOU_DAT_ALG::StringView8::isDigit('5'));
IsTrue(NOU::NOU_DAT_ALG::StringView8::isDigit('6'));
IsTrue(NOU::NOU_DAT_ALG::StringView8::isDigit('7'));
IsTrue(NOU::NOU_DAT_ALG::StringView8::isDigit('8'));
IsTrue(NOU::NOU_DAT_ALG::StringView8::isDigit('9'));

IsTrue(!NOU::NOU_DAT_ALG::StringView8::isDigit(' '));
IsTrue(!NOU::NOU_DAT_ALG::StringView8::isDigit('A'));
IsTrue(!NOU::NOU_DAT_ALG::StringView8::isDigit('%'));
IsTrue(!NOU::NOU_DAT_ALG::StringView8::isDigit('-'));

IsTrue(NOU::NOU_DAT_ALG::StringView8::stringToBoolean("true"));

IsTrue(!NOU::NOU_DAT_ALG::StringView8::stringToBoolean("false"));
IsTrue(!NOU::NOU_DAT_ALG::StringView8::stringToBoolean("abcde"));
IsTrue(!NOU::NOU_DAT_ALG::StringView8::stringToBoolean("12345"));
IsTrue(!NOU::NOU_DAT_ALG::StringView8::stringToBoolean("!?$%&"));

NOU::NOU_DAT_ALG::StringView8 sv = "Hello World!";

IsTrue(sv[0] == 'H');
IsTrue(sv[1] == 'e');
IsTrue(sv[2] == 'l');
IsTrue(sv[3] == 'l');
IsTrue(sv[4] == 'o');
IsTrue(sv[5] == ' ');
IsTrue(sv[6] == 'W');
IsTrue(sv[7] == 'o');
IsTrue(sv[8] == 'r');
IsTrue(sv[9] == 'l');
IsTrue(sv[10] == 'd');
IsTrue(sv[11] == '!');

IsTrue(sv.size() == 12);

IsTrue(*sv.indexIterator(0) == 'H');
IsTrue(*sv.indexIterator(1) == 'e');
IsTrue(*sv.indexIterator(2) == 'l');
IsTrue(*sv.indexIterator(3) == 'l');
IsTrue(*sv.indexIterator(4) == 'o');
IsTrue(*sv.indexIterator(5) == ' ');
IsTrue(*sv.indexIterator(6) == 'W');
IsTrue(*sv.indexIterator(7) == 'o');
IsTrue(*sv.indexIterator(8) == 'r');
IsTrue(*sv.indexIterator(9) == 'l');
IsTrue(*sv.indexIterator(10) == 'd');
IsTrue(*sv.indexIterator(11) == '!');

IsTrue(sv == "Hello World!");

IsTrue(sv.find('e') == 1);
IsTrue(sv.find('e', 1) == 1);

IsTrue(sv.find('o') == 4);
IsTrue(sv.find('o', 5) == 7);
IsTrue(sv.find('z') == NOU::NOU_DAT_ALG::StringView8::NULL_INDEX);

IsTrue(sv.find("ello") == 1);
IsTrue(sv.find("o") == 4);
IsTrue(sv.find("o", 5) == 7);
IsTrue(sv.find("test") == NOU::NOU_DAT_ALG::StringView8::NULL_INDEX);

IsTrue(sv.firstIndexOf('H') == 0);
IsTrue(sv.firstIndexOf('o') == 4);
IsTrue(sv.firstIndexOf('z') == NOU::NOU_DAT_ALG::StringView8::NULL_INDEX);

IsTrue(sv.lastIndexOf('H') == 0);
IsTrue(sv.lastIndexOf('o') == 7);
IsTrue(sv.lastIndexOf('z') == NOU::NOU_DAT_ALG::StringView8::NULL_INDEX);

IsTrue(sv.firstIndexOfNot('H') == 1);
IsTrue(sv.firstIndexOfNot('o') == 0);
IsTrue(sv.firstIndexOfNot('z') == 0);

IsTrue(sv.lastIndexOfNot('H') == 11);
IsTrue(sv.lastIndexOfNot('o') == 11);
IsTrue(sv.lastIndexOfNot('z') == 11);

IsTrue(sv.startsWith('H'));
IsTrue(!sv.startsWith('g'));

IsTrue(sv.startsWith("Hell"));
IsTrue(!sv.startsWith("World"));

IsTrue(sv.endsWith("rld!") == true);
IsTrue(!sv.endsWith("World") == true);

IsTrue((sv.compareTo("Abc") > 0));
IsTrue((sv.compareTo("Hello World!") == 0));
IsTrue((sv.compareTo("Xyz") < 0));

NOU::NOU_DAT_ALG::StringView8 subStr = sv.logicalSubstring(6);

IsTrue(subStr.size() == 6);

IsTrue(subStr[0] == 'W');
IsTrue(subStr[1] == 'o');
IsTrue(subStr[2] == 'r');
IsTrue(subStr[3] == 'l');
IsTrue(subStr[4] == 'd');
IsTrue(subStr[5] == '!');

IsTrue(sv == "Hello World!");
IsTrue(sv != "Hello z World!");
IsTrue(sv < "xyz");
IsTrue((sv > "abc"));

NOU::NOU_DAT_ALG::StringView8 sv1 = "Hello World!";
NOU::NOU_DAT_ALG::StringView8 sv2 = "Bye World!";

sv1 = sv2;

IsTrue(sv1 == sv2);


IsTrue(NOU::NOU_DAT_ALG::StringView8::stringToUint32("123") == 123);
IsTrue(NOU::NOU_DAT_ALG::StringView8::stringToUint32("9999999") == 9999999);
IsTrue(NOU::NOU_DAT_ALG::StringView8::stringToUint32("0") == 0);

IsTrue(NOU::NOU_DAT_ALG::StringView8::stringToInt32("123") == 123);
IsTrue(NOU::NOU_DAT_ALG::StringView8::stringToInt32("9999999") == 9999999);
IsTrue(NOU::NOU_DAT_ALG::StringView8::stringToInt32("0") == 0);
IsTrue(NOU::NOU_DAT_ALG::StringView8::stringToInt32("-123") == -123);
IsTrue(NOU::NOU_DAT_ALG::StringView8::stringToInt32("-9999999") == -9999999);
IsTrue(NOU::NOU_DAT_ALG::StringView8::stringToInt32("-0") == -0);

IsTrue(NOU::NOU_DAT_ALG::epsilonCompare(
        NOU::NOU_DAT_ALG::StringView8::stringToFloat32("123"), 123.0f, 0.001f) == 0);
IsTrue(NOU::NOU_DAT_ALG::epsilonCompare(
        NOU::NOU_DAT_ALG::StringView8::stringToFloat32("9999999"), 9999999.0f, 0.001f) == 0);
IsTrue(NOU::NOU_DAT_ALG::epsilonCompare(
        NOU::NOU_DAT_ALG::StringView8::stringToFloat32("0"), 0.0f, 0.001f) == 0);
IsTrue(NOU::NOU_DAT_ALG::epsilonCompare(
        NOU::NOU_DAT_ALG::StringView8::stringToFloat32("123.456"), 123.456f, 0.001f) == 0);
IsTrue(NOU::NOU_DAT_ALG::epsilonCompare(
        NOU::NOU_DAT_ALG::StringView8::stringToFloat32("5.99"), 5.99f, 0.001f) == 0);
IsTrue(NOU::NOU_DAT_ALG::epsilonCompare(
        NOU::NOU_DAT_ALG::StringView8::stringToFloat32("14.5"), 14.5f, 0.001f) == 0);
IsTrue(NOU::NOU_DAT_ALG::epsilonCompare(
        NOU::NOU_DAT_ALG::StringView8::stringToFloat32("-123.456"), -123.456f, 0.001f) == 0);
IsTrue(NOU::NOU_DAT_ALG::epsilonCompare(
        NOU::NOU_DAT_ALG::StringView8::stringToFloat32("-5.99"), -5.99f, 0.001f) == 0);
IsTrue(NOU::NOU_DAT_ALG::epsilonCompare(
        NOU::NOU_DAT_ALG::StringView8::stringToFloat32("-14.5"), -14.5f, 0.001f) == 0);

NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(DebugClass)
{
{
NOU::DebugClass dbgCls0;

IsTrue(NOU::DebugClass::getCounter() == 1);

{
NOU::DebugClass dbgCls1 = dbgCls0;

IsTrue(NOU::DebugClass::getCounter() == 2);
}

IsTrue(NOU::DebugClass::getCounter() == 1);

NOU::DebugClass dbgCls2 = NOU::NOU_CORE::move(dbgCls0);

IsTrue(NOU::DebugClass::getCounter() == 2);
}

IsTrue(NOU::DebugClass::getCounter() == 0);

NOU::DebugClass dbgCls0(1);
NOU::DebugClass dbgCls1(3);

IsTrue(dbgCls0 < dbgCls1);
IsTrue(!(dbgCls0 > dbgCls1));
IsTrue(dbgCls0 <= dbgCls1);
IsTrue(!(dbgCls0 >= dbgCls1));
IsTrue(!(dbgCls0 == dbgCls1));
IsTrue(dbgCls0 != dbgCls1);

NOU::DebugClass dbgCls2(1);

IsTrue(!(dbgCls0 < dbgCls2));
IsTrue(!(dbgCls0 > dbgCls2));
IsTrue(dbgCls0 <= dbgCls2);
IsTrue(dbgCls0 >= dbgCls2);
IsTrue(dbgCls0 == dbgCls2);
IsTrue(!(dbgCls0 != dbgCls2));

IsTrue(dbgCls0.get() == 1);
IsTrue(dbgCls1.get() == 3);
IsTrue(dbgCls2.get() == 1);

NOU::DebugClass dbgCls3 = dbgCls0;
NOU::DebugClass dbgCls4 = NOU::NOU_CORE::move(dbgCls1);

IsTrue(dbgCls3.get() == 1);
IsTrue(dbgCls4.get() == 3);

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

IsTrue(NOU::NOU_CORE::IsDefaultConstructible<int>::value);
IsTrue(NOU::NOU_CORE::IsDefaultConstructible
       <NOU::NOU_MEM_MNGT::GenericAllocationCallback<int>>::value);
IsTrue(!(NOU::NOU_CORE::IsDefaultConstructible<NotDefaultConstructible>::value));

NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(ErrorHandler)
{
NOU::NOU_CORE::ErrorHandler handler;

IsTrue(handler.getErrorCount() == 0);

NOU_PUSH_ERROR(handler, NOU::NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS, "The index was out of "
                                                                        "bounds.");

IsTrue(handler.getErrorCount() == 1);

//validate that the error in the handler is the one that was supposed to be pushed
IsTrue(handler.peekError().getID() == NOU::NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS);
IsTrue(NOU::NOU_DAT_ALG::StringView8(handler.peekError().getFnName()) == NOU_FUNC_NAME);
IsTrue(NOU::NOU_DAT_ALG::StringView8(handler.peekError().getFile()) == __FILE__);
IsTrue(NOU::NOU_DAT_ALG::StringView8(handler.peekError().getMsg()) ==
       "The index was out of bounds.");
IsTrue(NOU::NOU_DAT_ALG::StringView8(handler.peekError().getName()) ==
       "INDEX_OUT_OF_BOUNDS");

auto errorPeek = handler.peekError();
auto errorPop = handler.popError();

//validate that the popped error is the same one as the peeked error.
IsTrue(errorPeek.getID() == errorPop.getID());
IsTrue(NOU::NOU_DAT_ALG::StringView8(errorPeek.getFnName()) == errorPop.getFnName());
IsTrue(errorPeek.getLine() == errorPop.getLine());
IsTrue(NOU::NOU_DAT_ALG::StringView8(errorPeek.getFile()) == errorPop.getFile());
IsTrue(NOU::NOU_DAT_ALG::StringView8(errorPeek.getMsg()) == errorPop.getMsg());
IsTrue(NOU::NOU_DAT_ALG::StringView8(errorPeek.getName()) == errorPop.getName());

IsTrue(handler.getErrorCount() == 0);

NOU_PUSH_ERROR(handler, NOU::NOU_CORE::ErrorCodes::UNKNOWN_ERROR, "Some message");
NOU_PUSH_ERROR(handler, NOU::NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS, "Some other message");

IsTrue(handler.getErrorCount() == 2);

//validate that the order in which the errors are popped is correct
IsTrue(handler.popError().getID() == NOU::NOU_CORE::ErrorCodes::UNKNOWN_ERROR);
IsTrue(handler.popError().getID() == NOU::NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS);

IsTrue(handler.getErrorCount() == 0);

NOU::NOU_CORE::ErrorHandler::ErrorType error = 50000;

//push some invalid error code
NOU_PUSH_ERROR(handler, error, "Some invalid code");

IsTrue(handler.peekError().getID() == NOU::NOU_CORE::ErrorCodes::UNKNOWN_ERROR);
IsTrue(handler.peekError().getActualID() == error);

NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(EpsilonCompare)
{
IsTrue(NOU::NOU_DAT_ALG::epsilonCompare(122.456, 123.457, 0.1) < 0);
IsTrue(NOU::NOU_DAT_ALG::epsilonCompare(123.456, 123.457, 0.1) == 0);
IsTrue(NOU::NOU_DAT_ALG::epsilonCompare(124.456, 123.457, 0.1) > 0);

NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(InvokeResult)
{
IsTrue(NOU::NOU_CORE::AreSame<void, NOU::NOU_CORE::InvokeResult_t<
                                    decltype(dummyFunc0), int>>::value);
IsTrue(NOU::NOU_CORE::AreSame<int, NOU::NOU_CORE::InvokeResult_t<
                                   decltype(dummyFunc1), int>>::value);

NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(Uninitialized)
{
{
NOU::NOU_DAT_ALG::Uninitialized<NOU::DebugClass> ui;

IsTrue(!ui.isValid());

IsTrue(NOU::DebugClass::getCounter() == 0);

ui = NOU::DebugClass(5);

IsTrue(ui.isValid());

IsTrue(ui->get() == 5);

IsTrue(NOU::DebugClass::getCounter() == 1);

ui = NOU::DebugClass(10);

IsTrue(ui.isValid());

IsTrue(ui->get() == 10);

IsTrue(NOU::DebugClass::getCounter() == 1);
}
IsTrue(NOU::DebugClass::getCounter() == 0);
}

TEST_METHOD(Quicksort)

{

int arr[5] = {2,1,3,5,4};
NOU::NOU_DAT_ALG::qsort(arr, 0, 4);
IsTrue(arr[0] == 1);
IsTrue(arr[1] == 2);
IsTrue(arr[2] == 3);
IsTrue(arr[3] == 4);
IsTrue(arr[4] == 5);




}

TEST_METHOD(Random)
{
NOU::NOU_DAT_ALG::Random random;

for (NOU::uint32 i = 0; i < 100; i++)
{
typename NOU::NOU_DAT_ALG::Random::Value rand = random.rand(0, 10);

bool condition = rand >= 0 && rand <= 10;
IsTrue(condition);
}
}

TEST_METHOD(PoolAllocator)
{
NOU::NOU_MEM_MNGT::PoolAllocator<NOU::DebugClass> pa;

NOU::NOU_DAT_ALG::Vector<NOU::DebugClass*> dbgCls;

NOU::sizeType testValue = 1234;

const NOU::sizeType ALLOC_SIZE = 4321;

IsTrue(NOU::DebugClass::getCounter() == 0);

for (NOU::sizeType i = 0; i < ALLOC_SIZE; i++)
{
dbgCls.push(pa.allocate(testValue));
}

for (NOU::DebugClass* value : dbgCls)
{
IsTrue(value->get() == testValue);
}

IsTrue(NOU::DebugClass::getCounter() == ALLOC_SIZE);

for (NOU::sizeType i = 0; i < ALLOC_SIZE; i++)
{
pa.deallocate(dbgCls.pop());
}

IsTrue(NOU::DebugClass::getCounter() == 0);

IsTrue(NOU::NOU_CORE::getErrorHandler().getErrorCount() == 0);

{
NOU::NOU_DAT_ALG::Uninitialized<NOU::DebugClass> uninit;

IsTrue(!uninit.isValid());

uninit = NOU::DebugClass(1);

IsTrue(uninit.isValid());

uninit.destroy();

IsTrue(!uninit.isValid());

IsTrue(NOU::DebugClass::getCounter() == 0);
}

NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(GeneralPurposeAllocator)
{
using HandleType = NOU::NOU_MEM_MNGT::GeneralPurposeAllocator::
GeneralPurposeAllocatorPointer<NOU::DebugClass>;

NOU::NOU_MEM_MNGT::GeneralPurposeAllocator gpa;
NOU::NOU_DAT_ALG::Vector<HandleType> dbgVec;
NOU::sizeType testValue = 12345;
const NOU::sizeType ALLOC_SIZE = 40;

IsTrue(NOU::DebugClass::getCounter() == 0);

IsTrue(NOU::NOU_CORE::getErrorHandler().getErrorCount() == 0);

dbgVec.push(gpa.allocateObjects<NOU::DebugClass>(1, testValue));
gpa.deallocateObjects(dbgVec.at(0));
dbgVec.pop();
gpa.deallocateObjects(dbgVec.at(0));

IsTrue(NOU::NOU_CORE::getErrorHandler().getErrorCount() == 1);
NOU::NOU_CORE::getErrorHandler().popError();

for (NOU::sizeType i = 0; i < ALLOC_SIZE; i++)
{
dbgVec.push(gpa.allocateObject<NOU::DebugClass>(testValue));
}

for (HandleType &value : dbgVec)
{
IsTrue(value->get() == testValue);
}

for (int i = 0; i < dbgVec.size(); i++)
{
gpa.deallocateObjects(dbgVec.at(i));
}

IsTrue(NOU::DebugClass::getCounter() == 0);

NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(String)
{
NOU::NOU_DAT_ALG::String<NOU::char8> str;

str.append('a');
IsTrue(str[0] == 'a');

str.append("Hallo");
IsTrue(str[1] == 'H');

str.insert(0, 'A');
IsTrue(str[0] == 'A');

str.appendIf(1, 'T');
IsTrue(str[str.size() - 1] == 'T');

str.append(1);
IsTrue(str[str.size() - 1] == '1');

str.append(-1);
IsTrue(str[str.size() - 2] == '-');
IsTrue(str[str.size() - 1] == '1');

NOU::sizeType i = 0; // becasue of NULLTERMINATOR
str.clear();
IsTrue(str.size() == i);

str.append("Hallo Welt");
str.replace('l', 'V', 0, str.size() - 1);
IsTrue(str[2] == 'V');
IsTrue(str[3] == 'V');
IsTrue(str[8] == 'V');

str.clear();
str.append(17.025);
IsTrue(str[0] == '1');
IsTrue(str[1] == '7');
IsTrue(str[2] == '.');
IsTrue(str[3] == '0');
IsTrue(str[4] == '2');
IsTrue(str[5] == '5');

str.remove(2, str.size());
IsTrue(str[0] == '1');
IsTrue(str[1] == '7');

NOU::NOU_DAT_ALG::String<NOU::char8> substr;

substr.append(str.substring(0, 1));
IsTrue(str[0] == '1');

substr.clear();
substr.append(str.copy());
IsTrue(str[0] == '1');
IsTrue(str[1] == '7');
substr.clear();
str.clear();
substr.append("AAAAA");
str.append("Hallo");

NOU::NOU_DAT_ALG::String<NOU::char8> str1;
NOU::NOU_DAT_ALG::String<NOU::char8> str2 = "Hallo";

str1 = str2;
IsTrue(str1 == "Hallo");

str1 = "User";
IsTrue(str1 == "User");

NOU::NOU_DAT_ALG::String<NOU::char8> str3 = str1.substring(0, 2);
IsTrue(str3 == "Us");

str1 = str3.fillRange('a', 0, 2);
IsTrue(str1 == "aa");

str1 = "NostraUtils";

str3 = str1.preserve(6, 11);
IsTrue(str3 == "Utils");

str1 = "";

str2 = str1.concat("Hallo");
IsTrue(str2 == "Hallo");
str1 = str2.concat(1);
IsTrue(str1 == "Hallo1");
str2 = str1.concat('a');
IsTrue(str2 == "Hallo1a");
str1 = str2.concat(1.3);
IsTrue(str1 == "Hallo1a1.3");

str1 = "User";
str2 = "Hallo";

str1.copySubstringTo(str2, 0,4,5);
IsTrue(str2 == "HalloUser");

str1 = "User";
str1.copySubstringHere("Hallo",0,5,0);
IsTrue(str1 == "HalloUser");

str1.replace(0, 9, "wasgeht");
IsTrue(str1 == "wasgeht");

str1 = "ThisIsAString";
str1.replace("String", "Integer");

//IsTrue(str1 == "ThisIsAInteger");

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

IsTrue(b.at(0) == 1);
IsTrue(b.at(1) == 2);
IsTrue(b.at(2) == 3);
IsTrue(b.at(3) == 4);
IsTrue(b.at(4) == 1);
IsTrue(b.at(5) == 4);

b.dequeue();

IsTrue(b.at(0) == 2);
IsTrue(b.at(1) == 3);
IsTrue(b.at(2) == 4);
IsTrue(b.at(3) == 1);
IsTrue(b.at(4) == 4);

b.decreaseKey(2, 2);

IsTrue(b.at(0) == 2);
IsTrue(b.at(1) == 3);
IsTrue(b.at(2) == 4);
IsTrue(b.at(3) == 1);
IsTrue(b.at(4) == 4);

NOU::NOU_DAT_ALG::BinaryHeap<NOU::int32> c(5);

c.enqueue(1, 11);
c.enqueue(2, 5);
c.enqueue(3, 17);
c.enqueue(3, 176);
c.enqueue(5, 188);

IsTrue(c.checkIfPresent(3) == true);

c.deleteById(4);

IsTrue(c.at(0) == 11);
IsTrue(c.at(1) == 5);
IsTrue(c.at(2) == 17);
IsTrue(c.at(3) == 188);

NOU_CHECK_ERROR_HANDLER;
}


TEST_METHOD(Hashfunction)
{
NOU::int64 i1 = 243536768574;
NOU::int64 i2 = 243536768574;

NOU::sizeType h = NOU::NOU_DAT_ALG::hashObj(&i1, 20);
//AreEqual(h, NOU::NOU_DAT_ALG::hashObj(&i2, 20));
IsTrue(h == NOU::NOU_DAT_ALG::hashObj(&i2, 20));

NOU::NOU_DAT_ALG::String<NOU::char8> str1 = "The quick onyx goblin jumps over the lazy dwarf";
NOU::NOU_DAT_ALG::String<NOU::char8> str2 = "The quick onyx goblin jumps over the lazy dwarf";

h = NOU::NOU_DAT_ALG::hashObj(&str1, 20);
//AreEqual(h, NOU::NOU_DAT_ALG::hashObj(&str2, 20));
IsTrue(h == NOU::NOU_DAT_ALG::hashObj(&str2, 20));


}

TEST_METHOD(HashMap)
{
NOU::NOU_DAT_ALG::HashMap<NOU::char8, NOU::int32> hm(100);
NOU::NOU_DAT_ALG::HashMap<NOU::char8, NOU::int32> hm1(100);
NOU::NOU_DAT_ALG::String<NOU::char8> str = "The quick onyx goblin jumps over the lazy dwarf";
NOU::boolean b;

//AreEqual(hm.isEmpty(), true);
IsTrue(hm.isEmpty() == true);

for (NOU::sizeType i = 0; i < str.size(); i++) {
b = hm.map(str.at(i), 1, sizeof(str.at(i)));
}

//AreEqual(hm.isEmpty(), false);

IsTrue(hm.isEmpty() == false);

for (NOU::sizeType i = 0; i < str.size(); i++) {
//AreEqual(hm.get(str.at(i)), 1);
IsTrue(hm.get(str.at(i), sizeof(str.at(i))) == 1);
}
NOU::char8 k = 'h';

//NOU::int32 count = hm.remove(k, &out);

NOU::boolean r = hm.remove(k);
IsTrue(r);

//AreEqual(1, count);


for (NOU::sizeType i = 0; i < str.size(); i++)
{
k = str.at(i);
if (!hm1.containsKey(str.at(i)))
{
hm1.map(k, 1, sizeof(k));
}
else
{
hm1.map(k, hm1.get(k, sizeof(k)) + 1, sizeof(k));
}
}

//AreEqual(hm1.get('h'), 2);
//AreEqual(hm1.get(' '), 8);

IsTrue(hm1.get('h', sizeof('h')) == 2);
IsTrue(hm1.get(' ', sizeof(' ')) == 8);

NOU::NOU_DAT_ALG::HashMap<NOU::int32, NOU::int32> cm(100);

cm.map(5, 1, sizeof(5));
cm.map(41, 2, sizeof(41));
cm.map(10, 3, sizeof(10));
cm.map(49875, 4, sizeof(49875));

NOU::NOU_DAT_ALG::Vector<NOU::int32> c;

c = cm.entrySet();

//AreEqual(c[0], 1);
//AreEqual(c[1], 4);
//AreEqual(c[2], 3);
//AreEqual(c[3], 2);

IsTrue(c[0] == 1);
IsTrue(c[1] == 4);
IsTrue(c[2] == 3);
IsTrue(c[3] == 2);

NOU::NOU_DAT_ALG::Vector<NOU::int32> a;

a = cm.keySet();

//AreEqual(a[0], 5);
//AreEqual(a[1], 49875);
//AreEqual(a[2], 10);
//AreEqual(a[3], 41);

IsTrue(a[0] == 5);
IsTrue(a[1] == 49875);
IsTrue(a[2] == 10);
IsTrue(a[3] == 41);

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


IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec.data(), search_vals[0], 0, vec.size() - 1) == 0);
IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec.data(), search_vals[1], 0, vec.size() - 1) == 1);
IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec.data(), search_vals[2], 0, vec.size() - 1) == -1);
IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec.data(), search_vals[3], 0, vec.size() - 1) == 4);
IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec.data(), search_vals[4], 0, vec.size() - 1) == 6);
IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec.data(), search_vals[5], 0, vec.size() - 1) == 5);
IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec.data(), search_vals[6], 0, vec.size() - 1) == -1);

IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec, search_vals[0], 0, -1) == 0);
IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec, search_vals[1], 0, -1) == 1);
IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec, search_vals[2], 0, -1) == -1);
IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec, search_vals[3], 0, -1) == 4);
IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec, search_vals[4], 0, -1) == 6);
IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec, search_vals[5], 0, -1) == 5);
IsTrue(NOU::NOU_DAT_ALG::binarySearch(vec, search_vals[6], 0, -1) == -1);

NOU::sizeType insertionIndex;

NOU::NOU_DAT_ALG::binarySearch(vec.data(), search_vals[2], 0, vec.size() - 1, &insertionIndex);
IsTrue(insertionIndex == 4);
NOU::NOU_DAT_ALG::binarySearch(vec.data(), search_vals[6], 0, vec.size() - 1, &insertionIndex);
IsTrue(insertionIndex == 7);
NOU::NOU_DAT_ALG::binarySearch(vec.data(), search_vals[7], 0, vec.size() - 1, &insertionIndex);
IsTrue(insertionIndex == 0);

NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(VectorIterator)
{
NOU::NOU_DAT_ALG::Vector<NOU::DebugClass> vec;

vec.push(NOU::DebugClass(0));
vec.push(NOU::DebugClass(1));
vec.push(NOU::DebugClass(2));
vec.push(NOU::DebugClass(3));
vec.push(NOU::DebugClass(4));
vec.push(NOU::DebugClass(5));


//Iterator
IsTrue(vec.begin() == vec.begin());
IsTrue(vec.begin() + 3 == vec.begin() + 3);
IsTrue(vec.end() == vec.end());

IsTrue(vec.begin() != vec.end());
IsTrue(vec.begin() + 3 != vec.begin() + 4);



IsTrue(vec.begin()->get() == 0);
IsTrue((++vec.begin())->get() == 1);
IsTrue((vec.begin() + 1)->get() == 1);
IsTrue((vec.begin() + 2)->get() == 2);
IsTrue((vec.begin() + 3)->get() == 3);
IsTrue((vec.begin() + 4)->get() == 4);
IsTrue((vec.begin() + 5)->get() == 5);

IsTrue((vec.end() - 1)->get() == 5);
IsTrue((vec.end() - 2)->get() == 4);
IsTrue((vec.end() - 3)->get() == 3);
IsTrue((vec.end() - 4)->get() == 2);
IsTrue((vec.end() - 5)->get() == 1);
IsTrue((vec.end() - 6)->get() == 0);

auto it = vec.begin();

IsTrue(it->get() == 0);

it += 1;
IsTrue(it->get() == 1);

it += 1;
IsTrue(it->get() == 2);

it += 1;
IsTrue(it->get() == 3);

it += 1;
IsTrue(it->get() == 4);

it += 1;
IsTrue(it->get() == 5);

it -= 1;
IsTrue(it->get() == 4);

it -= 1;
IsTrue(it->get() == 3);

it -= 1;
IsTrue(it->get() == 2);

it -= 1;
IsTrue(it->get() == 1);

it -= 1;
IsTrue(it->get() == 0);




//Reverse Iterator
IsTrue(vec.rbegin() == vec.rbegin());
IsTrue(vec.rbegin() + 3 == vec.rbegin() + 3);
IsTrue(vec.end() == vec.end());

IsTrue(vec.rbegin() != vec.rend());
IsTrue(vec.rbegin() + 3 != vec.rbegin() + 4);



IsTrue(vec.rbegin()->get() == 5);
IsTrue((++vec.rbegin())->get() == 4);
IsTrue((vec.rbegin() + 1)->get() == 4);
IsTrue((vec.rbegin() + 2)->get() == 3);
IsTrue((vec.rbegin() + 3)->get() == 2);
IsTrue((vec.rbegin() + 4)->get() == 1);
IsTrue((vec.rbegin() + 5)->get() == 0);

IsTrue((vec.rend() - 1)->get() == 0);
IsTrue((vec.rend() - 2)->get() == 1);
IsTrue((vec.rend() - 3)->get() == 2);
IsTrue((vec.rend() - 4)->get() == 3);
IsTrue((vec.rend() - 5)->get() == 4);
IsTrue((vec.rend() - 6)->get() == 5);

auto rit = vec.rbegin();

IsTrue(rit->get() == 5);

rit += 1;
IsTrue(rit->get() == 4);

rit += 1;
IsTrue(rit->get() == 3);

rit += 1;
IsTrue(rit->get() == 2);

rit += 1;
IsTrue(rit->get() == 1);

rit += 1;
IsTrue(rit->get() == 0);

rit -= 1;
IsTrue(rit->get() == 1);

rit -= 1;
IsTrue(rit->get() == 2);

rit -= 1;
IsTrue(rit->get() == 3);

rit -= 1;
IsTrue(rit->get() == 4);

rit -= 1;
IsTrue(rit->get() == 5);

NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(ObjectPool)
{
NOU::NOU_DAT_ALG::ObjectPool<NOU::DebugClass> objPool(5);

IsTrue(objPool.capacity() == 5);
IsTrue(objPool.size() == 0);
IsTrue(objPool.remainingObjects() == 0);

objPool.pushObject(NOU::DebugClass(0));

IsTrue(objPool.capacity() == 5);
IsTrue(objPool.size() == 1);
IsTrue(objPool.remainingObjects() == 1);

objPool.pushObject(NOU::DebugClass(1));
objPool.pushObject(NOU::DebugClass(2));

IsTrue(objPool.capacity() == 5);
IsTrue(objPool.size() == 3);
IsTrue(objPool.remainingObjects() == 3);

NOU::DebugClass &obj0 = objPool.get();

IsTrue(objPool.capacity() == 5);
IsTrue(objPool.size() == 3);
IsTrue(objPool.remainingObjects() == 2);

NOU::DebugClass &obj1 = objPool.get();

IsTrue(objPool.capacity() == 5);
IsTrue(objPool.size() == 3);
IsTrue(objPool.remainingObjects() == 1);

objPool.giveBack(obj0);

IsTrue(objPool.capacity() == 5);
IsTrue(objPool.size() == 3);
IsTrue(objPool.remainingObjects() == 2);
NOU::int64 i1 = 243536768574;
NOU::int64 i2 = 243536768574;

NOU::sizeType h = NOU::NOU_DAT_ALG::hashObj(&i1, 20);
IsTrue(h == NOU::NOU_DAT_ALG::hashObj(&i2, 20));

NOU::NOU_DAT_ALG::String<NOU::char8> str1 = "The quick onyx goblin jumps over the lazy dwarf";
NOU::NOU_DAT_ALG::String<NOU::char8> str2 = "The quick onyx goblin jumps over the lazy dwarf";

h = NOU::NOU_DAT_ALG::hashObj(&str1, 20);
IsTrue(h == NOU::NOU_DAT_ALG::hashObj(&str2, 20));


}

static void taskTestFunction1(NOU::int32 i, NOU::int32 *out)
{
    *out = i;
}

static NOU::int32 taskTestFunction2(NOU::int32 i)
{
    return i;
}

class DummyClass
{
    //empty class
};

static NOU::int32 taskTestFunction3(const DummyClass dc)
{
    return 1;
}

static void taskTestFunction4(const DummyClass dc)
{

}

TEST_METHOD(Task)
{
NOU::int32 i1 = 5;
NOU::int32 out;

auto task1 = NOU::NOU_THREAD::makeTask(&taskTestFunction1, i1, &out);

task1.execute();

IsTrue(out == i1);



//just to make sure that INVALID_OBJECT is the first error in the handler later
IsTrue(NOU::NOU_CORE::getErrorHandler().getErrorCount() == 0);

NOU::int32 i2 = 5;

auto task2 = NOU::NOU_THREAD::makeTask(&taskTestFunction2, i2);

task2.getResult();

IsTrue(NOU::NOU_CORE::getErrorHandler().getErrorCount() == 1);
IsTrue(NOU::NOU_CORE::getErrorHandler().popError().getID() ==
       NOU::NOU_CORE::ErrorCodes::INVALID_OBJECT);

task2.execute();

IsTrue(task2.getResult() == i2);


//check if this compiles
const DummyClass dc;

auto task3 = NOU::NOU_THREAD::makeTask(&taskTestFunction3, dc);

auto task4 = NOU::NOU_THREAD::makeTask(&taskTestFunction4, dc);

NOU_CHECK_ERROR_HANDLER;
}

//no more tests are possible, since the remaining methods of thread manager are either not reliable
//(like currentlyAvailableThreads(), which may change any moment) or there are no observable values
//produced (like pushTask())
TEST_METHOD(ThreadManager)
{
NOU::NOU_THREAD::ThreadManager &manager = NOU::NOU_THREAD::getThreadManager();

IsTrue(manager.maximumAvailableThreads() >= NOU::NOU_THREAD::ThreadManager::DEFAULT_THREAD_COUNT);

IsTrue(manager.maximumAvailableThreads() >= NOU::NOU_THREAD::ThreadManager::DEFAULT_THREAD_COUNT);

if (NOU::NOU_THREAD::ThreadWrapper::maxThreads() > NOU::NOU_THREAD::ThreadManager::DEFAULT_THREAD_COUNT)
{
IsTrue(manager.maximumAvailableThreads() == NOU::NOU_THREAD::ThreadWrapper::maxThreads() - 1);
}

NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(OffsetOf)
{
struct TestStruct
{
    NOU::int32 x;
    NOU::int32 y;
    NOU::int32 z;
};

IsTrue(NOU_OFFSET_OF(TestStruct, x) == offsetof(TestStruct, x));
IsTrue(NOU_OFFSET_OF(TestStruct, y) == offsetof(TestStruct, y));
IsTrue(NOU_OFFSET_OF(TestStruct, z) == offsetof(TestStruct, z));

NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(Path)
{
#if NOU_OS == NOU_OS_WINDOWS

NOU::NOU_FILE_MNGT::Path p = "\\testfile.exe";
	NOU::NOU_FILE_MNGT::Path p1 = "testdir\\testfile.test";
	NOU::NOU_FILE_MNGT::Path p2 = "\\test.dir\\testfile.test";
	NOU::NOU_FILE_MNGT::Path p3 = "test.dir\\testfile";
	NOU::NOU_FILE_MNGT::Path p4 = "testfile.test\\";
	NOU::NOU_FILE_MNGT::Path p5 = "testfile";
	NOU::NOU_FILE_MNGT::Path p6 = "test.tar.gz";

	NOU::NOU_FILE_MNGT::Path p10 = "C:\\Users\\TestUser\\TestDir\\MyFile.exe";
	NOU::NOU_FILE_MNGT::Path p11 = "C:\\Users\\TestUser\\TestDir\\MyFolder\\MyFile.txt";
	NOU::NOU_FILE_MNGT::Path p12 = "C:\\Users\\TestUser\\TestDir";
	NOU::NOU_FILE_MNGT::Path p13 = "D:\\Users\\";
	NOU::NOU_FILE_MNGT::Path p14 = "D:\\Users\\SomeOtherDir";

	NOU::NOU_FILE_MNGT::Path cwd = NOU::NOU_FILE_MNGT::Path::currentWorkingDirectory();

	NOU::NOU_DAT_ALG::String8 str = cwd.getAbsolutePath();
	str.append("\\Test\\TestUser\\TestDir2");

	// p15 == cwd\\Test\\Dennis\\WasGehtAb
	NOU::NOU_FILE_MNGT::Path p15 = str;

	IsTrue(p.getName() == "testfile");
	IsTrue(p1.getName() == "testfile");
	IsTrue(p2.getName() == "testfile");
	IsTrue(p3.getName() == "testfile");
	IsTrue(p4.getName() == "");
	IsTrue(p5.getName() == "testfile");
	IsTrue(p6.getName() == "test.tar");

	IsTrue(p.getFileExtension() == "exe");
	IsTrue(p1.getFileExtension() == "test");
	IsTrue(p2.getFileExtension() == "test");
	IsTrue(p3.getFileExtension() == "");
	IsTrue(p4.getFileExtension() == "");
	IsTrue(p5.getFileExtension() == "");
	IsTrue(p6.getFileExtension() == "gz");

	IsTrue(p.getNameAndExtension() == "testfile.exe");
	IsTrue(p1.getNameAndExtension() == "testfile.test");
	IsTrue(p2.getNameAndExtension() == "testfile.test");
	IsTrue(p3.getNameAndExtension() == "testfile");
	IsTrue(p4.getNameAndExtension() == "");
	IsTrue(p5.getNameAndExtension() == "testfile");
	IsTrue(p6.getNameAndExtension() == "test.tar.gz");

	IsTrue(p10.getParentPath() == "C:\\Users\\TestUser\\TestDir");
	IsTrue(p11.getParentPath() == "C:\\Users\\TestUser\\TestDir\\MyFolder");
	IsTrue(p12.getParentPath() == "C:\\Users\\TestUser");
	IsTrue(p13.getParentPath() == "D:");
	IsTrue(p14.getParentPath() == "D:\\Users");

	IsTrue(p15.getRelativePath() == "Test\\TestUser\\TestDir2");
	if (str.startsWith('C'))
	{
		NOU::NOU_FILE_MNGT::Path p16 = "D:\\Users\\TestUser\\TestDir";
		IsTrue(p16.getRelativePath() == "D:\\Users\\TestUser\\TestDir");
	}
	else {
		NOU::NOU_FILE_MNGT::Path p16 = "C:\\Users\\TestUser\\TestDir";
		IsTrue(p16.getRelativePath() == "C:\\Users\\TestUser\\TestDir");
	}

	p15 = "Hallo";
	IsTrue("\\Test\\TestUser\\TestDir2\\Hallo");

#elif NOU_OS == NOU_OS_LINUX || NOU_OS == NOU_OS_UNIX || NOU_OS == NOU_OS_MAC

NOU::NOU_FILE_MNGT::Path p = "\\testfile.exe";
	NOU::NOU_FILE_MNGT::Path p1 = "testdir\\testfile.test";
	NOU::NOU_FILE_MNGT::Path p2 = "\\test.dir\\testfile.test";
	NOU::NOU_FILE_MNGT::Path p3 = "test.dir\\testfile";
	NOU::NOU_FILE_MNGT::Path p4 = "testfile.test\\";
	NOU::NOU_FILE_MNGT::Path p5 = "testfile";
	NOU::NOU_FILE_MNGT::Path p6 = "test.tar.gz";

	NOU::NOU_FILE_MNGT::Path p10 = "/Users/TestUser/TestDir/MyFile.exe";
	NOU::NOU_FILE_MNGT::Path p11 = "/Users/TestUser/TestDir/MyFolder/MyFile.txt";
	NOU::NOU_FILE_MNGT::Path p12 = "/Users/TestUser/TestDir";
	NOU::NOU_FILE_MNGT::Path p13 = "/Users/";
	NOU::NOU_FILE_MNGT::Path p14 = "/Users/SomeOtherDir";

	NOU::NOU_FILE_MNGT::Path cwd = NOU::NOU_FILE_MNGT::Path::currentWorkingDirectory();

	NOU::NOU_DAT_ALG::String8 str = cwd.getAbsolutePath();
	str.append("/Test/TestUser/TestDir2");

	NOU::NOU_FILE_MNGT::Path p15 = str;

	IsTrue(p.getName() == "testfile");
	IsTrue(p1.getName() == "testfile");
	IsTrue(p2.getName() == "testfile");
	IsTrue(p3.getName() == "testfile");
	IsTrue(p4.getName() == "");
	IsTrue(p5.getName() == "testfile");
	IsTrue(p6.getName() == "test.tar");

	IsTrue(p.getFileExtension() == "exe");
	IsTrue(p1.getFileExtension() == "test");
	IsTrue(p2.getFileExtension() == "test");
	IsTrue(p3.getFileExtension() == "");
	IsTrue(p4.getFileExtension() == "");
	IsTrue(p5.getFileExtension() == "");
	IsTrue(p6.getFileExtension() == "gz");

	IsTrue(p.getNameAndExtension() == "testfile.exe");
	IsTrue(p1.getNameAndExtension() == "testfile.test");
	IsTrue(p2.getNameAndExtension() == "testfile.test");
	IsTrue(p3.getNameAndExtension() == "testfile");
	IsTrue(p4.getNameAndExtension() == "");
	IsTrue(p5.getNameAndExtension() == "testfile");
	IsTrue(p6.getNameAndExtension() == "test.tar.gz");

	IsTrue(p10.getParentPath() == "/Users/TestUser/TestDir");
	IsTrue(p11.getParentPath() == "/Users/TestUser/TestDir/MyFolder");
	IsTrue(p12.getParentPath() == "/Users/TestUser");
	IsTrue(p13.getParentPath() == "");
	IsTrue(p14.getParentPath() == "/Users");

	IsTrue(p15.getRelativePath() == "Test/TestUser/TestDir2");

#endif

}

TEST_METHOD(IsBaseOf)
{
	class Base
	{
	
	};
	
	class Derived : public Base
	{
	
	};
	
	IsTrue(NOU::NOU_CORE::IsBaseOf<Base, Derived>::value);
	IsTrue(!NOU::NOU_CORE::IsBaseOf<Derived, Base>::value);
}

TEST_METHOD(Logging)
{
	static NOU::NOU_CORE::Event testEvent(NOU::NOU_CORE::EventLevelCodes::DEBUG, "Unittest error.");

	static NOU::NOU_DAT_ALG::String8 testOutput = NOU::NOU_CORE::Logger::print(testEvent);
	static NOU::NOU_DAT_ALG::String8 writeOutput;

	NOU::NOU_CORE::Logger* log = NOU::NOU_CORE::Logger::instance();

	static NOU::NOU_THREAD::Mutex mutex;
	static NOU::NOU_THREAD::ConditionVariable variable;

	class TestLogger : public NOU::NOU_CORE::ILogger
	{
		void write(const NOU::NOU_CORE::Event& event, StringType filename)
		{
			writeOutput = NOU::NOU_CORE::Logger::print(event);
			variable.notifyAll();
		}
	};

	log->pushLogger<TestLogger>();
	log->write(NOU::NOU_CORE::EventLevelCodes::DEBUG, "Unittest error.");

	//Wait until the logger has actually printed the message
	NOU::NOU_THREAD::UniqueLock lock(mutex);
	variable.wait(lock);

	if (testOutput.size() == writeOutput.size()) //For better error message
	{
		for (int i = 0; i < testOutput.size(); i++)
		{
			IsTrue(testOutput.at(i) == writeOutput.at(i));
		}
	}
	else
	{
		IsTrue(false);
	}

	NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(File)
{
	NOU::NOU_FILE_MNGT::File f("UnitTestFile");
	NOU::NOU_DAT_ALG::StringView8 testString = "Nostra";
	NOU::char8 *buff;
	NOU::char8 firstIn[6];
	NOU::boolean errBit;



	// Creating file and testing if it exists
	IsTrue(!f.exists());
	f.createFile();
	IsTrue(f.exists());
	NOU::sizeType s;

	// Read/Write
	f.open();
	buff = firstIn;
	errBit = f.write(testString);
	IsTrue(errBit);
	f.close();
	s = f.size();
	f.open(NOU::NOU_FILE_MNGT::AccessMode::READ);
	f.read(s, buff);

	for(NOU::sizeType i = 0; i < s; i++)
	{
		IsTrue(buff[i] == testString[i]);
	}



	// Deleting File
	f.close();
	IsTrue(f.deleteFile());
	IsTrue(!f.exists());
}

TEST_METHOD(INIFile)
{
	NOU::NOU_FILE_MNGT::INIFile parser = NOU::NOU_FILE_MNGT::INIFile("unittest.ini");

	parser.setString("TEST_STR", "Testing");
	IsTrue(parser.getString("TEST_STR") == "Testing");

	parser.setInt("TEST_INT", 42);
	IsTrue(parser.getInt("TEST_INT") == 42);

	parser.setFloat("TEST_FLOAT", 13.37);
	IsTrue(parser.getFloat("TEST_FLOAT") > 13.369);
	IsTrue(parser.getFloat("TEST_FLOAT") < 13.381);

	parser.remove("TEST_STR");
	IsTrue(parser.getString("TEST_STR").size() == 0);

	parser.remove("TEST_INT");
	IsTrue(parser.getInt("TEST_INT") == 0);

	parser.remove("TEST_FLOAT");
	IsTrue(parser.getFloat("TEST_FLOAT") < 0.1);

	parser.setString("TEST_STR", "Testing", "section");
	IsTrue(parser.getString("TEST_STR", "section") == "Testing");

	parser.setInt("TEST_INT", 42, "section");
	IsTrue(parser.getInt("TEST_INT", "section") == 42);

	parser.setFloat("TEST_FLOAT", 13.37, "section");
	IsTrue(parser.getFloat("TEST_FLOAT", "section") > 13.369);
	IsTrue(parser.getFloat("TEST_FLOAT", "section") < 13.381);

	NOU_CHECK_ERROR_HANDLER;
}

void callback(const char *msg, const char *fnName, NOU::sizeType line, const char *file)
{
	IsTrue(false);
}

int main(int argc, char** argv)
{
	NOU::NOU_CORE::getAssertionSettings().printOnFail = true;
	NOU::NOU_CORE::getAssertionSettings().pushErrorOnFail = false;
	NOU::NOU_CORE::getAssertionSettings().callbackOnFail = callback;

    int result = Catch::Session().run(argc, argv);

    std::cout << "Test run has finished. Press ENTER to return." << std::endl;
    std::cin.get();

    return result;
}