#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/NostraUtils.hpp"

#include <iostream>

using namespace std;
using namespace NOU;
using namespace NOU_CORE;

int main()
{

	uint32 begin, end;

	begin = currentTimeMillis();
	for (int i = 0; i < 1000000000; i++);
	end = currentTimeMillis();
	cout << "Time in ms: " << end - begin << endl;
	system("pause");
}