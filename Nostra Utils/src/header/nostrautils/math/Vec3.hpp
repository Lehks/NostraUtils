#ifndef NOU_DAT_MATH_VEC3_HPP
#define NOU_DAT_MATH_VEC3_HPP

#include "nostrautils\core\StdIncludes.hpp"

#include <initializer_list>

namespace NOU::NOU_MATH
{
	template<typename T, sizeType N>
	class NOU_CLASS Vector 
	{
		public:
			using InitalizerList = std::initializer_list<T>;

		private:
			T m_data[N];

		public:
			Vector();
			Vector(InitalizerList initializerList);
			Vector add(const Vector & vec);
			Vector sub(const Vector & vec);
			T dot(const Vector & vec);
			Vector cross(const Vector & vec);
			Vector mult(const T);

			Vector operator + (const Vector & vec);
			Vector operator - (const Vector & vec);
			T operator * (const Vector & vec);
			Vector operator * (const T num);

			T& get(sizeType index);
			const T& get(sizeType index) const;

	};

	using Vec3f = Vector<float32, 3>;
	using Vec3i = Vector<int32, 3>;

	using Vec2f = Vector<float32, 2>;
	using Vec2i = Vector<int32, 2>;
	
	template<typename T, sizeType N>
	Vector<T, N>::Vector():
		m_data{0}
	{}

	template<typename T, sizeType N>
	Vector<T, N>::Vector(InitalizerList initializerList) 
	{
		for (sizeType i = 0; i != N; i++)
			m_data[i] = *(initializerList.begin() + i);
	}


	template<typename T, sizeType N>
	Vector<T, N> Vector<T, N>::add(const Vector<T, N> & vec)
	{
		Vector ret(*this);

		for (sizeType i = 0; i < N; i++)
			ret.get(i) += vec.get(i);

		return ret;
	}


	template<typename T, sizeType N>
	Vector<T, N> Vector<T, N>::sub(const Vector<T, N> & vec)
	{
		Vector ret(*this);

		for (sizeType i = 0; i < N; i++)
			ret.get(i) -= vec.get(i);

		return ret;
	}


	template<typename T, sizeType N>
	T Vector<T, N>::dot(const Vector<T, N> & vec)
	{
		T ret = 0;

		for (sizeType i = 0; i < N; i++)
			ret += get(i) * vec.get(i);

		return ret;

		//return m_data[0] * vec.m_data[0] + m_data[1] * vec.m_data[1] + m_data[2] * vec.m_data[2];
	}


	template<typename T, sizeType N>
	Vector<T, N> Vector<T, N>::mult(const T num)
	{
		Vector ret(*this);

		for (sizeType i = 0; i < N; i++)
			ret.get(i) *= num;

		return ret;
	}


	template<typename T, sizeType N>
	Vector<T, N> Vector<T, N>::operator + (const Vector<T, N> & vec)
	{
		return add(vec);
	}


	template<typename T, sizeType N>
	Vector<T, N> Vector<T, N>::operator - (const Vector<T, N> & vec)
	{
		return sub(vec);
	}


	template<typename T, sizeType N>
	T Vector<T, N>::operator * (const Vector<T, N> & vec)
	{
		return dot(vec);
	}


	template<typename T, sizeType N>
	Vector<T, N> Vector<T, N>::operator * (const T num)
	{
		return mult(num);
	}

	template<typename T, sizeType N>
	T& Vector<T, N>::get(sizeType index)
	{
		return m_data[index];
	}

	template<typename T, sizeType N>
	const T& Vector<T, N>::get(sizeType index) const
	{
		return m_data[index];
	}

	template<typename T, sizeType N>
	Vector operator += (const Vector& vec0, const Vector& vec1) {
		return Vector()
	}
}
//+=, -=, *=

#endif
