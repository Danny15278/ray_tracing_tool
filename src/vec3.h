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

	Vec3& operator+=(const Vec3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vec3 operator/(const double scalar) const {
		return Vec3(x * (1/scalar), y * (1/scalar), z * (1/scalar));
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

	Vec3 component_multiply(const Vec3& other) {
		return Vec3(x * other.x, y * other.y, z * other.z);
	}

	bool near_zero() const {
		return (std::fabs(x) < 1e-8) && (std::fabs(y) < 1e-8) && (std::fabs(z) < 1e-8);
	}
};

Vec3 operator*(const double scalar, const Vec3& v) {
	return v * scalar;
}

double operator*(const Vec3& v1, const Vec3& v2) {
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z); 
}

inline Vec3 reflect(const Vec3& v, const Vec3& n) {
	return v - 2 * (v * n) * n;
}

#endif
