#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\ObjectPool.hpp"
#include "nostrautils\file_mngt\File.hpp"
#include <iostream>

using namespace std;
using namespace NOU;
//using namespace NOU_CORE;
//using namespace NOU_DAT_ALG;
using namespace NOU_FILE_MNGT;

int main()
{
	File f("TestFile.txt", WRITE, "D:\\C++\\NostraUtils\\Test");
	f.open();
	for (int i = 0; i < 10; i++)
	{
		cout << f.write('b') << endl;
	}
	f.close();
}