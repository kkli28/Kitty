#ifndef __VEC3_H__
#define __VEC3_H__

#include "std.h"

class Vec3 {
public:
	float x;
	float y;
	float z;

public:
	Vec3() : x(0.0f), y(0.0f), z(0.0f) {};
	Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
	Vec3(float nx, float ny, float nz) : x(nx), y(ny), z(nz) {}
	Vec3& operator=(const Vec3& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
	void zero() { x = y = z = 0.0f; }

	bool operator==(const Vec3& v) { return x == v.x && y == v.y && z == v.z; }
	bool operator!=(const Vec3& v) { return x != v.x || y != v.y || z != v.z; }

	Vec3 operator-() const { return Vec3(-x, -y, -z); }

	Vec3 operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
	Vec3 operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
	Vec3& operator+=(const Vec3& v) { x += v.x; y += v.y; z += v.z; return *this; }
	Vec3& operator-=(const Vec3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }

	Vec3 operator*(float f) const { return Vec3(x * f, y * f, z * f); }
	Vec3 operator/(float f) const { return Vec3(x / f, y / f, z / f); }
	Vec3& operator*=(float f) { x *= f; y *= f; z *= f; return *this; }
	Vec3& operator/=(float f) { x /= f; y /= f; z /= f; return *this; }
	void normalize() {
		float magSq = x * x + y * y + z * z;
		if (magSq > 0.0f) {
			float oneOverMag = 1.0f / magSq;
			x *= oneOverMag;
			y *= oneOverMag;
			z *= oneOverMag;
		}
	}

	float operator*(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }

public:
	static inline float mag(const Vec3& v) { return std::sqrt(v.x*v.x + v.y*v.y + v.z * v.z); }

	static inline Vec3 cossProduct(const Vec3& v1, const Vec3& v2) {
		return Vec3(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x
		);
	}

	static inline float distance(const Vec3& v1, const Vec3& v2) {
		float dx = v1.x - v2.x;
		float dy = v1.y - v2.y;
		float dz = v1.z - v2.z;
		return std::sqrt(dx * dx + dy * dy + dz * dz);
	}
};

inline Vec3 operator*(float f, const Vec3& v) { return Vec3(f * v.x, f * v.y, f * v.z); }

#endif // __VEC3_H__
