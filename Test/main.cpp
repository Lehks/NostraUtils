#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\BinaryHeap.hpp"
#include <iostream>


int main()
{

	NOU::NOU_DAT_ALG::BinaryHeap<NOU::int32> b;

	b.enqueue(10, 0);
	b.enqueue(11, 1);
	b.enqueue(12, 2);
	b.enqueue(13, 3);
	b.enqueue(14, 0);
	b.enqueue(15, 3);

	for (int i = 0; i < b.size(); i++)
	{
		std::cout << b.at(i);
		std::cout << " " << b.priorityAt(i) << std::endl;
	}

	b.dequeue();

	for (int i = 0; i < b.size(); i++)
	{
		std::cout << b.at(i);
		std::cout << " " << b.priorityAt(i) << std::endl;
	}

	b.decreaseKey(2, 154);

	for (int i = 0; i < b.size(); i++)
	{
		std::cout << b.at(i);
		std::cout << " " << b.priorityAt(i) << std::endl;
	}

	system("pause");
}
