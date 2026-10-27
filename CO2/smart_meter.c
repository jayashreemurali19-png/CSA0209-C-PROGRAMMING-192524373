/*
 * Task 4: Smart-meter time-of-day billing prototype.
 * Reads tariff values from a configuration file (tariff.conf).
 * Input is total off-peak Wh and peak Wh for one billing period.
 * Peak is 20% more expensive. Tariff is paise/kWh.
 * All fractional energy is retained in Wh; final currency is rounded
 * to the nearest paise using integer arithmetic.
 */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define CONFIG_FILE "tariff.conf"
#define PEAK_NUMERATOR 120LL
#define PEAK_DENOMINATOR 100LL
#define WH_PER_KWH 1000LL

static bool load_rate(const char *path, int64_t *rate_paise_per_kwh) {
    FILE *f = fopen(path, "r");
    char key[64];
    long long value;
    if (!f) return false;
    int found = 0;
    while (fscanf(f, "%63s %lld", key, &value) == 2) {
        if (strcmp(key, "OFFPEAK_PAISE_PER_KWH") == 0) {
            if (value <= 0 || value > 1000000000LL) { fclose(f); return false; }
            *rate_paise_per_kwh = (int64_t)value;
            found = 1;
        }
    }
    fclose(f);
    return found != 0;
}

static bool parse_nonnegative(const char *s, uint64_t *v) {
    char *end = NULL;
    if (!s || *s == '-' || *s == '\0') return false;
    errno = 0;
    unsigned long long x = strtoull(s, &end, 10);
    if (errno || end == s || *end || x > UINT64_MAX) return false;
    *v = (uint64_t)x;
    return true;
}

int main(void) {
    int64_t offpeak_rate;
    char a[64], b[64];
    uint64_t offpeak_wh, peak_wh;
    if (!load_rate(CONFIG_FILE, &offpeak_rate)) {
        fprintf(stderr, "ERROR: invalid or missing tariff.conf\n");
        return 1;
    }
    printf("Smart-meter billing (energy readings in Wh)\n");
    printf("Enter off-peak Wh and peak Wh: ");
    if (scanf("%63s %63s", a, b) != 2 ||
        !parse_nonnegative(a, &offpeak_wh) ||
        !parse_nonnegative(b, &peak_wh)) {
        fprintf(stderr, "ERROR: enter two non-negative integer Wh values\n");
        return 1;
    }
    /* Rates are paise/kWh. Calculate in 1/1000-paise units before final rounding. */
    if (offpeak_wh > (uint64_t)LLONG_MAX / (uint64_t)offpeak_rate ||
        peak_wh > (uint64_t)LLONG_MAX / (uint64_t)offpeak_rate) {
        fprintf(stderr, "ERROR: energy amount too large\n");
        return 1;
    }
    int64_t off_milli_paise = (int64_t)offpeak_wh * offpeak_rate;
    int64_t peak_base_milli_paise = (int64_t)peak_wh * offpeak_rate;
    if (peak_base_milli_paise > LLONG_MAX / PEAK_NUMERATOR) {
        fprintf(stderr, "ERROR: peak bill overflow\n");
        return 1;
    }
    int64_t peak_milli_paise = (peak_base_milli_paise * PEAK_NUMERATOR) / PEAK_DENOMINATOR;
    if (off_milli_paise > LLONG_MAX - peak_milli_paise) {
        fprintf(stderr, "ERROR: total overflow\n");
        return 1;
    }
    int64_t total_milli_paise = off_milli_paise + peak_milli_paise;
    int64_t total_paise = (total_milli_paise + 500) / 1000;
    printf("Off-peak energy: %" PRIu64 " Wh\n", offpeak_wh);
    printf("Peak energy: %" PRIu64 " Wh\n", peak_wh);
    printf("Off-peak rate: %" PRId64 " paise/kWh\n", offpeak_rate);
    printf("Peak rate: 20%% surcharge\n");
    printf("Total bill: Rs %" PRId64 ".%02" PRId64 "\n", total_paise / 100, total_paise % 100);
    return 0;
}
