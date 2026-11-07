#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <random>
#include "AgentPool.hpp"
#include "FoodPool.hpp"

namespace Simulation {
    // Initializes pools with starting values and random positions
    void init(AgentPool& agents, FoodPool& food, std::mt19937& rng);

    // Computes physics, steering and metabolism for one frame
    void update(AgentPool& agents, FoodPool& food, float dt, std::mt19937& rng);
}

#endif // SIMULATION_HPP