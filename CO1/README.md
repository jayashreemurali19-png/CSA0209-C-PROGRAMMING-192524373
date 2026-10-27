# CSA02 Assignment 1 — Grama Jyothi Rural Electricity Co-operative

**Student name:** REPLACE WITH YOUR NAME  
**Register number:** REPLACE WITH YOUR REGISTER NUMBER  
**Repository name:** `CSA02-<RegisterNumber>-Assignment1`  
**Compiler:** GCC (record your installed version using `gcc --version`)  
**Submission date:** 27-10-2026

> Before submission, replace the placeholders, run every program on your own computer, capture your own execution screenshots, and commit each task separately. Do not claim a screenshot was captured on your computer if it was not.

## Folder structure
- `Task01/analysis.md` — problem analysis and string-reading alternative.
- `Task02/` — meter rollover program, type/range discussion, float demonstration.
- `Task03/` — slab billing program and constant comparison.
- `Task04/` — macro examples, inline-function alternative and preprocessor evidence.
- Each task has its own `screenshots/` directory for execution evidence.

## Compile and run
Open a terminal in the repository root. Example commands (GCC):
```sh
gcc --version
gcc -std=c11 -Wall -Wextra -Wpedantic Task02/meter_rollover.c -o Task02/meter_rollover
./Task02/meter_rollover
gcc -std=c11 -Wall -Wextra -Wpedantic Task03/slab_billing.c -o Task03/slab_billing
./Task03/slab_billing
gcc -std=c11 -Wall -Wextra -Wpedantic Task04/macro_demo.c -o Task04/macro_demo
./Task04/macro_demo
gcc -std=c11 -Wall -Wextra -Wpedantic Task04/inline_demo.c -o Task04/inline_demo
./Task04/inline_demo
gcc -E Task04/macro_demo.c -o Task04/macro_expanded.i
```
On Windows PowerShell, run the executable as `.\Task02\meter_rollover.exe` (adjust the path for each task).

## Task summaries
- **Task 1:** Identifies input, output, constants, validation rules, assumptions and complexity of text vs integer readings.
- **Task 2:** Uses unsigned 16-bit-style arithmetic for meter rollover and integer paise for exact money.
- **Task 3:** Centralizes tariff values as macros and calculates slab charges in paise.
- **Task 4:** Demonstrates safe macro parentheses, macro pitfalls, preprocessing, and static inline alternatives.

## Suggested progressive GitHub commits
Make these commits separately after adding each task:
1. `Add Task 1 billing problem analysis`
2. `Add Task 2 data types and meter rollover program`
3. `Add Task 3 tariff constants and slab billing program`
4. `Add Task 4 safe macros and inline function comparison`
5. `Add README and verified execution evidence`

## GitHub submission checklist
- [ ] Replace student placeholders.
- [ ] Run every C program locally and verify output.
- [ ] Save your own terminal screenshots in the relevant `screenshots/` folder.
- [ ] Add your report's GitHub repository URL to the cover page.
- [ ] Push progressive commits to GitHub.
- [ ] Share the repository with faculty (public or private with faculty added as collaborator).
- [ ] Test that the faculty can open the repository.
