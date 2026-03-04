#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "utils.h"

class Camera {

private:
	

	Vec3 ray_colour(const Ray& r, const Hittable& objects) {

		HitRecord record;

		if (objects.hit(r, record)) {
			return 0.5 * (record.normal + 1);
		}

		Vec3 direction = r.direction();
		Vec3 normalised = direction.normalised();
		double sky_t = (normalised.y + 1) / 2;


		// For blue-white sky gradient

		Vec3 white(1.0, 1.0, 1.0);
		Vec3 blue(0.5, 0.7, 1.0);

		return (1 - sky_t) * white + sky_t * blue;	
	}
	
	// Random sampel square for anti-aliasing

	Vec3 sample_square() const {
		return Vec3(random_double() - 0.5, random_double() - 0.5, 0);
	}


public:

	// Image scene parameters
	int image_width{};
	int image_height{};
        Vec3 cam_position{0, 0, 0};
	int no_samples{};
        double focal_length{ 1.0 };


	void render(const Hittable& scene) {
		
		double asp_ratio{ double(image_width) / image_height };
		double viewport_h{ 2.0 };
		double viewport_w{ viewport_h * asp_ratio };
		double pixel_w{ viewport_w / image_width };
		double pixel_h{ viewport_h / image_height };

		std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

		for (int j{ 0 }; j < image_height; ++j) {
			for (int i{ 0 }; i < image_width; ++i) {


				// Calculate viewport pixels
				
				double x{ ((double (i) / (image_width - 1)) * viewport_w) - (viewport_w / 2) };
				double y{ ((double (j) / (image_height - 1)) * viewport_h) - (viewport_h / 2) };
				double z{ (double) (-focal_length) };
				
				Vec3 viewport_point(x, -y, z);

				Vec3 sum_pixel(0, 0, 0);
				for (int s{ 0 }; s < no_samples; ++s) {
					Vec3 offset{ sample_square().x * pixel_w, sample_square().y * pixel_h, 0 };
					
					Vec3 sample_point{ viewport_point + offset };
					Ray ray{ cam_position, (sample_point - cam_position) };
					sum_pixel += ray_colour(ray, scene);
				}

				sum_pixel = sum_pixel / no_samples;

				auto r{ sum_pixel.x };
				auto g{ sum_pixel.y };
				auto b{ sum_pixel.z };

				int rbyte{ int(255.99 * r) };
				int gbyte{ int(255.99 * g) };
				int bbyte{ int(255.99 * b) };

				std::cout << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
			}
		}
	}
};


#endif
