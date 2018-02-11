#ifndef NOU_DAT_MATH_VEC3_HPP
#define NOU_DAT_MATH_VEC3_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Utils.hpp"
#include "nostrautils\core\ErrorHandler.hpp"

#include <initializer_list>

namespace NOU::NOU_MATH
{
	template<uint32 N, typename T = float32>
	class NOU_CLASS Vec3 
	{
	public:
		using Type = T;
		using InitializerList = std::initializer_list<Type>;

		private:
			Type m_data[N];

		public:
			Vec3(InitializerList list);
			Vec3 add(const Vec3 & vec) const;
			Vec3 sub(const Vec3 & vec) const;
			Type dot(const Vec3 & vec) const;
			Vec3 cross(const Vec3 & vec) const;
			Vec3 mult(const Type) const;

			Vec3 operator + (const Vec3 & vec);
			Vec3 operator - (const Vec3 & vec) const;
			Type operator * (const Vec3 & vec) const;
			Vec3 operator * (const Type num) const;
	};


	using Vec3f = Vec3<3, float32>;
	using Vec3i = Vec3<3, float32>;
	using Vec2f = Vec3<2, int32>;
	using Vec2i = Vec3<2, int32>;

	template<uint32 N, typename T>
	Vec3<N, T>::Vec3(InitializerList list)
	{
		NOU_COND_PUSH_DBG_ERROR(list.size() != N, NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::SIZE_MISMATCH, 
			"The size of the vector did not match the size of the initializer list.");

		sizeType i = 0;

		for (const Type &t : list)
		{
			m_data[i] = NOU_CORE::move(t);
			i++;
		}
	}

	template<uint32 N, typename T>
	Vec3<N, T> Vec3<N, T>::add(const Vec3 & vec) 
	{
		return Vec3({ m_data[0] + vec.m_data[0],
			m_data[1] + vec.m_data[1], m_data[2] + vec.m_data[2] });
	}


	template<uint32 N, typename T>
	Vec3<N, T> Vec3<N, T>::sub(const Vec3 & vec) const
	{
		return Vec3({ m_data[0] - vec.m_data[0],
			m_data[1] - vec.m_data[1], m_data[2] - vec.m_data[2] });
	}


	template<uint32 N, typename T>
	typename Vec3<N, T>::Type Vec3<N, T>::dot(const Vec3<N, T> & vec) const
	{
		return m_data[0] * vec.m_data[0] + m_data[1] * vec.m_data[1] + m_data[2] * vec.m_data[2];
	}


	template<uint32 N, typename T>
	Vec3<N, T> Vec3<N, T>::mult(const Type num) const
	{
		return Vec3({ m_data[0] * num, m_data[1] * num, m_data[3] * num });
	}

	template<uint32 N, typename T>
	Vec3<N, T> Vec3<N, T>::operator + (const Vec3<N, T> & vec)
	{
		return add(vec);
	}


	template<uint32 N, typename T>
	Vec3<N, T> Vec3<N, T>::operator - (const Vec3<N, T> & vec) const
	{
		return sub(vec);
	}


	template<uint32 N, typename T>
	typename Vec3<N, T>::Type Vec3<N, T>::operator * (const Vec3<N, T> & vec) const
	{
		return dot(vec);
	}


	template<uint32 N, typename T>
	Vec3<N, T> Vec3<N, T>::operator * (const Type num) const
	{
		return mult(num);
	}

}

#endif
