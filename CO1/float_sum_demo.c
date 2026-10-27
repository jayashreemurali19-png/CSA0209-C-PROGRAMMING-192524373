#include <stdio.h>

int main(void)
{
    const int bills = 4000;
    float float_total = 0.0f;
    long long exact_paise = 0;

    for (int i = 0; i < bills; ++i) {
        float_total += 0.10f; /* Rs 0.10 per bill, binary approximation */
        exact_paise += 10;    /* 10 paise per bill, exact integer addition */
    }

    printf("Bills added: %d\n", bills);
    printf("Expected total: Rs 400.00\n");
    printf("float total: Rs %.7f\n", (double)float_total);
    printf("Integer paise total: Rs %lld.%02lld\n",
           exact_paise / 100, exact_paise % 100);
    return 0;
}
