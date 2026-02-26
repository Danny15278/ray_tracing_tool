#ifndef SPHERE_H
#define SPHERE_H

#include "ray.h"
#include "vec3.h"

class Sphere {

private:
	Vec3 centre;
	double radius;


public:
	Sphere(const Vec3& centre, double radius) : centre(centre), radius(radius) {}

	double intersect_point(const Ray& ray) {
		auto oc{ centre - ray.origin() };
		auto a{ ray.direction() * ray.direction() };
		auto b{ -2 * ray.direction() * oc };
		auto c{ (oc * oc) - (radius * radius) };
		auto discriminant{ b * b - 4 * a * c };
		
		if (discriminant < 0) {
			return -1.0;
		} else {
			return (-b - std::sqrt(discriminant)) / (2.0 * a);
		}
	}
};


#endif
