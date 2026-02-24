#include "ray.h"
#include "vec3.h"
#include <iostream>

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

	for (int j{ 0 }; j < image_height; ++j) {
		for (int i{ 0 }; i < image_width; ++i) {
			

			double x{ ((double (i) / (image_width - 1)) * viewport_w) - (viewport_w / 2) };
			double y{ ((double (j) / (image_height - 1)) * viewport_h) - (viewport_h / 2) };	

		}
	}
}
