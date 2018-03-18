#ifndef NOU_DAT_MATH_VEC_HPP
#define NOU_DAT_MATH_VEC_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Utils.hpp"
#include "nostrautils\core\ErrorHandler.hpp"
#include <initializer_list>


namespace NOU::NOU_MATH
{
	template<uint32 N, typename T = float32>
	class NOU_CLASS Vec
	{
		public:
			using Type = T;
			using InitializerList = std::initializer_list<Type>;

		private:
			Type m_data[N];

		public:
			Vec(InitializerList list);
			Vec(Type list[N]);
			Vec add(const Vec<N, T> & vec) const;
			Vec sub(const Vec & vec) const;
			Type dot(const Vec & vec) const;
			Vec cross(const Vec & vec) const;
			Vec mult(const Type) const;
			Type getCom(uint32 index) const;
			void setCom(uint32 index, T value);

			Vec operator + (const Vec & vec);
			Vec operator - (const Vec & vec) const;
			Type operator * (const Vec & vec) const;
			Vec operator * (const Type num) const;
	};


	using Vecf = Vec<3, float32>;
	using Veci = Vec<3, float32>;
	using Vec2f = Vec<2, int32>;
	using Vec2i = Vec<2, int32>;


	template<uint32 N, typename T>
	Vec<N, T>::Vec(InitializerList list)
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
	Vec<N, T>::Vec(Type list[N])
	{
		sizeType i = 0;

		for (i = 0; i < N; i++)
		{
			m_data[i] = list[i];
		}
	}


	/**
	\param A vector of the same size and type.

	\brief Adds this vector with another and returns the resulting new vector.
	*/
	template<uint32 N, typename T>
	Vec<N, T> Vec<N, T>::add(const Vec<N, T> & vec) const
	{
		sizeType i = 0;
		Type l[N];

		for (i = 0; i < N; i++)
		{
			l[i] = this->getCom(i) + vec.getCom(i);
		}

		return Vec<N, T>(l);
	}


	/**
	\param A vector of the same size and type.

	\brief Subtracts the given vector from this vector and returns the result as a new vector.
	*/
	template<uint32 N, typename T>
	Vec<N, T> Vec<N, T>::sub(const Vec & vec) const
	{
		sizeType i = 0;
		Type l[N];

		for (i = 0; i < N; i++)
		{
			l[i] = this->getCom(i) - vec.getCom(i);
		}

		return Vec<N, T>(l);
	}


	template<uint32 N, typename T>
	typename Vec<N, T>::Type Vec<N, T>::dot(const Vec<N, T> & vec) const
	{
		sizeType i = 0;
		Type dot;

		for (i = 0; i < N; i++)
		{
			dot += this->getCom(i) * vec.getCom(i);
		}

		return dot;
	}


	template<uint32 N, typename T>
	Vec<N, T> Vec<N, T>::mult(const Type num) const
	{
		sizeType i = 0;
		Type l[N];

		for (i = 0; i < N; i++)
		{
			l[i] = this->getCom(i) * num;
		}

		return Vec<N, T>(l);
	}


	template<uint32 N, typename T>
	Vec<N, T> Vec<N, T>::cross(const Vec<N, T> & vec) const
	{
		Type l[N];

		if (N != 3) {
			NOU_COND_PUSH_DBG_ERROR(N != 3, NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::SIZE_MISMATCH,
				"Cross operation is only available for 3D vectors!");
			return Vec<N, T>(l);
		}

		l[0] = this->getCom(1) * vec->getCom(2) - this->getCom(2) * this->getCom(1);
		l[1] = this->getCom(2) * vec->getCom(0) - this->getCom(0) * this->getCom(2);
		l[1] = this->getCom(0) * vec->getCom(1) - this->getCom(1) * this->getCom(0);

		return Vec<N, T>(l);
	}


	/**
	\param The Vector component to get. 

	\brief Returns the component at the requested index.
	*/
	template<uint32 N, typename T>
	typename Vec<N, T>::Type Vec<N, T>::getCom(uint32 index) const
	{
		NOU_COND_PUSH_DBG_ERROR(
			(index >= N || index < 0), 
			NOU_CORE::getErrorHandler(), 
			NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS,
			"Index out of bounds!"
		);
		
		return m_data[index];
	}


	/**
	\param The Vector index to change.
	\param The new value

	\brief Sets the value of a vector.
	*/
	template<uint32 N, typename T>
	void Vec<N, T>::setCom(uint32 index, T value)
	{
		NOU_COND_PUSH_DBG_ERROR(
			(index >= N || index < 0),
			NOU_CORE::getErrorHandler(),
			NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS,
			"Index out of bounds!"
		);

		m_data[index] = value;
	}


	template<uint32 N, typename T>
	Vec<N, T> Vec<N, T>::operator + (const Vec<N, T> & vec)
	{
		return add(vec);
	}


	template<uint32 N, typename T>
	Vec<N, T> Vec<N, T>::operator - (const Vec<N, T> & vec) const
	{
		return sub(vec);
	}


	template<uint32 N, typename T>
	typename Vec<N, T>::Type Vec<N, T>::operator * (const Vec<N, T> & vec) const
	{
		return dot(vec);
	}


	template<uint32 N, typename T>
	Vec<N, T> Vec<N, T>::operator * (const Type num) const
	{
		return mult(num);
	}
}
#endif
