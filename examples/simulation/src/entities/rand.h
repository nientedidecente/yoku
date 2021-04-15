#include <random>
#include <iostream>

class rng
{
public:
    static bool chance(const float probability)
    {
        static std::random_device randomDevice;
        static std::mt19937 randomEngine(randomDevice());
        static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
        return distribution(randomEngine) <= probability;
    }
};