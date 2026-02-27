#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct HitRecord {

	double t;
	Vec3 p;
	Vec3 normal;
};


class Hittable {

public:
	virtual bool hit(const Ray& r, HitRecord& record) = 0;
};



#endif
