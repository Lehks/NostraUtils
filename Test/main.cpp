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
	NOU::NOU_DAT_ALG::HashMap<NOU::char8, NOU::int32> hm(100);
	NOU::NOU_DAT_ALG::HashMap<NOU::char8, NOU::int32> hm1(100);
	NOU::NOU_DAT_ALG::String<NOU::char8> str = "The quick onyx goblin jumps over the lazy dwarf";
	NOU::boolean b;

	//Assert::AreEqual(hm.isEmpty(), true);

	for (NOU::sizeType i = 0; i < str.size(); i++) {
		b = hm.map(str.at(i), 1);
	}

	//Assert::AreEqual(hm.isEmpty(), false);

	for (int i = 0; i < str.size(); i++) {
		//Assert::AreEqual(hm.get(str.at(i)), 1);
	}
	NOU::char8 k = 'h';

	NOU::int32 count = hm.remove(k);
	//Assert::AreEqual(2, count);

	//Assert::AreEqual(NULL, hm.get(k));


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

	cout << hm1.get(' ') << endl;
	system("pause");
}