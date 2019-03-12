#include "Matrix4x3.h"
#include "MathUtil.h"
#include "Vec3.h"
#include "EulerAngles.h"
#include "Quaternion.h"
#include "RotationMatrix.h"

void Matrix4x3::setTranslation(const Vec3& v) {
	tx = v.x; ty = v.y; tz = v.z;
}

void Matrix4x3::setupTranslation(const Vec3& v) {
	m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
	m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
	tx = v.x;   ty = v.y;   tz = v.z;
}

void Matrix4x3::setupLocalToParent(const Vec3& pos, const EulerAngles& e) {
	RotationMatrix r;
	r.setup(e);
	setupLocalToParent(pos, r);
}

void Matrix4x3::setupLocalToParent(const Vec3& pos, const RotationMatrix& r) {
	m11 = r.m11; m12 = r.m21; m13 = r.m31;
	m21 = r.m12; m22 = r.m22; m23 = r.m32;
	m31 = r.m13; m32 = r.m23; m33 = r.m33;
	tx = pos.x;  ty = pos.y;  tz = pos.z;
}

void Matrix4x3::setupParentToLocal(const Vec3& pos, const EulerAngles& e) {
	RotationMatrix r;
	r.setup(e);
	setupParentToLocal(pos, r);
}

void Matrix4x3::setupParentToLocal(const Vec3& pos, const RotationMatrix& r) {
	m11 = r.m11; m12 = r.m12; m13 = r.m13;
	m21 = r.m21; m22 = r.m22; m23 = r.m23;
	m31 = r.m31; m32 = r.m32; m33 = r.m33;
	tx = -(pos.x * m11 + pos.y * m21 + pos.z * m31);
	ty = -(pos.x * m12 + pos.y * m22 + pos.z * m32);
	tx = -(pos.x * m13 + pos.y * m23 + pos.z * m33);
}

void Matrix4x3::setupRotate(int axis, float theta) {
	float s, c;
	MathUtil::sinCos(&s, &c, theta);
	switch (axis) {
	case 1: // x
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
		m21 = 0.0f; m22 = c;    m23 = s;
		m31 = 0.0f; m32 = -s;   m33 = c;

	case 2: // y
		m11 = c;    m12 = 0.0f; m13 = -s;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m31 = s;    m32 = 0.0f; m33 = c;

	case 3: // z
		m11 = c;    m12 = s;    m13 = 0.0f;
		m21 = -s;   m22 = c;    m23 = 0.0f;
		m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;

	default:
		assert(false);
	}
	tx = ty = tz = 0.0f;
}

void Matrix4x3::setupRotate(const Vec3& axis, float theta) {
	assert(fabs(axis*axis - 1.0f) < PRECISION);

	float s, c;
	MathUtil::sinCos(&s, &c, theta);
	float xx = axis.x * axis.x;
	float yy = axis.y * axis.y;
	float zz = axis.z * axis.z;
	float xy = axis.x * axis.y;
	float xz = axis.x * axis.z;
	float yz = axis.y * axis.z;
	float xs = axis.x * s;
	float ys = axis.y * s;
	float zs = axis.z * s;
	float c1 = 1.0f - c;

	m11 = xx * c1 + c;
	m12 = xy * c1 + zs;
	m13 = xz * c1 - ys;

	m21 = xy * c1 - zs;
	m22 = yy * c1 + c;
	m23 = yz * c1 + xs;

	m31 = xz * c1 + ys;
	m32 = yz * c1 - xs;
	m33 = zz * c1 + c;

	tx = ty = tz = 0.0f;
}
