#ifndef FOODPOOL_HPP
#define FOODPOOL_HPP

#include <vector>
#include <cstddef>

struct FoodPool {

    std::vector<float> posX;
    std::vector<float> posY;
    std::vector<bool> active;
    
    void resize(size_t count){
        
        posX.resize(count);
        posY.resize(count);
        active.resize(count);
    }
};

#endif // FOODPOOL_HPP