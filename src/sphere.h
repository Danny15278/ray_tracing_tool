#ifndef SPHERE_H
#define SPHERE_H

#include "ray.h"
#include "vec3.h"
#include "hittable.h"

class Sphere : public Hittable {

private:
	Vec3 centre;
	double radius;


public:
	Sphere(const Vec3& centre, double radius) : centre(centre), radius(radius) {}

	bool hit(const Ray& ray, HitRecord& record) override {
		auto oc{ centre - ray.origin() };
		auto a{ ray.direction() * ray.direction() };
		auto b{ -2 * ray.direction() * oc };
		auto c{ (oc * oc) - (radius * radius) };
		auto discriminant{ b * b - 4 * a * c };
		
		if (discriminant < 0) { return false; }

		record.t = ((-b - std::sqrt(discriminant)) / (2.0 * a));
		record.p = ray.pointAt(record.t);
		record.normal = (record.p - centre).normalised();
		record.front_face = (dot_product(ray.direction(), record.normal) < 0);
		if (!record.front_face) {
			record.normal = -1 * record.normal;
		}

		return (record.t >= 0);		
	}
};


#endif
