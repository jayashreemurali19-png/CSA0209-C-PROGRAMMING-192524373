#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void)
{
    printf("sizeof(char) = %zu, CHAR_MIN = %d, CHAR_MAX = %d\n",
           sizeof(char), CHAR_MIN, CHAR_MAX);
    printf("sizeof(short) = %zu, USHRT_MAX = %u\n",
           sizeof(unsigned short), (unsigned)USHRT_MAX);
    printf("sizeof(int) = %zu, INT_MIN = %d, INT_MAX = %d\n",
           sizeof(int), INT_MIN, INT_MAX);
    printf("sizeof(long) = %zu, LONG_MIN = %ld, LONG_MAX = %ld\n",
           sizeof(long), LONG_MIN, LONG_MAX);
    printf("sizeof(long long) = %zu, LLONG_MIN = %lld, LLONG_MAX = %lld\n",
           sizeof(long long), LLONG_MIN, LLONG_MAX);
    printf("sizeof(float) = %zu, FLT_DIG = %d, FLT_EPSILON = %.9g\n",
           sizeof(float), FLT_DIG, (double)FLT_EPSILON);
    printf("sizeof(double) = %zu, DBL_DIG = %d, DBL_EPSILON = %.17g\n",
           sizeof(double), DBL_DIG, DBL_EPSILON);
    return 0;
}
