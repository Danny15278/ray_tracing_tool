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

	Vec3 random_disk_point() const {
		auto p{ random_disk_vector() };
		return lookfrom + (p.x * defocus_disk_u) + (p.y * defocus_disk_v);
	}


public:

	// Image scene parameters
	
	int image_width{};
	int image_height{};
	int depth{};
	int no_samples{};

	double vfov{}; 			// field of view
	Vec3 lookfrom{ 0, 0, 0 }; 	// camera origin
	Vec3 lookat{ 0, 0, -1 }; 	// camera target
	Vec3 vup{ 0, 1, 0 }; 		// which direction is upwards in the scene
	Vec3 u, v, w; 			// describe camera's orientation via local coordinate axis
	
	double defocus_angle{ 0 }; 	// variation angle of rays via each pixel
	double focus_distance{ 10 }; 	// distance between lookfrom to plane of focus
	Vec3 defocus_disk_u{}; 		// horizontal radius of defocus disk
	Vec3 defocus_disk_v{}; 		// vertical radius of defocus disk

	// Render scene

	void render(const Hittable& scene) {
		
		double asp_ratio{ double(image_width) / image_height };
		double theta{ vfov * (pi / 180.0) };
		double h{ std::tan(theta / 2) };
		double viewport_h{ 2 * h * focus_distance }; 			// height of viewport
		double viewport_w{ viewport_h * asp_ratio }; 			// width of viewport
		double pixel_w{ viewport_w / image_width }; 			// size of pixel in viewport space
		double pixel_h{ viewport_h / image_height };

		w = (lookfrom - lookat).normalised(); 				
		u = cross_product(vup, w).normalised();
		v = cross_product(w, u);
		

		Vec3 viewport_u{ viewport_w * u }; 				// horizontal vector for viewport
		Vec3 viewport_v{ viewport_h * -v }; 				// vertical vector for viewport

		auto viewport_upper_left = lookfrom - (focus_distance * w) - viewport_u / 2 - viewport_v / 2;
		
		auto defocus_radius{ focus_distance * std::tan(degrees_to_radians(defocus_angle / 2)) };
		defocus_disk_u = u * defocus_radius;
		defocus_disk_v = v * defocus_radius;


		// Render ppm image

		std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
	
		// iterate through each pixel

		for (int j{ 0 }; j < image_height; ++j) {
			for (int i{ 0 }; i < image_width; ++i) {

				auto pixel_centre = viewport_upper_left + (double (i) / image_width) * viewport_u + (double (j) / image_height) * viewport_v;
				Vec3 sum_pixel(0, 0, 0);
				for (int s{ 0 }; s < no_samples; ++s) {

					// Antialiasing calculation

					Vec3 offset{ sample_square().x * (viewport_u / image_width) + sample_square().y * (viewport_v / image_height) };		
					Vec3 sample_point{ pixel_centre + offset };
					auto ray_origin = (defocus_angle <= 0) ? lookfrom : random_disk_point();
					Ray ray{ ray_origin, (sample_point - ray_origin) };
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
