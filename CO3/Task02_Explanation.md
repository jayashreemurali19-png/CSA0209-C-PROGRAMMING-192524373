# Task 2 — Input, Output and Validation

The program uses `%u` to read into `unsigned int`, checks that `scanf` returns 1, and validates the range before converting to `uint16_t`. The standard fixed-width format macros from `<inttypes.h>` (`PRIu16`, `PRIu32`, `PRId64`) are used for portable printing. `%d` is for `int`, `%u` for `unsigned int`, `%ld` for `long`, `%lld` for `long long`, `%f` for `float` output, `%lf` for `double` with `scanf` (for `printf`, `%f` prints a `double`), `%c` for a character and `%s` for a string. A mismatched format specifier can cause undefined behaviour.

Money is stored as integer paise and printed as rupees plus exactly two digits after the decimal point. Example: 16250 paise prints as `Rs 162.50`.

## Invalid input
Enter `abc` at the first prompt: `scanf` returns 0, and the program reports invalid input. This demo exits instead of retrying; a production program could consume the rest of the line and prompt again.

## Alternative: fgets + conversion
`fgets` reads a bounded line into a buffer, after which `strtol` or `sscanf` converts it. Reading and scanning a line of length L takes O(L) time; buffer storage is O(B), where B is the chosen buffer capacity. Line-based parsing gives clearer recovery because the whole bad line can be discarded. Direct `scanf` is concise, but a failed conversion can leave the offending character in the input stream unless explicitly consumed.
