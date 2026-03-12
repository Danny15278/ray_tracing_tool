
# Image Ray-Tracing Tool

A CPU-based ray-tracing image tool developed in modern C++, without the use of any external graphics APIs or libraries. Images are created with CPU multithreading for parallelism.<br>

Based on concepts introduced in Peter Shirley, Trevor David Black, and Steve Hollasch's book "Ray Tracing in One Weekend". 
After compiling main.cpp, ray-traced image files are produced in the .ppm file format. 


Features (example images can be found in /output)
- Ray-sphere interaction 
- Multithreaded rendering across CPU cores
- Scenes with multiple objects
- Surface normalisation and shading
- Pixel antialiasing
- Diffuse/lambertian, metal, and dielectric (glass) materials types
- Gamma correction
- Configurable camera positioning and field of view
- Defocus blur and depth of field adjustment


Requirements:
- C++ compiler (gcc, clang, etc.)
- CMake buid tool (v. 3.5)
- PPM Image format viewer (Gimp, ImageMagick, etc.)


Running and viewing image: (E.g. Using GCC compiler and ImageMagick in bash)<br>
`cmake --build build`<br>
`./build/ray_tracing > output/image_render.ppm`<br>
`display image_render.ppm`
