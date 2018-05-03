#ifndef NOU_MATH_VECTOR
#define NOU_MATH_VECTOR

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/core/Assertions.hpp"
#include "nostrautils/math/Utils.hpp"

#include <initializer_list>

namespace NOU::NOU_MATH
{
    template<typename T, sizeType N>
    class NOU_CLASS VectorBase
    {
        static_assert(N > 1, "A vector can not have 0 or 1 rows.");

    public:
        using InitializerList = std::initializer_list<T>;

    protected:
        T m_data[N];

        VectorBase() = default;
        VectorBase(const InitializerList &values);

    public:
        const T& value(sizeType index) const;
        T& value(sizeType index);

        sizeType size() const;

        const T* data() const;
        T* data();
    };

    template<typename T, sizeType N>
    class NOU_CLASS Vector : public VectorBase<T, N>
    {
    public:
        static Vector nullVector();

        Vector() = default;
        Vector(const typename VectorBase<T, N>::InitializerList &values);
        Vector(const Vector<T, 2> &vec, const typename VectorBase<T, N>::InitializerList &values);
        Vector(const Vector<T, 3> &vec, const typename VectorBase<T, N>::InitializerList &values);
        Vector(const Vector<T, 4> &vec, const typename VectorBase<T, N>::InitializerList &values);

        Vector add(const Vector &other) const;
        Vector& addAssign(const Vector &other);

        Vector sub(const Vector &other) const;
        Vector& subAssign(const Vector &other);

        Vector multiplicateElements(const Vector &other) const;
        Vector& multiplicateElementsAssign(const Vector &other);

        Vector divideElements(const Vector &other) const;
        Vector& divideElementsAssign(const Vector &other);

        Vector scale(float64 scale) const;
        Vector& scaleAssign(float64 scale);

        T dotProduct(const Vector &other) const;

        float32 length() const;

        Vector copy() const;

        boolean equal(const Vector &other) const;

        boolean unequal(const Vector &other) const;

        Vector& normalize();

        Vector invert() const;
        Vector& invertThis();

        Vector operator + (const Vector &other) const;
        Vector& operator += (const Vector &other);

        Vector operator - (const Vector &other) const;
        Vector& operator -= (const Vector &other);

        T operator * (const Vector &other) const;
        Vector operator * (const T &other) const;
        Vector& operator *= (const T &other);

        Vector operator - () const;

        boolean operator == (const Vector &other) const;
        boolean operator != (const Vector &other) const;
    };

    template<typename T>
    class NOU_CLASS Vector<T, 2> : public VectorBase<T, 2>
    {
    public:
        static Vector nullVector();

        Vector() = default;
        Vector(const T &x, const T &y);
        Vector(const typename VectorBase<T, 2>::InitializerList &values);

        Vector add(const Vector &other) const;
        Vector& addAssign(const Vector &other);

        Vector sub(const Vector &other) const;
        Vector& subAssign(const Vector &other);

        Vector multiplicateElements(const Vector &other) const;
        Vector& multiplicateElementsAssign(const Vector &other);

        Vector divideElements(const Vector &other) const;
        Vector& divideElementsAssign(const Vector &other);

        Vector scale(float64 scale) const;
        Vector& scaleAssign(float64 scale);

        T dotProduct(const Vector &other) const;

        float32 length() const;

        Vector copy() const;

        boolean equal(const Vector &other) const;

        boolean unequal(const Vector &other) const;

        Vector& normalize();

        Vector invert() const;
        Vector& invertThis();

        Vector operator + (const Vector &other) const;
        Vector& operator += (const Vector &other);

        Vector operator - (const Vector &other) const;
        Vector& operator -= (const Vector &other);

        T operator * (const Vector &other) const;
        Vector operator * (const T &other) const;
        Vector& operator *= (const T &other);

        Vector operator - () const;

        boolean operator == (const Vector &other) const;
        boolean operator != (const Vector &other) const;
    };

    template<typename T>
    class NOU_CLASS Vector<T, 3> : public VectorBase<T, 3>
    {
    public:
        static Vector nullVector();

        Vector() = default;
        Vector(const T &x, const T &y, const T &z);
        Vector(const Vector<T, 2> &vec, const T &z);
        Vector(const typename VectorBase<T, 3>::InitializerList &values);
        Vector(const Vector<T, 2> &vec, const typename VectorBase<T, 3>::InitializerList &values);

        Vector add(const Vector &other) const;
        Vector& addAssign(const Vector &other);

        Vector sub(const Vector &other) const;
        Vector& subAssign(const Vector &other);

        Vector multiplicateElements(const Vector &other) const;
        Vector& multiplicateElementsAssign(const Vector &other);

        Vector divideElements(const Vector &other) const;
        Vector& divideElementsAssign(const Vector &other);

        Vector scale(float64 scale) const;
        Vector& scaleAssign(float64 scale);

        T dotProduct(const Vector &other) const;
        Vector crossProduct(const Vector &other) const;

        float32 length() const;

        Vector copy() const;

        boolean equal(const Vector &other) const;

        boolean unequal(const Vector &other) const;

        Vector& normalize();

        Vector invert() const;
        Vector& invertThis();

        Vector operator + (const Vector &other) const;
        Vector& operator += (const Vector &other);

        Vector operator - (const Vector &other) const;
        Vector& operator -= (const Vector &other);

        T operator * (const Vector &other) const;
        Vector operator * (const T &other) const;
        Vector& operator *= (const T &other);

