#ifndef _2DE_VECTOR3_H_
#define _2DE_VECTOR3_H_

//#include "2de_Math.h"

#define __INLINE inline

class Vector3
{
public:
	float x, y, z;

	__INLINE Vector3(float Ax = 0.0f, float Ay = 0.0f, float Az = 0.0f) : x(Ax), y(Ay), z(Az){}

	__INLINE float operator[](int i)
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

	__INLINE Vector3 operator +(float s) const
	{
		return Vector3(x + s, y + s, z + s);
	}

	__INLINE Vector3 operator -(float s) const
	{
		return Vector3(x - s, y - s, z - s);
	}

	__INLINE Vector3 operator *(float s) const
	{
		return Vector3(x * s, y * s, z * s);
	}

	__INLINE Vector3 operator /(float s) const
	{
		assert(s != 0.0f);
		float t = 1.0f / s;
		return Vector3(x * t, y * t, z * t);
	}

	friend Vector3 operator *(float s, const Vector3 &v)
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

	__INLINE float operator *(const Vector3 &v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	__INLINE Vector3 operator ^(const Vector3 &v) const
	{
		return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	__INLINE float Length() const
	{
		return static_cast<float>(sqrt(static_cast<double>(x * x + y * y + z * z)));
	}

	float Normalize()
	{
		float l = Length();
		assert(l != 0.0f);
		(*this) *= (1.0f / l);
		return l;
	}

	Vector3 Normalized()
	{
		float l = Length();
		assert(l != 0.0f);
		Vector3 t = (*this) * (1.0f / l);
		return t;
	}

	float ComputeNormal(const Vector3& V0, const Vector3& V1, const Vector3& V2)
	{
		Vector3 E = V1 - V0;
		Vector3 F = V2 - V1;
		(*this)  = E ^ F;
		return (*this).Normalize();
	}
};

//template<>
//__INLINE Vector3 Clamp(const Vector3 &x, const Vector3 &min, const Vector3 &max)
//{
//	Vector3 result;
//	result.x = Clamp(x.x, min.x, max.x);
//	result.y = Clamp(x.y, min.y, max.y);
//	result.z = Clamp(x.z, min.z, max.z);
//	return result;
//}

#endif	//	_2DE_VECTOR3_H_
