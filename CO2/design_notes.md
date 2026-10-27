# Task 3 — Final design recommendation

## Recommendation
Use fixed-width integer types for readings and currency, centralised tariff definitions, input validation, and explicit overflow checks. For the original fixed tariff, compile-time constants are simple and fast. For a changing tariff, a validated configuration file is preferable because the tariff can change without rebuilding and redistributing the executable.

## Recommended types
- `uint32_t` for a meter reading if the meter protocol defines a 32-bit non-negative reading; use `uint64_t` for cumulative counters when required.
- `int64_t` for total currency in paise, after checking that the value fits.
- `size_t` for array sizes and indexes.
- `int64_t` intermediate products for units × rate, with overflow checks before multiplication/addition.
- Avoid `float` for money. `double` has a wide range but represents most decimal fractions approximately, so it is not the best representation for whole-paise billing.

## Tariff change
With compile-time constants, edit one central tariff definition and rebuild/test/redeploy. With a configuration file, load the tariff at startup, validate all values and slab boundaries, reject malformed configurations, and keep a version/audit record.

## Complexity
For fixed if-statements and a fixed number of slabs, calculation is O(1) per bill. For an array-and-loop implementation with s slabs, calculation is O(s) per bill and O(s) storage for the tariff table. For a fixed small number of slabs, the practical difference is negligible; arrays are easier to maintain when slabs change.

## Limitations
The basic sample uses a simplified 16-bit rollover rule and assumes a fixed charge of Rs 50.00. A production system must know the actual meter counter width, detect plausible rollover versus faulty/reset readings, handle corrections and missing readings, log tariff versions, and define legal rounding rules.

## District scale
At 800,000 bills, the example Rs 162.50 average bill totals Rs 130,000,000 (Rs 13 crore), or 13,000,000,000 paise. This exceeds a typical 32-bit signed integer range in paise. A 64-bit signed integer is appropriate for this illustrative total, subject to checked arithmetic.


## Runnable alternative implementation
`alternative_slabs.c` stores cumulative limits and rates in a `Slab` array and loops over the entries. It is a small executable example of the array-based alternative. For a tariff with `s` slabs, each bill takes O(s) time in the worst case and the table uses O(s) space.
