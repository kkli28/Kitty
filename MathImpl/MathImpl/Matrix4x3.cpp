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

void Matrix4x3::fromQuaternion(const Quaternion& q) {
	float xx = q.x * q.x;
	float yy = q.y * q.y;
	float zz = q.z * q.z;
	float wx = q.w * q.x;
	float wy = q.w * q.y;
	float wz = q.w * q.z;
	float xy = q.x * q.y;
	float xz = q.x * q.z;
	float yz = q.y * q.z;

	m11 = 1.0f - 2.0f * (yy + zz);
	m12 = 2.0f * (xy + wz);
	m13 = 2.0f * (xz - wy);

	m21 = 2.0f * (xy - wz);
	m22 = 1.0f - 2.0f * (xx + zz);
	m23 = 2.0f * (wx + yz);

	m31 = 2.0f * (wy + xz);
	m32 = 2.0f * (yz - wx);
	m33 = 1.0f - 2.0f * (xx + yy);

	tx = ty = tz = 0.0f;
}

void Matrix4x3::setupScale(const Vec3& v) {
	m11 = v.x;  m12 = 0.0f; m13 = 0.0f;
	m21 = 0.0f; m22 = v.y;  m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = v.z;
	tx = ty = tz = 0.0f;
}

void Matrix4x3::setupScaleAlongAxis(const Vec3& axis, float k) {
	assert(fabs(axis * axis - 1.0f) < PRECISION);

	float k1 = k - 1.0f;
	
	m11 = 1.0f + k1 * axis.x * axis.x;
	m22 = 1.0f + k1 * axis.y * axis.y;
	m33 = 1.0f + k1 * axis.z * axis.z;

	m12 = m21 = k1 * axis.x * axis.y;
	m13 = m31 = k1 * axis.x * axis.z;
	m23 = m32 = k1 * axis.y * axis.z;

	tx = ty = tz = 0.0f;
}

void Matrix4x3::setupShear(int axis, float s, float t) {
	switch (axis) {
	case 1:
		m11 = 1.0f; m12 = s;    m13 = t;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		break;

	case 2:
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
		m21 = s;    m22 = 1.0f; m23 = t;
		m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		break;

	case 3:
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m31 = s;    m32 = t;    m33 = 1.0f;
		break;

	default:
		assert(false);
	}

	tx = ty = tz = 0.0f;
}

void Matrix4x3::setupProject(const Vec3& v) {
	assert(fabs(v * v - 1.0f) < PRECISION);

	m11 = 1.0f - v.x * v.x;
	m22 = 1.0f - v.y * v.y;
	m33 = 1.0f - v.z * v.z;

	m12 = m21 = -v.x * v.y;
	m13 = m31 = -v.x * v.z;
	m23 = m32 = -v.y * v.z;

	tx = ty = tz = 0.0f;
}

void Matrix4x3::setupReflect(int axis, float k) {
	m12 = m13 = m21 = m23 = m31 = m32 = 0.0f;
	switch (axis) {
	case 1:
		m11 = -1.0f; m22 = 1.0f; m33 = 1.0f;
		tx = 2.0f * k; ty = 0.0f; tz = 0.0f;
		break;

	case 2:
		m11 = 1.0f; m22 = -1.0f; m33 = 1.0f;
		ty = 2.0f * k; tx = 0.0f;  tz = 0.0f;
		break;

	case 3:
		m11 = 1.0f; m22 = 1.0f; m33 = -1.0f;
		tz = 2.0f * k;  tx = 0.0f; ty = 0.0f;
		break;
		
	default:
		assert(false);
	}
}

void Matrix4x3::setupReflect(const Vec3& v) {
	assert(fabs(v * v - 1.0f) < PRECISION);
	
	m11 = 1.0f - 2.0f * v.x * v.x;
	m22 = 1.0f - 2.0f * v.y * v.y;
	m33 = 1.0f - 2.0f * v.z * v.z;
	
	m12 = m21 = -2.0f * v.x * v.y;
	m13 = m31 = -2.0f * v.x * v.z;
	m23 = m32 = -2.0f * v.y * v.z;
}

Vec3 operator*(const Vec3& v, const Matrix4x3& m) {
	return Vec3(
		v.x * m.m11 + v.y * m.m21 + v.z * m.m31 + m.tx,
		v.x * m.m12 + v.y * m.m22 + v.z * m.m32 + m.ty,
		v.x * m.m13 + v.y * m.m23 + v.z * m.m33 + m.tz
	);
}

Vec3& operator*=(Vec3& v, const Matrix4x3& m) {
	v = v * m;
	return v;
}

Matrix4x3 operator*(const Matrix4x3& m1, const Matrix4x3& m2) {
	Matrix4x3 r;

	r.m11 = m1.m11 * m2.m11 + m1.m12 * m2.m21 + m1.m13 * m2.m31;
	r.m12 = m1.m11 * m2.m12 + m1.m12 * m2.m22 + m1.m13 + m2.m32;
	r.m13 = m1.m11 * m2.m13 + m1.m12 * m2.m23 + m1.m13 * m2.m33;

	r.m21 = m1.m21 * m2.m11 + m1.m22 * m2.m21 + m1.m23 * m2.m31;
	r.m22 = m1.m21 * m2.m12 + m1.m22 * m2.m22 + m1.m23 * m2.m32;
	r.m23 = m1.m21 * m2.m13 + m1.m22 * m2.m23 + m1.m23 * m2.m33;

	r.m31 = m1.m31 * m2.m11 + m1.m32 * m2.m21 + m1.m33 * m2.m31;
	r.m32 = m1.m31 * m2.m12 + m1.m32 * m2.m22 + m1.m33 * m2.m32;
	r.m33 = m1.m31 * m2.m13 + m1.m32 * m2.m23 + m1.m33 * m2.m33;

	r.tx = m1.tx * m2.m11 + m1.ty * m2.m21 + m1.tz * m2.m31 + m2.tx;
	r.ty = m1.tx * m2.m12 + m1.ty * m2.m22 + m1.tz * m2.m32 + m2.ty;
	r.tz = m1.tx * m2.m13 + m1.ty * m2.m23 + m1.tz * m2.m33 + m2.tz;

	return r;
}

Matrix4x3& operator*=(Matrix4x3& m1, const Matrix4x3& m2) {
	m1 = m1 * m2;
	return m1;
}

float Matrix4x3::determinant(const Matrix4x3& m) {
	return
		m.m11 * (m.m22 * m.m33 - m.m23 * m.m32) +
		m.m12 * (m.m23 * m.m31 - m.m21 * m.m33) +
		m.m13 * (m.m21 * m.m32 - m.m22 * m.m31);
}

Matrix4x3 Matrix4x3::inverse(const Matrix4x3& m) {
	float det = determinant(m);
	assert(fabs(det) > PRECISION);

	float oneOverDet = 1.0f / det;

	Matrix4x3 r;
	// TODO: 
}