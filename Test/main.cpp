#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils/NostraUtils.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace NOU;
using namespace NOU_CORE;

int main()
{

	uint32 begin, end;

	begin = currentTimeMillis();
	for (int i = 0; i < 100000000; i++);
	end = currentTimeMillis();
	cout << "Time in ms: " << end - begin << endl;
	system("pause");
}