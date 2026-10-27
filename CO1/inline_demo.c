#include <stdio.h>

static inline long long rupees_to_paise(long long rupees)
{
    return rupees * 100LL;
}

static inline int square_int(int value)
{
    return value * value;
}

static inline int max_int(int a, int b)
{
    return a > b ? a : b;
}

int main(void)
{
    int a = 4;
    int b = 7;
    printf("Rs 12 -> %lld paise\n", rupees_to_paise(12));
    printf("square(a + 1) = %d\n", square_int(a + 1));
    printf("max(a, b) = %d\n", max_int(a, b));
    return 0;
}
