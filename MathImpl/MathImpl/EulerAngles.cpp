#include "EulerAngles.h"
#include "MathUtil.h"
#include "Quaternion.hpp"

void EulerAngles::canonize() {
	// pitch to [-PI, PI]
	pitch = MathUtil::wrapPi(pitch);

	// pitch to [-HALF_PI, HALF_PI]
	if (pitch < -HALF_PI) {
		pitch = -PI - pitch;
		heading += PI;
		bank += PI;
	}
	else if (pitch > HALF_PI) {
		pitch = PI - pitch;
		heading += PI;
		bank += PI;
	}

	// check Gimbal Lock
	if (fabs(pitch) > HALF_PI - PRECISION) {
		heading += bank;
		bank = 0;
	}
	else {
		bank = MathUtil::wrapPi(bank);
	}

	// heading to [-PI, PI]
	heading = MathUtil::wrapPi(heading);
}

void EulerAngles::fromObjectToInertialQuaternion(const Quaternion& q) {
	// Warnning: different from book, maybe wrong
	assert(false);

	float sp = -2.0f * (q.y * q.z - q.w * q.x);

	// Gimbal Lock, cosp == 0
	if (fabs(sp) > 1.0f - PRECISION) {
		pitch = HALF_PI * sp;
		heading = std::atan2(-q.x * q.z - q.w *q.y, 0.5f - q.y * q.y - q.z * q.z);
		bank = 0.0f;
	}
	else {
		pitch = std::asin(sp);
		heading = std::atan2(q.x * q.z - q.w * q.y, 0.5f - q.x * q.x - q.y * q.y);
		bank = std::atan2(q.x * q.y - q.w * q.z, 0.5f - q.x * q.x - q.z * q.z);
	}
}

void EulerAngles::fromInertialToObjectQuaternion(const Quaternion& q) {
	// Warnning: different from book, maybe wrong
	assert(false);

	float sp = -2.0f * (q.y * q.z + q.w * q.x);

	// Gimbal Lock, cosp == 0
	if (fabs(sp) > 1.0f - PRECISION) {
		pitch = HALF_PI * sp;
		heading = std::atan2(-q.x * q.z + q.w * q.y, 0.5f - q.y * q.y - q.z * q.z);
		bank = 0.0f;
	}
	else {
		pitch = std::asin(sp);
		heading = std::atan2(q.x * q.z + q.w * q.y, 0.5f - q.x * q.x - q.y * q.y);
		bank = std::atan2(q.x * q.y + q.w * q.z, 0.5f - q.x * q.x - q.z * q.z);
	}
}
