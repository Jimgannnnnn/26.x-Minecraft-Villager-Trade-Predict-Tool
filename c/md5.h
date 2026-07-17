#ifndef MD5_H
#define MD5_H

#include <stdint.h>

typedef struct {
    uint64_t lo, hi;
} Seed128;

void md5_hash_bytes(const char* input, int len, uint8_t digest[16]);
Seed128 seed_from_hash(const char* identifier);

#endif
