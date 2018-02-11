#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\BinaryHeap.hpp"
#include "nostrautils\dat_alg\ObjectPool.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace NOU;
using namespace NOU_CORE;
using namespace NOU_DAT_ALG;

void callback(const ErrorLocation&)
{
	__debugbreak();
}

class A
{
private:
	int i;
public:
	A() = default;
	A(int i) : i(i) {}
	A(const A&) = delete;
	A(A&&) = default;

	int get() const { return i; }
};

int main()
{
	ObjectPool<A> objectPool;

	objectPool.pushObject(A());
	objectPool.pushObject(A());
	objectPool.pushObject(A());

	A& a = objectPool.get();
	A& a1 = objectPool.get();
	A& a2 = objectPool.get();

	objectPool.giveBack(a);

	while (getErrorHandler().getErrorCount() != 0)
		std::cout << getErrorHandler().popError().getName() << std::endl;

	std::cin.get();
}