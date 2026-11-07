# Ecosystem Simulation

A 2D ecosystem simulation built from scratch in C++20 and Raylib, focusing on autonomous agents and emergent behaviors. 

The project is designed with a strict focus on Data-Oriented Design (DOD) and clean architecture, ensuring high performance and modularity.

## Architecture

* **Data-Oriented Design:** Entities are stored using the Structure of Arrays (SoA) memory layout to maximize CPU cache utilization.
* **Decoupled Systems:** Physics and simulation logic are completely isolated from the rendering engine.
* **Modern C++:** Written in strict C++20.

## Building from source

### Prerequisites
You need `cmake`, a C++20 compatible compiler, and `raylib` installed on your system.

### Build instructions
```bash
mkdir build
cd build
cmake ..
make
```

### Run
```bash
./ecosystem
```

## Roadmap
* **V1 (Current):** Modular SoA architecture, headless physics, basic autonomous agents.
* **V2:** Spatial hashing implementation for O(1) collision and proximity checks.
* **V3:** Predator-prey dynamics and advanced emergent behaviors.