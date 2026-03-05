
# Image Ray-Tracing Tool

A ray-tracing image tool developed in modern C++. 
Based on concepts introduced in Peter Shirley, Trevor David Black, and Steve Hollasch's book "Ray Tracing in One Weekend". 
After compiling main.cpp, ray-traced image files are produced in the .ppm file format. 

Features so far:
- Sky gradient
- Sphere object
- Scenes with multiple objects
- Surface normalisation
- Pixel antialiasing
- Diffuse/Lambertian surfaces for objects

Requirements:
- C++ compiler (gcc, clang, etc.)
- PPM Image format viewer (Gimp, ImageMagick, etc.)

Running and viewing image (E.g. Using GCC compiler)<br>
`g++ main.cpp -o main`<br>
`./main > image.ppm`<br>
`display image.ppm`
