#include "Quaternion.h"
#include "MathUtil.h"
#include "Vec3.h"
#include "EulerAngles.h"

void Quaternion::setToRotateAboutX(float theta) {
	float halfT = theta * 0.5f;
	w = cos(halfT);
	x = std::sin(halfT);
	y = 0.0f;
	z = 0.0f;
}

void Quaternion::setToRotateAboutY(float theta) {
	float halfT = theta * 0.5f;
	w = cos(halfT);
	x = 0.0f;
	y = std::sin(halfT);
	z = 0.0f;
}

void Quaternion::setToRotateAboutZ(float theta) {
	float halfT = theta * 0.5f;
	w = cos(halfT);
	x = 0.0f;
	y = 0.0f;
	z = std::sin(halfT);
}

void Quaternion::setToRotateAboutAxis(const Vec3& u, float theta) {
	assert(std::fabs(Vec3::mag(u) - 1.0f) < PRECISION);
	float halfT = theta * 0.5f;
	float sinHalfT = std::sin(halfT);
	w = std::cos(halfT);
	x = u.x * sinHalfT;
	y = u.y * sinHalfT;
	z = u.z * sinHalfT;
}

void Quaternion::setToRotateObjectToInertial(const EulerAngles& e) {
	float sh, sp, sb;
	float ch, cp, cb;
	MathUtil::sinCos(&sh, &ch, e.heading * 0.5f);
	MathUtil::sinCos(&sp, &cp, e.pitch * 0.5f);
	MathUtil::sinCos(&sb, &cb, e.bank * 0.5f);
	w = ch * cp * cb + sh * sp * sb;
	x = ch * sp * cb + sh * cp * sb;
	y = sh * cp * cb - ch * sp * sb;
	z = ch * cp * sb - sh * sp * cb;
}

void Quaternion::setToRotateInertialToObject(const EulerAngles& e) {
	float sh, sp, sb;
	float ch, cp, cb;
	MathUtil::sinCos(&sh, &ch, e.heading * 0.5f);
	MathUtil::sinCos(&sp, &cp, e.pitch * 0.5f);
	MathUtil::sinCos(&sb, &cb, e.bank * 0.5f);
	w = ch * cp * cb + sh * sp * sb;
	x = -ch * sp * cb - sh * cp * sb;
	y = ch * sp * sb - sh * cp * cb;
	z = sh * sp * cb - ch * cp * sb;
}

// q1*q2 = [s*t - v*u, su + tv + vxu], param q is q1 and *this is q2
Quaternion Quaternion::operator*(const Quaternion& q) const {
	Quaternion result;
	result.w = q.w * w - q.x * x - q.y * y - q.z * z;
	result.x = q.w * x + w * q.x + q.y * z - q.z * y;
	result.y = q.w * y + w * q.y + q.z * x - q.x * z;
	result.z = q.w * z + w * q.z + q.x * y - q.y * x;
	return result;
}

Quaternion& Quaternion::operator*=(const Quaternion& q) {
	*this = *this * q;
	return *this;
}

void Quaternion::normalize() {
	float mag = std::sqrt(w*w + x * x + y * y + z * z);
	if (mag > 0.0f) {
		float oneOverMag = 1.0f / mag;
		w *= oneOverMag;
		x *= oneOverMag;
		y *= oneOverMag;
		z *= oneOverMag;
	}
	else {
		// wrong!
		assert(false);
		identity();
	}
}

float Quaternion::getRotationAngle() const {
	return MathUtil::safeAcos(w) * 2.0f;
}

Vec3 Quaternion::getRotationAxis() const {
	// w = cos(0/2), 1-w*w = sin^2(0/2)
	float sqSin = 1.0f - w * w;
	if (sqSin <= 0.0f) {
		return Vec3(1.0f, 0.0f, 0.0f);
	}
	
	float f = 1.0f / std::sqrt(sqSin);
	return Vec3(x * f, y * f, z * f);
}

float Quaternion::dotProduct(const Quaternion& q1, const Quaternion& q2) {
	return q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
}

Quaternion Quaternion::slerp(const Quaternion& q0, const Quaternion& q1, float t) {
	if (t <= 0.0f) return q0;
	if (t >= 1.0f) return q1;

	float cosT = dotProduct(q0, q1);
	float q1w = q1.w;
	float q1x = q1.x;
	float q1y = q1.y;
	float q1z = q1.z;

	// prefer -q
	if (cosT < 0.0f) {
		q1w = -q1w;
		q1x = -q1x;
		q1y = -q1y;
		q1z = -q1z;
		cosT = -cosT;
	}
	assert(cosT < 1.0f + PRECISION);
	
	float k0, k1;

	// q0 ~= q1, lerp is proper
	if (cosT > 1.0f - PRECISION) {
		k0 = 1.0f - t;
		k1 = t;
	}
	else {
		float sinT = std::sqrt(1.0f - cosT * cosT);
		float theta = atan2(sinT, cosT);
		float oneOverSinT = 1.0f / sinT;
		k0 = std::sin((1.0f - t) * theta) * oneOverSinT;
		k1 = std::sin(t * theta) * oneOverSinT;
	}
	Quaternion result;
	result.w = k0 * q0.w + k1 * q1w;
	result.x = k0 * q0.x + k1 * q1x;
	result.y = k0 * q0.y + k1 * q1y;
	result.z = k0 * q0.z + k1 * q1z;
	return result;
}

Quaternion Quaternion::conjugate(const Quaternion& q) {
	return Quaternion(q.w, -q.x, -q.y, -q.z);
}

Quaternion Quaternion::pow(const Quaternion& q, float e) {
	if (fabs(q.w) > 1.0f - PRECISION) {
		return q;
	}
	
	float theta = std::acos(q.w);
	float newTheta = theta * e;
	float mult = sin(newTheta) / sin(theta);
	Quaternion result;
	result.w = cos(newTheta);
	result.x = q.x * mult;
	result.y = q.y * mult;
	result.z = q.z * mult;
	return result;
}
