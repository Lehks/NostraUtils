#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\mem_mngt\Pointer.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace NOU;
using namespace NOU_CORE;
using namespace NOU_DAT_ALG;

class A
{
public:
	A() = default;

//	A(const A&) 
//	{
//		std::cout << "Cpy" << std::endl;
//	};

	A(const A&) = delete;

	A(A&&) = default;

//	A(const A&) = delete;

//	A(A&&) = default;

/*private:
	A(const A&) { }*/
};

byte bytes[sizeof(A)] alignas(A);

template<typename... ARGS>
void set(ARGS&& ...args)
{
	new (bytes) A(move(args)...);
}

#ifndef VEC_TEST
void vecTest()
{
	//A a;
	//set(a);

	
	//vec.emplace(0, move(a2));
}

void vfTableTest()
{}

#else

void vecTest()
{}

void vfTableTest()
{
	NOU::NOU_MEM_MNGT::UniquePtr<int> uPtr(new int(5), NOU::NOU_MEM_MNGT::defaultDeleter);

	std::cout << *uPtr << std::endl;
}

#endif

int main()
{
//	std::vector<A> stdVec;
//	stdVec.reserve(5);
//	stdVec.push_back(A());

	Vector<A> vec;
	
	A a;
	vec.insert(0, A());
	vec.pushBack(A());
	vec.push(A());
	vec.emplace(0, A());


	std::cin.get();
}