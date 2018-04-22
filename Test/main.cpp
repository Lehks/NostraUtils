#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\ObjectPool.hpp"
#include "nostrautils\file_mngt\Path.hpp"
#include "nostrautils\file_mngt\Folder.hpp"
#include "nostrautils/dat_alg/Vector.hpp"
#include "nostrautils/dat_alg/String.hpp"
#include <iostream>
#include <Windows.h>


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
	//NOU_CORE::ErrorHandler::setCallback(callback);

	//NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> vec;
	//const NOU::NOU_DAT_ALG::String8 str;

	NOU::NOU_FILE_MNGT::Folder f("C:\\Users\\Mahan\\Desktop");
	//NOU::NOU_FILE_MNGT::File file("C:\\Users\\Mahan\\Desktop", AccessMode::READ);
	

	//f.read_directory("C:\\Users\\Mahan\\Desktop\\", vec);
	//f.create("P:\\Users\\Mahan\\Desktop\\");

	 
	// f.create();
     NOU_DAT_ALG::Vector<Folder> v = f.listFiles(); 

     for (sizeType i = 0; i < v.size(); i++)
	
		std::cout << v[i].getPath().getAbsolutePath().rawStr() << std::endl;

	

	//NOU_DAT_ALG::Vector<Folder> v = f.listFolders();

	//for (sizeType i = 0; i < v.size(); i++)
	//{
		//std::cout << v[i].getPath().getAbsolutePath().rawStr() << std::endl;
	//}
	
	

	//char windir_name[MAX_PATH];
	//GetWindowsDirectory(windir_name, sizeof(windir_name));
	//cout << "Windows-Directory: " << windir_name << endl;
	


	
	//std::cout << f.getPath().getAbsolutePath().rawStr() << std::endl;

	 system("Pause");

	 
}							