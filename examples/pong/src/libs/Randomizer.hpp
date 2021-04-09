#pragma once

#include <random>
#include <memory>

class Randomizer
{

public:
    Randomizer() {}
    bool chance(const float probability);
    int integer(const int min, const int max);
};
