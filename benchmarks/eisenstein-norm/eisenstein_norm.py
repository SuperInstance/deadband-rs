#!/usr/bin/env python3
"""Eisenstein norm benchmark — Python/numpy.

Eisenstein norm: |a + bω|² = a² + ab + b²
Computes 1,000,000 norms for pairs (a,b) cycling through 0..999.
"""

import time
import sys

ITERS = 1_000_000
RANGE = 1000

def eisenstein_norm(a, b):
    """Compute a² + ab + b²."""
    return a * a + a * b + b * b

def main():
    # Generate input pairs: (i % RANGE, (i // RANGE) % RANGE) for i in 0..ITERS-1
    # This cycles through all (a,b) combinations in 0..999
    pairs = []
    for i in range(ITERS):
        a = i % RANGE
        b = (i // RANGE) % RANGE
        pairs.append((a, b))

    # Warm up
    _ = eisenstein_norm(3, 5)

    # Benchmark
    start = time.perf_counter()
    total = 0
    for a, b in pairs:
        total += eisenstein_norm(a, b)
    elapsed = time.perf_counter() - start

    throughput = ITERS / elapsed

    # Verify a few known values
    assert eisenstein_norm(0, 0) == 0, "norm(0,0) should be 0"
    assert eisenstein_norm(1, 0) == 1, "norm(1,0) should be 1"
    assert eisenstein_norm(1, 1) == 3, "norm(1,1) should be 3"
    assert eisenstein_norm(3, 5) == 9 + 15 + 25, "norm(3,5) should be 49"
    assert eisenstein_norm(7, 3) == 49 + 21 + 9, "norm(7,3) should be 79"

    print(f"Python Eisenstein Norm Benchmark")
    print(f"=================================")
    print(f"Iterations:  {ITERS:,}")
    print(f"Time:        {elapsed:.4f}s")
    print(f"Throughput:  {throughput:,.0f} ops/sec")
    print(f"Checksum:    {total}")
    print()

if __name__ == "__main__":
    main()
