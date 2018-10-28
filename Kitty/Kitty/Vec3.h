#ifndef __VEC3_H__
#define __VEC3_H__

#include <cmath>

class Vec3 {
public:
	float x, y, z;

	// 构造函数
	Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vec3(float nx, float ny, float nz) : x(nx), y(ny), z(nz) {}
	Vec3(const Vec3& vec) : x(vec.x), y(vec.y), z(vec.z) {}

	// 赋值操作
	Vec3& operator=(const Vec3& vec) {
		x = vec.x;
		y = vec.y;
		z = vec.z;
		return *this;
	}

	// 置零
	void zero() {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	// 取反
	Vec3 operator-() const {
		return Vec3(-x, -y, -z);
	}

	// 加减法
	Vec3 operator+(const Vec3& vec) const {
		return Vec3(x + vec.x, y + vec.y, z + vec.z);
	}
	Vec3& operator+=(const Vec3& vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}
	Vec3 operator-(const Vec3& vec) const {
		return Vec3(x - vec.x, y - vec.y, z - vec.z);
	}
	Vec3& operator-=(const Vec3& vec) {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}

	// 标量乘法：kV
	Vec3 operator*(float k) const {
		return Vec3(x * k, y * k, z * k);
	}
	Vec3& operator*=(float k) {
		x *= k;
		y *= y;
		z *= z;
		return *this;
	}

	// 标量除法：V/k
	Vec3 operator/(float k) const {
		float t = 1.0f / k;
		return Vec3(x * t, y * t, z * t);
	}

	Vec3& operator/=(float k) {
		float t = 1.0f / k;
		x *= t;
		y *= t;
		z *= t;
		return *this;
	}

	// 标准化
	void normalize() {
		float magSq = x * x + y * y + z * z;
		if (magSq > 0) {
			float t = 1.0f / magSq;
			x *= t;
			y *= t;
			z *= t;
		}
	}

	// 点乘
	float operator*(const Vec3& vec) const {
		return x * vec.x + y * vec.y + z * vec.z;
	}

public:
	static inline float mag(const Vec3& vec) {
		return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	}
	static inline float distance(const Vec3& p1, const Vec3& p2) {
		float dx = p1.x - p2.x;
		float dy = p1.y - p2.y;
		float dz = p1.z - p2.z;
		return sqrt(dx * dx + dy * dy + dz * dz);
	}
	static inline Vec3 cross(const Vec3& vec1, const Vec3& vec2) {
		return Vec3(
			vec1.y * vec2.z - vec1.z * vec2.y,
			vec1.z * vec2.x - vec1.x * vec2.z,
			vec1.x * vec2.y - vec1.y * vec2.x
		);
	}
};

// ==
inline bool operator==(const Vec3& vec1, const Vec3& vec2) {
	return vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z;
}

// !=
inline bool operator!=(const Vec3& vec1, const Vec3& vec2) {
	return !(vec1 == vec2);
}

// kV
inline Vec3 operator*(float k, const Vec3& vec) {
	return vec * k;
}

#endif // __VEC3_H__
