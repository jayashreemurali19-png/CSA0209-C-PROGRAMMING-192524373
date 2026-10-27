# CSA02-<RegisterNumber>-Assignment1

**Student name:** `<Your Name>`  
**Register number:** `<Your Register Number>`  
**Compiler:** GCC (record the exact output of `gcc --version` on your machine)  
**Build standard:** C11

## Compile
From the repository root:

```sh
gcc --version
gcc -std=c11 -Wall -Wextra -Wpedantic Task01/billing.c -o Task01/billing
gcc -std=c11 -Wall -Wextra -Wpedantic Task02/measure_types.c -o Task02/measure_types
gcc -std=c11 -Wall -Wextra -Wpedantic Task03/alternative_slabs.c -o Task03/alternative_slabs
gcc -std=c11 -Wall -Wextra -Wpedantic Task04/smart_meter.c -o Task04/smart_meter
```

## Run
```sh
cd Task01
./billing
python3 test_billing.py
cd ../Task02
./measure_types
cd ../Task03
./alternative_slabs
cd ../Task04
./smart_meter
```

For Task 4, keep `tariff.conf` in the same working directory as `smart_meter`.

## Task summaries
- **Task 1:** Slab billing in integer paise, validation and rollover test cases.
- **Task 2:** Measured C type sizes/ranges and compared float/double with integer paise.
- **Task 3:** Design decision, complexity analysis and configuration-file alternative in `Task03/design_notes.md`.
- **Task 4:** Prototype using watt-hour totals and a configuration-based off-peak tariff with a 20% peak surcharge.

## Submission notes
Replace placeholders in this README and the report cover page. Run the code with your compiler, retain your actual outputs/screenshots, and commit each task separately. The screenshots in this starter package show the recorded execution in the build environment; regenerate them on your own system before submission if compiler details differ.
