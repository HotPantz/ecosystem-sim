#include "Simulation.hpp"
#include "Config.hpp"
#include <cmath>      // Needed later for update()
#include <algorithm>  // Needed later for update()

namespace Simulation {

    void init(AgentPool& agents, FoodPool& food, std::mt19937& rng) {

        agents.resize(NUM_AGENTS);
        food.resize(NUM_FOOD);

        // Distributions setup
        std::uniform_real_distribution<float> distX(0.0f, static_cast<float>(SCREEN_WIDTH));
        std::uniform_real_distribution<float> distY(0.0f, static_cast<float>(SCREEN_HEIGHT));
        std::uniform_real_distribution<float> distVel(-100.0f, 100.0f);

        for (size_t i = 0; i < NUM_AGENTS; ++i) {
            agents.posX[i] = distX(rng);
            agents.posY[i] = distY(rng);
            agents.velX[i] = distVel(rng);
            agents.velY[i] = distVel(rng);
            agents.size[i] = AGENT_DEFAULT_SIZE;
            agents.energy[i] = 100.0f;
        }

        // Reusing distX and distY for food
        for (size_t i = 0; i < NUM_FOOD; ++i) {
            food.posX[i] = distX(rng);
            food.posY[i] = distY(rng);
            food.active[i] = true;
        }
    }

    void update(AgentPool& agents, FoodPool& food, float dt, std::mt19937& rng) {

        std::uniform_real_distribution<float> distX(0.0f, static_cast<float>(SCREEN_WIDTH));
        std::uniform_real_distribution<float> distY(0.0f, static_cast<float>(SCREEN_HEIGHT));
        
        for(size_t i=0;i<NUM_AGENTS; ++i){

            float minDistSq = VISION_RADIUS_SQ;
            int targetFoodIndex = -1;

            for(size_t j = 0; j< NUM_FOOD; ++j){
                
                if (!food.active[j]) continue;

                float dx = food.posX[j] - agents.posX[i];
                float dy = food.posY[j] - agents.posY[i];
                float distSq = dx * dx + dy * dy;

                if(distSq < minDistSq){
                    minDistSq = distSq;
                    targetFoodIndex = static_cast<int>(j);
                }
            }

            if (targetFoodIndex != -1){

                float foodDistance = std::sqrt(minDistSq);

                if (foodDistance > 0.001f){
                    

                    float dx = food.posX[targetFoodIndex] - agents.posX[i];
                    float dy = food.posY[targetFoodIndex] - agents.posY[i];

                    // Desired velocities
                    float desiredVelX = (dx / foodDistance) * VMAX;
                    float desiredVelY = (dy / foodDistance) * VMAX;

                    //Steering

                    agents.velX[i] += (desiredVelX - agents.velX[i]) * STEERING_RATE * dt;
                    agents.velY[i] += (desiredVelY - agents.velY[i]) * STEERING_RATE * dt;
                }   
            }

            agents.posX[i] += agents.velX[i] * dt;
            agents.posY[i] += agents.velY[i] * dt;
            agents.energy[i] -= 5.0f*dt;

            if (agents.posX[i] < 0 || agents.posX[i] > SCREEN_WIDTH){
                agents.velX[i] *= -1;
            };
            if (agents.posY[i] < 0 || agents.posY[i] > SCREEN_HEIGHT){
                agents.velY[i] *= -1;
            };

            for (size_t j = 0; j < NUM_FOOD; ++j) {
                if (!food.active[j]) continue;

                    float dx = agents.posX[i] - food.posX[j];
                    float dy = agents.posY[i] - food.posY[j];
                    float distSq = dx * dx + dy * dy;

                    // If less than 8 pixels
                    if (distSq < 64.0f) {
                        agents.energy[i] = std::min(100.0f, agents.energy[i] + 30.0f);
                        agents.size[i] += 0.5f; // Increasing the size as they eat
                        food.posX[j] = distX(rng); // respawn de la nourriture
                        food.posY[j] = distY(rng);
                    }
            }

            if (agents.energy[i] <= 0.0f) {
                agents.posX[i] = distX(rng);
                agents.posY[i] = distY(rng);
                agents.energy[i] = 100.0f;
                agents.size[i] = AGENT_DEFAULT_SIZE;
            }
        }
    }
} // namespace Simulation