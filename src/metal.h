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


public:
	Metal(const Vec3& albedo) : albedo(albedo) {}

	bool scatter (const Ray& ray_in, const HitRecord& record, Vec3& col_attenuation, Ray& scattered) const override {
		Vec3 reflected{ reflect(ray_in.direction(), record.normal) };

		scattered = Ray(record.p, reflected);
		col_attenuation = albedo;
		return true;
	}
	


};

#endif
