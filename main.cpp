#include "ray.h"
#include "vec3.h"
#include <iostream>

int main() {

	int image_width{ 400 };
	int image_height{ 200 };
	double asp_ratio{ double(image_width) / image_height };

	double viewport_h{ 2.0 };
	double viewport_w{ viewport_h * asp_ratio };

	Vec3 cam_position();
	double focal_length{ 1.0 };

	Vec3 vewport_centre{ cam_position + Vec3(0, 0, -focal_length);

	for (int j{ 0 }; j < image_height; ++j) {
		for (int i{ 0 }; i < image_width; ++i) {
			
		}
	}
}
