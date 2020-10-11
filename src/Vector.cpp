#include <cmath>
#include "Vector.h"
#include <iostream>

// operations
inline float squared(float f) {
return f * f;
}

float dot(const Vector3& v1, const Vector3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 cross(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}


Vector3 reflect(const Vector3& v1, const Vector3& v2)
{
	float f = dot(v1, v2);
	return Vector3(v1 - v2 * 2.0f * f);
}

// Vector2
Vector2::Vector2() :
	u(0.0f),
	v(0.0f)
{}

Vector2::Vector2(float u, float v) :
	u(u),
	v(v)
{}

Vector2::Vector2(const Vector2& v2) :
	u(v2.u),
	v(v2.v)
{}

void Vector2::print() {
	std::cout << "2D Vector with u: " << u << " v: " << v << std::endl;
}

Vector2::~Vector2()
{}

// Vector3
Vector3::Vector3() :
	x(1.0f),
	y(0.0f),
	z(0.0f)
{}

Vector3::Vector3(float x, float y, float z) :
	x(x),
	y(y),
	z(z)
{}

Vector3::Vector3(const Vector3& v) :
	x(v.x),
	y(v.y),
	z(v.z)
{}

Vector3::Vector3(float f) :
	x(f),
	y(f),
	z(f)
{}

void Vector3::print() {
	std::cout << 
		"3D Vector with x: " << x << 
		" y: " << y << 
		" z: " << z << std::endl;
}

inline float Vector3::length2() {
	return squared(x) + squared(y) + squared(z);
}

inline float Vector3::length() {
	return std::sqrt(length2());
}

float Vector3::normalize() {
	float l = length();
	*this /= l;
	return l;
}

Vector3 Vector3::normalized() {
	Vector3 v(*this);
	v.normalize();
	return v;
}

// Operators
Vector3& Vector3::operator =(const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;

	return *this;
}

Vector3& Vector3::operator +=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3& Vector3::operator -=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3& Vector3::operator *=(float f)
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}

Vector3& Vector3::operator /=(float f)
{
	x /= f;
	y /= f;
	z /= f;
	return *this;
}

Vector3::~Vector3()
{}