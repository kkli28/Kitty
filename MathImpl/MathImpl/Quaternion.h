#ifndef __QUATERNION_H__
#define __QUATERNION_H__

// Quaternion: save Orientation or Angular

#include "std.h"

class Vec3;
class EulerAngles;

class Quaternion {
public:
	float w;
	float x;
	float y;
	float z;

public:
	Quaternion() : w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}
	Quaternion(float nw, float nx, float ny, float nz) : w(nw), x(nx), y(ny), z(nz) {}

	void identity() { w = 1.0f; x = y = z = 0.0f; }

	void setToRotateAboutX(float theta);
	void setToRotateAboutY(float theta);
	void setToRotateAboutZ(float theta);
	void setToRotateAboutAxis(const Vec3& u, float theta);

	void setToRotateObjectToInertial(const EulerAngles& e);
	void setToRotateInertialToObject(const EulerAngles& e);

	Quaternion operator*(const Quaternion& q) const;
	Quaternion& operator*=(const Quaternion& q);

	void normalize();

	float getRotationAngle() const;
	Vec3 getRotationAxis() const;

public:
	static float dotProduct(const Quaternion& q1, const Quaternion& q2);
	static Quaternion slerp(const Quaternion& q1, const Quaternion& q2, float t);
	static Quaternion conjugate(const Quaternion& q);
	static Quaternion pow(const Quaternion& q, float e);
};

#endif // __QUATERNION_H__
