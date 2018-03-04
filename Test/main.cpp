#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\Random.hpp"   
#include <iostream>



int main()
{ 
	double a; 
	a = NOU::NOU_DAT_ALG::randTwo(50,100,66); 
	std::cout << a << std::endl; 
	

	system("Pause"); 
}