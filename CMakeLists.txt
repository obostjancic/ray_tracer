cmake_minimum_required(VERSION 3.13)
project(ray_tracer)

set(CMAKE_CXX_STANDARD 14)

add_executable(ray_tracer main.cpp Ray.h Vector3D.h Hitable.h Sphere.h HitableList.h Camera.h Material.h Util.h Ellipsoid.h Parser.h)