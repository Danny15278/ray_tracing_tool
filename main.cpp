#include "ray.h"
#include "vec3.h"

#include <iostream>


bool sphere_point(const Vec3& centre, double radius, const Ray& ray) {
	auto oc{ centre - ray.origin() };
	auto a{ ray.direction() * ray.direction() };
	auto b{ -2 * ray.direction() * oc };
	auto c{ (oc * oc) - (radius * radius) };
	auto discriminant{ b * b - 4 * a * c };
	return (discriminant >= 0);
}


Vec3 ray_colour(const Ray& r) {
	Vec3 direction = r.direction();
	
	Vec3 normalised = direction.normalised();
	double t = (normalised.y + 1) / 2;

	if (sphere_point(Vec3(0, 0, -1), 0.5, r)) {
			return Vec3(1, 0, 0);
	}

	// For blue-white sky gradient
	
	Vec3 white(1.0, 1.0, 1.0);
	Vec3 blue(0.5, 0.7, 1.0);

	return (1 - t) * white + t * blue;

}



int main() {

	int image_width{ 400 };
	int image_height{ 200 };
	double asp_ratio{ double(image_width) / image_height };

	double viewport_h{ 2.0 };
	double viewport_w{ viewport_h * asp_ratio };

	Vec3 cam_position(0, 0, 0);
	double focal_length{ 1.0 };

	Vec3 viewport_centre{ cam_position + Vec3(0, 0, -focal_length) };

	

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
