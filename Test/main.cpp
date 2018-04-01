#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\ObjectPool.hpp"
#include "nostrautils\file_mngt\File.hpp"
#include "nostrautils\file_mngt\Path.hpp"
#include <iostream>

using namespace std;
using namespace NOU;
//using namespace NOU_CORE;
using namespace NOU_DAT_ALG;
using namespace NOU_FILE_MNGT;

int main()
{
	String8 sv = "Hello World!";
	String8 s = sv.substring(0, 5);

	std::cout << s.rawStr() << std::endl;

	NOU::NOU_FILE_MNGT::Path cwd = NOU::NOU_FILE_MNGT::Path::currentWorkingDirectory();

	NOU::NOU_DAT_ALG::String8 str = cwd.getAbsolutePath();
	str.append("\\Test\\Dennis\\WasGehtAb");

	std::cout << str.rawStr() << std::endl;

	NOU::NOU_FILE_MNGT::Path p15 = str;

	std::cout << Path::currentWorkingDirectory().getAbsolutePath().rawStr() << std::endl;

	std::cout << p15.getRelativePath().rawStr() << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;

	

	std::cout << std::endl;

	std::cin.get();
}							