# Task 1 — Understand the Problem and Identify the Data

## 1. Inputs and why they are needed

| Data item | Meaning and justification |
|---|---|
| Household number | Identifies the account and lets the office associate a bill with the correct household. Store as an integer if purely numeric; use a character array if IDs can contain letters or leading zeroes. |
| Previous meter reading | Reading at the start of the billing period. It is in the meter register's range 0–65535. |
| Current meter reading | Reading at the end of the billing period. It has the same range as the previous reading. |
| Household category | Selects the applicable tariff or fixed charge if categories have different rules. An `enum` is suitable for a small, fixed set of categories. |
| Tariff/slab values | Rates and slab boundaries used to calculate the bill. They should be defined once, not copied into many expressions. |

## 2. Computed values and outputs

- **Units consumed:** for a 16-bit register, `(current - previous) mod 65536`. This handles one rollover, assuming fewer than 65,536 units were consumed between readings.
- **Energy charge:** sum of the charges for the units falling into each slab.
- **Fixed charge:** monthly charge independent of usage, according to the stated tariff.
- **Total bill:** fixed charge + energy charge, stored and calculated in paise to avoid fractional-paise errors.
- **Household bill record:** household number, readings, units, category, and each charge should be printed or saved for auditability.

## 3. Constants and values that may vary

The meter modulus `65536`, slab limits `100` and `200`, rates `0`, `225` and `450` paise per unit, and fixed charge `5000` paise are tariff/configuration constants for this assignment. Use named macros or typed `const` values so tariff changes are made in one location. Readings and household identifiers vary for every account. Units and bill amounts are computed for every account.

## 4. Range, fractional and large values

- Meter readings are non-negative integers in the inclusive range 0–65535.
- Consumption is non-negative. The result can be 0–65535 under the one-rollover assumption.
- Rates and money are represented as whole paise, so the stored amount is integral, even though displayed rupees have two decimal digits.
- District totals can be large because as many as 800,000 bills may be processed. Use a sufficiently wide integer type such as `long long` for aggregate money and validate multiplication/addition bounds.
- Negative bills are not valid. A negative difference in readings means rollover or invalid data, not negative consumption.

## 5. Correctness rules and validation

1. Both readings must be in the meter register's valid range.
2. Consumption must be non-negative and must follow the rollover rule.
3. Energy charge must be non-negative for non-negative units and rates.
4. Total paise must equal fixed-charge paise + energy-charge paise.
5. Output rupees and paise with exactly two digits after the decimal point.
6. Invalid household/category data should be rejected or flagged, not silently billed.
7. The one-rollover formula assumes at most one wrap between readings. Smart-meter data should include timestamps or rollover counts if multiple wraps are possible.

## 6. Assumptions

- Meter is an unsigned 16-bit register with modulus 65,536.
- At most one rollover occurs between two monthly readings.
- Tariff example is progressive: first 100 units free, units 101–200 at 225 paise/unit, and units above 200 at 450 paise/unit.
- Fixed charge is Rs 50.00 (5,000 paise).
- Taxes, subsidies, late fees, and category-specific tariff differences are excluded unless explicitly added.
- The assignment's example treats slab rates as marginal rates, not a single rate applied to all units.

## 7. Alternative: store readings as text

A string such as `"01530"` preserves leading zeroes and is useful when reading meter exports or fixed-width files. The program must validate that every character is a digit, convert the string to an integer (for example with `strtoul`), and then compare/subtract numeric values. For a reading containing `d` digits, validation and conversion take **O(d)** time. Comparing strings lexicographically is only numerically correct when strings have equal width and consistent leading-zero rules; numeric conversion is safer.

An integer reading typically uses `sizeof(meter_t)` bytes (2 bytes on common systems where `unsigned short` is 2 bytes). A string uses `d + 1` bytes including the null terminator, plus any pointer/metadata if dynamically allocated. Conversion needs temporary storage only if the application stores both forms; otherwise it can parse into a numeric variable and discard the text. Per-reading conversion is O(d) time; storage is O(d) for text versus O(1) fixed-size storage for the integer representation.

## 8. Complexity as household count grows

For `n` households, one constant-time bill calculation per household takes **O(n)** time. If processing one household at a time, working memory is **O(1)** beyond the input/output buffers. Storing all household records requires **O(n)** memory. Increasing from 4,000 to 800,000 households changes the amount of work linearly; it does not change the asymptotic complexity.
