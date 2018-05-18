#define CATCH_CONFIG_RUNNER
#include "Catch/catch.hpp"

#define NOU_DEBUG
#define NOU_DLL

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
IsTrue(str1 == "ThisIsAInteger");

str1 = "ThisIsAString";
str1.replace("String", "Intege");
IsTrue(str1 == "ThisIsAIntege");

str1 = "ThisIsAString";
str1.replace("AString", "Intege");
IsTrue(str1 == "ThisIsIntege");


str1 = "ThisIsAString";
str1.replace(0, 7, "Integer");
IsTrue(str1 == "IntegerString");

str1 = "ThisIsAString";
str1.replace(0,13, "Integer");
IsTrue(str1 == "Integer");

str1 = "ThisIsAString";
str1.replace(0, 5, "Integer");
IsTrue(str1 == "IntegersAString");

NOU::NOU_DAT_ALG::String8 newstr(50, 'b');
IsTrue(newstr.getCapacity() == 50);

newstr.appendBuffer(10);
IsTrue(newstr.getCapacity() == 60);

newstr.removeRemainingBufferFromString();
IsTrue(newstr.getCapacity() == 1);

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
b = hm.map(str.at(i), 1);
}

//AreEqual(hm.isEmpty(), false);

IsTrue(hm.isEmpty() == false);

for (NOU::sizeType i = 0; i < str.size(); i++) {
//AreEqual(hm.get(str.at(i)), 1);
IsTrue(hm.get(str.at(i)) == 1);
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
hm1.map(k, 1);
}
else
{
hm1.map(k, hm1.get(k) + 1);
}
}

//AreEqual(hm1.get('h'), 2);
//AreEqual(hm1.get(' '), 8);

IsTrue(hm1.get('h') == 2);
IsTrue(hm1.get(' ') == 8);

NOU::NOU_DAT_ALG::HashMap<NOU::int32, NOU::int32> cm(100);

cm.map(5, 1);
cm.map(41, 2);
cm.map(10, 3);
cm.map(49875, 4);

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
	NOU::NOU_DAT_ALG::String8 filename = "unittest_testfile.txt";
	NOU::NOU_DAT_ALG::String8 output = "1. 2. 3. This is a string for testing the unittests.";
	NOU::NOU_DAT_ALG::String8 buffer;

	NOU::NOU_FILE_MNGT::Path path = NOU::NOU_FILE_MNGT::Path::currentWorkingDirectory();

	path += filename;

	NOU::NOU_FILE_MNGT::File file(path);

	file.createFile();
	IsTrue(file.exists() == true);

	file.open(NOU::NOU_FILE_MNGT::AccessMode::WRITE);
	IsTrue(file.isCurrentlyOpen() == true);

	file.write(output);

	file.close();
	IsTrue(file.isCurrentlyOpen() == false);

	file.fetchSize();
	file.open(NOU::NOU_FILE_MNGT::AccessMode::READ);
	file.read(buffer); //Reads the hole file into the buffer.

	file.close();
	IsTrue(file.isCurrentlyOpen() == false);

	file.deleteFile();
	IsTrue(file.exists() == false);

	for (int i = 0; i < buffer.size() - 1; i++)
	{
		IsTrue(output[i] == buffer[i]);
	}

	NOU_CHECK_ERROR_HANDLER;
}

