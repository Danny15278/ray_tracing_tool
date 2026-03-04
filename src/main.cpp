#include "ray.h"
#include "vec3.h"
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"

#include <iostream>


int main() {

	// creating hittable_list to handle all objects in the image scene 
	
	Hittable_List scene; 
	

	// Adding objects to the image scene 
		
	scene.add_object(std::make_shared<Sphere>(Vec3(0, 0, -1), 0.5));
	scene.add_object(std::make_shared<Sphere>(Vec3(0, -100.5, -1), 100));
	

	Camera camera;
	camera.image_width = 800;
	camera.image_height = 400;
	camera.no_samples = 50;
	camera.render(scene);
}
