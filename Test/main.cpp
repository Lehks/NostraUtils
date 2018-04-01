#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\ObjectPool.hpp"
#include "nostrautils\file_mngt\File.hpp"
#include "nostrautils\file_mngt\Path.hpp"
#include <iostream>

using namespace std;
using namespace NOU;
//using namespace NOU_CORE;
//using namespace NOU_DAT_ALG;
using namespace NOU_FILE_MNGT;

int main()
{
	Path p14 = "D:\\NostraUtils\\Test\\Dennis\\Hallo\\";

	Path cwd = Path::currentWorkingDirectory();

	Path p18 = cwd.getAbsolutePath();

	NOU_DAT_ALG::String8 str = p18.getParentPath();

	Path p19 = str;

	std::cout << Path::currentWorkingDirectory().getAbsolutePath().rawStr() << std::endl;

	std::cout << p14.getRelativePath().rawStr() << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;

	

	std::cout << std::endl;

	std::cin.get();
}							