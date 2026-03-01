#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <vector>
#include <memory>
#include <limits>



/*
 * Creates a vector store of all Hittable objects and implements the hit method.
 * When rays are cast from camera, we can loop through all objects in the scene.
 * Closest hit get stored allowing for differentiation of objects. 
 */




class Hittable_List : public Hittable {

public:
	std::vector<std::shared_ptr<Hittable>> objects;
	

	void add_object(std::shared_ptr<Hittable> object) {
		objects.push_back(object);
	}

	void clear() {
		objects.clear();
	}

	bool hit(const Ray& ray, HitRecord& record) const override {
		HitRecord temp_record{};
		bool hit{ false };
		double closest{ std::numeric_limits<double>::infinity() };

		for (const auto& object : objects) {
			if (object->hit(ray, temp_record)) {
				hit = true;
				if (temp_record.t < closest) {
					closest = temp_record.t;
					record = temp_record;
				}
			}
		}
		return hit;
	}
};

#endif
