#include "nostrautils\math\Vec3.hpp"
#include "nostrautils\core\StdIncludes.hpp"
#include <iostream>

namespace NOU::NOU_MATH 
{
	Vec3::Vec3(const float32 x, const float32 y, const float32 z) :
		m_data{x, y, z}
	{
		
	}


	Vec3 Vec3::add(const Vec3 & vec)
	{ 
		return Vec3(m_data[0] + vec.m_data[0],
			m_data[1] + vec.m_data[1], m_data[2] + vec.m_data[2]);
	}


	Vec3 Vec3::sub(const Vec3 & vec)
	{
		return Vec3(m_data[0] - vec.m_data[0],
			m_data[1] - vec.m_data[1], m_data[2] - vec.m_data[2]);
	}


	float32 Vec3::dot(const Vec3 & vec)
	{
		return m_data[0] * vec.m_data[0] + m_data[1] * vec.m_data[1] + m_data[2] * vec.m_data[2];
	}


	Vec3 Vec3::mult(const float32 num)
	{
		return Vec3(m_data[0] * num, m_data[1] * num, m_data[3] * num);
	}


	Vec3 Vec3::operator + (const Vec3 & vec)
	{
		return add(vec);
	}


	Vec3 Vec3::operator - (const Vec3 & vec)
	{
		return sub(vec);
	}


	float32 Vec3::operator * (const Vec3 & vec)
	{
		return dot(vec);
	}


	Vec3 Vec3::operator * (const float32 num)
	{
		return mult(num);
	}
}
