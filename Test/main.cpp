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
	Path p = "\\testfile.exe";
	Path p1 = "testdir\\testfile.test";
	Path p2 = "\\test.dir\\testfile.test";
	Path p3 = "test.dir\\testfile";
	Path p4 = "testfile.test\\";
	Path p5 = "testfile";
	Path p6 = "test.tar.gz";

	Path p7 = "C:\\Test\\Test";
	Path p8 = "\\Test";
	Path p9 = "Ichhassemeinleben.exe";

	// "C:\\Users\\Dennis\\TestDir"; //<- current directory (TestDir)

	Path p10 = "C:\\Users\\Dennis\\TestDir\\MyFile.exe"; 
	Path p11 = "C:\\Users\\Dennis\\TestDir\\MyFolder\\MyFile.txt"; 
	Path p12 = "C:\\Users\\Dennis\\TestDir"; 
	Path p13 = "D:\\Users\\"; 
	Path p14 = "D:\\Users\\SomeOtherDir"; 

	Path cwd = Path::currentWorkingDirectory();

	std::cout << Path::currentWorkingDirectory().getAbsolutePath().rawStr() << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << p10.getRelativePath().rawStr() << std::endl;
	std::cout << p11.getRelativePath().rawStr() << std::endl;
	std::cout << p12.getRelativePath().rawStr() << std::endl;
	std::cout << p13.getRelativePath().rawStr() << std::endl;
	std::cout << p14.getRelativePath().rawStr() << std::endl;
	std::cout << cwd.getRelativePath().rawStr() << std::endl;

	std::cout << std::endl;

	std::cin.get();
}							