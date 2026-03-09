
# Image Ray-Tracing Tool

A ray-tracing image tool developed in modern, raw C++ without the use of any external graphics APIs or libraries.<br>
Based on concepts introduced in Peter Shirley, Trevor David Black, and Steve Hollasch's book "Ray Tracing in One Weekend". 
After compiling main.cpp, ray-traced image files are produced in the .ppm file format. 

Features so far:
- Sky gradient
- Sphere object
- Scenes with multiple objects
- Surface normalisation
- Pixel antialiasing
- Diffuse/Lambertian materials with recursive ray bouncing
- Metal reflective materials, as well as fuzzy metal surfaces
- Gamma correction

Requirements:
- C++ compiler (gcc, clang, etc.)
- PPM Image format viewer (Gimp, ImageMagick, etc.)

Running and viewing image (E.g. Using GCC compiler and ImageMagick in bash)<br>
`g++ main.cpp -o main`<br>
`./main > image.ppm`<br>
`display image.ppm`
