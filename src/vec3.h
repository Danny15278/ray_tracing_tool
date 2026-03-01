#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>



// operates a class representing a 3-D vetor as doubles, as well as utility functions.



class Vec3 {
	
	public:
		double x, y, z;

		Vec3(double x, double y, double z) : x(x), y(y), z(z) {}
		Vec3() : x(0), y(0), z(0) {}



		Vec3 operator+(const Vec3& other) const {
			return Vec3(x + other.x, y + other.y, z + other.z);
		}

		Vec3 operator-(const Vec3& other) const {
			return Vec3(x - other.x, y - other.y, z - other.z);
		}

		Vec3 operator*(const double scalar) const {
			return Vec3(x * scalar, y * scalar, z * scalar); 
		}

		double length_squared() const {
			return x * x + y * y + z * z;
		}

		double length() const {
			return std::sqrt(length_squared());
		}
		
		Vec3 operator+(const double scalar) const {
			return Vec3(x + scalar, y + scalar, z + scalar);
		}
		
		Vec3 normalised() const {
			double len = length();
			return Vec3(x / len, y / len, z / len);
		}
		
};

Vec3 operator*(const double scalar, const Vec3& v) {
	return v * scalar;
}

double operator*(const Vec3& v1, const Vec3& v2) {
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z); 
}

inline double dot_product(const Vec3& v1, const Vec3 v2) {
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
#endif
