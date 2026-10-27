# Task 2 — Choose the Data Types

## Recommended data types

| Item | Suggested type | Reason |
|---|---|---|
| Meter reading | `unsigned short` (`meter_t`) | Non-negative register; on the expected system it is 2 bytes and can represent 0–65535. Verify with `sizeof` and `USHRT_MAX`. |
| Consumption | `unsigned int` | Holds 0–65535 units and makes the non-negative meaning explicit. |
| Household number | `unsigned long long` or string | Numeric ID can be large; use a string if leading zeroes or letters matter. |
| Category | `enum` | Small set of named categories. |
| Slab limits | `int` or named macros | Small whole-unit boundaries. |
| Rates and fixed charge | `long` or `long long` integer paise | Exact monetary arithmetic without binary floating-point rounding. |
| One bill total | `long` / `long long` | Select based on range and platform; `long long` has at least 64 bits in standard C. |
| District aggregate | `long long` | Safer for sums across hundreds of thousands of households. |
| Display-only rupees | integer division/remainder | Format paise as rupees and two-digit paise; avoid converting the stored value to float. |

## Range and size evidence

Run `limits_demo.c` on the same system used for submission. Sizes are implementation-dependent; do not assume every system has identical sizes. `limits.h` provides integer limits such as `USHRT_MAX`, `INT_MAX`, `LONG_MAX`, and `LLONG_MAX`; `float.h` provides floating-point properties such as `FLT_DIG`, `DBL_DIG`, and `DBL_EPSILON`.

## Why money should not be stored as float rupees

Binary floating-point cannot represent many decimal fractions exactly. Repeated arithmetic can accumulate small errors, and rounding at different stages can change a bill by a paisa. Store amounts in integer paise instead. For example, Rs 2.25 becomes 225 paise and Rs 50.00 becomes 5,000 paise. Only format the integer amount for display.

`float` often has about 6–7 decimal significant digits, while `double` often has about 15–16. Their exact properties are implementation-dependent. Neither type guarantees exact representation of all decimal fractions.

## Float accumulation demonstration

`float_sum_demo.c` compares repeated addition of Rs 0.10 using `float` with integer paise. The displayed result depends on the implementation, but floating-point accumulation may differ from the exact expected value; integer paise remains exact for values that fit in the integer type. This demonstrates a precision risk, not a claim that every run must show the same error.

## Complete Code — TODO 1

`meter_rollover.c` uses unsigned arithmetic only:

```c
return (unsigned int)((current - previous) & USHRT_MAX);
```

Because `USHRT_MAX` is 65535 on the required 16-bit meter system, the bit mask keeps the low 16 bits. The subtraction is performed after integer promotion, and masking gives modulo-65536 behavior. For previous 65400 and current 120, the calculation is `120 - 65400 = -65280`; keeping the low 16 bits yields `256`. It is not a negative consumption because the counter wrapped from 65535 to 0.

**Portability note:** the expression assumes `USHRT_MAX == 65535`, which is checked by the program. For a general meter format, define the register modulus explicitly and use a type wide enough to represent the arithmetic.

## Alternative: `double` rupees

A `double` solution could calculate rates in rupees and round at the billing boundary, for example by converting a final amount to integer paise with a documented rounding rule. This is less reliable than keeping all tariff calculations in paise because the binary representation of decimal fractions is approximate. Each addition is O(1) for either representation. Integer paise usually occupies `sizeof(long long)` bytes; `double` occupies `sizeof(double)` bytes. Actual sizes must be measured with `sizeof`.

If each floating-point operation introduces an error bounded approximately by a small relative machine-precision factor, the accumulated error can grow with the number of operations; it is not always a simple fixed error per bill. Integer paise has zero rounding error for exact integer operations as long as overflow does not occur. Choose a wide integer type and check aggregate bounds.
