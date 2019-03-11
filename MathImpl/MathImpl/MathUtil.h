#ifndef __MATH_UTIL_H__
#define __MATH_UTIL_H__

#include "std.h"

const float PI = 3.14159265f;
const float TWO_PI = PI * 2.0f;
const float HALF_PI = PI / 2.0f;
const float OVER_PI = 1.0f / PI;
const float OVER_TWO_PI = 1.0f / TWO_PI;
const float PRECISION = 1e-4;

class MathUtil
{
public:
	static float wrapPi(float theta) {
		theta += PI;
		theta -= std::floor(theta * OVER_TWO_PI) * TWO_PI;
		theta -= PI;
		return theta;
	}

	static float safeAcos(float x) {
		if (x <= -1.0f) return PI;
		if (x >= 1.0f) return 0.0f;
		return std::acos(x);
	}


	// maybe faster in some platforms
	static inline void sinCos(float *retSine, float* retCos, float theta)
	{
		*retSine = std::sin(theta);
		*retCos = std::cos(theta);
	}
};

#endif // __MATH_UTIL_H__
