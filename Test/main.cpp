#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\BinaryHeap.hpp"
#include "nostrautils\dat_alg\ObjectPool.hpp"
#include <iostream>

using namespace NOU;
using namespace NOU_CORE;
using namespace NOU_DAT_ALG;

int main()
{
	ObjectPool<A> objectPool(3);

	objectPool.pushObject(A());
	objectPool.pushObject(A());
	objectPool.pushObject(A());

	A& a = objectPool.get();
	A& a1 = objectPool.get();
	A& a2 = objectPool.get();

	objectPool.giveBack(a);
	objectPool.giveBack(a1);
	objectPool.giveBack(a2);

	while (getErrorHandler().getErrorCount() != 0)
		std::cout << getErrorHandler().popError().getName() << std::endl;

	std::cin.get();
}