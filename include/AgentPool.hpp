#ifndef AGENTPOOL_HPP
#define AGENTPOOL_HPP

#include <vector>
#include <cstddef>

struct AgentPool {

    std::vector<float> posX;
    std::vector<float> posY;
    std::vector<float> velX;
    std::vector<float> velY;
    std::vector<float> size;
    std::vector<float> energy;
    
    void resize(size_t count){
        
        posX.resize(count);
        posY.resize(count);
        velX.resize(count);
        velY.resize(count);
        size.resize(count);
        energy.resize(count);
    }
};


#endif // AGENTPOOL_HPP