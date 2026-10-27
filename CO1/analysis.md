# Task 4 — Use Macros Safely

## Macros in this program

- `RUPEES_TO_PAISE(x)` converts whole rupees to paise.
- `SQUARE(x)` calculates the square of an expression.
- `MAX_VALUE(a, b)` chooses the larger of two values.

Every macro parameter and the entire replacement expression are parenthesized. This is important because the preprocessor performs textual substitution before C compilation.

## Why parentheses matter

An unsafe definition `#define SQUARE(x) x*x` called as `SQUARE(a+1)` expands to `a+1*a+1`. Operator precedence makes that `a + (1*a) + 1`, not `(a+1)*(a+1)`. The safe definition `#define SQUARE(x) ((x) * (x))` expands correctly.

## Why MAX can evaluate an argument twice

The expression `((a) > (b) ? (a) : (b))` may evaluate the selected argument again after the comparison. Therefore `MAX_VALUE(i++, j)` can increment `i` more than once and has surprising behavior. Avoid side effects in macro arguments. A typed function or `static inline` function evaluates each argument once as part of the function call.

## Show preprocessor expansion

Run:
```sh
gcc -E Task04/macro_demo.c -o Task04/macro_expanded.i
```
Then search the generated file for the expanded `printf` expressions. Standard headers make the output long, so search for `SQUARE` or the relevant `printf` line; macro names themselves are normally replaced before the output is written.

## Inline-function alternative and complexity

`static inline` functions provide type checking and evaluate arguments once. A compiler may inline a call, but `inline` is a request/permission rather than a guarantee. A function call can have a small call/return overhead when not inlined; an expanded macro has no call overhead. Both perform O(1) work for these simple calculations.

A macro's replacement code is expanded at every use, so if a large macro is used `k` times, generated code can grow roughly with `k` times the expansion size. A function may share one implementation when not inlined; an optimizer may also inline it and duplicate code. Runtime complexity is O(1) per call/use, and the overall program cost is O(k) for k uses. Small macro expansions may be optimized to the same machine instructions as inline functions.

## Safer practice

Prefer ordinary functions or `static inline` functions for calculations that need type checking or might receive expressions with side effects. Use macros for compile-time configuration and simple textual tasks where their limitations are understood.
