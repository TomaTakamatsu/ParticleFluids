cmake_minimum_required(VERSION 3.21)

project(ParticleFluids)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(vendor/raylib)

add_executable(ParticleFluids
    src/main.cpp
    src/physics/FluidSolver.cpp
    src/graphics/Renderer.cpp
)

target_link_libraries(ParticleFluids PRIVATE raylib)

target_include_directories(ParticleFluids PRIVATE 
    include 
    vendor/raygui/src 
)