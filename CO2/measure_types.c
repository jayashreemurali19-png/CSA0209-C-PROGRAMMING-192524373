/*
 * Task 2: Compare currency accumulation and integer type ranges.
 * Uses a reproducible bill pattern and prints measured totals.
 */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <float.h>
#include <stddef.h>

#define FIXED_PAISE 5000LL
#define BILL_PAISE 16250LL /* Rs 162.50 example bill */

int main(void) {
    const uint64_t counts[] = {4000ULL, 60000ULL, 800000ULL};
    printf("Compiler-visible type measurements\n");
    printf("sizeof(int)=%zu, sizeof(long)=%zu, sizeof(long long)=%zu, sizeof(double)=%zu, sizeof(float)=%zu\n",
           sizeof(int), sizeof(long), sizeof(long long), sizeof(double), sizeof(float));
    printf("INT_MIN=%d INT_MAX=%d\n", INT_MIN, INT_MAX);
    printf("LONG_MIN=%ld LONG_MAX=%ld\n", LONG_MIN, LONG_MAX);
    printf("LLONG_MIN=%lld LLONG_MAX=%lld\n", LLONG_MIN, LLONG_MAX);
    printf("FLT_DIG=%d DBL_DIG=%d LDBL_DIG=%d\n", FLT_DIG, DBL_DIG, LDBL_DIG);
    for (size_t i = 0; i < sizeof counts / sizeof counts[0]; ++i) {
        uint64_t n = counts[i];
        long long exact_paise = (long long)n * BILL_PAISE;
        double double_rupees = (double)n * 162.50;
        float float_rupees = (float)n * 162.50f;
        printf("bills=%" PRIu64 " exact_paise=%lld exact_rupees=%.2f float_rupees=%.2f double_rupees=%.2f\n",
               n, exact_paise, exact_paise / 100.0, (double)float_rupees, double_rupees);
    }
    printf("district int test: 800000 * 16250 paise exceeds 32-bit signed int range.\n");
    return 0;
}
