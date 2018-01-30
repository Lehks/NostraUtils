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

//	A(const A&) {std::cout << "Lol." << std::endl;};

	A(const A&) = delete;

	A(A&&)
	{}
};

byte b[sizeof(A)] alignas (A);

template<typename T, typename... ARGS>
void set(ARGS&&... a)
{
	T t(NOU_CORE::move(a)...);
}

int main()
{
	A a;
	set<A>(a);
	/*
	Vector<A> vec;

	A a0;
	A a1;
	A a2;

	vec.push(move(a0));
	vec.insert(move(a1), 0);
	vec.emplace(0, move(a2));
	*/
}