#include "raylib.h"
#include <random>

// Project headers
#include "Config.hpp"
#include "AgentPool.hpp"
#include "FoodPool.hpp"
#include "Simulation.hpp"
#include "Renderer.hpp" // <-- Nouveau header

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Ecosystem HPC - V1");
    SetWindowMonitor(0);
    SetTargetFPS(60);

    AgentPool agents;
    FoodPool food;
    std::mt19937 rng(666);

    // 1. Setup
    Simulation::init(agents, food, rng);

    // 2. Game Loop
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        
        // Logic (CPU Math)
        Simulation::update(agents, food, dt, rng);

        // Graphics (GPU / Raylib)
        Renderer::beginFrame();
        Renderer::drawAgents(agents);
        Renderer::drawFood(food);
        Renderer::endFrame();
    }

    CloseWindow();
    return 0;
}