        Vector operator - () const;

        boolean operator == (const Vector &other) const;
        boolean operator != (const Vector &other) const;
    };

    template<typename T>
    class NOU_CLASS Vector<T, 4> : public VectorBase<T, 4>
    {
    public:
        static Vector nullVector();

        Vector() = default;
        Vector(const T &x, const T &y, const T &z, const T &w);
        Vector(const Vector<T, 2> &vec, const T &z, const T &w);
        Vector(const Vector<T, 3> &vec, const T &w);
        Vector(const typename VectorBase<T, 4>::InitializerList &values);
        Vector(const Vector<T, 2> &vec, const typename VectorBase<T, 4>::InitializerList &values);
        Vector(const Vector<T, 3> &vec, const typename VectorBase<T, 4>::InitializerList &values);

        Vector add(const Vector &other) const;
        Vector& addAssign(const Vector &other);

        Vector sub(const Vector &other) const;
        Vector& subAssign(const Vector &other);

        Vector multiplicateElements(const Vector &other) const;
        Vector& multiplicateElementsAssign(const Vector &other);

        Vector divideElements(const Vector &other) const;
        Vector& divideElementsAssign(const Vector &other);

        Vector scale(float64 scale) const;
        Vector& scaleAssign(float64 scale);

        T dotProduct(const Vector &other) const;

        float32 length() const;

        Vector copy() const;

        boolean equal(const Vector &other) const;

        boolean unequal(const Vector &other) const;

        Vector& normalize();

        Vector invert() const;
        Vector& invertThis();

        Vector operator + (const Vector &other) const;
        Vector& operator += (const Vector &other);

        Vector operator - (const Vector &other) const;
        Vector& operator -= (const Vector &other);

        T operator * (const Vector &other) const;
        Vector operator * (const T &other) const;
        Vector& operator *= (const T &other);

        Vector operator - () const;

        boolean operator == (const Vector &other) const;
        boolean operator != (const Vector &other) const;
    };

    template<sizeType N>
    using Vecf = Vector<float32, N>;

    template<sizeType N>
    using Veci = Vector<int32, N>;

    using Vec2 = Vecf<2>;
    using Vec3 = Vecf<3>;
    using Vec4 = Vecf<4>;
    using Vec2i = Veci<2>;
    using Vec3i = Veci<3>;
    using Vec4i = Veci<4>;

    template<typename T, sizeType N>
    VectorBase<T, N>::VectorBase(const InitializerList &values)
    {
        NOU_ASSERT(values.size() == size());

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
        NOU_ASSERT(index < size());

        return m_data[index];
    }

    template<typename T, sizeType N>
    T& VectorBase<T, N>::value(sizeType index)
    {
        NOU_ASSERT(index < size());

        return m_data[index];
    }

    template<typename T, sizeType N>
    sizeType  VectorBase<T, N>::size() const
    {
        return N;
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
    Vector<T, N> Vector<T, N>::nullVector()
    {
        Vector<T, N> ret;

        for (sizeType i = 0; i < N; i++)
        {
            ret.value(i) = 0;
        }

        return ret;
    }

    template<typename T, sizeType N>
    Vector<T, N>::Vector(const typename VectorBase<T, N>::InitializerList &values) :
        VectorBase<T, N>(values)
    {}

    template<typename T, sizeType N>
    Vector<T, N>::Vector(const Vector<T, 2> &vec, const typename VectorBase<T, N>::InitializerList &values)
    {
        NOU_ASSERT(values.VectorBase<T, N>::size() == VectorBase<T, N>::size() - 2);

        VectorBase<T, N>::value(0) = vec.value(0);
        VectorBase<T, N>::value(1) = vec.value(1);

        sizeType index = 2;

        for (auto i = values.begin(); i != values.end(); i++)
        {
            VectorBase<T, N>::value(index++) = *i;
        }
    }

    template<typename T, sizeType N>
    Vector<T, N>::Vector(const Vector<T, 3> &vec, const typename VectorBase<T, N>::InitializerList &values)
    {
        NOU_ASSERT(values.VectorBase<T, N>::size() == VectorBase<T, N>::size() - 3);

        VectorBase<T, N>::value(0) = vec.value(0);
        VectorBase<T, N>::value(1) = vec.value(1);
        VectorBase<T, N>::value(2) = vec.value(2);

        sizeType index = 3;

        for (auto i = values.begin(); i != values.end(); i++)
        {
            VectorBase<T, N>::value(index++) = *i;
        }
    }

    template<typename T, sizeType N>
    Vector<T, N>::Vector(const Vector<T, 4> &vec, const typename VectorBase<T, N>::InitializerList &values)
    {
        NOU_ASSERT(values.size() == VectorBase<T, N>() - 4);

        VectorBase<T, N>::value(0) = vec.value(0);
        VectorBase<T, N>::value(1) = vec.value(1);
        VectorBase<T, N>::value(2) = vec.value(2);
        VectorBase<T, N>::value(3) = vec.value(3);

        sizeType index = 4;

        for (auto i = values.begin(); i != values.end(); i++)
        {
            VectorBase<T, N>::value(index++) = *i;
        }
    }

    template<typename T, sizeType N>
    Vector<T, N> Vector<T, N>::add(const Vector<T, N> &other) const
    {
        Vector<T, N> ret;

        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            ret.value(i) = VectorBase<T, N>::value(i) + other.value(i);
        }

        return ret;
    }

