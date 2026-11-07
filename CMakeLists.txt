cmake_minimum_required(VERSION 3.20)
project(EcosystemHPC CXX)

# Strict C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optimizations for Ryzen (O3 + native architecture) and strict warnings
add_compile_options(-O3 -march=native -Wall -Wextra)

# Find Raylib dependency
find_package(raylib REQUIRED)

# Executable definition (compile all .cpp source files)
add_executable(ecosystem 
    src/main.cpp
    src/Simulation.cpp
    src/Renderer.cpp
)

# Tell the compiler where to find the header files (.hpp)
target_include_directories(ecosystem PRIVATE include)

# Link the Raylib library
target_link_libraries(ecosystem PRIVATE raylib)