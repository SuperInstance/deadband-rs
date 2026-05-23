# deadband-rs

Rust library for deadband detection, noise filtering, and constraint-theory math primitives — the numerical backbone of the Cocapn fleet's tolerance system.

## Install

```toml
[dependencies]
deadband = { git = "https://github.com/SuperInstance/deadband-rs" }
```

```bash
cargo build --release
cargo test
```

## Minimal Working Example

```rust
use deadband::div360::div360;
use deadband::eisenstein::snap;
use deadband::bma::berlekamp_massey;

// Exact angle arithmetic — zero floating-point drift
let (q, r) = div360(730);  // (2, 10) — 730° = 2 full rotations + 10°

// Snap to nearest Eisenstein lattice point
let (n, m, err) = snap(3.7, 2.1);  // nearest point in Z[ω]

// Find shortest LFSR for a binary sequence
let seq = vec![1, 0, 1, 1, 0, 1, 0, 1, 1];
let (poly, len) = berlekamp_massey(&seq);
```

## Key Concept: Deadband Filtering

A deadband filter suppresses changes below a perceptibility threshold:

```
|Δ| ≤ k  →  not perceivable → output stays at last significant value
|Δ| > k  →  perceivable     → output passes through
```

This is thermostat hysteresis, audio noise gating, and constraint tolerance — all the same idea. If the change doesn't matter, don't propagate it. The fleet uses deadband filtering to avoid thrashing on sub-threshold fluctuations in agent scores, clock drift, and constraint violations.

### Modules

| Module | What It Does |
|--------|-------------|
| `div360` | Exact integer ÷360 for angle arithmetic — zero drift across 129,600 integer pairs |
| `eisenstein` | Snap Cartesian points to nearest Eisenstein integer (hexagonal lattice Z[ω]) |
| `bma` | Berlekamp-Massey algorithm over GF(2) — shortest LFSR for binary sequences |
| `hpdf` | Uniform sampling over regular hexagons (rejection method) |
| `fib_spline` | Fibonacci spiral vector search — near-uniform angular coverage in O(√n) |
| `shell` | 2×2 matrix eigendecomposition — classify dynamics (node, saddle, spiral, center) |

### When to Use Which

- **`div360`** — Any angle math. Replaces `f64` modulo with exact integer remainders.
- **`eisenstein`** — Quantization to hexagonal grid. Used by the fleet's coordinate snap.
- **`bma`** — Sequence analysis, anomaly detection in binary streams.
- **`hpdf`** — Monte Carlo sampling in hexagonal domains.
- **`fib_spline`** — Direction search, interpolation over sparse angle grids.
- **`shell`** — Stability analysis of 2D linear systems.

## Features

| Feature | Default | Description |
|---------|---------|-------------|
| `python` | off | Python bindings via PyO3 |
| `simd` | off | SIMD-accelerated filters |

## Running the Demo

```bash
cargo run
```

Runs an interactive test of all modules: /360 arithmetic verification, Eisenstein snap accuracy, Fibonacci spiral coverage, and 2×2 matrix classification.

## Related Repos

- [superinstance-ffi](https://github.com/SuperInstance/superinstance-ffi) — C/WASM bindings exposing these primitives
- [holonomy-consensus](https://github.com/SuperInstance/holonomy-consensus) — Fleet consensus protocol using Eisenstein lattice
- [constraint-theory-core](https://github.com/SuperInstance/constraint-theory-core) — Constraint engine built on these primitives

## License

Apache-2.0