/*
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
*/
TEST_METHOD(MathVec2)
{
	using namespace NOU::NOU_MATH;

	//check if the null vector works
	IsTrue(Vec2::nullVector().value(0) == 0.0f);
	IsTrue(Vec2::nullVector().value(1) == 0.0f);

	Vec2 vec0 = { 1.0f, 2.0f }; //check both ways of constructing
	Vec2 vec1(1.0f, 2.0f);
	Vec2 vec2(-1.0f, -2.0f);

	//check if value() works
	IsTrue(vec0.value(0) == 1.0f);
	IsTrue(vec0.value(1) == 2.0f);

	IsTrue(vec0.value(0) == 1.0f);
	IsTrue(vec0.value(1) == 2.0f);

	//compare
	IsTrue(vec0 == vec1);
	IsTrue(vec0 != vec2);

	//invert
	IsTrue(vec0 == -vec2);

	Vec2 vec2Cop = vec2;

	vec2Cop.invertThis();
	IsTrue(vec2Cop == -vec2);

	//scaling
	vec0 *= 2;
	IsTrue(vec0.value(0) == 2.0f);
	IsTrue(vec0.value(1) == 4.0f);

	Vec2 vec3(2.0f, 4.0f);
	IsTrue((vec1 * 2) == vec3);

	//dot product
	IsTrue((vec1 * vec2) == -5.0f);

	//sub
	IsTrue((vec1 - vec2) == Vec2(2.0f, 4.0f));

	Vec2 vec4 = Vec2::nullVector();
	vec4 -= vec1;
	IsTrue(vec4 == vec2);

	//add
	IsTrue((vec1 + vec2) == Vec2(0.0f, 0.0f));

	Vec2 vec10 = Vec2::nullVector();
	vec10 += vec1;
	IsTrue(vec10 == vec1);

	//copy
	Vec2 vec5 = vec1.copy();
	IsTrue(vec5 == vec1);

	//divideElements
	Vec2 vec6(5.0f, 10.0f);
	Vec2 vec7(2.0f, 2.0f);

	IsTrue(vec6.divideElements(vec7) == Vec2(5.0f / 2.0f, 10.0f / 2.0f));

	vec6.divideElementsAssign(vec7);
	IsTrue(vec6 == Vec2(5.0f / 2.0f, 10.0f / 2.0f));

	//multiplyElements
	Vec2 vec8(5.0f, 10.0f);
	Vec2 vec9(2.0f, 2.0f);

	IsTrue(vec8.multiplicateElements(vec9) == Vec2(5.0f * 2.0f, 10.0f * 2.0f));

	vec8.multiplicateElementsAssign(vec9);
	IsTrue(vec8 == Vec2(5.0f * 2.0f, 10.0f * 2.0f));

	Vec2 vec11(2.0f, 0.0f);
	IsTrue(vec11.length() == 2.0);

	Vec2 vec18(3.0f, 5.0f);
	IsTrue(vec18.normalize().length() == 1.0f);

	NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(MathVec2i)
{
	using namespace NOU::NOU_MATH;

	//check if the null vector works
	IsTrue(Vec2i::nullVector().value(0) == 0);
	IsTrue(Vec2i::nullVector().value(1) == 0);

	Vec2i vec0 = { 1, 2 }; //check both ways of constructing
	Vec2i vec1(1, 2);
	Vec2i vec2(-1, -2);

	//check if value() works
	IsTrue(vec0.value(0) == 1);
	IsTrue(vec0.value(1) == 2);

	IsTrue(vec0.value(0) == 1);
	IsTrue(vec0.value(1) == 2);

	//compare
	IsTrue(vec0 == vec1);
	IsTrue(vec0 != vec2);

	//invert
	IsTrue(vec0 == -vec2);

	Vec2i vec2Cop = vec2;

	vec2Cop.invertThis();
	IsTrue(vec2Cop == -vec2);

	//scaling
	vec0 *= 2;
	IsTrue(vec0.value(0) == 2);
	IsTrue(vec0.value(1) == 4);

	Vec2i vec3(2, 4);
	IsTrue((vec1 * 2) == vec3);

	//dot product
	IsTrue((vec1 * vec2) == -5);

	//sub
	IsTrue((vec1 - vec2) == Vec2i(2, 4));

	Vec2i vec4 = Vec2i::nullVector();
	vec4 -= vec1;
	IsTrue(vec4 == vec2);

	//add
	IsTrue((vec1 + vec2) == Vec2i(0, 0));

	Vec2i vec10 = Vec2i::nullVector();
	vec10 += vec1;
	IsTrue(vec10 == vec1);

	//copy
	Vec2i vec5 = vec1.copy();
	IsTrue(vec5 == vec1);

	//divideElements
	Vec2i vec6(5, 10);
	Vec2i vec7(2, 2);

	IsTrue(vec6.divideElements(vec7) == Vec2i(5 / 2, 10 / 2));

	vec6.divideElementsAssign(vec7);
	IsTrue(vec6 == Vec2i(5 / 2, 10 / 2));

	//multiplyElements
	Vec2i vec8(5, 10);
	Vec2i vec9(2, 2);

	IsTrue(vec8.multiplicateElements(vec9) == Vec2i(5 * 2, 10 * 2));

	vec8.multiplicateElementsAssign(vec9);
	IsTrue(vec8 == Vec2i(5 * 2, 10 * 2));

	Vec2i vec11(2, 0);
	IsTrue(vec11.length() == 2.0);

	//Not precise enough
	//Vec2i vec12(3, 5);
	//IsTrue(vec18.normalize().length() == 1.0);

	NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(MathVec3)
{
	using namespace NOU::NOU_MATH;

	//check if the null vector works
	IsTrue(Vec3::nullVector().value(0) == 0.0f);
	IsTrue(Vec3::nullVector().value(1) == 0.0f);
	IsTrue(Vec3::nullVector().value(2) == 0.0f);

	Vec3 vec0 = { 1.0f, 2.0f, 3.0f}; //check both ways of constructing
	Vec3 vec1(1.0f, 2.0f, 3.0f);
	Vec3 vec2(-1.0f, -2.0f, -3.0f);
	Vec3 vec12(Vec2(1.0f, 2.0f), 3.0f);
	Vec3 vec13(Vec2(1.0f, 2.0f), { 3.0f });

	//check if value() works
	IsTrue(vec0.value(0) == 1.0f);
	IsTrue(vec0.value(1) == 2.0f);
	IsTrue(vec0.value(2) == 3.0f);

	IsTrue(vec0.value(0) == 1.0f);
	IsTrue(vec0.value(1) == 2.0f);
	IsTrue(vec0.value(2) == 3.0f);

	IsTrue(vec12.value(0) == 1.0f);
	IsTrue(vec12.value(1) == 2.0f);
	IsTrue(vec12.value(2) == 3.0f);

	IsTrue(vec13.value(0) == 1.0f);
	IsTrue(vec13.value(1) == 2.0f);
	IsTrue(vec13.value(2) == 3.0f);

	//compare
	IsTrue(vec0 == vec1);
	IsTrue(vec0 != vec2);

	//invert
	IsTrue(vec0 == -vec2);

	Vec3 vec2Cop = vec2;

	vec2Cop.invertThis();
	IsTrue(vec2Cop == -vec2);

	//scaling
	vec0 *= 2;
	IsTrue(vec0.value(0) == 2.0f);
	IsTrue(vec0.value(1) == 4.0f);
	IsTrue(vec0.value(2) == 6.0f);

	Vec3 vec3(2.0f, 4.0f, 6.0f);
	IsTrue((vec1 * 2) == vec3);

	//dot product
	IsTrue((vec1 * vec2) == -14.0f);

	//cross product
	IsTrue((vec1.crossProduct(vec2)) == Vec3::nullVector());

	//sub
	IsTrue((vec1 - vec2) == Vec3(2.0f, 4.0f, 6.0f));

	Vec3 vec4 = Vec3::nullVector();
	vec4 -= vec1;
	IsTrue(vec4 == vec2);

	//add
	IsTrue((vec1 + vec2) == Vec3(0.0f, 0.0f, 0.0f));

	Vec3 vec10 = Vec3::nullVector();
	vec10 += vec1;
	IsTrue(vec10 == vec1);

	//copy
	Vec3 vec5 = vec1.copy();
	IsTrue(vec5 == vec1);

	//divideElements
	Vec3 vec6(5.0f, 10.0f, 20.0f);
	Vec3 vec7(2.0f, 2.0f, 2.0f);

	IsTrue(vec6.divideElements(vec7) == Vec3(5.0f / 2.0f, 10.0f / 2.0f, 20.0f / 2.0f));

	vec6.divideElementsAssign(vec7);
	IsTrue(vec6 == Vec3(5.0f / 2.0f, 10.0f / 2.0f, 20.0f / 2.0f));

	//multiplyElements
	Vec3 vec8(5.0f, 10.0f, 20.0f);
	Vec3 vec9(2.0f, 2.0f, 2.0f);

	IsTrue(vec8.multiplicateElements(vec9) == Vec3(5.0f * 2.0f, 10.0f * 2.0f, 20.0f * 2.0f));

	vec8.multiplicateElementsAssign(vec9);
	IsTrue(vec8 == Vec3(5.0f * 2.0f, 10.0f * 2.0f, 20.0f * 2.0f));

	Vec3 vec11(2.0f, 0.0f, 0.0f);
	IsTrue(vec11.length() == 2.0);

	Vec3 vec18(3.0f, 5.0f, 8.0f);
	IsTrue(vec18.normalize().length() == 1.0f);

	NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(MathVec3i)
{
	using namespace NOU::NOU_MATH;

	//check if the null vector works
	IsTrue(Vec3i::nullVector().value(0) == 0);
	IsTrue(Vec3i::nullVector().value(1) == 0);
	IsTrue(Vec3i::nullVector().value(2) == 0);

	Vec3i vec0 = { 1, 2, 3 }; //check both ways of constructing
	Vec3i vec1(1, 2, 3);
	Vec3i vec2(-1, -2, -3);
	Vec3i vec12(Vec2i(1, 2), 3);
	Vec3i vec13(Vec2i(1, 2), { 3 });

	//check if value() works
	IsTrue(vec0.value(0) == 1);
	IsTrue(vec0.value(1) == 2);
	IsTrue(vec0.value(2) == 3);

	IsTrue(vec1.value(0) == 1);
	IsTrue(vec1.value(1) == 2);
	IsTrue(vec1.value(2) == 3);

	IsTrue(vec12.value(0) == 1);
	IsTrue(vec12.value(1) == 2);
	IsTrue(vec12.value(2) == 3);

	IsTrue(vec13.value(0) == 1);
	IsTrue(vec13.value(1) == 2);
	IsTrue(vec13.value(2) == 3);

	//compare
	IsTrue(vec0 == vec1);
	IsTrue(vec0 != vec2);

	//invert
	IsTrue(vec0 == -vec2);

	Vec3i vec2Cop = vec2;

	vec2Cop.invertThis();
	IsTrue(vec2Cop == -vec2);

	//scaling
	vec0 *= 2;
	IsTrue(vec0.value(0) == 2);
	IsTrue(vec0.value(1) == 4);
	IsTrue(vec0.value(2) == 6);

	Vec3i vec3(2, 4, 6);
	IsTrue((vec1 * 2) == vec3);

	//dot product
	IsTrue((vec1 * vec2) == -14);

	//cross product
	IsTrue((vec1.crossProduct(vec2)) == Vec3i::nullVector());

	//sub
	IsTrue((vec1 - vec2) == Vec3i(2, 4, 6));

	Vec3i vec4 = Vec3i::nullVector();
	vec4 -= vec1;
	IsTrue(vec4 == vec2);

	//add
	IsTrue((vec1 + vec2) == Vec3i(0, 0, 0));

	Vec3i vec10 = Vec3i::nullVector();
	vec10 += vec1;
	IsTrue(vec10 == vec1);

	//copy
	Vec3i vec5 = vec1.copy();
	IsTrue(vec5 == vec1);

	//divideElements
	Vec3i vec6(5, 10, 20);
	Vec3i vec7(2, 2, 2);

	IsTrue(vec6.divideElements(vec7) == Vec3i(5 / 2, 10 / 2, 20 / 2));

	vec6.divideElementsAssign(vec7);
	IsTrue(vec6 == Vec3i(5 / 2, 10 / 2, 20 / 2));

	//multiplyElements
	Vec3i vec8(5, 10, 20);
	Vec3i vec9(2, 2, 2);

	IsTrue(vec8.multiplicateElements(vec9) == Vec3i(5 * 2, 10 * 2, 20 * 2));

	vec8.multiplicateElementsAssign(vec9);
	IsTrue(vec8 == Vec3i(5 * 2, 10 * 2, 20 * 2));

	Vec3i vec11(2, 0, 0);
	IsTrue(vec11.length() == 2.0);

	//Not precise enough
	//Vec3i vec12(3, 5, 8);
	//IsTrue(vec18.normalize().length() == 1.0);

	NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(MathVec4)
{
	using namespace NOU::NOU_MATH;

	//check if the null vector works
	IsTrue(Vec4::nullVector().value(0) == 0.0f);
	IsTrue(Vec4::nullVector().value(1) == 0.0f);
	IsTrue(Vec4::nullVector().value(2) == 0.0f);
	IsTrue(Vec4::nullVector().value(3) == 0.0f);

	Vec4 vec0 = { 1.0f, 2.0f, 3.0f, 4.0f }; //check both ways of constructing
	Vec4 vec1(1.0f, 2.0f, 3.0f, 4.0f);
	Vec4 vec2(-1.0f, -2.0f, -3.0f, -4.0f);
	Vec4 vec12(Vec2(1.0f, 2.0f), 3.0f, 4.0f);
	Vec4 vec13(Vec2(1.0f, 2.0f), { 3.0f, 4.0f });
	Vec4 vec14(Vec3(1.0f, 2.0f, 3.0f), 4.0f);
	Vec4 vec15(Vec3(1.0f, 2.0f, 3.0f), { 4.0f });

	//check if value() works
	IsTrue(vec0.value(0) == 1.0f);
	IsTrue(vec0.value(1) == 2.0f);
	IsTrue(vec0.value(2) == 3.0f);
	IsTrue(vec0.value(3) == 4.0f);

	//check if value() works
	IsTrue(vec1.value(0) == 1.0f);
	IsTrue(vec1.value(1) == 2.0f);
	IsTrue(vec1.value(2) == 3.0f);
	IsTrue(vec1.value(3) == 4.0f);

	IsTrue(vec12.value(0) == 1.0f);
	IsTrue(vec12.value(1) == 2.0f);
	IsTrue(vec12.value(2) == 3.0f);
	IsTrue(vec12.value(3) == 4.0f);

	IsTrue(vec13.value(0) == 1.0f);
	IsTrue(vec13.value(1) == 2.0f);
	IsTrue(vec13.value(2) == 3.0f);
	IsTrue(vec13.value(3) == 4.0f);

	IsTrue(vec14.value(0) == 1.0f);
	IsTrue(vec14.value(1) == 2.0f);
	IsTrue(vec14.value(2) == 3.0f);
	IsTrue(vec14.value(3) == 4.0f);

	IsTrue(vec15.value(0) == 1.0f);
	IsTrue(vec15.value(1) == 2.0f);
	IsTrue(vec15.value(2) == 3.0f);
	IsTrue(vec15.value(3) == 4.0f);

	//compare
	IsTrue(vec0 == vec1);
	IsTrue(vec0 != vec2);

	//invert
	IsTrue(vec0 == -vec2);

	Vec4 vec2Cop = vec2;

	vec2Cop.invertThis();
	IsTrue(vec2Cop == -vec2);

	//scaling
	vec0 *= 2;
	IsTrue(vec0.value(0) == 2.0f);
	IsTrue(vec0.value(1) == 4.0f);
	IsTrue(vec0.value(2) == 6.0f);
	IsTrue(vec0.value(3) == 8.0f);

	Vec4 vec3(2.0f, 4.0f, 6.0f, 8.0f);
	IsTrue((vec1 * 2) == vec3);

	//dot product
	IsTrue((vec1 * vec2) == -30.0);

	//sub
	IsTrue((vec1 - vec2) == Vec4(2.0f, 4.0f, 6.0f, 8.0f));

	Vec4 vec4 = Vec4::nullVector();
	vec4 -= vec1;
	IsTrue(vec4 == vec2);

	//add
	IsTrue((vec1 + vec2) == Vec4(0.0f, 0.0f, 0.0f, 0.0f));

	Vec4 vec10 = Vec4::nullVector();
	vec10 += vec1;
	IsTrue(vec10 == vec1);

	//copy
	Vec4 vec5 = vec1.copy();
	IsTrue(vec5 == vec1);

	//divideElements
	Vec4 vec6(5.0f, 10.0f, 20.0f, 40.0f);
	Vec4 vec7(2.0f, 2.0f, 2.0f, 2.0f);

	IsTrue(vec6.divideElements(vec7) == Vec4(5.0f / 2.0f, 10.0f / 2.0f, 20.0f / 2.0f, 40.0f / 2.0f));

	vec6.divideElementsAssign(vec7);
	IsTrue(vec6 == Vec4(5.0f / 2.0f, 10.0f / 2.0f, 20.0f / 2.0f, 40.0f / 2.0f));

	//multiplyElements
	Vec4 vec8(5.0f, 10.0f, 20.0f, 40.0f);
	Vec4 vec9(2.0f, 2.0f, 2.0f, 2.0f);

	IsTrue(vec8.multiplicateElements(vec9) == Vec4(5.0f * 2.0f, 10.0f * 2.0f, 20.0f * 2.0f, 40.0f * 2.0f));

	vec8.multiplicateElementsAssign(vec9);
	IsTrue(vec8 == Vec4(5.0f * 2.0f, 10.0f * 2.0f, 20.0f * 2.0f, 40.0f * 2.0f));

	Vec4 vec11(2.0f, 0.0f, 0.0f, 0.0f);
	IsTrue(vec11.length() == 2);

	Vec4 vec18(3.0f, 5.0f, 8.0f, 3.0f);
	IsTrue(vec18.normalize().length() == 1.0f);

	NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(MathVec4i)
{
	using namespace NOU::NOU_MATH;

	//check if the null vector works
	IsTrue(Vec4i::nullVector().value(0) == 0);
	IsTrue(Vec4i::nullVector().value(1) == 0);
	IsTrue(Vec4i::nullVector().value(2) == 0);
	IsTrue(Vec4i::nullVector().value(3) == 0);

	Vec4i vec0 = { 1, 2, 3, 4 }; //check both ways of constructing
	Vec4i vec1(1, 2, 3, 4);
	Vec4i vec2(-1, -2, -3, -4);
	Vec4i vec12(Vec2i(1, 2), 3, 4);
	Vec4i vec13(Vec2i(1, 2), { 3, 4 });
	Vec4i vec14(Vec3i(1, 2, 3), 4);
	Vec4i vec15(Vec3i(1, 2, 3), { 4 });


	//check if value() works
	IsTrue(vec0.value(0) == 1);
	IsTrue(vec0.value(1) == 2);
	IsTrue(vec0.value(2) == 3);
	IsTrue(vec0.value(3) == 4);

	IsTrue(vec12.value(0) == 1);
	IsTrue(vec12.value(1) == 2);
	IsTrue(vec12.value(2) == 3);
	IsTrue(vec12.value(3) == 4);

	IsTrue(vec13.value(0) == 1);
	IsTrue(vec13.value(1) == 2);
	IsTrue(vec13.value(2) == 3);
	IsTrue(vec13.value(3) == 4);

	IsTrue(vec14.value(0) == 1);
	IsTrue(vec14.value(1) == 2);
	IsTrue(vec14.value(2) == 3);
	IsTrue(vec14.value(3) == 4);

	IsTrue(vec15.value(0) == 1);
	IsTrue(vec15.value(1) == 2);
	IsTrue(vec15.value(2) == 3);
	IsTrue(vec15.value(3) == 4);

	//check if value() works
	IsTrue(vec1.value(0) == 1);
	IsTrue(vec1.value(1) == 2);
	IsTrue(vec1.value(2) == 3);
	IsTrue(vec1.value(3) == 4);

	//compare
	IsTrue(vec0 == vec1);
	IsTrue(vec0 != vec2);

	//invert
	IsTrue(vec0 == -vec2);

	Vec4i vec2Cop = vec2;

	vec2Cop.invertThis();
	IsTrue(vec2Cop == -vec2);

	//scaling
	vec0 *= 2;
	IsTrue(vec0.value(0) == 2);
	IsTrue(vec0.value(1) == 4);
	IsTrue(vec0.value(2) == 6);
	IsTrue(vec0.value(3) == 8);

	Vec4i vec3(2, 4, 6, 8);
	IsTrue((vec1 * 2) == vec3);

	//dot product
	IsTrue((vec1 * vec2) == -30.0);

	//sub
	IsTrue((vec1 - vec2) == Vec4i(2, 4, 6, 8));

	Vec4i vec4 = Vec4i::nullVector();
	vec4 -= vec1;
	IsTrue(vec4 == vec2);

	//add
	IsTrue((vec1 + vec2) == Vec4i(0, 0, 0, 0));

	Vec4i vec10 = Vec4i::nullVector();
	vec10 += vec1;
	IsTrue(vec10 == vec1);

	//copy
	Vec4i vec5 = vec1.copy();
	IsTrue(vec5 == vec1);

	//divideElements
	Vec4i vec6(5, 10, 20, 40);
	Vec4i vec7(2, 2, 2, 2);

	IsTrue(vec6.divideElements(vec7) == Vec4i(5 / 2, 10 / 2, 20 / 2, 40 / 2));

	vec6.divideElementsAssign(vec7);
	IsTrue(vec6 == Vec4i(5 / 2, 10 / 2, 20 / 2, 40 / 2));

	//multiplyElements
	Vec4i vec8(5, 10, 20, 40);
	Vec4i vec9(2, 2, 2, 2);

	IsTrue(vec8.multiplicateElements(vec9) == Vec4i(5 * 2, 10 * 2, 20 * 2, 40 * 2));

	vec8.multiplicateElementsAssign(vec9);
	IsTrue(vec8 == Vec4i(5 * 2, 10 * 2, 20 * 2, 40 * 2));

	Vec4i vec11(2, 0, 0, 0);
	IsTrue(vec11.length() == 2.0);

	//Not precise enough
	//Vec4i vec12(3, 5, 8, 3);
	//IsTrue(vec18.normalize().length() == 1.0);

	NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(MathVec5f)
{
	using namespace NOU::NOU_MATH;

	//check if the null vector works
	IsTrue(Vector<NOU::float32, 5>::nullVector().value(0) == 0.0f);
	IsTrue(Vector<NOU::float32, 5>::nullVector().value(1) == 0.0f);
	IsTrue(Vector<NOU::float32, 5>::nullVector().value(2) == 0.0f);
	IsTrue(Vector<NOU::float32, 5>::nullVector().value(3) == 0.0f);
	IsTrue(Vector<NOU::float32, 5>::nullVector().value(4) == 0.0f);

	Vector<NOU::float32, 5> vec0 = { 1.0f,  2.0f,  3.0f,  4.0f,  5.0f };
	Vector<NOU::float32, 5> vec1(  { 1.0f,  2.0f,  3.0f,  4.0f,  5.0f });
	Vector<NOU::float32, 5> vec2( { -1.0f, -2.0f, -3.0f, -4.0f, -5.0f });
	Vector<NOU::float32, 5> vec12(Vec2(1.0f, 2.0f), { 3.0f,  4.0f,  5.0f });
	Vector<NOU::float32, 5> vec13(Vec2(1.0f, 2.0f), { 3.0f, 4.0f, 5.0f });
	Vector<NOU::float32, 5> vec14(Vec3(1.0f, 2.0f, 3.0f), { 4.0f,  5.0f });
	Vector<NOU::float32, 5> vec15(Vec3(1.0f, 2.0f, 3.0f), { 4.0f, 5.0f });
	Vector<NOU::float32, 5> vec16(Vec4(1.0f, 2.0f, 3.0f, 4.0f), { 5.0f });
	Vector<NOU::float32, 5> vec17(Vec4(1.0f, 2.0f, 3.0f, 4.0f), { 5.0f });


	//check if value() works
	IsTrue(vec0.value(0) == 1.0f);
	IsTrue(vec0.value(1) == 2.0f);
	IsTrue(vec0.value(2) == 3.0f);
	IsTrue(vec0.value(3) == 4.0f);
	IsTrue(vec0.value(4) == 5.0f);

	//check if value() works
	IsTrue(vec1.value(0) == 1.0f);
	IsTrue(vec1.value(1) == 2.0f);
	IsTrue(vec1.value(2) == 3.0f);
	IsTrue(vec1.value(3) == 4.0f);
	IsTrue(vec1.value(4) == 5.0f);

	IsTrue(vec12.value(0) == 1.0f);
	IsTrue(vec12.value(1) == 2.0f);
	IsTrue(vec12.value(2) == 3.0f);
	IsTrue(vec12.value(3) == 4.0f);
	IsTrue(vec12.value(4) == 5.0f);

	IsTrue(vec13.value(0) == 1.0f);
	IsTrue(vec13.value(1) == 2.0f);
	IsTrue(vec13.value(2) == 3.0f);
	IsTrue(vec13.value(3) == 4.0f);
	IsTrue(vec13.value(4) == 5.0f);

	IsTrue(vec14.value(0) == 1.0f);
	IsTrue(vec14.value(1) == 2.0f);
	IsTrue(vec14.value(2) == 3.0f);
	IsTrue(vec14.value(3) == 4.0f);
	IsTrue(vec14.value(4) == 5.0f);

	IsTrue(vec15.value(0) == 1.0f);
	IsTrue(vec15.value(1) == 2.0f);
	IsTrue(vec15.value(2) == 3.0f);
	IsTrue(vec15.value(3) == 4.0f);
	IsTrue(vec15.value(4) == 5.0f);

	IsTrue(vec16.value(0) == 1.0f);
	IsTrue(vec16.value(1) == 2.0f);
	IsTrue(vec16.value(2) == 3.0f);
	IsTrue(vec16.value(3) == 4.0f);
	IsTrue(vec16.value(4) == 5.0f);

	IsTrue(vec17.value(0) == 1.0f);
	IsTrue(vec17.value(1) == 2.0f);
	IsTrue(vec17.value(2) == 3.0f);
	IsTrue(vec17.value(3) == 4.0f);
	IsTrue(vec17.value(4) == 5.0f);

	//compare
	IsTrue(vec0 == vec1);
	IsTrue(vec0 != vec2);

	//invert
	IsTrue(vec0 == -vec2);

	Vector<NOU::float32, 5> vec2Cop = vec2;

	vec2Cop.invertThis();
	IsTrue(vec2Cop == -vec2);

	//scaling
	vec0 *= 2;
	IsTrue(vec0.value(0) == 2.0f);
	IsTrue(vec0.value(1) == 4.0f);
	IsTrue(vec0.value(2) == 6.0f);
	IsTrue(vec0.value(3) == 8.0f);
	IsTrue(vec0.value(4) == 10.0f);

	Vector<NOU::float32, 5> vec3({ 2.0f, 4.0f, 6.0f, 8.0f, 10.0f });
	IsTrue((vec1 * 2) == vec3);

	//dot product
	IsTrue((vec1 * vec2) == -55.0);

	//sub
	IsTrue((vec1 - vec2) == Vector<NOU::float32, 5>({ 2.0f, 4.0f, 6.0f, 8.0f, 10.0f}));

	Vector<NOU::float32, 5> vec4 = Vector<NOU::float32, 5>::nullVector();
	vec4 -= vec1;
	IsTrue(vec4 == vec2);

	//add
	IsTrue((vec1 + vec2) == Vector<NOU::float32, 5>({ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }));

	Vector<NOU::float32, 5> vec10 = Vector<NOU::float32, 5>::nullVector();
	vec10 += vec1;
	IsTrue(vec10 == vec1);

	//copy
	Vector<NOU::float32, 5> vec5 = vec1.copy();
	IsTrue(vec5 == vec1);

	//divideElements
	Vector<NOU::float32, 5> vec6({ 5.0f, 10.0f, 20.0f, 40.0f, 80.0f });
	Vector<NOU::float32, 5> vec7({ 2.0f, 2.0f, 2.0f, 2.0f, 2.0f });

	IsTrue(vec6.divideElements(vec7) == Vector<NOU::float32, 5>({ 5.0f / 2.0f, 10.0f / 2.0f, 20.0f / 2.0f, 
		40.0f / 2.0f, 80.0f / 2.0f }));

	vec6.divideElementsAssign(vec7);
	IsTrue(vec6 == Vector<NOU::float32, 5>({ 5.0f / 2.0f, 10.0f / 2.0f, 20.0f / 2.0f, 40.0f / 2.0f,  
		80.0f / 2.0f }));

	//multiplyElements
	Vector<NOU::float32, 5> vec8({ 5.0f, 10.0f, 20.0f, 40.0f, 80.0f });
	Vector<NOU::float32, 5> vec9({ 2.0f, 2.0f, 2.0f, 2.0f, 2.0f });

	IsTrue(vec8.multiplicateElements(vec9) == Vector<NOU::float32, 5>({ 5.0f * 2.0f, 10.0f * 2.0f, 
		20.0f * 2.0f, 40.0f * 2.0f, 80.0f * 2.0f }));

	vec8.multiplicateElementsAssign(vec9);
	IsTrue(vec8 == Vector<NOU::float32, 5>({ 5.0f * 2.0f, 10.0f * 2.0f, 20.0f * 2.0f, 40.0f * 2.0f, 
		80.0f * 2.0f }));

	Vector<NOU::float32, 5> vec11({ 2.0f, 0.0f, 0.0f, 0.0f, 0.0f});
	IsTrue(vec11.length() == 2.0);

	Vector<NOU::float32, 5> vec18({ 3.0f, 5.0f, 8.0f, 3.0f, 1.0f });
	IsTrue(vec18.normalize().length() == 1.0);

	NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(MathVec5i)
{
	using namespace NOU::NOU_MATH;

	//check if the null vector works
	IsTrue(Vector<NOU::int32, 5>::nullVector().value(0) == 0);
	IsTrue(Vector<NOU::int32, 5>::nullVector().value(1) == 0);
	IsTrue(Vector<NOU::int32, 5>::nullVector().value(2) == 0);
	IsTrue(Vector<NOU::int32, 5>::nullVector().value(3) == 0);
	IsTrue(Vector<NOU::int32, 5>::nullVector().value(4) == 0);

	Vector<NOU::int32, 5> vec0 = { 1,  2,  3,  4,  5 };
	Vector<NOU::int32, 5> vec1({ 1,  2,  3,  4,  5 });
	Vector<NOU::int32, 5> vec2({ -1, -2, -3, -4, -5 });
	Vector<NOU::int32, 5> vec12(Vec2i(1, 2), { 3,  4,  5 });
	Vector<NOU::int32, 5> vec13(Vec2i(1, 2), { 3, 4, 5 });
	Vector<NOU::int32, 5> vec14(Vec3i(1, 2, 3), { 4,  5 });
	Vector<NOU::int32, 5> vec15(Vec3i(1, 2, 3), { 4, 5 });
	Vector<NOU::int32, 5> vec16(Vec4i(1, 2, 3, 4), { 5 });
	Vector<NOU::int32, 5> vec17(Vec4i(1, 2, 3, 4), { 5 });


	//check if value() works
	IsTrue(vec0.value(0) == 1);
	IsTrue(vec0.value(1) == 2);
	IsTrue(vec0.value(2) == 3);
	IsTrue(vec0.value(3) == 4);
	IsTrue(vec0.value(4) == 5);

	//check if value() works
	IsTrue(vec1.value(0) == 1);
	IsTrue(vec1.value(1) == 2);
	IsTrue(vec1.value(2) == 3);
	IsTrue(vec1.value(3) == 4);
	IsTrue(vec1.value(4) == 5);

	IsTrue(vec12.value(0) == 1);
	IsTrue(vec12.value(1) == 2);
	IsTrue(vec12.value(2) == 3);
	IsTrue(vec12.value(3) == 4);
	IsTrue(vec12.value(4) == 5);

	IsTrue(vec13.value(0) == 1);
	IsTrue(vec13.value(1) == 2);
	IsTrue(vec13.value(2) == 3);
	IsTrue(vec13.value(3) == 4);
	IsTrue(vec13.value(4) == 5);

	IsTrue(vec14.value(0) == 1);
	IsTrue(vec14.value(1) == 2);
	IsTrue(vec14.value(2) == 3);
	IsTrue(vec14.value(3) == 4);
	IsTrue(vec14.value(4) == 5);

	IsTrue(vec15.value(0) == 1);
	IsTrue(vec15.value(1) == 2);
	IsTrue(vec15.value(2) == 3);
	IsTrue(vec15.value(3) == 4);
	IsTrue(vec15.value(4) == 5);

	IsTrue(vec16.value(0) == 1);
	IsTrue(vec16.value(1) == 2);
	IsTrue(vec16.value(2) == 3);
	IsTrue(vec16.value(3) == 4);
	IsTrue(vec16.value(4) == 5);

	IsTrue(vec17.value(0) == 1);
	IsTrue(vec17.value(1) == 2);
	IsTrue(vec17.value(2) == 3);
	IsTrue(vec17.value(3) == 4);
	IsTrue(vec17.value(4) == 5);

	//compare
	IsTrue(vec0 == vec1);
	IsTrue(vec0 != vec2);

	//invert
	IsTrue(vec0 == -vec2);

	Vector<NOU::int32, 5> vec2Cop = vec2;

	vec2Cop.invertThis();
	IsTrue(vec2Cop == -vec2);

	//scaling
	vec0 *= 2;
	IsTrue(vec0.value(0) == 2);
	IsTrue(vec0.value(1) == 4);
	IsTrue(vec0.value(2) == 6);
	IsTrue(vec0.value(3) == 8);
	IsTrue(vec0.value(4) == 10);

	Vector<NOU::int32, 5> vec3({ 2, 4, 6, 8, 10 });
	IsTrue((vec1 * 2) == vec3);

	//dot product
	IsTrue((vec1 * vec2) == -55.0);

	//sub
	IsTrue((vec1 - vec2) == Vector<NOU::int32, 5>({ 2, 4, 6, 8, 10 }));

	Vector<NOU::int32, 5> vec4 = Vector<NOU::int32, 5>::nullVector();
	vec4 -= vec1;
	IsTrue(vec4 == vec2);

	//add
	IsTrue((vec1 + vec2) == Vector<NOU::int32, 5>({ 0, 0, 0, 0, 0 }));

	Vector<NOU::int32, 5> vec10 = Vector<NOU::int32, 5>::nullVector();
	vec10 += vec1;
	IsTrue(vec10 == vec1);

	//copy
	Vector<NOU::int32, 5> vec5 = vec1.copy();
	IsTrue(vec5 == vec1);

	//divideElements
	Vector<NOU::int32, 5> vec6({ 5, 10, 20, 40, 80 });
	Vector<NOU::int32, 5> vec7({ 2, 2, 2, 2, 2 });

	IsTrue(vec6.divideElements(vec7) == Vector<NOU::int32, 5>({ 5 / 2, 10 / 2, 20 / 2,
		40 / 2, 80 / 2 }));

	vec6.divideElementsAssign(vec7);
	IsTrue(vec6 == Vector<NOU::int32, 5>({ 5 / 2, 10 / 2, 20 / 2, 40 / 2,
		80 / 2 }));

	//multiplyElements
	Vector<NOU::int32, 5> vec8({ 5, 10, 20, 40, 80 });
	Vector<NOU::int32, 5> vec9({ 2, 2, 2, 2, 2 });

	IsTrue(vec8.multiplicateElements(vec9) == Vector<NOU::int32, 5>({ 5 * 2, 10 * 2,
		20 * 2, 40 * 2, 80 * 2 }));

	vec8.multiplicateElementsAssign(vec9);
	IsTrue(vec8 == Vector<NOU::int32, 5>({ 5 * 2, 10 * 2, 20 * 2, 40 * 2,
		80 * 2 }));

	Vector<NOU::int32, 5> vec11({ 2, 0, 0, 0, 0 });
	IsTrue(vec11.length() == 2.0);

	//Not precise enough
	//Vector<NOU::int32, 5> vec12({ 3, 5, 8, 3, 1 });
	//IsTrue(vec18.normalize().length() == 1.0);

	NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(MathMat2)
{
	NOU::NOU_MATH::Mat2 mat0 = { { 1.0f, 2.0f },{ 3.0f, 4.0f } };
	NOU::NOU_MATH::Mat2 mat1(1.0f, 2.0f, 3.0f, 4.0f);
	NOU::NOU_MATH::Mat2 mat2(2.0f, 3.0f, 4.0f, 5.0f);

	//Check if the values are correct
	IsTrue(mat0.value(0, 0) == 1.0f);
	IsTrue(mat0.value(0, 1) == 2.0f);
	IsTrue(mat0.value(1, 0) == 3.0f);
	IsTrue(mat0.value(1, 1) == 4.0f);

	//Matrices have the same values; check if equal and unequal work and check if the 2. constructor works
	IsTrue(mat0 == mat1);
	IsTrue(mat0 != mat2);
	IsTrue(!(mat0 == mat2));
	IsTrue(mat0 == mat0);

	//zeroes
	IsTrue(NOU::NOU_MATH::Mat2::zeroes() == NOU::NOU_MATH::Mat2(0.0f, 0.0f,
		0.0f, 0.0f));

	//identity
	IsTrue(NOU::NOU_MATH::Mat2::identity() == NOU::NOU_MATH::Mat2(1.0f, 0.0f,
		0.0f, 1.0f));

	//add
	NOU::NOU_MATH::Mat2 mat3 = mat0 + mat2;

	IsTrue(mat3.value(0, 0) == 3.0f);
	IsTrue(mat3.value(0, 1) == 5.0f);
	IsTrue(mat3.value(1, 0) == 7.0f);
	IsTrue(mat3.value(1, 1) == 9.0f);

	IsTrue((mat0 += mat2) == mat3);

	//sub
	NOU::NOU_MATH::Mat2 mat4 = mat1 - mat2;

	IsTrue(mat4.value(0, 0) == -1.0f);
	IsTrue(mat4.value(0, 1) == -1.0f);
	IsTrue(mat4.value(1, 0) == -1.0f);
	IsTrue(mat4.value(1, 1) == -1.0f);

	IsTrue((mat1 -= mat2) == mat4);

	//mult
	NOU::NOU_MATH::Mat2 mat5(1.0f, 2.0f, 3.0f, 4.0f);
	NOU::NOU_MATH::Mat2 mat6(2.0f, 3.0f, 4.0f, 5.0f);

	NOU::NOU_MATH::Mat2 mat7 = mat5 * mat6;

	IsTrue(mat7.value(0, 0) == 10.0f);
	IsTrue(mat7.value(0, 1) == 13.0f);
	IsTrue(mat7.value(1, 0) == 22.0f);
	IsTrue(mat7.value(1, 1) == 29.0f);

	//mult (2x2 * 2x2 special)
	NOU::NOU_MATH::Matrix<NOU::float32, 2, 3> mat8 = { { 1, 2, 3 },{ 4, 5, 6 } };
	NOU::NOU_MATH::Matrix<NOU::float32, 2, 3> mat9 = mat5 * mat8;

	IsTrue(mat9.value(0, 0) == 9.0f);
	IsTrue(mat9.value(0, 1) == 12.0f);
	IsTrue(mat9.value(0, 2) == 15.0f);
	IsTrue(mat9.value(1, 0) == 19.0f);
	IsTrue(mat9.value(1, 1) == 26.0f);
	IsTrue(mat9.value(1, 2) == 33.0f);

	//mult vector
	NOU::NOU_MATH::Vec2 vec0(1.0f, 2.0f);

	NOU::NOU_MATH::Vec2 vec1 = mat5 * vec0;
	IsTrue(vec1.value(0) == 5.0f);
	IsTrue(vec1.value(1) == 11.0f);

	//mult scale
	NOU::NOU_MATH::Mat2 mat10 = mat5 * 2;

	IsTrue(mat10.value(0, 0) == 2.0f);
	IsTrue(mat10.value(0, 1) == 4.0f);
	IsTrue(mat10.value(1, 0) == 6.0f);
	IsTrue(mat10.value(1, 1) == 8.0f);

	NOU::NOU_MATH::Mat2 mat11 = mat5;
	mat11 *= 2;

	IsTrue(mat11 == mat10);

	//transpose
	NOU::NOU_MATH::Mat2 mat12 = mat5.transpose();

	IsTrue(mat12.value(0, 0) == 1.0f);
	IsTrue(mat12.value(0, 1) == 3.0f);
	IsTrue(mat12.value(1, 0) == 2.0f);
	IsTrue(mat12.value(1, 1) == 4.0f);

	//copy
	IsTrue(mat5.copy() == mat5);

	NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(MathMat2i)
{
	NOU::NOU_MATH::Mat2i mat0 = { { 1, 2 },{ 3, 4 } };
	NOU::NOU_MATH::Mat2i mat1(1, 2, 3, 4);
	NOU::NOU_MATH::Mat2i mat2(2, 3, 4, 5);

	//Check if the values are correct
	IsTrue(mat0.value(0, 0) == 1);
	IsTrue(mat0.value(0, 1) == 2);
	IsTrue(mat0.value(1, 0) == 3);
	IsTrue(mat0.value(1, 1) == 4);

	//Matrices have the same values; check if equal and unequal work and check if the 2. constructor works
	IsTrue(mat0 == mat1);
	IsTrue(mat0 != mat2);
	IsTrue(!(mat0 == mat2));
	IsTrue(mat0 == mat0);

	//zeroes
	IsTrue(NOU::NOU_MATH::Mat2i::zeroes() == NOU::NOU_MATH::Mat2i(0, 0,
		                                                        0, 0));

	//identity
	IsTrue(NOU::NOU_MATH::Mat2i::identity() == NOU::NOU_MATH::Mat2i(1, 0,
		                                                          0, 1));

	//add
	NOU::NOU_MATH::Mat2i mat3 = mat0 + mat2;

	IsTrue(mat3.value(0, 0) == 3);
	IsTrue(mat3.value(0, 1) == 5);
	IsTrue(mat3.value(1, 0) == 7);
	IsTrue(mat3.value(1, 1) == 9);

	IsTrue((mat0 += mat2) == mat3);

	//sub
	NOU::NOU_MATH::Mat2i mat4 = mat1 - mat2;

	IsTrue(mat4.value(0, 0) == -1);
	IsTrue(mat4.value(0, 1) == -1);
	IsTrue(mat4.value(1, 0) == -1);
	IsTrue(mat4.value(1, 1) == -1);

	IsTrue((mat1 -= mat2) == mat4);

	//mult
	NOU::NOU_MATH::Mat2i mat5(1, 2, 3, 4);
	NOU::NOU_MATH::Mat2i mat6(2, 3, 4, 5);

	NOU::NOU_MATH::Mat2i mat7 = mat5 * mat6;

	IsTrue(mat7.value(0, 0) == 10);
	IsTrue(mat7.value(0, 1) == 13);
	IsTrue(mat7.value(1, 0) == 22);
	IsTrue(mat7.value(1, 1) == 29);

	//mult (2x2 * 2x2 special)
	NOU::NOU_MATH::Matrix<NOU::int32, 2, 3> mat8 = { {1, 2, 3}, { 4, 5, 6 } };
	NOU::NOU_MATH::Matrix<NOU::int32, 2, 3> mat9 = mat5 * mat8;

	IsTrue(mat9.value(0, 0) == 9);
	IsTrue(mat9.value(0, 1) == 12);
	IsTrue(mat9.value(0, 2) == 15);
	IsTrue(mat9.value(1, 0) == 19);
	IsTrue(mat9.value(1, 1) == 26);
	IsTrue(mat9.value(1, 2) == 33);

	//mult vector
	NOU::NOU_MATH::Vec2i vec0(1, 2);

	NOU::NOU_MATH::Vec2i vec1 = mat5 * vec0;
	IsTrue(vec1.value(0) == 5);
	IsTrue(vec1.value(1) == 11);

	//mult scale
	NOU::NOU_MATH::Mat2i mat10 = mat5 * 2;

	IsTrue(mat10.value(0, 0) == 2);
	IsTrue(mat10.value(0, 1) == 4);
	IsTrue(mat10.value(1, 0) == 6);
	IsTrue(mat10.value(1, 1) == 8);

	NOU::NOU_MATH::Mat2i mat11 = mat5;
	mat11 *= 2;

	IsTrue(mat11 == mat10);

	//transpose
	NOU::NOU_MATH::Mat2i mat12 = mat5.transpose();

	IsTrue(mat12.value(0, 0) == 1);
	IsTrue(mat12.value(0, 1) == 3);
	IsTrue(mat12.value(1, 0) == 2);
	IsTrue(mat12.value(1, 1) == 4);

	//copy
	IsTrue(mat5.copy() == mat5);

	NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(MathMat3)
{
	NOU::NOU_MATH::Mat3 mat0 = { { 1.0f, 2.0f, 3.0f }, { 4.0f, 5.0f, 6.0f }, { 7.0f, 8.0f, 9.0f } };
	NOU::NOU_MATH::Mat3 mat1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
	NOU::NOU_MATH::Mat3 mat2(2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f);

	//Check if the values are correct
	IsTrue(mat0.value(0, 0) == 1.0f);
	IsTrue(mat0.value(0, 1) == 2.0f);
	IsTrue(mat0.value(0, 2) == 3.0f);
	IsTrue(mat0.value(1, 0) == 4.0f);
	IsTrue(mat0.value(1, 1) == 5.0f);
	IsTrue(mat0.value(1, 2) == 6.0f);
	IsTrue(mat0.value(2, 0) == 7.0f);
	IsTrue(mat0.value(2, 1) == 8.0f);
	IsTrue(mat0.value(2, 2) == 9.0f);

	//Matrices have the same values; check if equal and unequal work and check if the 2. constructor works
	IsTrue(mat0 == mat1);
	IsTrue(mat0 != mat2);
	IsTrue(!(mat0 == mat2));
	IsTrue(mat0 == mat0);

	//zeroes
	IsTrue(NOU::NOU_MATH::Mat3::zeroes() == NOU::NOU_MATH::Mat3(0.0f, 0.0f, 0.0f, 
		                                                        0.0f, 0.0f, 0.0f, 
		                                                        0.0f, 0.0f, 0.0f));

	//identity
	IsTrue(NOU::NOU_MATH::Mat3::identity() == NOU::NOU_MATH::Mat3(1.0f, 0.0f, 0.0f,
		                                                          0.0f, 1.0f, 0.0f,
		                                                          0.0f, 0.0f, 1.0f));

	//add
	NOU::NOU_MATH::Mat3 mat3 = mat0 + mat2;

	IsTrue(mat3.value(0, 0) == 3.0f);
	IsTrue(mat3.value(0, 1) == 5.0f);
	IsTrue(mat3.value(0, 2) == 7.0f);
	IsTrue(mat3.value(1, 0) == 9.0f);
	IsTrue(mat3.value(1, 1) == 11.0f);
	IsTrue(mat3.value(1, 2) == 13.0f);
	IsTrue(mat3.value(2, 0) == 15.0f);
	IsTrue(mat3.value(2, 1) == 17.0f);
	IsTrue(mat3.value(2, 2) == 19.0f);

	IsTrue((mat0 += mat2) == mat3);

	//sub
	NOU::NOU_MATH::Mat3 mat4 = mat1 - mat2;

	IsTrue(mat4.value(0, 0) == -1.0f);
	IsTrue(mat4.value(0, 1) == -1.0f);
	IsTrue(mat4.value(0, 2) == -1.0f);
	IsTrue(mat4.value(1, 0) == -1.0f);
	IsTrue(mat4.value(1, 1) == -1.0f);
	IsTrue(mat4.value(1, 2) == -1.0f);
	IsTrue(mat4.value(2, 0) == -1.0f);
	IsTrue(mat4.value(2, 1) == -1.0f);
	IsTrue(mat4.value(2, 2) == -1.0f);

	IsTrue((mat1 -= mat2) == mat4);

	//mult
	NOU::NOU_MATH::Mat3 mat5(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
	NOU::NOU_MATH::Mat3 mat6(2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f);

	NOU::NOU_MATH::Mat3 mat7 = mat5 * mat6;

	IsTrue(mat7.value(0, 0) == 36.0f);
	IsTrue(mat7.value(0, 1) == 42.0f);
	IsTrue(mat7.value(0, 2) == 48.0f);
	IsTrue(mat7.value(1, 0) == 81.0f);
	IsTrue(mat7.value(1, 1) == 96.0f);
	IsTrue(mat7.value(1, 2) == 111.0f);
	IsTrue(mat7.value(2, 0) == 126.0f);
	IsTrue(mat7.value(2, 1) == 150.0f);
	IsTrue(mat7.value(2, 2) == 174.0f);

	//mult (2x2 * 2x2 special)
	NOU::NOU_MATH::Matrix<NOU::float32, 3, 4> mat8 = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 } };
	NOU::NOU_MATH::Matrix<NOU::float32, 3, 4> mat9 = mat5 * mat8;
	
	IsTrue(mat9.value(0, 0) == 38.0f);
	IsTrue(mat9.value(0, 1) == 44.0f);
	IsTrue(mat9.value(0, 2) == 50.0f);
	IsTrue(mat9.value(0, 3) == 56.0f);
	IsTrue(mat9.value(1, 0) == 83.0f);
	IsTrue(mat9.value(1, 1) == 98.0f);
	IsTrue(mat9.value(1, 2) == 113.0f);
	IsTrue(mat9.value(1, 3) == 128.0f);
	IsTrue(mat9.value(2, 0) == 128.0f);
	IsTrue(mat9.value(2, 1) == 152.0f);
	IsTrue(mat9.value(2, 2) == 176.0f);
	IsTrue(mat9.value(2, 3) == 200.0f);

	//mult vector
	NOU::NOU_MATH::Vec3 vec0(1.0f, 2.0f, 3.0f);

	NOU::NOU_MATH::Vec3 vec1 = mat5 * vec0;
	IsTrue(vec1.value(0) == 14.0f);
	IsTrue(vec1.value(1) == 32.0f);
	IsTrue(vec1.value(2) == 50.0f);

	//mult scale
	NOU::NOU_MATH::Mat3 mat10 = mat5 * 2;

	IsTrue(mat10.value(0, 0) == 2.0f);
	IsTrue(mat10.value(0, 1) == 4.0f);
	IsTrue(mat10.value(0, 2) == 6.0f);
	IsTrue(mat10.value(1, 0) == 8.0f);
	IsTrue(mat10.value(1, 1) == 10.0f);
	IsTrue(mat10.value(1, 2) == 12.0f);
	IsTrue(mat10.value(2, 0) == 14.0f);
	IsTrue(mat10.value(2, 1) == 16.0f);
	IsTrue(mat10.value(2, 2) == 18.0f);

	NOU::NOU_MATH::Mat3 mat11 = mat5;
	mat11 *= 2;

	IsTrue(mat11 == mat10);

	//transpose
	NOU::NOU_MATH::Mat3 mat12 = mat5.transpose();

	IsTrue(mat12.value(0, 0) == 1.0f);
	IsTrue(mat12.value(0, 1) == 4.0f);
	IsTrue(mat12.value(0, 2) == 7.0f);
	IsTrue(mat12.value(1, 0) == 2.0f);
	IsTrue(mat12.value(1, 1) == 5.0f);
	IsTrue(mat12.value(1, 2) == 8.0f);
	IsTrue(mat12.value(2, 0) == 3.0f);
	IsTrue(mat12.value(2, 1) == 6.0f);
	IsTrue(mat12.value(2, 2) == 9.0f);

	//copy
	IsTrue(mat5.copy() == mat5);

	NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(MathMat3i)
{
	NOU::NOU_MATH::Mat3i mat0 = { { 1, 2, 3 },{ 4, 5, 6 },{ 7, 8, 9 } };
	NOU::NOU_MATH::Mat3i mat1(1, 2, 3, 4, 5, 6, 7, 8, 9);
	NOU::NOU_MATH::Mat3i mat2(2, 3, 4, 5, 6, 7, 8, 9, 10);

	//Check if the values are correct
	IsTrue(mat0.value(0, 0) == 1);
	IsTrue(mat0.value(0, 1) == 2);
	IsTrue(mat0.value(0, 2) == 3);
	IsTrue(mat0.value(1, 0) == 4);
	IsTrue(mat0.value(1, 1) == 5);
	IsTrue(mat0.value(1, 2) == 6);
	IsTrue(mat0.value(2, 0) == 7);
	IsTrue(mat0.value(2, 1) == 8);
	IsTrue(mat0.value(2, 2) == 9);

	//Matrices have the same values; check if equal and unequal work and check if the 2. constructor works
	IsTrue(mat0 == mat1);
	IsTrue(mat0 != mat2);
	IsTrue(!(mat0 == mat2));
	IsTrue(mat0 == mat0);

	//zeroes
	IsTrue(NOU::NOU_MATH::Mat3i::zeroes() == NOU::NOU_MATH::Mat3i(0, 0, 0,
		0, 0, 0,
		0, 0, 0));

	//identity
	IsTrue(NOU::NOU_MATH::Mat3i::identity() == NOU::NOU_MATH::Mat3i(1, 0, 0,
		0, 1, 0,
		0, 0, 1));

	//add
	NOU::NOU_MATH::Mat3i mat3 = mat0 + mat2;

	IsTrue(mat3.value(0, 0) == 3);
	IsTrue(mat3.value(0, 1) == 5);
	IsTrue(mat3.value(0, 2) == 7);
	IsTrue(mat3.value(1, 0) == 9);
	IsTrue(mat3.value(1, 1) == 11);
	IsTrue(mat3.value(1, 2) == 13);
	IsTrue(mat3.value(2, 0) == 15);
	IsTrue(mat3.value(2, 1) == 17);
	IsTrue(mat3.value(2, 2) == 19);

	IsTrue((mat0 += mat2) == mat3);

	//sub
	NOU::NOU_MATH::Mat3i mat4 = mat1 - mat2;

	IsTrue(mat4.value(0, 0) == -1);
	IsTrue(mat4.value(0, 1) == -1);
	IsTrue(mat4.value(0, 2) == -1);
	IsTrue(mat4.value(1, 0) == -1);
	IsTrue(mat4.value(1, 1) == -1);
	IsTrue(mat4.value(1, 2) == -1);
	IsTrue(mat4.value(2, 0) == -1);
	IsTrue(mat4.value(2, 1) == -1);
	IsTrue(mat4.value(2, 2) == -1);

	IsTrue((mat1 -= mat2) == mat4);

	//mult
	NOU::NOU_MATH::Mat3i mat5(1, 2, 3, 4, 5, 6, 7, 8, 9);
	NOU::NOU_MATH::Mat3i mat6(2, 3, 4, 5, 6, 7, 8, 9, 10);

	NOU::NOU_MATH::Mat3i mat7 = mat5 * mat6;

	IsTrue(mat7.value(0, 0) == 36);
	IsTrue(mat7.value(0, 1) == 42);
	IsTrue(mat7.value(0, 2) == 48);
	IsTrue(mat7.value(1, 0) == 81);
	IsTrue(mat7.value(1, 1) == 96);
	IsTrue(mat7.value(1, 2) == 111);
	IsTrue(mat7.value(2, 0) == 126);
	IsTrue(mat7.value(2, 1) == 150);
	IsTrue(mat7.value(2, 2) == 174);

	//mult (2x2 * 2x2 special)
	NOU::NOU_MATH::Matrix<NOU::int32, 3, 4> mat8 = { { 1, 2, 3, 4 },{ 5, 6, 7, 8 },{ 9, 10, 11, 12 } };
	NOU::NOU_MATH::Matrix<NOU::int32, 3, 4> mat9 = mat5 * mat8;

	IsTrue(mat9.value(0, 0) == 38);
	IsTrue(mat9.value(0, 1) == 44);
	IsTrue(mat9.value(0, 2) == 50);
	IsTrue(mat9.value(0, 3) == 56);
	IsTrue(mat9.value(1, 0) == 83);
	IsTrue(mat9.value(1, 1) == 98);
	IsTrue(mat9.value(1, 2) == 113);
	IsTrue(mat9.value(1, 3) == 128);
	IsTrue(mat9.value(2, 0) == 128);
	IsTrue(mat9.value(2, 1) == 152);
	IsTrue(mat9.value(2, 2) == 176);
	IsTrue(mat9.value(2, 3) == 200);

	//mult vector
	NOU::NOU_MATH::Vec3i vec0(1, 2, 3);

	NOU::NOU_MATH::Vec3i vec1 = mat5 * vec0;
	IsTrue(vec1.value(0) == 14);
	IsTrue(vec1.value(1) == 32);
	IsTrue(vec1.value(2) == 50);

	//mult scale
	NOU::NOU_MATH::Mat3i mat10 = mat5 * 2;

	IsTrue(mat10.value(0, 0) == 2);
	IsTrue(mat10.value(0, 1) == 4);
	IsTrue(mat10.value(0, 2) == 6);
	IsTrue(mat10.value(1, 0) == 8);
	IsTrue(mat10.value(1, 1) == 10);
	IsTrue(mat10.value(1, 2) == 12);
	IsTrue(mat10.value(2, 0) == 14);
	IsTrue(mat10.value(2, 1) == 16);
	IsTrue(mat10.value(2, 2) == 18);

	NOU::NOU_MATH::Mat3i mat11 = mat5;
	mat11 *= 2;

	IsTrue(mat11 == mat10);

	//transpose
	NOU::NOU_MATH::Mat3i mat12 = mat5.transpose();

	IsTrue(mat12.value(0, 0) == 1);
	IsTrue(mat12.value(0, 1) == 4);
	IsTrue(mat12.value(0, 2) == 7);
	IsTrue(mat12.value(1, 0) == 2);
	IsTrue(mat12.value(1, 1) == 5);
	IsTrue(mat12.value(1, 2) == 8);
	IsTrue(mat12.value(2, 0) == 3);
	IsTrue(mat12.value(2, 1) == 6);
	IsTrue(mat12.value(2, 2) == 9);

	//copy
	IsTrue(mat5.copy() == mat5);

	NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(MathMat4)
{
	NOU::NOU_MATH::Mat4 mat0 = { { 1.0f, 2.0f, 3.0f, 4.0f }, { 5.0f, 6.0f, 7.0f, 8.0f }, { 9.0f, 10.0f, 11.0f, 12.0f }, { 13.0f, 14.0f, 15.0f, 16.0f } };

	NOU::NOU_MATH::Mat4 mat1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
	NOU::NOU_MATH::Mat4 mat2(2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f);

	//Check if the values are correct
	IsTrue(mat0.value(0, 0) == 1.0f);
	IsTrue(mat0.value(0, 1) == 2.0f);
	IsTrue(mat0.value(0, 2) == 3.0f);
	IsTrue(mat0.value(0, 3) == 4.0f);
	IsTrue(mat0.value(1, 0) == 5.0f);
	IsTrue(mat0.value(1, 1) == 6.0f);
	IsTrue(mat0.value(1, 2) == 7.0f);
	IsTrue(mat0.value(1, 3) == 8.0f);
	IsTrue(mat0.value(2, 0) == 9.0f);
	IsTrue(mat0.value(2, 1) == 10.0f);
	IsTrue(mat0.value(2, 2) == 11.0f);
	IsTrue(mat0.value(2, 3) == 12.0f);
	IsTrue(mat0.value(3, 0) == 13.0f);
	IsTrue(mat0.value(3, 1) == 14.0f);
	IsTrue(mat0.value(3, 2) == 15.0f);
	IsTrue(mat0.value(3, 3) == 16.0f);

	//Matrices have the same values; check if equal and unequal work and check if the 2. constructor works
	IsTrue(mat0 == mat1);
	IsTrue(mat0 != mat2);
	IsTrue(!(mat0 == mat2));
	IsTrue(mat0 == mat0);

	//zeroes
	IsTrue(NOU::NOU_MATH::Mat4::zeroes() == NOU::NOU_MATH::Mat4(0.0f, 0.0f, 0.0f, 0.0f,
		                                                        0.0f, 0.0f, 0.0f, 0.0f,
		                                                        0.0f, 0.0f, 0.0f, 0.0f,
		                                                        0.0f, 0.0f, 0.0f, 0.0f));

	//identity
	IsTrue(NOU::NOU_MATH::Mat4::identity() == NOU::NOU_MATH::Mat4(1.0f, 0.0f, 0.0f, 0.0f,
		                                                          0.0f, 1.0f, 0.0f, 0.0f,
		                                                          0.0f, 0.0f, 1.0f, 0.0f,
		                                                          0.0f, 0.0f, 0.0f, 1.0f));

	//add
	NOU::NOU_MATH::Mat4 mat3 = mat0 + mat2;

	IsTrue(mat3.value(0, 0) == 3.0f);
	IsTrue(mat3.value(0, 1) == 5.0f);
	IsTrue(mat3.value(0, 2) == 7.0f);
	IsTrue(mat3.value(0, 3) == 9.0f);
	IsTrue(mat3.value(1, 0) == 11.0f);
	IsTrue(mat3.value(1, 1) == 13.0f);
	IsTrue(mat3.value(1, 2) == 15.0f);
	IsTrue(mat3.value(1, 3) == 17.0f);
	IsTrue(mat3.value(2, 0) == 19.0f);
	IsTrue(mat3.value(2, 1) == 21.0f);
	IsTrue(mat3.value(2, 2) == 23.0f);
	IsTrue(mat3.value(2, 3) == 25.0f);
	IsTrue(mat3.value(3, 0) == 27.0f);
	IsTrue(mat3.value(3, 1) == 29.0f);
	IsTrue(mat3.value(3, 2) == 31.0f);
	IsTrue(mat3.value(3, 3) == 33.0f);

	IsTrue((mat0 += mat2) == mat3);

	//sub
	NOU::NOU_MATH::Mat4 mat4 = mat1 - mat2;

	IsTrue(mat4.value(0, 0) == -1.0f);
	IsTrue(mat4.value(0, 1) == -1.0f);
	IsTrue(mat4.value(0, 2) == -1.0f);
	IsTrue(mat4.value(0, 3) == -1.0f);
	IsTrue(mat4.value(1, 0) == -1.0f);
	IsTrue(mat4.value(1, 1) == -1.0f);
	IsTrue(mat4.value(1, 2) == -1.0f);
	IsTrue(mat4.value(1, 3) == -1.0f);
	IsTrue(mat4.value(2, 0) == -1.0f);
	IsTrue(mat4.value(2, 1) == -1.0f);
	IsTrue(mat4.value(2, 2) == -1.0f);
	IsTrue(mat4.value(2, 3) == -1.0f);
	IsTrue(mat4.value(3, 0) == -1.0f);
	IsTrue(mat4.value(3, 1) == -1.0f);
	IsTrue(mat4.value(3, 2) == -1.0f);
	IsTrue(mat4.value(3, 3) == -1.0f);

	IsTrue((mat1 -= mat2) == mat4);

	//mult
	NOU::NOU_MATH::Mat4 mat5(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
	NOU::NOU_MATH::Mat4 mat6(2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f);

	NOU::NOU_MATH::Mat4 mat7 = mat5 * mat6;

	IsTrue(mat7.value(0, 0) == 100.0f);
	IsTrue(mat7.value(0, 1) == 110.0f);
	IsTrue(mat7.value(0, 2) == 120.0f);
	IsTrue(mat7.value(0, 3) == 130.0f);
	IsTrue(mat7.value(1, 0) == 228.0f);
	IsTrue(mat7.value(1, 1) == 254.0f);
	IsTrue(mat7.value(1, 2) == 280.0f);
	IsTrue(mat7.value(1, 3) == 306.0f);
	IsTrue(mat7.value(2, 0) == 356.0f);
	IsTrue(mat7.value(2, 1) == 398.0f);
	IsTrue(mat7.value(2, 2) == 440.0f);
	IsTrue(mat7.value(2, 3) == 482.0f);
	IsTrue(mat7.value(3, 0) == 484.0f);
	IsTrue(mat7.value(3, 1) == 542.0f);
	IsTrue(mat7.value(3, 2) == 600.0f);
	IsTrue(mat7.value(3, 3) == 658.0f);

	//mult (2x2 * 2x2 special)
	NOU::NOU_MATH::Matrix<NOU::float32, 4, 5> mat8 = { { 1, 2, 3, 4, 5 }, { 6, 7, 8, 9, 10 }, { 11, 12, 13, 14, 15 }, { 16, 17, 18, 19, 20 } };
	NOU::NOU_MATH::Matrix<NOU::float32, 4, 5> mat9 = mat5 * mat8;

	IsTrue(mat9.value(0, 0) == 110.0f);
	IsTrue(mat9.value(0, 1) == 120.0f);
	IsTrue(mat9.value(0, 2) == 130.0f);
	IsTrue(mat9.value(0, 3) == 140.0f);
	IsTrue(mat9.value(0, 4) == 150.0f);
	IsTrue(mat9.value(1, 0) == 246.0f);
	IsTrue(mat9.value(1, 1) == 272.0f);
	IsTrue(mat9.value(1, 2) == 298.0f);
	IsTrue(mat9.value(1, 3) == 324.0f);
	IsTrue(mat9.value(1, 4) == 350.0f);
	IsTrue(mat9.value(2, 0) == 382.0f);
	IsTrue(mat9.value(2, 1) == 424.0f);
	IsTrue(mat9.value(2, 2) == 466.0f);
	IsTrue(mat9.value(2, 3) == 508.0f);
	IsTrue(mat9.value(2, 4) == 550.0f);
	IsTrue(mat9.value(3, 0) == 518.0f);
	IsTrue(mat9.value(3, 1) == 576.0f);
	IsTrue(mat9.value(3, 2) == 634.0f);
	IsTrue(mat9.value(3, 3) == 692.0f);
	IsTrue(mat9.value(3, 4) == 750.0f);

	//mult vector
	NOU::NOU_MATH::Vec4 vec0(1.0f, 2.0f, 3.0f, 4.0f);

	NOU::NOU_MATH::Vec4 vec1 = mat5 * vec0;
	IsTrue(vec1.value(0) == 30.0f);
	IsTrue(vec1.value(1) == 70.0f);
	IsTrue(vec1.value(2) == 110.0f);
	IsTrue(vec1.value(3) == 150.0f);

	//mult scale
	NOU::NOU_MATH::Mat4 mat10 = mat5 * 2;

	IsTrue(mat10.value(0, 0) == 2.0f);
	IsTrue(mat10.value(0, 1) == 4.0f);
	IsTrue(mat10.value(0, 2) == 6.0f);
	IsTrue(mat10.value(0, 3) == 8.0f);
	IsTrue(mat10.value(1, 0) == 10.0f);
	IsTrue(mat10.value(1, 1) == 12.0f);
	IsTrue(mat10.value(1, 2) == 14.0f);
	IsTrue(mat10.value(1, 3) == 16.0f);
	IsTrue(mat10.value(2, 0) == 18.0f);
	IsTrue(mat10.value(2, 1) == 20.0f);
	IsTrue(mat10.value(2, 2) == 22.0f);
	IsTrue(mat10.value(2, 3) == 24.0f);
	IsTrue(mat10.value(3, 0) == 26.0f);
	IsTrue(mat10.value(3, 1) == 28.0f);
	IsTrue(mat10.value(3, 2) == 30.0f);
	IsTrue(mat10.value(3, 3) == 32.0f);

	NOU::NOU_MATH::Mat4 mat11 = mat5;
	mat11 *= 2;

	IsTrue(mat11 == mat10);

	//transpose
	NOU::NOU_MATH::Mat4 mat12 = mat5.transpose();

	IsTrue(mat12.value(0, 0) == 1.0f);
	IsTrue(mat12.value(0, 1) == 5.0f);
	IsTrue(mat12.value(0, 2) == 9.0f);
	IsTrue(mat12.value(0, 3) == 13.0f);
	IsTrue(mat12.value(1, 0) == 2.0f);
	IsTrue(mat12.value(1, 1) == 6.0f);
	IsTrue(mat12.value(1, 2) == 10.0f);
	IsTrue(mat12.value(1, 3) == 14.0f);
	IsTrue(mat12.value(2, 0) == 3.0f);
	IsTrue(mat12.value(2, 1) == 7.0f);
	IsTrue(mat12.value(2, 2) == 11.0f);
	IsTrue(mat12.value(2, 3) == 15.0f);
	IsTrue(mat12.value(3, 0) == 4.0f);
	IsTrue(mat12.value(3, 1) == 8.0f);
	IsTrue(mat12.value(3, 2) == 12.0f);
	IsTrue(mat12.value(3, 3) == 16.0f);

	//copy
	IsTrue(mat5.copy() == mat5);

	NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(MathMat4i)
{
	NOU::NOU_MATH::Mat4i mat0 = { { 1, 2, 3, 4 },{ 5, 6, 7, 8 },{ 9, 10, 11, 12 },{ 13, 14, 15, 16 } };

	NOU::NOU_MATH::Mat4i mat1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	NOU::NOU_MATH::Mat4i mat2(2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17);

	//Check if the values are correct
	IsTrue(mat0.value(0, 0) == 1);
	IsTrue(mat0.value(0, 1) == 2);
	IsTrue(mat0.value(0, 2) == 3);
	IsTrue(mat0.value(0, 3) == 4);
	IsTrue(mat0.value(1, 0) == 5);
	IsTrue(mat0.value(1, 1) == 6);
	IsTrue(mat0.value(1, 2) == 7);
	IsTrue(mat0.value(1, 3) == 8);
	IsTrue(mat0.value(2, 0) == 9);
	IsTrue(mat0.value(2, 1) == 10);
	IsTrue(mat0.value(2, 2) == 11);
	IsTrue(mat0.value(2, 3) == 12);
	IsTrue(mat0.value(3, 0) == 13);
	IsTrue(mat0.value(3, 1) == 14);
	IsTrue(mat0.value(3, 2) == 15);
	IsTrue(mat0.value(3, 3) == 16);

	//Matrices have the same values; check if equal and unequal work and check if the 2. constructor works
	IsTrue(mat0 == mat1);
	IsTrue(mat0 != mat2);
	IsTrue(!(mat0 == mat2));
	IsTrue(mat0 == mat0);

	//zeroes
	IsTrue(NOU::NOU_MATH::Mat4i::zeroes() == NOU::NOU_MATH::Mat4i(0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0));

	//identity
	IsTrue(NOU::NOU_MATH::Mat4i::identity() == NOU::NOU_MATH::Mat4i(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1));

	//add
	NOU::NOU_MATH::Mat4i mat3 = mat0 + mat2;

	IsTrue(mat3.value(0, 0) == 3);
	IsTrue(mat3.value(0, 1) == 5);
	IsTrue(mat3.value(0, 2) == 7);
	IsTrue(mat3.value(0, 3) == 9);
	IsTrue(mat3.value(1, 0) == 11);
	IsTrue(mat3.value(1, 1) == 13);
	IsTrue(mat3.value(1, 2) == 15);
	IsTrue(mat3.value(1, 3) == 17);
	IsTrue(mat3.value(2, 0) == 19);
	IsTrue(mat3.value(2, 1) == 21);
	IsTrue(mat3.value(2, 2) == 23);
	IsTrue(mat3.value(2, 3) == 25);
	IsTrue(mat3.value(3, 0) == 27);
	IsTrue(mat3.value(3, 1) == 29);
	IsTrue(mat3.value(3, 2) == 31);
	IsTrue(mat3.value(3, 3) == 33);

	IsTrue((mat0 += mat2) == mat3);

	//sub
	NOU::NOU_MATH::Mat4i mat4 = mat1 - mat2;

	IsTrue(mat4.value(0, 0) == -1);
	IsTrue(mat4.value(0, 1) == -1);
	IsTrue(mat4.value(0, 2) == -1);
	IsTrue(mat4.value(0, 3) == -1);
	IsTrue(mat4.value(1, 0) == -1);
	IsTrue(mat4.value(1, 1) == -1);
	IsTrue(mat4.value(1, 2) == -1);
	IsTrue(mat4.value(1, 3) == -1);
	IsTrue(mat4.value(2, 0) == -1);
	IsTrue(mat4.value(2, 1) == -1);
	IsTrue(mat4.value(2, 2) == -1);
	IsTrue(mat4.value(2, 3) == -1);
	IsTrue(mat4.value(3, 0) == -1);
	IsTrue(mat4.value(3, 1) == -1);
	IsTrue(mat4.value(3, 2) == -1);
	IsTrue(mat4.value(3, 3) == -1);

	IsTrue((mat1 -= mat2) == mat4);

	//mult
	NOU::NOU_MATH::Mat4i mat5(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	NOU::NOU_MATH::Mat4i mat6(2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17);

	NOU::NOU_MATH::Mat4i mat7 = mat5 * mat6;

	IsTrue(mat7.value(0, 0) == 100);
	IsTrue(mat7.value(0, 1) == 110);
	IsTrue(mat7.value(0, 2) == 120);
	IsTrue(mat7.value(0, 3) == 130);
	IsTrue(mat7.value(1, 0) == 228);
	IsTrue(mat7.value(1, 1) == 254);
	IsTrue(mat7.value(1, 2) == 280);
	IsTrue(mat7.value(1, 3) == 306);
	IsTrue(mat7.value(2, 0) == 356);
	IsTrue(mat7.value(2, 1) == 398);
	IsTrue(mat7.value(2, 2) == 440);
	IsTrue(mat7.value(2, 3) == 482);
	IsTrue(mat7.value(3, 0) == 484);
	IsTrue(mat7.value(3, 1) == 542);
	IsTrue(mat7.value(3, 2) == 600);
	IsTrue(mat7.value(3, 3) == 658);

	//mult (2x2 * 2x2 special)
	NOU::NOU_MATH::Matrix<NOU::int32, 4, 5> mat8 = { { 1, 2, 3, 4, 5 },{ 6, 7, 8, 9, 10 },{ 11, 12, 13, 14, 15 },{ 16, 17, 18, 19, 20 } };
	NOU::NOU_MATH::Matrix<NOU::int32, 4, 5> mat9 = mat5 * mat8;

	IsTrue(mat9.value(0, 0) == 110);
	IsTrue(mat9.value(0, 1) == 120);
	IsTrue(mat9.value(0, 2) == 130);
	IsTrue(mat9.value(0, 3) == 140);
	IsTrue(mat9.value(0, 4) == 150);
	IsTrue(mat9.value(1, 0) == 246);
	IsTrue(mat9.value(1, 1) == 272);
	IsTrue(mat9.value(1, 2) == 298);
	IsTrue(mat9.value(1, 3) == 324);
	IsTrue(mat9.value(1, 4) == 350);
	IsTrue(mat9.value(2, 0) == 382);
	IsTrue(mat9.value(2, 1) == 424);
	IsTrue(mat9.value(2, 2) == 466);
	IsTrue(mat9.value(2, 3) == 508);
	IsTrue(mat9.value(2, 4) == 550);
	IsTrue(mat9.value(3, 0) == 518);
	IsTrue(mat9.value(3, 1) == 576);
	IsTrue(mat9.value(3, 2) == 634);
	IsTrue(mat9.value(3, 3) == 692);
	IsTrue(mat9.value(3, 4) == 750);

	//mult vector
	NOU::NOU_MATH::Vec4i vec0(1, 2, 3, 4);

	NOU::NOU_MATH::Vec4i vec1 = mat5 * vec0;
	IsTrue(vec1.value(0) == 30);
	IsTrue(vec1.value(1) == 70);
	IsTrue(vec1.value(2) == 110);
	IsTrue(vec1.value(3) == 150);

	//mult scale
	NOU::NOU_MATH::Mat4i mat10 = mat5 * 2;

	IsTrue(mat10.value(0, 0) == 2);
	IsTrue(mat10.value(0, 1) == 4);
	IsTrue(mat10.value(0, 2) == 6);
	IsTrue(mat10.value(0, 3) == 8);
	IsTrue(mat10.value(1, 0) == 10);
	IsTrue(mat10.value(1, 1) == 12);
	IsTrue(mat10.value(1, 2) == 14);
	IsTrue(mat10.value(1, 3) == 16);
	IsTrue(mat10.value(2, 0) == 18);
	IsTrue(mat10.value(2, 1) == 20);
	IsTrue(mat10.value(2, 2) == 22);
	IsTrue(mat10.value(2, 3) == 24);
	IsTrue(mat10.value(3, 0) == 26);
	IsTrue(mat10.value(3, 1) == 28);
	IsTrue(mat10.value(3, 2) == 30);
	IsTrue(mat10.value(3, 3) == 32);

	NOU::NOU_MATH::Mat4i mat11 = mat5;
	mat11 *= 2;

	IsTrue(mat11 == mat10);

	//transpose
	NOU::NOU_MATH::Mat4i mat12 = mat5.transpose();

	IsTrue(mat12.value(0, 0) == 1);
	IsTrue(mat12.value(0, 1) == 5);
	IsTrue(mat12.value(0, 2) == 9);
	IsTrue(mat12.value(0, 3) == 13);
	IsTrue(mat12.value(1, 0) == 2);
	IsTrue(mat12.value(1, 1) == 6);
	IsTrue(mat12.value(1, 2) == 10);
	IsTrue(mat12.value(1, 3) == 14);
	IsTrue(mat12.value(2, 0) == 3);
	IsTrue(mat12.value(2, 1) == 7);
	IsTrue(mat12.value(2, 2) == 11);
	IsTrue(mat12.value(2, 3) == 15);
	IsTrue(mat12.value(3, 0) == 4);
	IsTrue(mat12.value(3, 1) == 8);
	IsTrue(mat12.value(3, 2) == 12);
	IsTrue(mat12.value(3, 3) == 16);

	//copy
	IsTrue(mat5.copy() == mat5);

	NOU_CHECK_ERROR_HANDLER;
}

TEST_METHOD(MathMat5)
{
	NOU::NOU_MATH::Matrix<NOU::float32, 5, 4> mat0 = { { 1.0f, 2.0f, 3.0f, 4.0f },
	                                                   { 5.0f, 6.0f, 7.0f, 8.0f },
	                                                   { 9.0f, 10.0f, 11.0f, 12.0f },
	                                                   { 13.0f, 14.0f, 15.0f, 16.0f },
	                                                   { 17.0f, 18.0f, 19.0f, 20.0f } };

	NOU::NOU_MATH::Matrix<NOU::float32, 5, 4> mat1 = { { 1.0f, 2.0f, 3.0f, 4.0f },
	                                                   { 5.0f, 6.0f, 7.0f, 8.0f },
	                                                   { 9.0f, 10.0f, 11.0f, 12.0f },
	                                                   { 13.0f, 14.0f, 15.0f, 16.0f },
	                                                   { 17.0f, 18.0f, 19.0f, 20.0f } };

	NOU::NOU_MATH::Matrix<NOU::float32, 5, 4> mat2 = { { 2.0f, 3.0f, 4.0f, 5.0f },
	                                                   { 6.0f, 7.0f, 8.0f, 9.0f },
	                                                   { 10.0f, 11.0f, 12.0f, 13.0f },
	                                                   { 14.0f, 15.0f, 16.0f, 17.0f },
	                                                   { 18.0f, 19.0f, 20.0f, 21.0f } };

	//Check if the values are correct
	IsTrue(mat0.value(0, 0) == 1.0f);
	IsTrue(mat0.value(0, 1) == 2.0f);
	IsTrue(mat0.value(0, 2) == 3.0f);
	IsTrue(mat0.value(0, 3) == 4.0f);
	IsTrue(mat0.value(1, 0) == 5.0f);
	IsTrue(mat0.value(1, 1) == 6.0f);
	IsTrue(mat0.value(1, 2) == 7.0f);
	IsTrue(mat0.value(1, 3) == 8.0f);
	IsTrue(mat0.value(2, 0) == 9.0f);
	IsTrue(mat0.value(2, 1) == 10.0f);
	IsTrue(mat0.value(2, 2) == 11.0f);
	IsTrue(mat0.value(2, 3) == 12.0f);
	IsTrue(mat0.value(3, 0) == 13.0f);
	IsTrue(mat0.value(3, 1) == 14.0f);
	IsTrue(mat0.value(3, 2) == 15.0f);
	IsTrue(mat0.value(3, 3) == 16.0f);
	IsTrue(mat0.value(4, 0) == 17.0f);
	IsTrue(mat0.value(4, 1) == 18.0f);
	IsTrue(mat0.value(4, 2) == 19.0f);
	IsTrue(mat0.value(4, 3) == 20.0f);

	//Matrices have the same values; check if equal and unequal work and check if the 2. constructor works
	IsTrue(mat0 == mat1);
	IsTrue(mat0 != mat2);
	IsTrue(!(mat0 == mat2));
	IsTrue(mat0 == mat0);

	//zeroes
	NOU::NOU_MATH::Matrix<NOU::float32, 5, 4> matZeroes = NOU::NOU_MATH::Matrix<NOU::float32, 5, 4>::zeroes();

	IsTrue(matZeroes.value(0, 0) == 0.0f);
	IsTrue(matZeroes.value(0, 1) == 0.0f);
	IsTrue(matZeroes.value(0, 2) == 0.0f);
	IsTrue(matZeroes.value(0, 3) == 0.0f);
	IsTrue(matZeroes.value(1, 0) == 0.0f);
	IsTrue(matZeroes.value(1, 1) == 0.0f);
	IsTrue(matZeroes.value(1, 2) == 0.0f);
	IsTrue(matZeroes.value(1, 3) == 0.0f);
	IsTrue(matZeroes.value(2, 0) == 0.0f);
	IsTrue(matZeroes.value(2, 1) == 0.0f);
	IsTrue(matZeroes.value(2, 2) == 0.0f);
	IsTrue(matZeroes.value(2, 3) == 0.0f);
	IsTrue(matZeroes.value(3, 0) == 0.0f);
	IsTrue(matZeroes.value(3, 1) == 0.0f);
	IsTrue(matZeroes.value(3, 2) == 0.0f);
	IsTrue(matZeroes.value(3, 3) == 0.0f);
	IsTrue(matZeroes.value(4, 0) == 0.0f);
	IsTrue(matZeroes.value(4, 1) == 0.0f);
	IsTrue(matZeroes.value(4, 2) == 0.0f);
	IsTrue(matZeroes.value(4, 3) == 0.0f);

	//identity
	NOU::NOU_MATH::Matrix<NOU::float32, 5, 4> matIden = NOU::NOU_MATH::Matrix<NOU::float32, 5, 4>::identity();

	IsTrue(matIden.value(0, 0) == 1.0f);
	IsTrue(matIden.value(0, 1) == 0.0f);
	IsTrue(matIden.value(0, 2) == 0.0f);
	IsTrue(matIden.value(0, 3) == 0.0f);
	IsTrue(matIden.value(1, 0) == 0.0f);
	IsTrue(matIden.value(1, 1) == 1.0f);
	IsTrue(matIden.value(1, 2) == 0.0f);
	IsTrue(matIden.value(1, 3) == 0.0f);
	IsTrue(matIden.value(2, 0) == 0.0f);
	IsTrue(matIden.value(2, 1) == 0.0f);
	IsTrue(matIden.value(2, 2) == 1.0f);
	IsTrue(matIden.value(2, 3) == 0.0f);
	IsTrue(matIden.value(3, 0) == 0.0f);
	IsTrue(matIden.value(3, 1) == 0.0f);
	IsTrue(matIden.value(3, 2) == 0.0f);
	IsTrue(matIden.value(3, 3) == 1.0f);
	IsTrue(matIden.value(4, 0) == 0.0f);
	IsTrue(matIden.value(4, 1) == 0.0f);
	IsTrue(matIden.value(4, 2) == 0.0f);
	IsTrue(matIden.value(4, 3) == 0.0f);

	//add
	NOU::NOU_MATH::Matrix<NOU::float32, 5, 4> mat3 = mat0 + mat2;

	IsTrue(mat3.value(0, 0) == 3.0f);
	IsTrue(mat3.value(0, 1) == 5.0f);
	IsTrue(mat3.value(0, 2) == 7.0f);
	IsTrue(mat3.value(0, 3) == 9.0f);
	IsTrue(mat3.value(1, 0) == 11.0f);
	IsTrue(mat3.value(1, 1) == 13.0f);
	IsTrue(mat3.value(1, 2) == 15.0f);
	IsTrue(mat3.value(1, 3) == 17.0f);
	IsTrue(mat3.value(2, 0) == 19.0f);
	IsTrue(mat3.value(2, 1) == 21.0f);
	IsTrue(mat3.value(2, 2) == 23.0f);
	IsTrue(mat3.value(2, 3) == 25.0f);
	IsTrue(mat3.value(3, 0) == 27.0f);
	IsTrue(mat3.value(3, 1) == 29.0f);
	IsTrue(mat3.value(3, 2) == 31.0f);
	IsTrue(mat3.value(3, 3) == 33.0f);
	IsTrue(mat3.value(4, 0) == 35.0f);
	IsTrue(mat3.value(4, 1) == 37.0f);
	IsTrue(mat3.value(4, 2) == 39.0f);
	IsTrue(mat3.value(4, 3) == 41.0f);

	IsTrue((mat0 += mat2) == mat3);

	//sub
	NOU::NOU_MATH::Matrix<NOU::float32, 5, 4> mat4 = mat1 - mat2;

	IsTrue(mat4.value(0, 0) == -1.0f);
	IsTrue(mat4.value(0, 1) == -1.0f);
	IsTrue(mat4.value(0, 2) == -1.0f);
	IsTrue(mat4.value(0, 3) == -1.0f);
	IsTrue(mat4.value(1, 0) == -1.0f);
	IsTrue(mat4.value(1, 1) == -1.0f);
	IsTrue(mat4.value(1, 2) == -1.0f);
	IsTrue(mat4.value(1, 3) == -1.0f);
	IsTrue(mat4.value(2, 0) == -1.0f);
	IsTrue(mat4.value(2, 1) == -1.0f);
	IsTrue(mat4.value(2, 2) == -1.0f);
	IsTrue(mat4.value(2, 3) == -1.0f);
	IsTrue(mat4.value(3, 0) == -1.0f);
	IsTrue(mat4.value(3, 1) == -1.0f);
	IsTrue(mat4.value(3, 2) == -1.0f);
	IsTrue(mat4.value(3, 3) == -1.0f);
	IsTrue(mat4.value(4, 0) == -1.0f);
	IsTrue(mat4.value(4, 1) == -1.0f);
	IsTrue(mat4.value(4, 2) == -1.0f);
	IsTrue(mat4.value(4, 3) == -1.0f);

	IsTrue((mat1 -= mat2) == mat4);

	//mult
	NOU::NOU_MATH::Matrix<NOU::float32, 5, 5> mat5 = { { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f },
	                                                   { 6.0f, 7.0f, 8.0f, 9.0f, 10.0f },
	                                                   { 11.0f, 12.0f, 13.0f, 14.0f, 15.0f },
	                                                   { 16.0f, 17.0f, 18.0f, 19.0f, 20.0f },
	                                                   { 21.0f, 22.0f, 23.0f, 24.0f, 25.0f } };

	NOU::NOU_MATH::Matrix<NOU::float32, 5, 4> mat6 = { { 2.0f, 3.0f, 4.0f, 5.0f },
	                                                   { 6.0f, 7.0f, 8.0f, 9.0f },
	                                                   { 10.0f, 11.0f, 12.0f, 13.0f },
	                                                   { 14.0f, 15.0f, 16.0f, 17.0f },
	                                                   { 18.0f, 19.0f, 20.0f, 21.0f } };

	NOU::NOU_MATH::Matrix<NOU::float32, 5, 4> mat7 = mat5 * mat6;

	IsTrue(mat7.value(0, 0) == 190.0f);
	IsTrue(mat7.value(0, 1) == 205.0f);
	IsTrue(mat7.value(0, 2) == 220.0f);
	IsTrue(mat7.value(0, 3) == 235.0f);
	IsTrue(mat7.value(1, 0) == 440.0f);
	IsTrue(mat7.value(1, 1) == 480.0f);
	IsTrue(mat7.value(1, 2) == 520.0f);
	IsTrue(mat7.value(1, 3) == 560.0f);
	IsTrue(mat7.value(2, 0) == 690.0f);
	IsTrue(mat7.value(2, 1) == 755.0f);
	IsTrue(mat7.value(2, 2) == 820.0f);
	IsTrue(mat7.value(2, 3) == 885.0f);
	IsTrue(mat7.value(3, 0) == 940.0f);
	IsTrue(mat7.value(3, 1) == 1030.0f);
	IsTrue(mat7.value(3, 2) == 1120.0f);
	IsTrue(mat7.value(3, 3) == 1210.0f);
	IsTrue(mat7.value(4, 0) == 1190.0f);
	IsTrue(mat7.value(4, 1) == 1305.0f);
	IsTrue(mat7.value(4, 2) == 1420.0f);
	IsTrue(mat7.value(4, 3) == 1535.0f);

	//mult vector
	NOU::NOU_MATH::Vector<NOU::float32, 5> vec0 = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };

	NOU::NOU_MATH::Vector<NOU::float32, 5> vec1 = mat5 * vec0;
	IsTrue(vec1.value(0) == 55.0f);
	IsTrue(vec1.value(1) == 130.0f);
	IsTrue(vec1.value(2) == 205.0f);
	IsTrue(vec1.value(3) == 280.0f);
	IsTrue(vec1.value(4) == 355.0f);

	//mult scale
	NOU::NOU_MATH::Matrix<NOU::float32, 5, 5> mat10 = mat5 * 2;

	IsTrue(mat10.value(0, 0) == 02.0f);
	IsTrue(mat10.value(0, 1) == 04.0f);
	IsTrue(mat10.value(0, 2) == 06.0f);
	IsTrue(mat10.value(0, 3) == 08.0f);
	IsTrue(mat10.value(0, 4) == 10.0f);
	IsTrue(mat10.value(1, 0) == 12.0f);
	IsTrue(mat10.value(1, 1) == 14.0f);
	IsTrue(mat10.value(1, 2) == 16.0f);
	IsTrue(mat10.value(1, 3) == 18.0f);
	IsTrue(mat10.value(1, 4) == 20.0f);
	IsTrue(mat10.value(2, 0) == 22.0f);
	IsTrue(mat10.value(2, 1) == 24.0f);
	IsTrue(mat10.value(2, 2) == 26.0f);
	IsTrue(mat10.value(2, 3) == 28.0f);
	IsTrue(mat10.value(2, 4) == 30.0f);
	IsTrue(mat10.value(3, 0) == 32.0f);
	IsTrue(mat10.value(3, 1) == 34.0f);
	IsTrue(mat10.value(3, 2) == 36.0f);
	IsTrue(mat10.value(3, 3) == 38.0f);
	IsTrue(mat10.value(3, 4) == 40.0f);
	IsTrue(mat10.value(4, 0) == 42.0f);
	IsTrue(mat10.value(4, 1) == 44.0f);
	IsTrue(mat10.value(4, 2) == 46.0f);
	IsTrue(mat10.value(4, 3) == 48.0f);
	IsTrue(mat10.value(4, 4) == 50.0f);

	NOU::NOU_MATH::Matrix<NOU::float32, 5, 5> mat11 = mat5;
	mat11 *= 2;

	IsTrue(mat11 == mat10);

	//transpose
	NOU::NOU_MATH::Matrix<NOU::float32, 5, 5> mat12 = mat5.transpose();

	IsTrue(mat12.value(0, 0) == mat5.value(0, 0));
	IsTrue(mat12.value(0, 1) == mat5.value(1, 0));
	IsTrue(mat12.value(0, 2) == mat5.value(2, 0));
	IsTrue(mat12.value(0, 3) == mat5.value(3, 0));
	IsTrue(mat12.value(0, 4) == mat5.value(4, 0));
	IsTrue(mat12.value(1, 0) == mat5.value(0, 1));
	IsTrue(mat12.value(1, 1) == mat5.value(1, 1));
	IsTrue(mat12.value(1, 2) == mat5.value(2, 1));
	IsTrue(mat12.value(1, 3) == mat5.value(3, 1));
	IsTrue(mat12.value(1, 4) == mat5.value(4, 1));
	IsTrue(mat12.value(2, 0) == mat5.value(0, 2));
	IsTrue(mat12.value(2, 1) == mat5.value(1, 2));
	IsTrue(mat12.value(2, 2) == mat5.value(2, 2));
	IsTrue(mat12.value(2, 3) == mat5.value(3, 2));
	IsTrue(mat12.value(2, 4) == mat5.value(4, 2));
	IsTrue(mat12.value(3, 0) == mat5.value(0, 3));
	IsTrue(mat12.value(3, 1) == mat5.value(1, 3));
	IsTrue(mat12.value(3, 2) == mat5.value(2, 3));
	IsTrue(mat12.value(3, 3) == mat5.value(3, 3));
	IsTrue(mat12.value(3, 4) == mat5.value(4, 3));
	IsTrue(mat12.value(4, 0) == mat5.value(0, 4));
	IsTrue(mat12.value(4, 1) == mat5.value(1, 4));
	IsTrue(mat12.value(4, 2) == mat5.value(2, 4));
	IsTrue(mat12.value(4, 3) == mat5.value(3, 4));
	IsTrue(mat12.value(4, 4) == mat5.value(4, 4));

	//copy
	IsTrue(mat5.copy() == mat5);

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