    template<typename T, sizeType N>
    Vector<T, N>& Vector<T, N>::addAssign(const Vector<T, N> &other)
    {
        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            VectorBase<T, N>::value(i) += other.value(i);
        }

        return *this;
    }

    template<typename T, sizeType N>
    Vector<T, N> Vector<T, N>::sub(const Vector<T, N> &other) const
    {
        Vector<T, N> ret;

        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            ret.value(i) = VectorBase<T, N>::value(i) - other.value(i);
        }

        return ret;
    }

    template<typename T, sizeType N>
    Vector<T, N>& Vector<T, N>::subAssign(const Vector<T, N> &other)
    {
        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            VectorBase<T, N>::value(i) -= other.value(i);
        }

        return *this;
    }

    template<typename T, sizeType N>
    Vector<T, N> Vector<T, N>::multiplicateElements(const Vector<T, N> &other) const
    {
        Vector<T, N> ret;

        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            ret.value(i) = VectorBase<T, N>::value(i) * other.value(i);
        }

        return ret;
    }

    template<typename T, sizeType N>
    Vector<T, N>& Vector<T, N>::multiplicateElementsAssign(const Vector<T, N> &other)
    {
        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            VectorBase<T, N>::value(i) *= other.value(i);
        }

        return *this;
    }

    template<typename T, sizeType N>
    Vector<T, N> Vector<T, N>::divideElements(const Vector<T, N> &other) const
    {
        Vector<T, N> ret;

        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            NOU_ASSERT(other.value(i) != 0);

            ret.value(i) = VectorBase<T, N>::value(i) / other.value(i);
        }

        return ret;
    }

    template<typename T, sizeType N>
    Vector<T, N>& Vector<T, N>::divideElementsAssign(const Vector<T, N> &other)
    {
        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            NOU_ASSERT(other.value(i) != 0);

            VectorBase<T, N>::value(i) /= other.value(i);
        }

        return *this;
    }

    template<typename T, sizeType N>
    Vector<T, N> Vector<T, N>::scale(float64 scale) const
    {
        Vector<T, N> ret;

        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            ret.value(i) = VectorBase<T, N>::value(i) * scale;
        }

        return ret;
    }

    template<typename T, sizeType N>
    Vector<T, N>& Vector<T, N>::scaleAssign(float64 scale)
    {
        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            VectorBase<T, N>::value(i) *= scale;
        }

        return *this;
    }

    template<typename T, sizeType N>
    T Vector<T, N>::dotProduct(const Vector<T, N> &other) const
    {
        //do this outside the loop to avoid having to initialize ret with 0 
        //(which might not work for any type)
        T ret = VectorBase<T, N>::value(0) * other.value(0); 

        for (sizeType i = 1; i < VectorBase<T, N>::size(); i++)
        {
            ret += VectorBase<T, N>::value(i) * other.value(i);
        }

        return ret;
    }

    template<typename T, sizeType N>
    float32 Vector<T, N>::length() const
    {
        return NOU_MATH::sqrt(*this * *this);
    }

    template<typename T, sizeType N>
    Vector<T, N> Vector<T, N>::copy() const
    {
        Vector<T, N> ret;

        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            ret.value(i) = VectorBase<T, N>::value(i);
        }

        return ret;
    }

    template<typename T, sizeType N>
    boolean Vector<T, N>::equal(const Vector<T, N> &other) const
    {
        if (VectorBase<T, N>::data() == other.VectorBase<T, N>::data())
            return true;

        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            if (VectorBase<T, N>::value(i) != other.value(i))
                return false;
        }

        return true;
    }

    template<typename T, sizeType N>
    boolean Vector<T, N>::unequal(const Vector<T, N> &other) const
    {
        return !equal(other);
    }

    template<typename T, sizeType N>
    Vector<T, N>& Vector<T, N>::normalize()
    {
        *this *= 1 / length();

        return *this;
    }

    template<typename T, sizeType N>
    Vector<T, N> Vector<T, N>::invert() const
    {
        Vector<T, N> ret;

        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            ret.value(i) = -VectorBase<T, N>::value(i);
        }

        return ret;
    }

    template<typename T, sizeType N>
    Vector<T, N>& Vector<T, N>::invertThis()
    {
        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            VectorBase<T, N>::value(i) = -VectorBase<T, N>::value(i);
        }

        return *this;
    }

    template<typename T, sizeType N>
    Vector<T, N> Vector<T, N>::operator + (const Vector<T, N> &other) const
    {
        return add(other);
    }

    template<typename T, sizeType N>
    Vector<T, N>& Vector<T, N>::operator += (const Vector<T, N> &other)
    {
        return addAssign(other);;
    }

    template<typename T, sizeType N>
    Vector<T, N> Vector<T, N>::operator - (const Vector<T, N> &other) const
    {
        return sub(other);
    }

    template<typename T, sizeType N>
    Vector<T, N>& Vector<T, N>::operator -= (const Vector<T, N> &other)
    {
        return subAssign(other);
    }

    template<typename T, sizeType N>
    T Vector<T, N>::operator * (const Vector<T, N> &other) const
    {
        return dotProduct(other);
    }

    template<typename T, sizeType N>
    Vector<T, N> Vector<T, N>::operator * (const T &other) const
    {
        return scale(other);
    }

    template<typename T, sizeType N>
    Vector<T, N>& Vector<T, N>::operator *= (const T &other)
    {
        return scaleAssign(other);
    }

    template<typename T, sizeType N>
    Vector<T, N> Vector<T, N>::operator - () const
    {
        return invert();
    }

    template<typename T, sizeType N>
    boolean Vector<T, N>::operator == (const Vector<T, N> &other) const
    {
        return equal(other);
    }

    template<typename T, sizeType N>
    boolean Vector<T, N>::operator != (const Vector<T, N> &other) const
    {
        return unequal(other);
    }





    template<typename T>
    Vector<T, 2> Vector<T, 2>::nullVector()
    {
        return Vector<T, 2>(0, 0);
    }

    template<typename T>
    Vector<T, 2>::Vector(const T &x, const T &y)
    {
        VectorBase<T, 2>::value(0) = x;
        VectorBase<T, 2>::value(1) = y;
    }

    template<typename T>
    Vector<T, 2>::Vector(const typename VectorBase<T, 2>::InitializerList &values) :
        VectorBase<T, 2>(values)
    {}

    template<typename T>
    Vector<T, 2> Vector<T, 2>::add(const Vector<T, 2> &other) const
    {
        return Vector<T, 2>(VectorBase<T, 2>::value(0) + other.value(0), VectorBase<T, 2>::value(1) + other.value(1));
    }

    template<typename T>
    Vector<T, 2>& Vector<T, 2>::addAssign(const Vector<T, 2> &other)
    {
        VectorBase<T, 2>::value(0) += other.value(0);
        VectorBase<T, 2>::value(1) += other.value(1);

        return *this;
    }

    template<typename T>
    Vector<T, 2> Vector<T, 2>::sub(const Vector<T, 2> &other) const
    {
        return Vector<T, 2>(VectorBase<T, 2>::value(0) - other.value(0), VectorBase<T, 2>::value(1) - other.value(1));
    }

    template<typename T>
    Vector<T, 2>& Vector<T, 2>::subAssign(const Vector<T, 2> &other)
    {
        VectorBase<T, 2>::value(0) -= other.value(0);
        VectorBase<T, 2>::value(1) -= other.value(1);

        return *this;
    }

    template<typename T>
    Vector<T, 2> Vector<T, 2>::multiplicateElements(const Vector<T, 2> &other) const
    {
        return Vector<T, 2>(VectorBase<T, 2>::value(0) * other.value(0), VectorBase<T, 2>::value(1) * other.value(1));
    }

    template<typename T>
    Vector<T, 2>& Vector<T, 2>::multiplicateElementsAssign(const Vector<T, 2> &other)
    {
        VectorBase<T, 2>::value(0) *= other.value(0);
        VectorBase<T, 2>::value(1) *= other.value(1);

        return *this;
    }

    template<typename T>
    Vector<T, 2> Vector<T, 2>::divideElements(const Vector<T, 2> &other) const
    {
        NOU_ASSERT(other.value(0) != 0);
        NOU_ASSERT(other.value(1) != 0);

        return Vector<T, 2>(VectorBase<T, 2>::value(0) / other.value(0), VectorBase<T, 2>::value(1) / other.value(1));
    }

    template<typename T>
    Vector<T, 2>& Vector<T, 2>::divideElementsAssign(const Vector<T, 2> &other)
    {
        NOU_ASSERT(other.value(0) != 0);
        NOU_ASSERT(other.value(1) != 0);

        VectorBase<T, 2>::value(0) /= other.value(0);
        VectorBase<T, 2>::value(1) /= other.value(1);

        return *this;
    }

    template<typename T>
    Vector<T, 2> Vector<T, 2>::scale(float64 scale) const
    {
        return Vector<T, 2>(VectorBase<T, 2>::value(0) * scale, VectorBase<T, 2>::value(1) * scale);
    }

    template<typename T>
    Vector<T, 2>& Vector<T, 2>::scaleAssign(float64 scale)
    {
        VectorBase<T, 2>::value(0) *= scale;
        VectorBase<T, 2>::value(1) *= scale;

        return *this;
    }

    template<typename T>
    T Vector<T, 2>::dotProduct(const Vector<T, 2> &other) const
    {
        return VectorBase<T, 2>::value(0) * other.value(0) + VectorBase<T, 2>::value(1) * other.value(1);
    }

    template<typename T>
    float32 Vector<T, 2>::length() const
    {
        return NOU_MATH::sqrt(*this * *this);
    }

    template<typename T>
    Vector<T, 2> Vector<T, 2>::copy() const
    {
        return Vector<T, 2>(VectorBase<T, 2>::value(0), VectorBase<T, 2>::value(1));
    }

    template<typename T>
    boolean Vector<T, 2>::equal(const Vector<T, 2> &other) const
    {
        return VectorBase<T, 2>::data() == other.VectorBase<T, 2>::data() || (VectorBase<T, 2>::value(0) == other.value(0) && VectorBase<T, 2>::value(1) == other.value(1));
    }

    template<typename T>
    boolean Vector<T, 2>::unequal(const Vector<T, 2> &other) const
    {
        return !equal(other);
    }

    template<typename T>
    Vector<T, 2>& Vector<T, 2>::normalize()
    {
        *this *= 1.0f / length();

        return *this;
    }

    template<typename T>
    Vector<T, 2> Vector<T, 2>::invert() const
    {
        Vector<T, 2> ret;

        ret.value(0) = -VectorBase<T, 2>::value(0);
        ret.value(1) = -VectorBase<T, 2>::value(1);

        return ret;
    }

    template<typename T>
    Vector<T, 2>& Vector<T, 2>::invertThis()
    {
        VectorBase<T, 2>::value(0) = -VectorBase<T, 2>::value(0);
        VectorBase<T, 2>::value(1) = -VectorBase<T, 2>::value(1);

        return *this;
    }

    template<typename T>
    Vector<T, 2> Vector<T, 2>::operator + (const Vector<T, 2> &other) const
    {
        return add(other);
    }

    template<typename T>
    Vector<T, 2>& Vector<T, 2>::operator += (const Vector<T, 2> &other)
    {
        return addAssign(other);;
    }

    template<typename T>
    Vector<T, 2> Vector<T, 2>::operator - (const Vector<T, 2> &other) const
    {
        return sub(other);
    }

    template<typename T>
    Vector<T, 2>& Vector<T, 2>::operator -= (const Vector<T, 2> &other)
    {
        return subAssign(other);
    }

    template<typename T>
    T Vector<T, 2>::operator * (const Vector<T, 2> &other) const
    {
        return dotProduct(other);
    }

    template<typename T>
    Vector<T, 2> Vector<T, 2>::operator * (const T &other) const
    {
        return scale(other);
    }

    template<typename T>
    Vector<T, 2>& Vector<T, 2>::operator *= (const T &other)
    {
        return scaleAssign(other);
    }

    template<typename T>
    Vector<T, 2> Vector<T, 2>::operator - () const
    {
        return invert();
    }

    template<typename T>
    boolean Vector<T, 2>::operator == (const Vector<T, 2> &other) const
    {
        return equal(other);
    }

    template<typename T>
    boolean Vector<T, 2>::operator != (const Vector<T, 2> &other) const
    {
        return unequal(other);
    }





    template<typename T>
    Vector<T, 3> Vector<T, 3>::nullVector()
    {
        return Vector<T, 3>(0, 0, 0);
    }

    template<typename T>
    Vector<T, 3>::Vector(const T &x, const T &y, const T &z)
    {
        VectorBase<T, 3>::value(0) = x;
        VectorBase<T, 3>::value(1) = y;
        VectorBase<T, 3>::value(2) = z;
    }

    template<typename T>
    Vector<T, 3>::Vector(const Vector<T, 2> &vec, const T &z) :
        Vector<T, 3>(vec.value(0), vec.value(1), z)
    {}

    template<typename T>
    Vector<T, 3>::Vector(const typename VectorBase<T, 3>::InitializerList &values) :
        VectorBase<T, 3>(values)
    {}

    template<typename T>
    Vector<T, 3>::Vector(const Vector<T, 2> &vec, const typename VectorBase<T, 3>::InitializerList &values)
    {
        NOU_ASSERT(values.size() == 1);

        VectorBase<T, 3>::value(0) = vec.value(0);
        VectorBase<T, 3>::value(1) = vec.value(1);

        sizeType index = 2;

        for (auto i = values.begin(); i != values.end(); i++)
        {
            VectorBase<T, 3>::value(index++) = *i;
        }
    }

    template<typename T>
    Vector<T, 3> Vector<T, 3>::add(const Vector<T, 3> &other) const
    {
        return Vector<T, 3>(VectorBase<T, 3>::value(0) + other.value(0), VectorBase<T, 3>::value(1) + other.value(1), VectorBase<T, 3>::value(2) + other.value(2));
    }

    template<typename T>
    Vector<T, 3>& Vector<T, 3>::addAssign(const Vector<T, 3> &other)
    {
         VectorBase<T, 3>::value(0) += other.value(0);
         VectorBase<T, 3>::value(1) += other.value(1);
         VectorBase<T, 3>::value(2) += other.value(2);

        return *this;
    }

    template<typename T>
    Vector<T, 3> Vector<T, 3>::sub(const Vector<T, 3> &other) const
    {
        return Vector<T, 3>(VectorBase<T, 3>::value(0) - other.value(0), VectorBase<T, 3>::value(1) - other.value(1), VectorBase<T, 3>::value(2) - other.value(2));
    }

    template<typename T>
    Vector<T, 3>& Vector<T, 3>::subAssign(const Vector<T, 3> &other)
    {
        VectorBase<T, 3>::value(0) -= other.value(0);
        VectorBase<T, 3>::value(1) -= other.value(1);
        VectorBase<T, 3>::value(2) -= other.value(2);

        return *this;
    }

    template<typename T>
    Vector<T, 3> Vector<T, 3>::multiplicateElements(const Vector<T, 3> &other) const
    {
        return Vector<T, 3>(VectorBase<T, 3>::value(0) * other.value(0), VectorBase<T, 3>::value(1) * other.value(1), VectorBase<T, 3>::value(2) * other.value(2));
    }

    template<typename T>
    Vector<T, 3>& Vector<T, 3>::multiplicateElementsAssign(const Vector<T, 3> &other)
    {
        VectorBase<T, 3>::value(0) *= other.value(0);
        VectorBase<T, 3>::value(1) *= other.value(1);
        VectorBase<T, 3>::value(2) *= other.value(2);

        return *this;
    }

    template<typename T>
    Vector<T, 3> Vector<T, 3>::divideElements(const Vector<T, 3> &other) const
    {
        NOU_ASSERT(other.value(0) != 0);
        NOU_ASSERT(other.value(1) != 0);
        NOU_ASSERT(other.value(2) != 0);

        return Vector<T, 3>(VectorBase<T, 3>::value(0) / other.value(0), VectorBase<T, 3>::value(1) / other.value(1), VectorBase<T, 3>::value(2) / other.value(2));
    }

    template<typename T>
    Vector<T, 3>& Vector<T, 3>::divideElementsAssign(const Vector<T, 3> &other)
    {
        NOU_ASSERT(other.value(0) != 0);
        NOU_ASSERT(other.value(1) != 0);
        NOU_ASSERT(other.value(2) != 0);

        VectorBase<T, 3>::value(0) /= other.value(0);
        VectorBase<T, 3>::value(1) /= other.value(1);
        VectorBase<T, 3>::value(2) /= other.value(2);

        return *this;
    }

    template<typename T>
    Vector<T, 3> Vector<T, 3>::scale(float64 scale) const
    {
        return Vector<T, 3>(VectorBase<T, 3>::value(0) * scale, VectorBase<T, 3>::value(1) * scale, VectorBase<T, 3>::value(2) * scale);
    }

    template<typename T>
    Vector<T, 3>& Vector<T, 3>::scaleAssign(float64 scale)
    {
        VectorBase<T, 3>::value(0) *= scale;
        VectorBase<T, 3>::value(1) *= scale;
        VectorBase<T, 3>::value(2) *= scale;

        return *this;
    }

    template<typename T>
    T Vector<T, 3>::dotProduct(const Vector<T, 3> &other) const
    {
        return VectorBase<T, 3>::value(0) * other.value(0) + VectorBase<T, 3>::value(1) * other.value(1) + VectorBase<T, 3>::value(2) * other.value(2);
    }

    template<typename T>
    Vector<T, 3> Vector<T, 3>::crossProduct(const Vector<T, 3> &other) const
    {
        return Vector<T, 3>(
                VectorBase<T, 3>::value(1) * other.value(2) - VectorBase<T, 3>::value(2) * other.value(1),
                VectorBase<T, 3>::value(2) * other.value(0) - VectorBase<T, 3>::value(0) * other.value(2),
                VectorBase<T, 3>::value(0) * other.value(1) - VectorBase<T, 3>::value(1) * other.value(0));
    }

    template<typename T>
    float32 Vector<T, 3>::length() const
    {
        return NOU_MATH::sqrt(*this * *this);
    }

    template<typename T>
    Vector<T, 3> Vector<T, 3>::copy() const
    {
        return Vector<T, 3>(VectorBase<T, 3>::value(0), VectorBase<T, 3>::value(1), VectorBase<T, 3>::value(2));
    }

    template<typename T>
    boolean Vector<T, 3>::equal(const Vector<T, 3> &other) const
    {
        return VectorBase<T, 3>::data() == other.VectorBase<T, 3>::data() || (VectorBase<T, 3>::value(0) == other.value(0) && VectorBase<T, 3>::value(1) == other.value(1) 
            && VectorBase<T, 3>::value(2) == other.value(2));
    }

    template<typename T>
    boolean Vector<T, 3>::unequal(const Vector<T, 3> &other) const
    {
        return !equal(other);
    }

    template<typename T>
    Vector<T, 3>& Vector<T, 3>::normalize()
    {
        *this *= 1 / length();

        return *this;
    }

    template<typename T>
    Vector<T, 3> Vector<T, 3>::invert() const
    {
        Vector<T, 3> ret;

        ret.value(0) = -VectorBase<T, 3>::value(0);
        ret.value(1) = -VectorBase<T, 3>::value(1);
        ret.value(2) = -VectorBase<T, 3>::value(2);

        return ret;
    }

    template<typename T>
    Vector<T, 3>& Vector<T, 3>::invertThis()
    {
        VectorBase<T, 3>::value(0) = -VectorBase<T, 3>::value(0);
        VectorBase<T, 3>::value(1) = -VectorBase<T, 3>::value(1);
        VectorBase<T, 3>::value(2) = -VectorBase<T, 3>::value(2);

        return *this;
    }

    template<typename T>
    Vector<T, 3> Vector<T, 3>::operator + (const Vector<T, 3> &other) const
    {
        return add(other);
    }

    template<typename T>
    Vector<T, 3>& Vector<T, 3>::operator += (const Vector<T, 3> &other)
    {
        return addAssign(other);;
    }

    template<typename T>
    Vector<T, 3> Vector<T, 3>::operator - (const Vector<T, 3> &other) const
    {
        return sub(other);
    }

    template<typename T>
    Vector<T, 3>& Vector<T, 3>::operator -= (const Vector<T, 3> &other)
    {
        return subAssign(other);
    }

    template<typename T>
    T Vector<T, 3>::operator * (const Vector<T, 3> &other) const
    {
        return dotProduct(other);
    }

    template<typename T>
    Vector<T, 3> Vector<T, 3>::operator * (const T &other) const
    {
        return scale(other);
    }

    template<typename T>
    Vector<T, 3>& Vector<T, 3>::operator *= (const T &other)
    {
        return scaleAssign(other);
    }

    template<typename T>
    Vector<T, 3> Vector<T, 3>::operator - () const
    {
        return invert();
    }

    template<typename T>
    boolean Vector<T, 3>::operator == (const Vector<T, 3> &other) const
    {
        return equal(other);
    }

    template<typename T>
    boolean Vector<T, 3>::operator != (const Vector<T, 3> &other) const
    {
        return unequal(other);
    }





    template<typename T>
    Vector<T, 4> Vector<T, 4>::nullVector()
    {
        return Vector<T, 4>(0, 0, 0, 0);
    }

    template<typename T>
    Vector<T, 4>::Vector(const T &x, const T &y, const T &z, const T &w)
    {
        VectorBase<T, 4>::value(0) = x;
        VectorBase<T, 4>::value(1) = y;
        VectorBase<T, 4>::value(2) = z;
        VectorBase<T, 4>::value(3) = w;
    }

    template<typename T>
    Vector<T, 4>::Vector(const Vector<T, 2> &vec, const T &z, const T &w)
    {
        VectorBase<T, 4>::value(0) = vec.value(0);
        VectorBase<T, 4>::value(1) = vec.value(1);
        VectorBase<T, 4>::value(2) = z;
        VectorBase<T, 4>::value(3) = w;
    }

    template<typename T>
    Vector<T, 4>::Vector(const Vector<T, 3> &vec, const T &w)
    {
        VectorBase<T, 4>::value(0) = vec.value(0);
        VectorBase<T, 4>::value(1) = vec.value(1);
        VectorBase<T, 4>::value(2) = vec.value(2);
        VectorBase<T, 4>::value(3) = w;
    }

    template<typename T>
    Vector<T, 4>::Vector(const typename VectorBase<T, 4>::InitializerList &values) :
        VectorBase<T, 4>(values)
    {}

    template<typename T>
    Vector<T, 4>::Vector(const Vector<T, 2> &vec, const typename VectorBase<T, 4>::InitializerList &values)
    {
        NOU_ASSERT(values.size() == 2);

        VectorBase<T, 4>::value(0) = vec.value(0);
        VectorBase<T, 4>::value(1) = vec.value(1);

        sizeType index = 2;

        for (auto i = values.begin(); i != values.end(); i++)
        {
            VectorBase<T, 4>::value(index++) = *i;
        }
    }

    template<typename T>
    Vector<T, 4>::Vector(const Vector<T, 3> &vec, const typename VectorBase<T, 4>::InitializerList &values)
    {
        NOU_ASSERT(values.size() == 1);

        VectorBase<T, 4>::value(0) = vec.value(0);
        VectorBase<T, 4>::value(1) = vec.value(1);
        VectorBase<T, 4>::value(2) = vec.value(2);

        sizeType index = 3;

        for (auto i = values.begin(); i != values.end(); i++)
        {
            VectorBase<T, 4>::value(index++) = *i;
        }
    }

    template<typename T>
    Vector<T, 4> Vector<T, 4>::add(const Vector<T, 4> &other) const
    {
        return Vector<T, 4>(VectorBase<T, 4>::value(0) + other.value(0), VectorBase<T, 4>::value(1) + other.value(1), VectorBase<T, 4>::value(2) + other.value(2), 
            VectorBase<T, 4>::value(3) + other.value(3));
    }

    template<typename T>
    Vector<T, 4>& Vector<T, 4>::addAssign(const Vector<T, 4> &other)
    {
        VectorBase<T, 4>::value(0) += other.value(0);
        VectorBase<T, 4>::value(1) += other.value(1);
        VectorBase<T, 4>::value(2) += other.value(2);
        VectorBase<T, 4>::value(3) += other.value(3);

        return *this;
    }

    template<typename T>
    Vector<T, 4> Vector<T, 4>::sub(const Vector<T, 4> &other) const
    {
        return Vector<T, 4>(VectorBase<T, 4>::value(0) - other.value(0), VectorBase<T, 4>::value(1) - other.value(1), VectorBase<T, 4>::value(2) - other.value(2), 
            VectorBase<T, 4>::value(3) - other.value(3));
    }

    template<typename T>
    Vector<T, 4>& Vector<T, 4>::subAssign(const Vector<T, 4> &other)
    {
        VectorBase<T, 4>::value(0) -= other.value(0);
        VectorBase<T, 4>::value(1) -= other.value(1);
        VectorBase<T, 4>::value(2) -= other.value(2);
        VectorBase<T, 4>::value(3) -= other.value(3);

        return *this;
    }

    template<typename T>
    Vector<T, 4> Vector<T, 4>::multiplicateElements(const Vector<T, 4> &other) const
    {
        return Vector<T, 4>(VectorBase<T, 4>::value(0) * other.value(0), VectorBase<T, 4>::value(1) * other.value(1), VectorBase<T, 4>::value(2) * other.value(2), 
            VectorBase<T, 4>::value(3) * other.value(3));
    }

    template<typename T>
    Vector<T, 4>& Vector<T, 4>::multiplicateElementsAssign(const Vector<T, 4> &other)
    {
        VectorBase<T, 4>::value(0) *= other.value(0);
        VectorBase<T, 4>::value(1) *= other.value(1);
        VectorBase<T, 4>::value(2) *= other.value(2);
        VectorBase<T, 4>::value(3) *= other.value(3);

        return *this;
    }

    template<typename T>
    Vector<T, 4> Vector<T, 4>::divideElements(const Vector<T, 4> &other) const
    {
        NOU_ASSERT(other.value(0) != 0);
        NOU_ASSERT(other.value(1) != 0);
        NOU_ASSERT(other.value(2) != 0);
        NOU_ASSERT(other.value(3) != 0);

        return Vector<T, 4>(VectorBase<T, 4>::value(0) / other.value(0), VectorBase<T, 4>::value(1) / other.value(1), VectorBase<T, 4>::value(2) / other.value(2), 
            VectorBase<T, 4>::value(3) / other.value(3));
    }

    template<typename T>
    Vector<T, 4>& Vector<T, 4>::divideElementsAssign(const Vector<T, 4> &other)
    {
        NOU_ASSERT(other.value(0) != 0);
        NOU_ASSERT(other.value(1) != 0);
        NOU_ASSERT(other.value(2) != 0);
        NOU_ASSERT(other.value(3) != 0);

        VectorBase<T, 4>::value(0) /= other.value(0);
        VectorBase<T, 4>::value(1) /= other.value(1);
        VectorBase<T, 4>::value(2) /= other.value(2);
        VectorBase<T, 4>::value(3) /= other.value(3);

        return *this;
    }

    template<typename T>
    Vector<T, 4> Vector<T, 4>::scale(float64 scale) const
    {
        return Vector<T, 4>(VectorBase<T, 4>::value(0) * scale, VectorBase<T, 4>::value(1) * scale, VectorBase<T, 4>::value(2) * scale, VectorBase<T, 4>::value(3) * scale);
    }

    template<typename T>
    Vector<T, 4>& Vector<T, 4>::scaleAssign(float64 scale)
    {
        VectorBase<T, 4>::value(0) *= scale;
        VectorBase<T, 4>::value(1) *= scale;
        VectorBase<T, 4>::value(2) *= scale;
        VectorBase<T, 4>::value(3) *= scale;

        return *this;
    }

    template<typename T>
    T Vector<T, 4>::dotProduct(const Vector<T, 4> &other) const
    {
        return VectorBase<T, 4>::value(0) * other.value(0) + VectorBase<T, 4>::value(1) * other.value(1) + VectorBase<T, 4>::value(2) * other.value(2)
            + VectorBase<T, 4>::value(3) * other.value(3);
    }

    template<typename T>
    float32 Vector<T, 4>::length() const
    {
        return NOU_MATH::sqrt(*this * *this);
    }

    template<typename T>
    Vector<T, 4> Vector<T, 4>::copy() const
    {
        return Vector<T, 4>(VectorBase<T, 4>::value(0), VectorBase<T, 4>::value(1), VectorBase<T, 4>::value(2), VectorBase<T, 4>::value(3));
    }

    template<typename T>
    boolean Vector<T, 4>::equal(const Vector<T, 4> &other) const
    {
        return VectorBase<T, 4>::data() == other.data() || (VectorBase<T, 4>::value(0) == other.value(0) && VectorBase<T, 4>::value(1) == other.value(1) && 
            VectorBase<T, 4>::value(2) == other.value(2) && VectorBase<T, 4>::value(3) == other.value(3));
    }

    template<typename T>
    boolean Vector<T, 4>::unequal(const Vector<T, 4> &other) const
    {
        return !equal(other);
    }

    template<typename T>
    Vector<T, 4>& Vector<T, 4>::normalize()
    {
        *this *= 1 / length();

        return *this;
    }

    template<typename T>
    Vector<T, 4> Vector<T, 4>::invert() const
    {
        Vector<T, 4> ret;

        ret.value(0) = -VectorBase<T, 4>::value(0);
        ret.value(1) = -VectorBase<T, 4>::value(1);
        ret.value(2) = -VectorBase<T, 4>::value(2);
        ret.value(3) = -VectorBase<T, 4>::value(3);

        return ret;
    }

    template<typename T>
    Vector<T, 4>& Vector<T, 4>::invertThis()
    {
        VectorBase<T, 4>::value(0) = -VectorBase<T, 4>::value(0);
        VectorBase<T, 4>::value(1) = -VectorBase<T, 4>::value(1);
        VectorBase<T, 4>::value(2) = -VectorBase<T, 4>::value(2);
        VectorBase<T, 4>::value(3) = -VectorBase<T, 3>::value(3);

        return *this;
    }

    template<typename T>
    Vector<T, 4> Vector<T, 4>::operator + (const Vector<T, 4> &other) const
    {
        return add(other);
    }

    template<typename T>
    Vector<T, 4>& Vector<T, 4>::operator += (const Vector<T, 4> &other)
    {
        return addAssign(other);;
    }

    template<typename T>
    Vector<T, 4> Vector<T, 4>::operator - (const Vector<T, 4> &other) const
    {
        return sub(other);
    }

    template<typename T>
    Vector<T, 4>& Vector<T, 4>::operator -= (const Vector<T, 4> &other)
    {
        return subAssign(other);
    }

    template<typename T>
    T Vector<T, 4>::operator * (const Vector<T, 4> &other) const
    {
        return dotProduct(other);
    }

    template<typename T>
    Vector<T, 4> Vector<T, 4>::operator * (const T &other) const
    {
        return scale(other);
    }

    template<typename T>
    Vector<T, 4>& Vector<T, 4>::operator *= (const T &other)
    {
        return scaleAssign(other);
    }

    template<typename T>
    Vector<T, 4> Vector<T, 4>::operator - () const
    {
        return invert();
    }

    template<typename T>
    boolean Vector<T, 4>::operator == (const Vector<T, 4> &other) const
    {
        return equal(other);
    }

    template<typename T>
    boolean Vector<T, 4>::operator != (const Vector<T, 4> &other) const
    {
        return unequal(other);
    }
}

#endif