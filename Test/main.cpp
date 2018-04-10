#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\Hashing.hpp"
#include "nostrautils\dat_alg\String.hpp"

#include <iostream>
#include <ctime>

using namespace std;
using namespace NOU;
using namespace NOU_DAT_ALG;

int main()
{
	NOU::NOU_DAT_ALG::String8 s0 = "asdfghjkl";
	NOU::NOU_DAT_ALG::String8 s1 = "asdfghjkk";

	NOU::byte *b0 = new NOU::byte[5];
	NOU::byte *b1 = new NOU::byte[5];

	for (int i = 0; i < 4; i++) {
		b0[i] = i;
		b1[i] = i;
	}

	b0[5] = 200;
	b0[5] = 201;


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