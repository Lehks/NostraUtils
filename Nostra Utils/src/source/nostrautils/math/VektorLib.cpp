#include "stdafx.h"
#include "VektorLib.h"
#include <iostream>

namespace Vektor {
	/*int a, b, c, d, e, f;
	
	int vec1[3] = { a,b,c };
	int vec2[3] = { d,e,f };
	*/
	MyVektor::MyVektor(int x, int y, int z) :
		m_data{x, y, z}
	{
		
	}

	MyVektor MyVektor::add(const MyVektor &vec)
	{
		return MyVektor(m_data[0] + vec.m_data[0], 
			m_data[1] + vec.m_data[1], m_data[2] + vec.m_data[2]);
	}

	MyVektor MyVektor::sus(const MyVektor &vec) 
	{
		return MyVektor(m_data[0] - vec.m_data[0],
			m_data[1] - vec.m_data[1], m_data[2] - vec.m_data[2]);
	}

	MyVektor MyVektor::mul(const MyVektor &vec)
	{
		return MyVektor(m_data[0] * vec.m_data[0],
			m_data[1] * vec.m_data[1], m_data[2] * vec.m_data[2]);
	}

	MyVektor MyVektor::div(const MyVektor &vec)
	{ 
		return MyVektor(m_data[0] / vec.m_data[0],
			m_data[1] / vec.m_data[1], m_data[2] / vec.m_data[2]);
	}

	MyVektor MyVektor::operator+(const MyVektor &vek)
	{
		return add(vek);
	}
}
