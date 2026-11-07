# Project Architecture - Ecosystem HPC (C++20 & Raylib)

## Project Goal
Develop a high-performance computing (HPC) evolutionary ecosystem simulation in C++20.
The objective is to simulate a massive number of entities (10,000+) at 60 FPS using CPU cache-friendly data structures (SoA) and parallel computing principles.

---

## File Structure and Responsibilities

```text
src/
├── Config.hpp        # Global system constants (no executable logic)
├── AgentPool.hpp     # Structure of Arrays (SoA) for agent memory
├── FoodPool.hpp      # Structure of Arrays (SoA) for food entities
├── Simulation.hpp    # Header for physics and behavioral logic
├── Simulation.cpp    # Implementation: Steering, vision, collisions, metabolism
├── Renderer.hpp      # Header for the graphical rendering engine
├── Renderer.cpp      # Raylib implementation (Drawing entities)
└── main.cpp          # Minimal entry point (Main loop)
```

### Module Details:

1. **Config.hpp**
   - Role: Single source of truth for all constants (SCREEN_WIDTH, NUM_AGENTS, VMAX, etc.).
   - Dependencies: None.

2. **AgentPool.hpp & FoodPool.hpp**
   - Role: Data structure definitions using Structure of Arrays (SoA).
   - HPC Constraint: Pre-allocate memory (resize) at startup, zero dynamic allocation during the main loop.

3. **Simulation.hpp / .cpp**
   - Role: Core physics and logic engine.
   - Responsibilities:
     - Position updates (x = x + v * dt).
     - Vision and steering force calculations.
     - Health/energy management and death/respawn handling.
     - Agent/food collision detection.
   - Dependencies: Config.hpp, AgentPool.hpp, FoodPool.hpp, <cmath>, <algorithm>, <random>.

4. **Renderer.hpp / .cpp**
   - Role: Complete isolation of the graphical layer.
   - Responsibilities: Drawing circles (agents and food) and displaying FPS.
   - Dependencies: raylib.h, AgentPool.hpp, FoodPool.hpp.

5. **main.cpp**
   - Role: High-level orchestration.
   - Responsibilities: Raylib window initialization, data instantiation, main while loop.

---

## Data Flow (Per Frame)

```text
[ main.cpp ]
     |
     +-- 1. Simulation::update(agents, food, dt, rng)
     |        +-- Vision calculation & Steering (SoA)
     |        +-- Physics integration (Position & Velocity)
     |        +-- Collision detection & Health update
     |
     +-- 2. Renderer::draw(agents, food)
              +-- ClearBackground(BLACK)
              +-- DrawCircle (Agents & Food)
              +-- EndDrawing()
```

---

## Applied HPC Principles
- **Structure of Arrays (SoA):** Optimizing CPU L1/L2/L3 cache lines during sequential memory access.
- **Squared Distance (dist^2):** Eliminating costly std::sqrt calls during proximity checks.
- **Simulation/Render Decoupling:** Enabling future headless mode execution for pure performance benchmarking (perf, gprof).