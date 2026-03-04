#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"


/* 
 * Defining the material type of the objects.
 */


class Material {

public:
	virtual ~Material() = default;

	virtual bool scatter (const Ray& ray_in, const HitRecord& record, Vec3& col_attenuation, Ray& scattered) const = 0;

	
