#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include <iostream>
#include <vector>

using namespace NOU;
using namespace NOU_CORE;
using namespace NOU_DAT_ALG;

class A
{
public:
	A()
	{}

	A(const A&) = delete;

	A(A&&)
	{}
};

byte b[sizeof(A)] alignas (A);

template<typename... ARGS>
void set(ARGS&&... a)
{
	new (b) A(move(a)...);
}

int main()
{
	//A a;
	//set(a);

//	Vector<A> vec;
}