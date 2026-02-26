#include "ray.h"
#include "vec3.h"
#include "sphere.h"


#include <iostream>


Vec3 ray_colour(const Ray& r) {

	Vec3 centre(0, 0, -1);
	Sphere sphere(centre, 0.5);
	
	auto sphere_t{ sphere.intersect_point(r) };
	if (sphere_t >= 0.0) {
		Vec3 P{ r.pointAt(sphere_t) };
		return 0.5 * ((P - centre).normalised() + 1);
	}

	Vec3 direction = r.direction();
	Vec3 normalised = direction.normalised();
	double sky_t = (normalised.y + 1) / 2;


	// For blue-white sky gradient
	
	Vec3 white(1.0, 1.0, 1.0);
	Vec3 blue(0.5, 0.7, 1.0);

	return (1 - sky_t) * white + sky_t * blue;

}



int main() {

	int image_width{ 400 };
	int image_height{ 200 };
	double asp_ratio{ double(image_width) / image_height };

	double viewport_h{ 2.0 };
	double viewport_w{ viewport_h * asp_ratio };

	Vec3 cam_position(0, 0, 0);
	double focal_length{ 1.0 };

	
	// mapping pixels onto viewport
	
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j{ 0 }; j < image_height; ++j) {
		for (int i{ 0 }; i < image_width; ++i) {
			
			double x{ ((double (i) / (image_width - 1)) * viewport_w) - (viewport_w / 2) };
			double y{ ((double (j) / (image_height - 1)) * viewport_h) - (viewport_h / 2) };
			double z{ (double) (-focal_length) };
			
			Vec3 viewport_point(x, -y, z);
			Ray ray{ cam_position, (viewport_point - cam_position) };
			Vec3 colour{ ray_colour(ray) };

			auto r{ colour.x };
			auto g{ colour.y };
			auto b{ colour.z };

			int rbyte{ int(255.99 * r) };
			int gbyte{ int(255.99 * g) };
			int bbyte{ int(255.99 * b) };

			std::cout << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';

		}
	}
}
