cmake_minimum_required(VERSION 3.5)
project(ray_tracing)
add_executable(ray_tracing src/main.cpp)
target_compile_options(ray_tracing PRIVATE -O2)
