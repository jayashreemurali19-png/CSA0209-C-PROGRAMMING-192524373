/*
 * Task 1: Grama Jyothi electricity billing
 * Currency is stored in paise to avoid floating-point currency errors.
 * Assumptions: first 100 units free; units 101-200 at Rs 2.25/unit;
 * units above 200 at Rs 4.50/unit; fixed charge Rs 50.00 per bill.
 * Meter rollover is a 16-bit counter: 65535 -> 0.
 */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define FREE_UNITS 100u
#define SECOND_SLAB_LIMIT 200u
#define RATE_SLAB2_PAISE 225LL
#define RATE_SLAB3_PAISE 450LL
#define FIXED_CHARGE_PAISE 5000LL
#define METER_MAX 65535u

static bool parse_u32(const char *s, uint32_t *out) {
    char *end = NULL;
    unsigned long long value;
    if (s == NULL || *s == '\0' || *s == '-') return false;
    errno = 0;
    value = strtoull(s, &end, 10);
    if (errno != 0 || end == s || *end != '\0' || value > UINT32_MAX) return false;
    *out = (uint32_t)value;
    return true;
}

static bool calculate_units(uint32_t previous, uint32_t current, uint32_t *units) {
    if (previous <= METER_MAX && current <= METER_MAX) {
        if (current >= previous) {
            *units = current - previous;
            return true;
        }
        /* A rollover is accepted only when previous is near the counter maximum.
           For this 16-bit meter, any decrease is interpreted as one rollover. */
        *units = (METER_MAX - previous) + 1u + current;
        return true;
    }
    if (current >= previous) {
        *units = current - previous;
        return true;
    }
    return false;
}

static bool calculate_bill(uint32_t units, int64_t *bill_paise) {
    int64_t energy = 0;
    if (units > FREE_UNITS) {
        uint32_t slab2 = units < SECOND_SLAB_LIMIT ? units - FREE_UNITS : 100u;
        energy += (int64_t)slab2 * RATE_SLAB2_PAISE;
    }
    if (units > SECOND_SLAB_LIMIT) {
        energy += (int64_t)(units - SECOND_SLAB_LIMIT) * RATE_SLAB3_PAISE;
    }
    if (energy > INT64_MAX - FIXED_CHARGE_PAISE) return false;
    *bill_paise = energy + FIXED_CHARGE_PAISE;
    return true;
}

static void print_bill(const char *label, uint32_t prev, uint32_t curr) {
    uint32_t units;
    int64_t bill;
    if (!calculate_units(prev, curr, &units)) {
        printf("%s: ERROR invalid readings\n", label);
        return;
    }
    if (!calculate_bill(units, &bill)) {
        printf("%s: ERROR bill overflow\n", label);
        return;
    }
    printf("%s: previous=%" PRIu32 ", current=%" PRIu32
           ", units=%" PRIu32 ", bill=Rs %" PRId64 ".%02" PRId64 "\n",
           label, prev, curr, units, bill / 100, bill % 100);
}

int main(void) {
    char line[128];
    char prev_text[64], curr_text[64], extra[2];
    uint32_t previous, current;
    printf("Grama Jyothi Billing System\n");
    printf("Assumption: fixed charge Rs 50.00; first 100 units free; "
           "101-200 at Rs 2.25; above 200 at Rs 4.50.\n");
    printf("Enter previous and current 16-bit meter readings separated by space: ");
    if (!fgets(line, sizeof line, stdin)) {
        fprintf(stderr, "ERROR: no input\n");
        return 1;
    }
    if (sscanf(line, "%63s %63s %1s", prev_text, curr_text, extra) != 2 ||
        !parse_u32(prev_text, &previous) || !parse_u32(curr_text, &current) ||
        previous > METER_MAX || current > METER_MAX) {
        fprintf(stderr, "ERROR: enter two non-negative integer readings from 0 to 65535.\n");
        return 1;
    }
    if (current < previous && previous < 60000u) {
        fprintf(stderr, "ERROR: current reading is lower than previous reading without a plausible rollover.\n");
        return 1;
    }
    print_bill("Bill", previous, current);
    return 0;
}
