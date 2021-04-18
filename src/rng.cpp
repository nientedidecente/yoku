#include <vector>

#include "rng.hpp"
#include <vector>
#include <algorithm>
#include <random>

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

    std::string rng::str(const int length)
    {
        static std::vector<char> alphabet{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
                                          'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                          'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                                          'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                          'w', 'x', 'y', 'z'};
        static std::random_device randomDevice;
        std::default_random_engine randomEngine(randomDevice());
        std::shuffle(alphabet.begin(), alphabet.end(), randomEngine);
        std::string result = "";
        for (size_t i = 0; i < length; i++)
        {
            result += alphabet[rng::integer(0, alphabet.size() - 1)];
        }

        return result;
    }
}