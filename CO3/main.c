#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "billing.h"

int read_uint16(const char *prompt, uint16_t *value) {
    unsigned int temp;
    int result;
    printf("%s", prompt);
    result = scanf("%u", &temp);
    if (result != 1 || temp > UINT16_MAX) {
        fprintf(stderr, "Invalid input: enter a whole number from 0 to 65535.\n");
        return 0;
    }
    *value = (uint16_t)temp;
    return 1;
}

uint32_t calculate_units(uint16_t previous, uint16_t current) {
    uint32_t units;
    if (current >= previous) {
        units = (uint32_t)current - (uint32_t)previous;
    } else {
        /* 16-bit meter rolls from 65535 to 0. */
        units = (uint32_t)UINT16_MAX + 1u - (uint32_t)previous + (uint32_t)current;
    }
#ifdef DEBUG
    fprintf(stderr, "[DEBUG] previous=%" PRIu16 ", current=%" PRIu16
                    ", units=%" PRIu32 "\n", previous, current, units);
#endif
    return units;
}

int64_t calculate_energy_charge(uint32_t units) {
    uint32_t charged_second = 0;
    uint32_t charged_third = 0;
    if (units > FREE_UNITS) {
        uint32_t remaining = units - FREE_UNITS;
        charged_second = remaining < SECOND_SLAB_UNITS ? remaining : SECOND_SLAB_UNITS;
        if (remaining > SECOND_SLAB_UNITS) {
            charged_third = remaining - SECOND_SLAB_UNITS;
        }
    }
    int64_t charge = (int64_t)charged_second * SECOND_SLAB_RATE_PAISE
                   + (int64_t)charged_third * THIRD_SLAB_RATE_PAISE;
#ifdef DEBUG
    fprintf(stderr, "[DEBUG] second-slab units=%" PRIu32
                    ", third-slab units=%" PRIu32
                    ", energy charge=%" PRId64 " paise\n",
                    charged_second, charged_third, charge);
#endif
    return charge;
}

Bill calculate_bill(uint16_t previous, uint16_t current) {
    Bill bill;
    bill.previous_reading = previous;
    bill.current_reading = current;
    bill.units = calculate_units(previous, current);
    bill.energy_charge_paise = calculate_energy_charge(bill.units);
    bill.total_paise = FIXED_CHARGE_PAISE + bill.energy_charge_paise;
    return bill;
}

void print_money(int64_t paise) {
    printf("Rs %" PRId64 ".%02" PRId64, paise / 100, paise % 100);
}

void print_bill(const Bill *bill) {
    printf("\n--- Electricity Bill ---\n");
    printf("Previous reading : %" PRIu16 "\n", bill->previous_reading);
    printf("Current reading  : %" PRIu16 "\n", bill->current_reading);
    printf("Units consumed   : %" PRIu32 "\n", bill->units);
    printf("Fixed charge     : ");
    print_money(FIXED_CHARGE_PAISE);
    printf("\nEnergy charge    : ");
    print_money(bill->energy_charge_paise);
    printf("\nTotal bill       : ");
    print_money(bill->total_paise);
    printf("\n");
}

int main(void) {
    uint16_t previous, current;
    puts("Grama Jyothi Electricity Billing");
    if (!read_uint16("Enter previous meter reading (0-65535): ", &previous)) return EXIT_FAILURE;
    if (!read_uint16("Enter current meter reading (0-65535): ", &current)) return EXIT_FAILURE;
    Bill bill = calculate_bill(previous, current);
    print_bill(&bill);
    return EXIT_SUCCESS;
}
