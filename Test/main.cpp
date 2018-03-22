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
	FILE * pFile;
	char mystring[100];

	#pragma warning(suppress : 4996)
	pFile = fopen("TestFile", "r");
	if (pFile == NULL) perror("Error opening file");
	else
	{
		if (fgets(mystring, 100, pFile) != NULL)
			puts(mystring);
		fclose(pFile);
	}
	system("pause");
	return 0;
}