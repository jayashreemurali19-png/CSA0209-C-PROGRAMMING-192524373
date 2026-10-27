#include <stdio.h>
int main(void) {
    printf("1) 5 / 2 = %d (integer division truncates)\n", 5 / 2);
    printf("2) (int)(1.0 / 3.0 * 100) = %d (cast truncates)\n", (int)(1.0 / 3.0 * 100));
    printf("3) 1 / 3.0 = %.6f (floating-point approximation)\n", 1 / 3.0);
    return 0;
}
