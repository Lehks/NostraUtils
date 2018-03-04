#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\BinaryHeap.hpp"
#include "nostrautils\dat_alg\HashMap.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include <string>
#include <iostream>

class foo {
public:
	std::string name = "Hallo";

	foo(std::string name);
};

int main()
{
	foo f1("Dennis");
	foo f2("Mahan");
	foo f3("Leslie");

	NOU::NOU_DAT_ALG::Vector<foo> entrySetVec(1);
	NOU::NOU_DAT_ALG::Vector<NOU::sizeType> keySetVec(1);

	NOU::NOU_DAT_ALG::HashMap<NOU::sizeType, foo> hm(100);

	hm.map(15, f1);
	hm.map(10, f2);
	hm.map(17, f3);

	entrySetVec = hm.entrySet();
	keySetVec = hm.keySet();

	for (int i = 0; i < entrySetVec.size(); i++)
	{
		std::cout << keySetVec[i] << " " <<entrySetVec[i].name << std::endl;
	}

	system("pause");
}

foo::foo(std::string name)	:
	name(name)
{
}
