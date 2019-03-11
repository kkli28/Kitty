#ifndef __ROTATION_MATRIX_H__
#define __ROTATION_MATRIX_H__

// RotationMatrix: a 3x3 orthogonal matrix, assume only contain rotation

#include "std.h"

class Vec3;
class EulerAngles;
class Quaternion;

class RotationMatrix {
public:
	float m11, m12, m13;
	float m21, m22, m23;
	float m31, m32, m33;

public:
	RotationMatrix() : m11(1.0f), m12(0.0f), m13(0.0f), m21(0.0f), m22(1.0f), m23(0.0f), m31(0.0f), m32(0.0f), m33(1.0f) {}

	void identity() { 
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
	}

	// Construct matrix
	void setup(const EulerAngles& e);
	void fromInertialToObjectQuaternion(const Quaternion& q);
	void fromObjectToInertialQuaternion(const Quaternion& q);

	// Do rotation
	Vec3 inertialToObject(const Vec3& v) const;
	Vec3 objectToInertial(const Vec3& v) const;
};

#endif // __ROTATION_MATRIX_H__
