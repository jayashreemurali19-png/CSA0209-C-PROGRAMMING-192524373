#include <stdio.h>

#define RUPEES_TO_PAISE(rupees) ((long long)(rupees) * 100LL)
#define SQUARE(x) ((x) * (x))
#define MAX_VALUE(a, b) (((a) > (b)) ? (a) : (b))

int main(void)
{
    int a = 4;
    int b = 7;
    int i = 3;
    int j = 5;

    printf("Rs 12 -> %lld paise\n", RUPEES_TO_PAISE(12));
    printf("SQUARE(a + 1) = %d\n", SQUARE(a + 1));
    printf("MAX_VALUE(a, b) = %d\n", MAX_VALUE(a, b));

    /* Do not use side-effect expressions such as i++ in MAX_VALUE.
       An argument may be evaluated more than once. */
    printf("i before unsafe example = %d; MAX_VALUE(i++, j) is unsafe\n", i);
    printf("i after print remains = %d\n", i);
    return 0;
}
