# Task 3 — Define the Constants

## Choice of constants

The tariff values are defined using uppercase, descriptive `#define` names because the task explicitly asks for macro-based constants. The rates are expressed in paise per unit, and the fixed charge is in paise. The slab boundaries and rates are written in one place so a tariff revision is centralized.

- `#define`: textual substitution by the preprocessor; it has no C type and generally allocates no storage itself. It has no ordinary block scope and can be inspected in preprocessor output, but not as a normal variable in a debugger.
- `const` variable: has a type and follows C scope rules; the compiler can diagnose type-related mistakes more effectively. Depending on use and optimization, it may or may not occupy storage.
- `enum`: good for named integral choices such as household categories or states; enum constants are integer constant expressions. It is not suitable for fractional values, though paise values are integers.

Use uppercase names with words separated by underscores. Include units in names such as `_PAISE` to reduce confusion.

## Complete Code — TODO 1

The completed `slab_billing.c` calculates each slab progressively. It adds 0 paise for the first 100 units, 225 paise for each unit from 101 through 200, and 450 paise for every unit above 200. The fixed charge is added first.

Expected results:
- 0 units: Rs 50.00
- 100 units: Rs 50.00
- 150 units: Rs 162.50
- 200 units: Rs 275.00
- 350 units: Rs 950.00

To test a revision, change `#define RATE2_PAISE 225` to `#define RATE2_PAISE 230`, rebuild, and rerun. Bills using the second slab change by 5 paise for every unit in that slab. Bills at 100 units or below do not change. Bills above 200 change by Rs 0.05 for each of the 100 second-slab units, or Rs 5.00, assuming the first 100 units remain free.

## Complexity

Each bill calculation uses a fixed number of arithmetic operations and comparisons, so it takes **O(1)** time and **O(1)** extra space. For `n` households the total is **O(n)** time. Replacing `#define` with `const` or `enum` does not materially change asymptotic running time. The main differences are type checking, scope, debugger visibility, and whether a variable needs storage.
