# Eisenstein Norm Cross-Language Benchmark Results

**Date:** 2026-05-21  
**Formula:** `|a + bω|² = a² + ab + b²`  
**Iterations:** 1,000,000 (pairs cycling 0..999)  
**Host:** WSL2 Linux 6.6.87.2 (x86_64)  
**Checksum:** 915,167,250,000 (verified identical across all languages)

## Results

| Language | Time (1M ops) | Throughput (ops/sec) | Binary Size | Compiler | Notes |
|----------|---------------|---------------------|-------------|----------|-------|
| **Rust** | 0.0005s | ~1,963,525,549 | 4.2 MB (375 KB stripped) | rustc -O | Fastest; auto-vectorizes well |
| **C** | 0.0006s | ~1,733,832,446 | 16 KB (14 KB stripped) | gcc -O2 | Tiny binary; near-identical perf |
| **Python** | 0.0923s | ~10,831,186 | 1.5 KB (source) | CPython 3 | ~180x slower; pure Python loop |

## Analysis

- **Rust vs C**: Within ~13% of each other. Both compile to nearly identical machine code for this simple integer arithmetic. Rust's larger binary comes from its standard library linkage.
- **Python**: ~180x slower than compiled languages, expected for a pure Python loop with per-iteration overhead. A numpy vectorized version would close the gap significantly.
- **Correctness**: All three implementations produce the same checksum (915,167,250,000), confirming algorithmic equivalence.

## Existing Implementations Found

- **Rust** (`eisenstein/`): Full `E12` type with norm `a² - ab + b²` (note: minus sign convention for ω = e^(2πi/3)), plus hex disk, Euclidean division, GCD in Z[ω], angle snapping
- **Python** (`eisenstein-embed/`): Quantization/embedding library with Eisenstein integer support

## How to Reproduce

```bash
cd benchmarks/eisenstein-norm

# Python
python3 eisenstein_norm.py

# C
gcc -O2 -o eisenstein_norm_c eisenstein_norm.c
./eisenstein_norm_c

# Rust
rustc -O -o eisenstein_norm_rs eisenstein_norm.rs
./eisenstein_norm_rs
```
