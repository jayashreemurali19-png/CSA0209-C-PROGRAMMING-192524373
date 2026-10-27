/*
 * Alternative slab implementation: data-driven tariff table.
 * Compile: gcc -std=c11 -Wall -Wextra -Wpedantic alternative_slabs.c -o alternative_slabs
 */
#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint32_t upper_limit; /* cumulative unit limit */
    int64_t rate_paise;
} Slab;

#define FIXED_CHARGE_PAISE 5000LL

static const Slab slabs[] = {
    {100u, 0LL},
    {200u, 225LL},
    {UINT32_MAX, 450LL}
};

static int64_t bill_for(uint32_t units) {
    uint32_t lower = 0;
    int64_t energy = 0;
    for (size_t i = 0; i < sizeof slabs / sizeof slabs[0]; ++i) {
        uint32_t upper = slabs[i].upper_limit;
        uint32_t slab_units = units > lower ? (units < upper ? units - lower : upper - lower) : 0;
        energy += (int64_t)slab_units * slabs[i].rate_paise;
        if (units <= upper) break;
        lower = upper;
    }
    return FIXED_CHARGE_PAISE + energy;
}

int main(void) {
    const uint32_t samples[] = {0u, 100u, 150u, 200u, 250u};
    for (size_t i = 0; i < sizeof samples / sizeof samples[0]; ++i) {
        int64_t paise = bill_for(samples[i]);
        printf("%u units -> Rs %lld.%02lld\n", samples[i],
               (long long)(paise / 100), (long long)(paise % 100));
    }
    return 0;
}
