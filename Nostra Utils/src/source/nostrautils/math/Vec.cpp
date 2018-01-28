#include <iostream>

int main() {
	double a, b, c;
	std::cin >> a;
	std::cin >> b;
	std::cin >> c;
	double vec[3] = { a,b,c };

	for (int i = 0; i < 3; i++) {
		std::cout << vec[i];
	    
	}


	system("pause");
	return 0;
}