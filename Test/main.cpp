#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\Hashing.hpp"
#include "nostrautils\dat_alg\String.hpp"

#include <iostream>
//#include <ctime>

using namespace std;
using namespace NOU;
using namespace NOU_DAT_ALG;

int main()
{
	NOU::NOU_DAT_ALG::String8 s0 = "asdfghjkl";
	NOU::NOU_DAT_ALG::String8 s1 = "asdfghjkk";

	NOU::byte b0[] = {123,34,87,45};
	NOU::byte b1[] = {123,34,87,46};


	MD5Hash h0 = md5(s0);
	MD5Hash h1 = md5(s1);

	int i1 = 0;

	for (NOU::sizeType i = 0; i < 16; i++)
	{
		i1 = (h0[i] == h1[i]) ? i1 + 1 : i1;
	}

	cout << i1 << endl;

	system("pause");
}