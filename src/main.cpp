#include "ray.h"
#include "vec3.h"
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"
#include "diffuse.h"
#include "metal.h"
#include "dielectric.h"

#include <iostream>


int main() {

	// creating hittable_list to handle all objects in the image scene 
	
	Hittable_List scene; 
	

	// Adding objects to the image scene 
	
	auto material_ground{ std::make_shared<Diffuse>(Vec3(0.8, 0.8, 0.0)) };
	auto material_centre{ std::make_shared<Diffuse>(Vec3(0.1, 0.2, 0.5)) };
	auto material_left{ std::make_shared<Dielectric>(1.00 / 1.33) };
	auto material_right{ std::make_shared<Metal>(Vec3(0.8, 0.6, 0.2), 1.0) };
		
	scene.add_object(std::make_shared<Sphere>(Vec3(0, -100.5, -1), 100, material_ground)); 
	scene.add_object(std::make_shared<Sphere>(Vec3(0.0, 0.0, -1.2), 0.5, material_centre));
	scene.add_object(std::make_shared<Sphere>(Vec3(-1.0, 0.0, -1.0), 0.5, material_left));
	scene.add_object(std::make_shared<Sphere>(Vec3(1.0, 0.0, -1.0), 0.5, material_right));	


	// Configuration of camera position and field of view
	
	Camera camera;
	camera.image_width = 800;
	camera.image_height = 400;
	camera.depth = 50;
	camera.no_samples = 100;
	
	
	camera.vfov = 90.0;
	camera.lookfrom = Vec3(-2, 2, 1);
	camera.lookat = Vec3(0, 0, -1);
	camera.vup = Vec3(0, 1, 0);


	camera.render(scene);
}
