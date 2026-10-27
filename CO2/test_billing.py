#!/usr/bin/env python3
"""Automated integration tests for billing.c. Run after compiling billing."""
import subprocess

CASES = [
    ("0 50", 0, "units=50, bill=Rs 50.00"),
    ("0 150", 0, "units=150, bill=Rs 162.50"),
    ("0 250", 0, "units=250, bill=Rs 387.50"),
    ("0 100", 0, "units=100, bill=Rs 50.00"),
    ("0 200", 0, "units=200, bill=Rs 275.00"),
    ("123 123", 0, "units=0, bill=Rs 50.00"),
    ("65535 0", 0, "units=1, bill=Rs 50.00"),
    ("abc 10", 1, "ERROR"),
    ("-1 10", 1, "ERROR"),
    ("500 400", 1, "ERROR"),
]
for data, expected_code, expected_text in CASES:
    p = subprocess.run(["./billing"], input=data + "\n", text=True,
                       stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output = p.stdout + p.stderr
    ok = p.returncode == expected_code and expected_text in output
    print(("PASS" if ok else "FAIL") + f" input={data!r} exit={p.returncode}")
    if not ok:
        print(output)
