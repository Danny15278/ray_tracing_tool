#ifndef UTILS_H
#define UTILS_H

#include "vec3.h"

#include <random>
#include <cmath>


const double pi{ M_PI };

inline double random_double() {
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generate_number(std::random_device{}());
	return distribution(generate_number);
}	


inline double random_double(double min, double max) {
	return min + (max - min) * random_double();
}


inline Vec3 random_vec3() {
	return Vec3(random_double(), random_double(), random_double());
}

inline Vec3 random_vec3(double min, double max) {
	return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

// Check if random vector falls inside sphere (for diffuse objects)

inline Vec3 random_unit_vector() {
        while (true) {
                Vec3 point{ random_vec3(-1, 1) };      
                double squared{ point.length_squared() };
                if (squared <= 1 && squared >= 1e-160)
                        return point / std::sqrt(squared);
        }
}

inline Vec3 random_disk_vector() {
	while (true) {
		auto p{ Vec3(random_double(-1, 1), random_double(-1, 1), 0) };
		if (p.length_squared() < 1)
			return p;
	}

}


inline double degrees_to_radians(double degrees) {
	return degrees * pi / 180.0;
}
#endif
