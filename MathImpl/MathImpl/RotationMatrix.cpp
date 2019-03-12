#include "RotationMatrix.h"
#include "MathUtil.h"
#include "Vec3.h"
#include "EulerAngles.h"
#include "Quaternion.h"

void RotationMatrix::setup(const EulerAngles& e) {
	float sh, sp, sb;
	float ch, cp, cb;
	MathUtil::sinCos(&sh, &ch, e.heading);
	MathUtil::sinCos(&sp, &cp, e.pitch);
	MathUtil::sinCos(&sb, &cb, e.bank);

	m11 = ch * cb + sh * sp * sb;
	m12 = -ch * sb + sh * sp * cb;
	m13 = sh * cp;

	m21 = sb * cp;
	m22 = cb * cp;
	m23 = -sp;

	m31 = -sh * cb + ch * sp * sb;
	m32 = sb * sh + ch * sp * cb;
	m33 = ch * cp;
}

void RotationMatrix::fromInertialToObjectQuaternion(const Quaternion& q) {
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
	m12 = 2.0f * (xy - wz);
	m13 = 2.0f * (wy + xz);

	m21 = 2.0f * (xy + wz);
	m22 = 1.0f - 2.0f * (xx + zz);
	m23 = 2.0f * (yz - wx);

	m31 = 2.0f * (xz - wy);
	m32 = 2.0f * (wx + yz);
	m33 = 1.0f - 2.0f * (xx + yy);
}

void RotationMatrix::fromObjectToInertialQuaternion(const Quaternion& q) {
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
}

Vec3 RotationMatrix::inertialToObject(const Vec3& v) const {
	//         |m11 m12 m13|
	// [x y z] |m21 m22 m23|
	//         |m31 m32 m33|
	return Vec3(
		m11 * v.x + m21 * v.y + m31 * v.z,
		m12 * v.x + m22 * v.y + m32 * v.z,
		m13 * v.x + m23 * v.y + m33 * v.z
	);
}

Vec3 RotationMatrix::objectToInertial(const Vec3& v) const {
	//         |m11 m21 m31|
	// [x y z] |m12 m22 m32|
	//         |m13 m23 m33|
	return Vec3(
		m11 * v.x + m12 * v.y + m13 * v.z,
		m21 * v.x + m22 * v.y + m23 * v.z,
		m31 * v.x + m32 * v.y + m33 * v.z
	);
}
