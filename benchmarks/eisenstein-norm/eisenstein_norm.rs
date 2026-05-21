/* Eisenstein norm benchmark — Rust.
 *
 * Eisenstein norm: |a + bω|² = a² + ab + b²
 * Computes 1,000,000 norms for pairs (a,b) cycling through 0..999.
 */

use std::time::Instant;

const ITERS: u64 = 1_000_000;
const RANGE: i64 = 1000;

#[inline(always)]
fn eisenstein_norm(a: i64, b: i64) -> i64 {
    a * a + a * b + b * b
}

fn main() {
    // Generate input pairs
    let mut a_arr = Vec::with_capacity(ITERS as usize);
    let mut b_arr = Vec::with_capacity(ITERS as usize);
    for i in 0..ITERS {
        a_arr.push((i % RANGE as u64) as i64);
        b_arr.push(((i / RANGE as u64) % RANGE as u64) as i64);
    }

    // Verify known values
    assert_eq!(eisenstein_norm(0, 0), 0);
    assert_eq!(eisenstein_norm(1, 0), 1);
    assert_eq!(eisenstein_norm(1, 1), 3);
    assert_eq!(eisenstein_norm(3, 5), 49);
    assert_eq!(eisenstein_norm(7, 3), 79);

    // Benchmark
    let start = Instant::now();
    let mut total: i64 = 0;
    for i in 0..ITERS as usize {
        total += eisenstein_norm(a_arr[i], b_arr[i]);
    }
    let elapsed = start.elapsed();
    let elapsed_s = elapsed.as_secs_f64();
    let throughput = ITERS as f64 / elapsed_s;

    println!("Rust Eisenstein Norm Benchmark");
    println!("================================");
    println!("Iterations:  {}", ITERS);
    println!("Time:        {:.4}s", elapsed_s);
    println!("Throughput:  {:.0} ops/sec", throughput);
    println!("Checksum:    {}", total);
    println!();
}
