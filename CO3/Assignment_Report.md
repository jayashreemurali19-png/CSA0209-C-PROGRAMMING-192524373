# CSA02 Assignment 1 — Grama Jyothi Rural Electricity Co-operative

**Student:** Parthiban M  
**Register number:** 192524230  
**Course:** CSA02  
**Submission date:** 27 October 2026  
**GitHub repository:** `CSA02-192524230-Assignment1` (insert the actual repository URL after creating it)

## Design decisions
1. Use `uint16_t` for a 16-bit meter reading and `uint32_t` for units consumed. The rollover calculation widens values before subtraction and uses a modulus of 65536.
2. Use `int64_t` for money in paise. The tariff rates are whole paise per unit, so multiplication and addition are exact within the chosen range.
3. Keep tariff constants in `billing.h` so revisions occur in one place.
4. Use include guards to prevent duplicate header declarations.
5. Use `#ifdef DEBUG` to include intermediate diagnostics only in a debug build.
6. Check `scanf`'s return value and validate the range before converting the input to a 16-bit reading.

## Tariff formula
Let `u` be units consumed. Energy charge in paise is:
- `0` when `u <= 100`;
- `(u - 100) * 225` when `100 < u <= 200`;
- `100 * 225 + (u - 200) * 450` when `u > 200`.

Total bill = fixed charge + energy charge. Fixed charge is set to Rs 5.00 for this demonstration because the assignment does not specify a fixed-charge value.

## Validation cases
- Normal reading: previous 120, current 250 → 130 units; energy charge Rs 67.50; total Rs 72.50.
- Rollover: previous 65535, current 0 → 1 unit; energy charge Rs 0.00; total Rs 5.00.
- Invalid input: `abc` is rejected.
- Debug build: `-DDEBUG` prints intermediate unit and slab values to standard error.

## Task 1 — Header files and conditional compilation
The header stores tariff constants, a `Bill` structure and function prototypes. Include guards prevent repeated processing. Quoted includes are appropriate for project headers; angle brackets are used for standard headers. A runtime debug variable incurs a condition test each time the check is reached; `#ifdef DEBUG` removes the debug blocks at preprocessing time in a non-debug build.

## Task 2 — Input/output and format specifiers
The program uses `%u` for an `unsigned int` temporary, checks whether `scanf` returns one successful conversion, and validates the 0–65535 range. Fixed-width integer values are printed using macros from `<inttypes.h>`. Currency is printed from paise with two digits after the decimal point. `fgets` plus `strtol` can provide line-level recovery; processing a line of length L is O(L) with O(B) buffer space for capacity B.

## Task 3 — Conversions and precision
Integer division truncates (`5 / 2` gives 2). Casting a floating-point result to an integer truncates rather than rounds. Casting a value outside the target signed integer range is not portable. The chosen billing rule avoids fractional-paise calculations by representing the energy rate as integer paise. A floating-point comparison should be measured by generating the same bills and comparing the total against the integer-paise result for increasing n; the precise observed error depends on the inputs and floating-point evaluation order.

## Task 4 — Compilation process
`gcc -E` expands includes and macros into preprocessed C, `gcc -S` emits assembly, `gcc -c` creates an object file, and linking creates the executable. Syntax/type diagnostics are compile-time errors; unresolved external symbols are link-time errors; rejected user input is handled at run time. The project is compiled with `-Wall -Wextra` and warnings should be resolved before submission.

## Smart-meter design challenge
For 15-minute smart-meter readings and time-of-day tariffs, retain the principles of integer money, centralised tariff configuration, validation and modular functions, but modify the data model. Store timestamped interval readings and tariff periods, calculate each interval under the applicable rate, and sum integer paise. For a district-scale stream, use a database or file-backed batch pipeline rather than keeping every reading in memory. Add tests for missing/duplicate/out-of-order intervals, clock/time-zone changes, meter rollover and tariff-version changes. The original single two-reading design should therefore be modified, not retained unchanged.

## Final pre-submission checklist
- [ ] Execute each task locally and inspect the output.
- [ ] Capture terminal screenshots of compile/run commands and results.
- [ ] Confirm the GCC version on the submission machine.
- [ ] Create the required GitHub repository and commit each task progressively.
- [ ] Add the faculty as a collaborator if private.
- [ ] Add the actual GitHub URL to this report and the repository README.
