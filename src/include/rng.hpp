#include <random>
#include <iostream>

namespace yoku
{
    class rng
    {
    public:
        static bool chance(const int probability);
        static bool chance(const float probability);
        static int integer(const int min, const int max);
    };
}