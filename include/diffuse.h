#ifndef DIFFUSE_H
#define DIFFUSE_H

#include "material.h"
#include "hittable.h"
#include "utils.h"

#include <memory>


// Diffuse/Lambertian material surface for objects



class Diffuse : public Material {

private:
	Vec3 albedo;


public:
Diffuse(const Vec3& albedo) : albedo(albedo) {}

	bool scatter (const Ray& ray_in, const HitRecord& record, Vec3& col_attenuation, Ray& scattered) const override {
		Vec3 random_scatter{ record.normal + random_unit_vector() };
		
		if (random_scatter.near_zero())
			random_scatter = record.normal;

		scattered = Ray(record.p, random_scatter);
		col_attenuation = albedo;
		return true;
		
	}

};

#endif
