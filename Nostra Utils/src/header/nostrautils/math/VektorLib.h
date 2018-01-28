// VektorLib.h
#include <iostream>

namespace Vektor {
	class MyVektor {
	public:
		int m_data[3];

	public:
		MyVektor(int x, int y, int z);
		MyVektor add(const MyVektor &vek);
		MyVektor sus(const MyVektor &vek);
		MyVektor mul(const MyVektor &vek);
		MyVektor div(const MyVektor &vek);

		MyVektor operator + (const MyVektor &vek);
	};
}
