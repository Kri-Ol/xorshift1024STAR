// -*- C++ -*-

#pragma once

#include <cstdint>
#include <algorithm>
#include <utility>

namespace OTI
{
    class xorshift1024star
    {
#pragma region Typedefs/Constants
        public: typedef uint_fast64_t result_type;
        public: typedef result_type   seed_type;

        // those values are from S.Vigna "An experimental exploration of Marsaglia's xorshift generators, scrambled",
        // http://arxiv.org/abs/1402.6246, known as M(31,11,30) with scrambling
        public: static constexpr uint32_t shift_a = 31U;
        public: static constexpr uint32_t shift_b = 11U;
        public: static constexpr uint32_t shift_c = 30U;

        public: static constexpr result_type  mult  = 1181783497276652981ULL;

        public: static constexpr seed_type    default_seed[] = { 3001ULL, 3079ULL, 3257ULL, 3511ULL,
                                                                4001ULL, 4057ULL, 4507ULL, 4583ULL,
                                                                5003ULL, 5281ULL, 5861ULL, 5987ULL,
                                                                6007ULL, 6229ULL, 6301ULL, 7901ULL };

        public: static constexpr float        norm  = float{double{1.0}/double{result_type{-1LL}}};
#pragma endregion

#pragma region Data
        private: mutable seed_type _seed[16];
        private: mutable int       _p;
#pragma endregion

#pragma region Ctor/Dtor/op=
        public: xorshift1024star(const seed_type* seed = default_seed):
            _seed{seed[0], seed[1], seed[2], seed[3], seed[4], seed[5], seed[6], seed[7], seed[8], seed[9], seed[10], seed[11], seed[12], seed[13], seed[14], seed[15]},
            _p{0}
        {
        }

        public: xorshift1024star(xorshift1024star const& r):
            xorshift1024star{r._seed}
        {
            _p = r._p;
        }

        public: xorshift1024star(xorshift1024star&& r):
            xorshift1024star{r._seed}
        {
            _p = r._p;
        }        

        public: xorshift1024star& operator=(xorshift1024star const& r)
        {
            std::copy(r._seed, r._seed + 16, _seed);
            _p = r._p;

            return *this;
        }

        public: xorshift1024star& operator=(xorshift1024star&& r)
        {
            std::copy(r._seed, r._seed + 16, _seed);
            _p = r._p;

            return *this;
        }

        public: ~xorshift1024star()
        {
        }
#pragma endregion

#pragma region Observers
        public: const seed_type* seed() const
        {
            return _seed;
        }
#pragma endregion

#pragma region Helpers
#pragma endregion

#pragma region Mutators
        public: result_type sample() const
        {
            uint64_t s0 = _seed[ _p ];
            _p = ( _p + 1 ) & 15;
            uint64_t s1 = _seed[ _p ];

            s1 ^= s1 << shift_a;
            s1 ^= s1 >> shift_b;
            s0 ^= s0 >> shift_c;
            return ( _seed[ _p ] = s0 ^ s1 ) * mult;
        }

        public: float number() const
        {
            return float(sample()) * norm;
        }

        public: void skip(uint64_t ns) const;
#pragma endregion
    };    
}
