# Task 1 — Header Files and Conditional Compilation

## Program structure
- `billing.h` contains tariff constants, the `Bill` structure and function prototypes.
- `main.c` contains function definitions and `main()`, which reads input, calculates the bill and prints it.
- `#ifndef BILLING_H / #define BILLING_H / #endif` is an include guard. It prevents declarations being processed more than once in one translation unit.
- `#include "billing.h"` searches the local project directory first; `#include <stdio.h>` searches implementation/system include paths.
- Compile normally with `gcc -std=c11 -Wall -Wextra main.c -o billing`. Compile with debug output using `gcc -std=c11 -Wall -Wextra -DDEBUG main.c -o billing_debug`.

## Alternative: runtime debug flag
A runtime `if (debug)` checks a condition whenever that code path is reached. `#ifdef DEBUG` removes debug statements during preprocessing unless `-DDEBUG` is supplied, so the non-debug executable contains no debug-print calls from those blocks. Both approaches have O(1) time per check; the runtime flag has a small constant test cost and typically retains debug-related code in the executable, while conditional compilation excludes it in release builds. Actual binary-size differences depend on compiler and optimization settings.
