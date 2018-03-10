#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\BinaryHeap.hpp"
#include "nostrautils\dat_alg\HashMap.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include <string>
#include <iostream>

using namespace std;

int main()
{
	NOU::NOU_DAT_ALG::HashMap<NOU::int32, NOU::int32> cm(100);

	cm.map(5, 1);
	cm.map(41, 2);
	cm.map(10, 3);
	cm.map(49875, 4);

	NOU::NOU_DAT_ALG::Vector<NOU::int32> c;

	c = cm.entrySet();

	for (int i = 0; i < cm.size(); i++)
	{
		std::cout << c[i] << std::endl;
	}

	NOU::NOU_DAT_ALG::Vector<NOU::int32> a;

	a = cm.keySet();

	for (int i = 0; i < cm.size(); i++)
	{
		std::cout << a[i] << std::endl;
	}

	system("pause");
}