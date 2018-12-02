//
// Created by chaed on 18. 12. 2.
//

#ifndef TERIS_FIGURE_CLASS_RANDOMGENERATOR_H
#define TERIS_FIGURE_CLASS_RANDOMGENERATOR_H

#pragma once

#include <cstdint>
#include <limits>

#include "../TDefine.h"


static CE auto seed()
{
    std::uint64_t shifted = 0;

    const auto time(__TIME__);

    for( const auto c : __TIME__ )
    {
        shifted <<= 8;
        shifted |= c;
    }

    return shifted;
}

class RandomGenerator {

public:



    using result_type = std::uint32_t;
    struct pcg32_random_t
    {
        std::uint64_t state = 0;
        std::uint64_t inc = seed();
    };
    pcg32_random_t rng;

    CE RandomGenerator(){}

    CE result_type operator()()
    {
        return pcg32_random_r();
    }

   /* static result_type constexpr min()
    {
        return std::numeric_limits<result_type>::min();
    }

    static result_type constexpr max()
    {
        return std::numeric_limits<result_type>::max();
    }*/


    static CE auto get_random(int count)
    {
        RandomGenerator rg;
        while(count > 0){
            rg();
            --count;
        }

        return rg();
    }

private:



    CE result_type pcg32_random_r()
    {
        std::uint64_t oldstate = rng.state;
        // Advance internal state
        rng.state = oldstate * 6364136223846793005ULL + (rng.inc|1);
        // Calculate output function (XSH RR), uses old state for max ILP
        std::uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
        std::uint32_t rot = oldstate >> 59u;
        return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
    }

};


#endif //TERIS_FIGURE_CLASS_RANDOMGENERATOR_H
