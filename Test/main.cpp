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
	Path p13 = "C:\\Users\\"; 
	Path p14 = "C:\\Users\\SomeOtherDir"; 

	std::cout << p10.getParentPath().rawStr() << std::endl;
	std::cout << p11.getParentPath().rawStr() << std::endl;
	std::cout << p12.getParentPath().rawStr() << std::endl;
	std::cout << p13.getParentPath().rawStr() << std::endl;
	std::cout << p14.getParentPath().rawStr() << std::endl;
	/*
	std::cout << Path::currentWorkingDirectory().getAbsolutePath().rawStr() << std::endl;

	std::cout << std::endl;

	std::cout << p.getName().rawStr()  << "\t"	<< (p.getName()  == "testfile") << " " << p.getName().size()  << std::endl;
	std::cout << p1.getName().rawStr() << "\t"	<< (p1.getName() == "testfile") << " " << p1.getName().size() << std::endl;
	std::cout << p2.getName().rawStr() << "\t"	<< (p2.getName() == "testfile") << " " << p2.getName().size() << std::endl;
	std::cout << p3.getName().rawStr() << "\t"	<< (p3.getName() == "testfile") << " " << p3.getName().size() << std::endl;
	std::cout << p4.getName().rawStr() << "\t"	<< (p4.getName() == "") << " " << p4.getName().size() << std::endl;
	std::cout << p5.getName().rawStr() << "\t" << (p5.getName() == "testfile") << " " << p5.getName().size() << std::endl;
	std::cout << p6.getName().rawStr() << "\t"	<< (p6.getName() == "testfile") << " " << p6.getName().size() << std::endl;

	std::cout << std::endl;

	std::cout << p.getFileExtension().rawStr()  << "\t"  << (p.getFileExtension() == "exe") << " " << p.getFileExtension().size() << std::endl;
	std::cout << p1.getFileExtension().rawStr() << "\t" << (p1.getFileExtension() == "test") << " " << p1.getFileExtension().size() << std::endl;
	std::cout << p2.getFileExtension().rawStr() << "\t" << (p2.getFileExtension() == "test") << " " << p2.getFileExtension().size() << std::endl;
	std::cout << p3.getFileExtension().rawStr() << "\t" << (p3.getFileExtension() == "") << " " << p3.getFileExtension().size() << std::endl;
	std::cout << p4.getFileExtension().rawStr() << "\t" << (p4.getFileExtension() == "") << " " << p4.getFileExtension().size() << std::endl;
	std::cout << p5.getFileExtension().rawStr() << "\t" << (p5.getFileExtension() == "") << " " << p5.getFileExtension().size() << std::endl;
	std::cout << p6.getFileExtension().rawStr() << "\t" << (p6.getFileExtension() == "gz") << " " << p6.getFileExtension().size() << std::endl;

	std::cout << std::endl;

	std::cout << p.getNameAndExtension().rawStr() << "\t" << (p.getNameAndExtension() == "testfile.exe") << " " << p.getNameAndExtension().size() << std::endl;
	std::cout << p1.getNameAndExtension().rawStr() << "\t" << (p1.getNameAndExtension() == "testfile.test") << " " << p1.getNameAndExtension().size() << std::endl;
	std::cout << p2.getNameAndExtension().rawStr() << "\t" << (p2.getNameAndExtension() == "testfile.test") << " " << p2.getNameAndExtension().size() << std::endl;
	std::cout << p3.getNameAndExtension().rawStr() << "\t" << (p3.getNameAndExtension() == "testfile") << " " << p3.getNameAndExtension().size() << std::endl;
	std::cout << p4.getNameAndExtension().rawStr() << "\t" << (p4.getNameAndExtension() == "") << " " << p4.getNameAndExtension().size() << std::endl;
	std::cout << p5.getNameAndExtension().rawStr() << "\t" << (p5.getNameAndExtension() == "testfile") << " " << p5.getNameAndExtension().size() << std::endl;
	std::cout << p6.getNameAndExtension().rawStr() << "\t" << (p6.getNameAndExtension() == "test.tar.gz") << " " << p6.getNameAndExtension().size() << std::endl;
	*/
	std::cin.get();
}							