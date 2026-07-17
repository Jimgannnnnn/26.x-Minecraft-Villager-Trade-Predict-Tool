#ifndef XOROSHIRO128PP_H
#define XOROSHIRO128PP_H

#include <stdint.h>

typedef struct {
    uint64_t s0, s1;
} Xoroshiro128PlusPlus;

void xoroshiro_init(Xoroshiro128PlusPlus* rng, int64_t seed_lo, int64_t seed_hi);
int64_t xoroshiro_next_long(Xoroshiro128PlusPlus* rng);
int xoroshiro_next_int(Xoroshiro128PlusPlus* rng, int bound);

#endif
