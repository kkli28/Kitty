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

	void fromQuaternion(const Quaternion& q);
	void setupScale(const Vec3& v);
	void setupScaleAlongAxis(const Vec3& axis, float k);
	void setupShear(int axis, float s, float t);
	void setupProject(const Vec3& v);
	void setupReflect(int axis, float k = 0.0f);
	void setupReflect(const Vec3& v);

public:
	static float determinant(const Matrix4x3& m);
	static Matrix4x3 inverse(const Matrix4x3& m);
	Vec3& getTranslation(const Matrix4x3& m);

	Vec3 getPositionFromParentToLocalMatrix(const Matrix4x3& m);
	Vec3 getPositionFromLocalToParentMatrix(const Matrix4x3& m);
};

Vec3 operator*(const Vec3& v, const Matrix4x3& m);
Vec3& operator*=(Vec3& v, const Matrix4x3& m);
Matrix4x3 operator*(const Matrix4x3& m1, const Matrix4x3& m2);
Matrix4x3& operator*=(Matrix4x3& m1, const Matrix4x3& m2);

#endif // __MATRIX_4X3__
