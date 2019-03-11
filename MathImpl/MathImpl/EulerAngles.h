#ifndef __EULER_ANGLES_H__
#define __EULER_ANGLES_H__

// EulerAngle: use heading-pitch-bank conventions

#include "std.h"

class Quaternion;
class Matrix4x3;
class RotationMatrix;

class EulerAngles {
public:
	float heading;
	float pitch;
	float bank;

public:
	EulerAngles() : heading(0.0f), pitch(0.0f), bank(0.0f) {}
	EulerAngles(float h, float p, float b) : heading(h), pitch(p), bank(b) {}
	
	void identity() { heading = pitch = bank = 0.0f; }
	void canonize();

	void fromObjectToInertialQuaternion(const Quaternion& q);
	void fromInertialToObjectQuaternion(const Quaternion& q);
	void fromObjectToWorldMatrix(const Matrix4x3& m);
	void fromWorldToObjectMatrix(const Matrix4x3& m);
	void fromRotationMatrix(const RotationMatrix& m);
};

#endif // __EULER_ANGLES_H__
