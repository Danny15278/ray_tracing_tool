#ifndef DIELECTRIC_H
#define DIELECTRIC_H


#include "material.h"
#include "hittable.h"
#include "utils.h"

#include <memory>


/* 
 * Dielectric material surfaces both reflect AND refract light,described in Snell's law
 * n * sin(theta) = n' * sin(theta')
 *
 * When ray hits surface, refracted rays split into one across the surface (perpendicular to normal),
 * and one through the surface (parallel to normal).
 */


class Dielectric : public Material {

private:
	// refractive index in either vacuum or air, or ratio of materials RI over RI of enclosing material
	
	double refraction_index{};


public:
	Dielectric(double refraction_index) : refraction_index(refraction_index) {}

	bool scatter(const Ray& ray_in, const HitRecord& record, Vec3& col_attenuation, Ray& scattered) const override {
		col_attenuation = Vec3(1.0, 1.0, 1.0);
		double eta_ratio{ record.front_face ? (1.0 / refraction_index) : refraction_index };
		
		double cos_theta{ std::fmin((-1 * ray_in.direction() * record.normal), 1.0) };
		double sin_theta{ std::sqrt(1.0 - cos_theta * cos_theta) };
		bool can_refract{ eta_ratio * sin_theta <= 1.0 };
		Vec3 direction{};

		if (can_refract)
			direction = refract(ray_in.direction(), record.normal, eta_ratio);
		else
			direction = reflect(ray_in.direction(), record.normal);


		scattered = Ray(record.p, direction);

		return true;
	}

};

#endif
