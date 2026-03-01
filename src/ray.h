#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include <iostream>


/* 
 * Represents a ray of light with a fixed three-dimensional point origin and extends ina  direction.
 * Has a pointAt() function to find a position along the ray.
 * P(t) = A + tb
 */



class Ray {

private:
	Vec3 orig;
	Vec3 dir;

public:
	const Vec3& origin() const {
		return orig;
	}

	const Vec3& direction() const {
		return dir;
	}


	Ray(Vec3 orig, Vec3 dir) : orig(orig), dir(dir) {}
	Ray() : orig(0, 0, 0), dir(0, 0, 0) {}
	
	Vec3 pointAt(double t) const {
		return orig + t * dir;
	}

};


#endif
