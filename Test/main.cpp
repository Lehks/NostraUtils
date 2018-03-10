#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\BinaryHeap.hpp"
#include "nostrautils\dat_alg\HashMap.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include <string>
#include <iostream>

int main()
{
	NOU::NOU_DAT_ALG::BinaryHeap<NOU::uint32> b(15);

	b.enqueue(10, 1);
	b.enqueue(11, 2);
	b.enqueue(12, 3);
	b.enqueue(13, 4);
	b.enqueue(14, 1);
	b.enqueue(15, 4);

	for (int i = 0; i < b.size(); i++)
	{
		std::cout << b.priorityAt(i) << " " << b.at(i) << std::endl;
	}

	b.dequeue();
	b.decreaseKey(2, 2);

	for (int i = 0; i < b.size(); i++)
	{
		std::cout << b.priorityAt(i) << " " << b.at(i) << std::endl;
	}

	system("pause");
}

