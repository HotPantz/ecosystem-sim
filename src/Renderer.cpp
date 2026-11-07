#include "Renderer.hpp"
#include "Config.hpp"
#include "raylib.h"

namespace Renderer {

    void beginFrame() {
        BeginDrawing();
        ClearBackground(BLACK);
    }

    void endFrame() {
        DrawFPS(10, 10);
        EndDrawing();
    }

    void drawAgents(const AgentPool& agents) {
        for (size_t i = 0; i < NUM_AGENTS; ++i) {
            Color color = (agents.energy[i] > 30.0f) ? GREEN : ORANGE;
            DrawCircle(static_cast<int>(agents.posX[i]), static_cast<int>(agents.posY[i]), agents.size[i], color);
        }
    }

    void drawFood(const FoodPool& food) {
        for (size_t i = 0; i < NUM_FOOD; ++i) {
            if (food.active[i]) {
                DrawCircle(static_cast<int>(food.posX[i]), static_cast<int>(food.posY[i]), 2.0f, RED);
            }
        }
    }

} // namespace Renderer