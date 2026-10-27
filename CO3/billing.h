#ifndef BILLING_H
#define BILLING_H

#include <stdint.h>
#include <stddef.h>

#define FIXED_CHARGE_PAISE 500
#define FREE_UNITS 100u
#define SECOND_SLAB_UNITS 100u
#define SECOND_SLAB_RATE_PAISE 225
#define THIRD_SLAB_RATE_PAISE 450

typedef struct {
    uint16_t previous_reading;
    uint16_t current_reading;
    uint32_t units;
    int64_t energy_charge_paise;
    int64_t total_paise;
} Bill;

int read_uint16(const char *prompt, uint16_t *value);
uint32_t calculate_units(uint16_t previous, uint16_t current);
int64_t calculate_energy_charge(uint32_t units);
Bill calculate_bill(uint16_t previous, uint16_t current);
void print_money(int64_t paise);
void print_bill(const Bill *bill);

#endif
