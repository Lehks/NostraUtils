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
		// Todo
	}


	Vec3 Vec3::div(const Vec3 & vec)
	{ 
		return Vec3(m_data[0] / vec.m_data[0],
			m_data[1] / vec.m_data[1], m_data[2] / vec.m_data[2]);
	}


	Vec3 Vec3::operator + (const Vec3 & vek)
	{
		return add(vek);
	}


	Vec3 Vec3::operator - (const Vec3 & vek)
	{
		return sub(vek);
	}

	Vec3 Vec3::operator / (const Vec3 & vek)
	{
		return div(vek);
	}
}
