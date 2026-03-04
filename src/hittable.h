#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"



/* 
 * Structure HitRecord stores values regarding a hit (between ray and object).
 * Hittable is an abstract base calss with virtual hit method, which is implemented by all objects that interact with rays.
 */


class Material;


struct HitRecord {

	double t;
	Vec3 p;
	Vec3 normal;
	bool front_face;

};


class Hittable {

public:
	virtual bool hit(const Ray& r, HitRecord& record) const = 0;
};



#endif
