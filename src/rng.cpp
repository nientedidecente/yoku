#include <vector>

#include "rng.hpp"

namespace yoku
{

    bool rng::chance(const int probability)
    {
        return rng::chance(float(probability) / 100.f);
    }

    bool rng::chance(const float probability)
    {
        static std::random_device randomDevice;
        static std::mt19937 randomEngine(randomDevice());
        static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
        return distribution(randomEngine) <= probability;
    }

    int rng::integer(const int min, const int max)
    {
        static std::random_device randomDevice;
        static std::mt19937 randomEngine(randomDevice());
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(randomEngine);
    }
}