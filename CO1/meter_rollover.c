#include <stdio.h>
#include <limits.h>

/* The meter register is a 16-bit counter: after 65535 it rolls over to 0. */
typedef unsigned short meter_t;

unsigned int consumption(meter_t previous, meter_t current)
{
    /* Masking to 16 bits implements modulo-65536 subtraction. */
    return (unsigned int)((current - previous) & USHRT_MAX);
}

int main(void)
{
    if (USHRT_MAX != 65535U) {
        fprintf(stderr, "This example requires unsigned short to have max 65535.\n");
        return 1;
    }

    printf("sizeof(meter_t) = %zu bytes, maximum reading = %u\n",
           sizeof(meter_t), (unsigned)USHRT_MAX);
    printf("Consumption: %u units\n", consumption(1200, 1530));
    printf("Consumption: %u units\n", consumption(65400, 120)); /* rolled over */
    return 0;
}
