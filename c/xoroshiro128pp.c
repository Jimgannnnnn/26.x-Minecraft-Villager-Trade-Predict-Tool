#include "xoroshiro128pp.h"

#define SILVER_RATIO_64 0x6A09E667F3BCC909ULL
#define GOLDEN_RATIO_64 0x9E3779B97F4A7C15ULL

static uint64_t rotl64(uint64_t x, int k) {
    return (x << k) | (x >> (64 - k));
}

void xoroshiro_init(Xoroshiro128PlusPlus* rng, int64_t seed_lo, int64_t seed_hi) {
    uint64_t lo = (uint64_t)seed_lo;
    uint64_t hi = (uint64_t)seed_hi;
    if (lo == 0 && hi == 0) {
        lo = SILVER_RATIO_64;
        hi = GOLDEN_RATIO_64;
    }
    rng->s0 = lo;
    rng->s1 = hi;
}

int64_t xoroshiro_next_long(Xoroshiro128PlusPlus* rng) {
    uint64_t s0 = rng->s0, s1 = rng->s1;
    uint64_t result = rotl64(s0 + s1, 17) + s0;
    s1 ^= s0;
    rng->s0 = rotl64(s0, 49) ^ s1 ^ (s1 << 21);
    rng->s1 = rotl64(s1, 28);
    return (int64_t)result;
}

int xoroshiro_next_int(Xoroshiro128PlusPlus* rng, int bound) {
    if (bound <= 0) return 0;
    uint64_t r = ((uint64_t)xoroshiro_next_long(rng)) >> 33;
    uint64_t m = (uint64_t)((uint32_t)bound - 1);
    if ((bound & m) == 0)
        return (int)(((uint64_t)bound * r) >> 31);
    for (;;) {
        uint64_t u = r;
        uint64_t result = u % (uint64_t)bound;
        if (u - result + m < (1ULL << 31))
            return (int)result;
        r = ((uint64_t)xoroshiro_next_long(rng)) >> 33;
    }
}
