
# Image Ray-Tracing Tool

A ray-tracing image tool developed in modern, raw C++ without the use of any external graphics APIs or libraries.<br>
Based on concepts introduced in Peter Shirley, Trevor David Black, and Steve Hollasch's book "Ray Tracing in One Weekend". 
After compiling main.cpp, ray-traced image files are produced in the .ppm file format. 

Features (example images can be found in /output)
- Ray-Sphere interaction 
- Scenes with multiple objects
- Surface normalisation and shading
- Pixel antialiasing
- Diffuse/Lambertian materials with recursive ray bouncing
- Metal reflective materials, as well as fuzzy metal surfaces
- Dielectric (glass) materials
- Gamma correction
- Configurable camera positioning and field of view
- Defocus blue and depth of field adjustment


Requirements:
- C++ compiler (gcc, clang, etc.)
- CMake buid tool
- PPM Image format viewer (Gimp, ImageMagick, etc.)

Running and viewing image (E.g. Using GCC compiler and ImageMagick in bash)<br>
./build/ray_tracing > output/image_render.ppm<br>
`display image_render.ppm`
