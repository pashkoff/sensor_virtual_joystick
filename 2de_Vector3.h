#ifndef _2DE_VECTOR3_H_
#define _2DE_VECTOR3_H_

#include <cassert>
#include <cmath>

//#include "2de_Math.h"


#define __INLINE inline

class Vector3
{
public:
	typedef double value_type;
	value_type x, y, z;

	__INLINE Vector3(value_type Ax = 0.0f, value_type Ay = 0.0f, value_type Az = 0.0f) : x(Ax), y(Ay), z(Az){}

	__INLINE value_type operator[](int i)
	{
		assert(i >= 0 && i <= 2);
		return *(&x + i);
	}

	__INLINE Vector3 operator +(const Vector3 &v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	__INLINE Vector3 operator -(const Vector3 &v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	__INLINE Vector3 operator +(value_type s) const
	{
		return Vector3(x + s, y + s, z + s);
	}

	__INLINE Vector3 operator -(value_type s) const
	{
		return Vector3(x - s, y - s, z - s);
	}

	__INLINE Vector3 operator *(value_type s) const
	{
		return Vector3(x * s, y * s, z * s);
	}

	__INLINE Vector3 operator /(value_type s) const
	{
		assert(s != 0.0f);
		value_type t = 1.0f / s;
		return Vector3(x * t, y * t, z * t);
	}

	friend Vector3 operator *(value_type s, const Vector3 &v)
	{
		return Vector3(v.x * s, v.y * s, v.z * s);
	}

	__INLINE Vector3& operator +=(const Vector3 &v)
	{ 
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	__INLINE Vector3& operator -=(const Vector3 &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	__INLINE Vector3& operator *=(float s)
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	__INLINE Vector3& operator /=(float s)
	{
		return *this = *this / s;
	}

	__INLINE Vector3 operator -() const
	{
		return Vector3(-x, -y, -z);
	}

	__INLINE value_type operator *(const Vector3 &v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	__INLINE Vector3 operator ^(const Vector3 &v) const
	{
		return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	__INLINE value_type Length() const
	{
		return static_cast<value_type>(sqrt(static_cast<value_type>(x * x + y * y + z * z)));
	}

	value_type Normalize()
	{
		value_type l = Length();
		assert(l != 0.0);
		(*this) *= (1.0 / l);
		return l;
	}

	Vector3 Normalized()
	{
		value_type l = Length();
		assert(l != 0.0f);
		Vector3 t = (*this) * (1.0f / l);
		return t;
	}

	value_type ComputeNormal(const Vector3& V0, const Vector3& V1, const Vector3& V2)
	{
		Vector3 E = V1 - V0;
		Vector3 F = V2 - V1;
		(*this)  = E ^ F;
		return (*this).Normalize();
	}
};

template<typename T>
__INLINE T clamp(const T &x , const T &min, const T &max)
{
	return std::min(std::max(x, min), max);
}

template<>
__INLINE Vector3 clamp(const Vector3 &x, const Vector3 &min, const Vector3 &max)
{
	Vector3 result;
	result.x = clamp(x.x, min.x, max.x);
	result.y = clamp(x.y, min.y, max.y);
	result.z = clamp(x.z, min.z, max.z);
	return result;
}

#endif	//	_2DE_VECTOR3_H_
