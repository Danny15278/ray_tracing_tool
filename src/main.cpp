#include "../include/vec3.h"
#include "../include/sphere.h"
#include "../include/hittable_list.h"
#include "../include/camera.h"
#include "../include/diffuse.h"
#include "../include/metal.h"
#include "../include/dielectric.h"
#include "../include/utils.h"


int main() {

	// creating hittable_list to handle all objects in the image scene 
	
	Hittable_List scene; 
	
/* Test Scene
 *
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
	
	
	camera.vfov = 20.0;
	camera.lookfrom = Vec3(-2, 2, 1);
	camera.lookat = Vec3(0, 0, -1);
	camera.vup = Vec3(0, 1, 0);

	camera.defocus_angle = 10.0;
	camera.focus_distance = 3.4;
*/

	auto material_ground{ std::make_shared<Diffuse>(Vec3(0.5, 0.5, 0.5)) };						// Ground surface sphere
	scene.add_object(std::make_shared<Sphere>(Vec3(0, -1000, 0), 1000, material_ground));

	for (int i{ -15 }; i < 15; ++i) {										// random small spheres, 80% diffuse, 15% metal, 5% glass
		for (int j{ -15 }; j < 15; ++j) {
			auto random_material{ random_double() };
			Vec3 centre(i + 0.9 * random_double(), 0.2, j + 0.9 * random_double()); 			// Offsets spehres randomly so not perfect grid

			if ((centre - Vec3(4, 0.2, 0)).length() > 0.9) {						// stops small spheres from overlapping with large 3 sphere positions
				std::shared_ptr<Material> sphere_material;

				if (random_material < 0.8) {
					auto albedo = random_vec3().component_multiply(random_vec3());
					sphere_material = std::make_shared<Diffuse>(albedo);
					scene.add_object(std::make_shared<Sphere>(centre, 0.2, sphere_material));	
				} else if (random_material < 0.95) {
					auto albedo = random_vec3(0.5, 1);
					auto fuzz = random_double(0, 0.5);
					sphere_material = std::make_shared<Metal>(albedo, fuzz);
					scene.add_object(std::make_shared<Sphere>(centre, 0.2, sphere_material));
				} else {
					sphere_material = std::make_shared<Dielectric>(1.5);
					scene.add_object(std::make_shared<Sphere>(centre, 0.2, sphere_material));
				}
			}
		}
	}




	auto dielectric_material = std::make_shared<Dielectric>(1.5);							// 3 large spheres
	scene.add_object(std::make_shared<Sphere>(Vec3(0, 1, 0), 1.0, dielectric_material));

	auto diffuse_material = std::make_shared<Diffuse>(Vec3(0.4, 0.2, 0.1));
	scene.add_object(std::make_shared<Sphere>(Vec3(-4, 1, 0), 1.0, diffuse_material));

	auto metal_material = std::make_shared<Metal>(Vec3(0.7, 0.6, 0.5), 0.0);
	scene.add_object(std::make_shared<Sphere>(Vec3(4, 1, 0), 1.0, metal_material));
	

	
	Camera camera;
	camera.image_width = 400;
	camera.image_height = 200;
	camera.depth = 20;
	camera.no_samples = 50;
	
	
	camera.vfov = 20.0;
	camera.lookfrom = Vec3(13, 2, 3);
	camera.lookat = Vec3(0, 0, 0);
	camera.vup = Vec3(0, 1, 0);

	camera.defocus_angle = 0.5;
	camera.focus_distance = 10.0;

	camera.render(scene);
}
