#include <iostream>
#include <string>


int main() {
	
	// Image parameters
	
	const int image_width{ 600 };
	const int image_height{ 380 };
	const int colour{ 255 };

	// Rendering image
	
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j{ 0 }; j < image_height; ++j) {
		std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
		for (int i{ 0 }; i < image_width; ++i) {
			int r, g, b;

			if (i <= 200) {
				r = 255;
				g = 0;
				b = 0;
			} else if (i <= 400) {
				r = 0;
				g = 255;
				b = 0;
			} else {
				r = 255;
				g = 255;
				b = 255;
			}


			std::cout << r << ' ' << g << ' ' << b << '\n';
		}
	}

}
