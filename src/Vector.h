#ifndef VECTOR_H
#define VECTOR_H

#ifndef PI
#define PI 3.1415926f
#endif

// general functions

inline float squared(float n);

struct Vector2 {
	float u, v;

	Vector2();
	Vector2(float u, float v);
	Vector2(const Vector2& v2);

	virtual ~Vector2();

	void print();
};

struct Vector3 {
	float x, y, z;

	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3& v);
	Vector3(float f);

	virtual ~Vector3();

	inline float length2();
	inline float length();

	float normalize();
	Vector3 normalized();
	void print();

	Vector3& operator =(const Vector3& v);
	Vector3& operator +=(const Vector3& v);
	Vector3& operator -=(const Vector3& v);
	Vector3& operator *=(float f);
	Vector3& operator /=(float f);

};

float dot(const Vector3& v1, const Vector3& v2);
Vector3 cross(const Vector3& v1, const Vector3& v2);
Vector3 reflect(const Vector3& v1, const Vector3& v2);

inline Vector3 operator +(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z);
}

inline Vector3 operator -(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z);
}

inline Vector3 operator *(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x * v2.x,
		v1.y * v2.y,
		v1.z * v2.z);
}

inline Vector3 operator *(const Vector3& v, float f)
{
	return Vector3(v.x * f,
		v.y * f,
		v.z * f);
}

inline Vector3 operator *(float f, const Vector3& v)
{
	return Vector3(f * v.x,
		f * v.y,
		f * v.z);
}

inline Vector3 operator /(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x / v2.x,
		v1.y / v2.y,
		v1.z / v2.z);
}

inline Vector3 operator /(const Vector3& v, float f)
{
	return Vector3(v.x / f,
		v.y / f,
		v.z / f);
}

inline Vector3 operator /(float f, const Vector3& v)
{
	return Vector3(f / v.x,
		f / v.y,
		f / v.z);
}

typedef Vector3 Point;

#endif