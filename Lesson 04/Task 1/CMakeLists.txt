cmake_minimum_required(VERSION 3.22.0)

project(Shapes_refactoring)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(Shapes SHARED shape.h shape.cpp transform.h transform.cpp line.h line.cpp sqr.h sqr.cpp 
cube.h cube.cpp circle.h circle.cpp cylinder.h cylinder.cpp)

add_executable(Shapes_refactoring main.cpp)

target_link_libraries(Shapes_refactoring Shapes)
