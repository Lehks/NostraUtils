#ifndef NOU_MATH_VECTOR
#define NOU_MATH_VECTOR

#include "nostrautils/core/StdIncludes.hpp"

#include <initializer_list>

namespace NOU::NOU_MATH
{
	template<typename T, sizeType N>
	class NOU_CLASS VectorBase
	{
	public:
		using InitializerList = std::initializer_list<T>;

	protected:
		T m_data[N];

		VectorBase() = default;
		VectorBase(const InitializerList &values);

	public:
		const T& value(sizeType index) const;
		T& value(sizeType index);

		const T* data() const;
		T* data();
	};

	template<typename T, sizeType N>
	class NOU_CLASS Vector : VectorBase<T, N>
	{
	public:
		Vector() = default;
		Vector(const typename VectorBase::InitializerList &values);

		Vector add(const Vector &other) const;
		Vector& addAssign(const Vector &other);

		Vector sub(const Vector &other) const;
		Vector& subAssign(const Vector &other);

		Vector multiplicateElements(const Vector &other) const;
		Vector& multiplicateElementsAssign(const Vector &other);

		Vector divideElements(const Vector &other) const;
		Vector& divideElementsAssign(const Vector &other);

		Vector scale(const T &scale) const;
		Vector& scaleAssign(const T &scale);

		T dotProduct(const Vector &other) const;

		T lenght() const;

		Vector copy() const;

		Vector& normalize();

		Vector& invert();

		Vector operator + (const Vector &other) const;
		Vector& operator += (const Vector &other);

		Vector operator - (const Vector &other) const;
		Vector& operator -= (const Vector &other);

		T operator * (const Vector &other) const;
		Vector operator * (const T &other) const;
		Vector& operator *= (const T &other);

		Vector& operator - ();
	};

	using Vec2 = Vector<float32, 2>;
	using Vec3 = Vector<float32, 3>;
	using Vec4 = Vector<float32, 4>;
	using Vec2i = Vector<int32, 2>;
	using Vec3i = Vector<int32, 3>;
	using Vec4i = Vector<int32, 4>;

	template<typename T, sizeType N>
	VectorBase<T, N>::VectorBase(const InitializerList &values)
	{
		sizeType index = 0;

		for (auto i = values.begin(); i != values.end(); i++)
		{
			m_data[index] = *i;
			index++;
		}
	}

	template<typename T, sizeType N>
	const T& VectorBase<T, N>::value(sizeType index) const
	{
		return m_data[index];
	}

	template<typename T, sizeType N>
	T& VectorBase<T, N>::value(sizeType index)
	{
		return m_data[index];
	}

	template<typename T, sizeType N>
	const T* VectorBase<T, N>::data() const
	{
		return m_data;
	}

	template<typename T, sizeType N>
	T* VectorBase<T, N>::data()
	{
		return m_data;
	}



	template<typename T, sizeType N>
	Vector<T, N>::Vector(const typename VectorBase<T, N>::InitializerList &values) :
		VectorBase<T, N>(values)
	{}

	template<typename T, sizeType N>
	Vector<T, N> Vector<T, N>::add(const Vector<T, N> &other) const
	{

	}

	template<typename T, sizeType N>
	Vector<T, N>& Vector<T, N>::addAssign(const Vector<T, N> &other)
	{

	}

	template<typename T, sizeType N>
	Vector<T, N> Vector<T, N>::sub(const Vector<T, N> &other) const
	{

	}

	template<typename T, sizeType N>
	Vector<T, N>& Vector<T, N>::subAssign(const Vector<T, N> &other)
	{

	}

	template<typename T, sizeType N>
	Vector<T, N> Vector<T, N>::multiplicateElements(const Vector<T, N> &other) const
	{

	}

	template<typename T, sizeType N>
	Vector<T, N>& Vector<T, N>::multiplicateElementsAssign(const Vector<T, N> &other)
	{

	}

	template<typename T, sizeType N>
	Vector<T, N> Vector<T, N>::divideElements(const Vector<T, N> &other) const
	{

	}

	template<typename T, sizeType N>
	Vector<T, N>& Vector<T, N>::divideElementsAssign(const Vector<T, N> &other)
	{

	}

	template<typename T, sizeType N>
	Vector<T, N> Vector<T, N>::scale(const T &scale) const
	{

	}

	template<typename T, sizeType N>
	Vector<T, N>& Vector<T, N>::scaleAssign(const T &scale)
	{

	}

	template<typename T, sizeType N>
	T Vector<T, N>::dotProduct(const Vector<T, N> &other) const
	{

	}

	template<typename T, sizeType N>
	T Vector<T, N>::lenght() const
	{

	}

	template<typename T, sizeType N>
	Vector<T, N> Vector<T, N>::copy() const
	{

	}

	template<typename T, sizeType N>
	Vector<T, N>& Vector<T, N>::normalize()
	{

	}

	template<typename T, sizeType N>
	Vector<T, N>& Vector<T, N>::invert()
	{

	}

	template<typename T, sizeType N>
	Vector<T, N> Vector<T, N>::operator + (const Vector<T, N> &other) const
	{

	}

	template<typename T, sizeType N>
	Vector<T, N>& Vector<T, N>::operator += (const Vector<T, N> &other)
	{

	}

	template<typename T, sizeType N>
	Vector<T, N> Vector<T, N>::operator - (const Vector<T, N> &other) const
	{

	}

	template<typename T, sizeType N>
	Vector<T, N>& Vector<T, N>::operator -= (const Vector<T, N> &other)
	{

	}

	template<typename T, sizeType N>
	T Vector<T, N>::operator * (const Vector<T, N> &other) const
	{

	}

	template<typename T, sizeType N>
	Vector<T, N> Vector<T, N>::operator * (const T &other) const
	{

	}

	template<typename T, sizeType N>
	Vector<T, N>& Vector<T, N>::operator *= (const T &other)
	{

	}

	template<typename T, sizeType N>
	Vector<T, N>& Vector<T, N>::operator - ()
	{

	}
}

#endif