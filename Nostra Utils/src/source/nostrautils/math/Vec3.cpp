#include "nostrautils\math\Vec3.hpp"
#include "nostrautils\core\StdIncludes.hpp"
#include <iostream>

namespace NOU::NOU_MATH 
{
	/*int a, b, c, d, e, f;
	
	int vec1[3] = { a,b,c };
	int vec2[3] = { d,e,f };
	*/
	Vec3::Vec3(float32 x, float32 y, float32 z) :
		m_data{x, y, z}
	{
		
	}


	Vec3 Vec3::add(const Vec3 &vec)
	{
		return Vec3(m_data[0] + vec.m_data[0],
			m_data[1] + vec.m_data[1], m_data[2] + vec.m_data[2]);
	}


	Vec3 Vec3::sub(const Vec3 &vec)
	{
		return Vec3(m_data[0] - vec.m_data[0],
			m_data[1] - vec.m_data[1], m_data[2] - vec.m_data[2]);
	}


	Vec3 Vec3::mult(const Vec3 &vec)
	{
		return Vec3(m_data[0] * vec.m_data[0],
			m_data[1] * vec.m_data[1], m_data[2] * vec.m_data[2]);
	}

	Vec3 Vec3::div(const Vec3 &vec)
	{ 
		return Vec3(m_data[0] / vec.m_data[0],
			m_data[1] / vec.m_data[1], m_data[2] / vec.m_data[2]);
	}


	Vec3 Vec3::operator+(const Vec3 &vek)
	{
		return add(vek);
	}
}
