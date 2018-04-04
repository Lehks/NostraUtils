#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\Hashing.hpp"

#include <iostream>
#include <ctime>

using namespace std;
using namespace NOU;
using namespace NOU_DAT_ALG;

int main()
{
	NOU::byte b0[] = { 55, 245, 987, 14, 7634 };
	NOU::byte b1[] = { 55, 245, 987, 14, 7634 };

	MD5Hash h0 = md5(b0, 5);
	MD5Hash h1 = md5(b1, 5);

	int i1 = 0;

	for (NOU::sizeType i = 0; i < 16; i++)
	{
		i1 = (h0[i] == h1[i]) ? i1 + 1 : i1;
	}

	cout << i1 << endl;

	system("pause");
}