cmake_minimum_required(VERSION 3.14)
project(Intersections)

set(CMAKE_CXX_STANDARD 14)

add_executable(Intersections main.cpp LineSegment.cpp LineSegment.h LineLibrary.cpp LineLibrary.h Vector3.h)