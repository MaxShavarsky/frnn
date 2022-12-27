cmake_minimum_required(VERSION 3.15)
project(frnn)

set(CMAKE_CXX_STANDARD 14)

include_directories(fixed-radius-near-neighbor)
include_directories(plotter)
include_directories(point-generator)
include_directories(utils)

add_executable(frnn
    fixed-radius-near-neighbor/fixed_radius_near_neighbor.cpp
    fixed-radius-near-neighbor/fixed_radius_near_neighbor.h
    plotter/pbPlots.cpp
    plotter/pbPlots.h
    plotter/plotter.cpp
    plotter/plotter.h
    plotter/supportLib.cpp
    plotter/supportLib.h
    point-generator/point_grid_generator.cpp
    point-generator/point_grid_generator.h
    utils/vector3d.cpp
    utils/vector3d.h
    main.cpp)
