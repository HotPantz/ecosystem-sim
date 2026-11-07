# Project Architecture - Ecosystem Simulation (C++20 & Raylib)

## Project Goal
Develop a 2D ecosystem simulation in C++20 focusing on autonomous agents, artificial life, and emergent behaviors. 
To observe these complex interactions at scale (10,000+ entities) while maintaining 60 FPS, the project strictly applies Data-Oriented Design (SoA) and cache-friendly memory layouts. Performance is treated as an enabler for scale, not as the final goal.

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
   - Performance Design: Pre-allocate memory at startup to avoid dynamic allocation during the main simulation loop.

3. **Simulation.hpp / .cpp**
   - Role: Core physics, behavior, and logic engine.
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

## Core Technical Principles
- **Structure of Arrays (SoA):** Maximizing CPU cache efficiency to allow thousands of agents to interact simultaneously without frame drops.
- **Squared Distance (dist^2):** Eliminating costly `std::sqrt` calls during proximity and vision checks.
- **Simulation/Render Decoupling:** Ensuring the simulation logic is mathematically isolated and can run entirely independently of the graphical window.