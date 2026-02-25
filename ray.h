#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include <iostream>

// Represents the ray object, starting at a fixed 3-D point and extends in a direction.
// P(t) = A + tb

class Ray {

private:
	Vec3 orig;
	Vec3 dir;

public:
	Ray(Vec3 orig, Vec3 dir) : orig(orig), dir(dir) {}
	Ray() : orig(0, 0, 0), dir(0, 0, 0) {}
	
	Vec3 pointAt(double t) {
		return orig + t * dir;
	}

};


#endif
