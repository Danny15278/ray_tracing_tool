#ifndef METAL_H
#define METAL_H


#include "material.h"
#include "hittable.h"
#include "utils.h"

#include <memory>


// Metal reflective surface material for objects



class Metal : public Material {

private:
	Vec3 albedo;
	double fuzz;


public:
	Metal(const Vec3& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

	bool scatter (const Ray& ray_in, const HitRecord& record, Vec3& col_attenuation, Ray& scattered) const override {
		Vec3 reflected{ reflect(ray_in.direction(), record.normal) };
		
		reflected = reflected.normalised() + fuzz * random_unit_vector();	
		scattered = Ray(record.p, reflected);
		col_attenuation = albedo;
		return (scattered.direction() * record.normal) > 0;
	}
	


};

#endif
