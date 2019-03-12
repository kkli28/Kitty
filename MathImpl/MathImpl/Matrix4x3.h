#ifndef __MATRIX_4X3_H__
#define __MATRIX_4X3_H__

// Matrix4x3

#include "std.h"

class Vec3;
class EulerAngles;
class Quaternion;
class RotationMatrix;

class Matrix4x3 {
public:
	float m11, m12, m13;
	float m21, m22, m23;
	float m31, m32, m33;
	float tx,  ty,  tz;

public:
	Matrix4x3() : m11(1.0f), m12(0.0f), m13(0.0f), m21(0.0f), m22(1.0f), m23(0.0f),
		m31(0.0f), m32(0.0f), m33(1.0f), tx(0.0f), ty(0.0f), tz(1.0f) {}

	void identity() {
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		tx = 0.0f; ty = 0.0f; tz = 1.0f;
	}

	void zeroTranslation() { tx = ty = tz = 0.0f; }
	void setTranslation(const Vec3& v);
	void setupTranslation(const Vec3& v);

	void setupLocalToParent(const Vec3& pos, const EulerAngles& e);
	void setupLocalToParent(const Vec3& pos, const RotationMatrix& r);
	void setupParentToLocal(const Vec3& pos, const EulerAngles& e);
	void setupParentToLocal(const Vec3& pos, const RotationMatrix& r);

	void setupRotate(int axis, float theta);
	void setupRotate(const Vec3& axis, float theta);

	// TODO:
	// void fromQuaternion(const Quaternion& q);
};

#endif // __MATRIX_4X3__
