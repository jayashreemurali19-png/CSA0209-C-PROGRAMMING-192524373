# Task 3 — Type Conversion and Precision

The implementation uses integer paise for all money calculations. It casts meter readings to `uint32_t` before subtraction so arithmetic does not accidentally wrap at 16 bits. The bill uses `int64_t` for monetary totals and multiplication.

## Three surprising expressions
1. `5 / 2` prints `2`, not `2.5`, because both operands are integers and integer division truncates toward zero.
2. `(int)4000000000L` is not a portable way to store a large value in `int`; the value is outside the usual 32-bit signed-int range, so the conversion result is implementation-defined (or an implementation-defined signal may be raised).
3. `printf("%d", (int)(1.0 / 3.0 * 100))` prints `33`, not a rounded `33` paise from a money policy; the floating result is truncated by the cast. A deliberate rounding rule must be specified.

For this assignment, the rule is to calculate the tariff in whole paise per unit and use integer multiplication; therefore no fractional paise rounding is needed. Rates are Rs 2.25 = 225 paise and Rs 4.50 = 450 paise.

## Alternative: float until the end
A floating-point implementation can accumulate binary representation and rounding errors; the total error may grow with the number of operations/bills, often roughly with n in a worst-case simple bound, but its exact measured behaviour depends on values, order and compiler. A meaningful measurement should compare a float-based total with the integer-paise reference for the same generated set of n bills. `float` commonly uses 4 bytes; `int64_t` uses 8 bytes on typical platforms. Integer-paise arithmetic is exact for the defined rates and avoids per-bill binary floating-point rounding.
