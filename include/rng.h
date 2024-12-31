#ifndef RNG
#define RNG

#include <random>
#include <chrono>

namespace rng
{
    inline std::random_device rd{};

    inline std::seed_seq ss
    {
        static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()),
        rd(), rd() 
    };

    inline std::mt19937 mt{ ss };
}

#endif