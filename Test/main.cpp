#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\ObjectPool.hpp"
#include "nostrautils\file_mngt\Path.hpp"
#include "nostrautils\file_mngt\Folder.hpp"
#include "nostrautils/dat_alg/Vector.hpp"
#include "nostrautils/dat_alg/String.hpp"
#include <iostream>
#include <stdio.h>


using namespace std;
using namespace NOU;
//using namespace NOU_CORE;
using namespace NOU_DAT_ALG;
using namespace NOU_FILE_MNGT;

//void callback(const NOU_CORE::ErrorLocation&)
//{
	//__debugbreak();
//}



int main(int argc, TCHAR *argv[])
{
	File f("abc.txt");
	cout << (f.exists() ? "Datei existsiert" : "Datei existiert nicht") << endl;
	f.open(AccessMode::WRITE);
	f.write("asdfasdfasdfasdfasdf");
	cout << (f.exists() ? "Datei existsiert" : "Datei existiert nicht") << endl;
	f.close();
	system("pause");
}