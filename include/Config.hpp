#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <cstddef>

constexpr int SCREEN_WIDTH = 2560;
constexpr int SCREEN_HEIGHT = 1440;

constexpr size_t NUM_AGENTS = 10;
constexpr float AGENT_DEFAULT_SIZE = 3.0f;

constexpr size_t NUM_FOOD = 1000;
constexpr float VISION_RADIUS_SQ = 80.0f * 80.0f;

constexpr float VMAX = 100.0f;
constexpr float STEERING_RATE = 5.0f;

#endif // CONFIG_HPP