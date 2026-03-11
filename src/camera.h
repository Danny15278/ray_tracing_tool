#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "utils.h"
#include "material.h"

class Camera {

private:

	Vec3 ray_colour(const Ray& r, const Hittable& objects, int depth) {

		// check max depth parameter

		if (depth <= 0)
			return Vec3(0, 0, 0);


		HitRecord record;

		// recursive call for scattering of ray based on material

		if (objects.hit(r, record)) {
			Ray scattered{};
			Vec3 col_attenuation{};

			if (record.material->scatter(r, record, col_attenuation, scattered))
				return col_attenuation.component_multiply(ray_colour(scattered, objects, depth - 1));

			return Vec3(0, 0, 0); 
		}

		Vec3 direction = r.direction();
		Vec3 normalised = direction.normalised();
		double sky_t = (normalised.y + 1) / 2;


		// For blue-white sky gradient

		Vec3 white(1.0, 1.0, 1.0);
		Vec3 blue(0.5, 0.7, 1.0);

		return (1 - sky_t) * white + sky_t * blue;	
	}
	
	// Random sample square for anti-aliasing

	Vec3 sample_square() const {
		return Vec3(random_double() - 0.5, random_double() - 0.5, 0);
	}


public:

	// Image scene parameters
	int image_width{};
	int image_height{};
	int depth{};
	int no_samples{};

	double vfov{};
	Vec3 lookfrom{ 0, 0, 0 }; 	// camera origin
	Vec3 lookat{ 0, 0, -1 }; 	// camera target
	Vec3 vup{ 0, 1, 0 }; 		// which direction is upwards in the scene
	Vec3 u, v, w;

	void render(const Hittable& scene) {
		
		double asp_ratio{ double(image_width) / image_height };

		double theta{ vfov * (pi / 180.0) };
		double h{ std::tan(theta / 2) };
		double viewport_h{ 2 * h };
		double viewport_w{ viewport_h * asp_ratio };
		double pixel_w{ viewport_w / image_width };
		double pixel_h{ viewport_h / image_height };
		double focal_length{ (lookfrom - lookat).length() };

		w = (lookfrom - lookat).normalised();
		u = cross_product(vup, w).normalised();
		v = cross_product(w, u);
		

		Vec3 viewport_u{ viewport_w * u };
		Vec3 viewport_v{ viewport_h * -v };
		auto viewport_upper_left = lookfrom - (focal_length * w) - viewport_u / 2 - viewport_v / 2;
		std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

		for (int j{ 0 }; j < image_height; ++j) {
			for (int i{ 0 }; i < image_width; ++i) {

				
				auto pixel_centre = viewport_upper_left + (double (i) / image_width) * viewport_u + (double (j) / image_height) * viewport_v;

				Vec3 sum_pixel(0, 0, 0);
				for (int s{ 0 }; s < no_samples; ++s) {

					// Antialiasing calculation

					Vec3 offset{ sample_square().x * (viewport_u / image_width) + sample_square().y * (viewport_v / image_height) };		
					Vec3 sample_point{ pixel_centre + offset };
					Ray ray{ lookfrom, (sample_point - lookfrom) };
					sum_pixel += ray_colour(ray, scene, depth);
				}

				sum_pixel = sum_pixel / no_samples;
				
				// Gamma correction

				auto r{ std::sqrt(sum_pixel.x) };
				auto g{ std::sqrt(sum_pixel.y) };
				auto b{ std::sqrt(sum_pixel.z) };

				int rbyte{ int(255.99 * r) };
				int gbyte{ int(255.99 * g) };
				int bbyte{ int(255.99 * b) };

				std::cout << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
			}
		}
	}
};


#endif
