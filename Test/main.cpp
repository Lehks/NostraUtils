#include "nostrautils\dat_alg\StringView.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"

#include <iostream>
#include <ctime>


int main()
{

	NOU::char8 str1[] = "Franz jagt im komplett verwahrlosten Taxi quer durch Bayern";
	NOU::char8 str2[] = "Frank jagt im komplett verwahrlosten Taxi quer durch Bayern";

	NOU::NOU_DAT_ALG::MD5Hash hash = NOU::NOU_DAT_ALG::md5(str1);
	//std::cout << "\"" << str1 << "\" -> " << hashInt << endl;
	NOU::NOU_DAT_ALG::MD5Hash hash1 = NOU::NOU_DAT_ALG::md5(str2);

	cout << "\"" << str1 << "\"" << " -> ";
	for (int i = 0; i < 16; i++)
	{
		if ((hash[i] < 100) & (hash[i] >= 10))
		{
			cout << " " << static_cast<int>(hash[i]) << " ";
		} else if (hash[i] < 10)
		{
			cout << "  " << static_cast<int>(hash[i]) << " ";
		} else
		{
			cout << static_cast<int>(hash[i]) << " ";
		}
	}
	cout << endl;
	cout << "\"" << str2 << "\"" << " -> ";
	for (int i = 0; i < 16; i++)
	{
		if ((hash1[i] < 100) & (hash1[i] >= 10))
		{
			cout << " " << static_cast<int>(hash1[i]) << " ";
		} else if(hash1[i] < 10)
		{
			cout << "  " << static_cast<int>(hash1[i]) << " ";
		} else
		{
			cout << static_cast<int>(hash1[i]) << " ";
		}
	} cout << endl;

	//NOU::byte f = 1;
	//
	////cout << (0b10000000 & 0b10110101) << endl;
	//
	//for (int i = 0; i < 10; i++)
	//{
	//	cout << static_cast<NOU::uint32>(f = NOU::NOU_DAT_ALG::leftRotation(f, 1)) << "\t" << static_cast<NOU::uint32>(NOU::NOU_DAT_ALG::leftRotation(f, 2)) << endl;
	//}

	system("pause");

}