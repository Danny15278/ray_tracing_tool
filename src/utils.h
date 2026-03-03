#ifndef UTILS_H
#define UTILS_H

#include <random>

inline double random_double() {
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generate_number(std::random_device{}());
	return distribution(generate_number);
}	


inline double random_double(double min, double max) {
	return min + (max - min) * random_double();
}

#endif
