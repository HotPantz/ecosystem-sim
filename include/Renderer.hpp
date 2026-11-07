#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "AgentPool.hpp"
#include "FoodPool.hpp"

namespace Renderer {
    void beginFrame();
    void endFrame();
    
    void drawAgents(const AgentPool& agents);
    void drawFood(const FoodPool& food);
}

#endif // RENDERER_HPP