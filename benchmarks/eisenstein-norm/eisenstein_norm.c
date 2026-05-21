/* Eisenstein norm benchmark — C.
 *
 * Eisenstein norm: |a + bω|² = a² + ab + b²
 * Computes 1,000,000 norms for pairs (a,b) cycling through 0..999.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define ITERS 1000000
#define RANGE 1000

static inline long long eisenstein_norm(int a, int b) {
    long long la = (long long)a;
    long long lb = (long long)b;
    return la * la + la * lb + lb * lb;
}

int main(void) {
    /* Generate input pairs */
    int *a_arr = malloc(ITERS * sizeof(int));
    int *b_arr = malloc(ITERS * sizeof(int));
    if (!a_arr || !b_arr) {
        fprintf(stderr, "malloc failed\n");
        return 1;
    }

    for (int i = 0; i < ITERS; i++) {
        a_arr[i] = i % RANGE;
        b_arr[i] = (i / RANGE) % RANGE;
    }

    /* Verify known values */
    assert(eisenstein_norm(0, 0) == 0);
    assert(eisenstein_norm(1, 0) == 1);
    assert(eisenstein_norm(1, 1) == 3);
    assert(eisenstein_norm(3, 5) == 49);
    assert(eisenstein_norm(7, 3) == 79);

    /* Benchmark */
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    long long total = 0;
    for (int i = 0; i < ITERS; i++) {
        total += eisenstein_norm(a_arr[i], b_arr[i]);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    double throughput = ITERS / elapsed;

    printf("C Eisenstein Norm Benchmark\n");
    printf("============================\n");
    printf("Iterations:  %d\n", ITERS);
    printf("Time:        %.4fs\n", elapsed);
    printf("Throughput:  %.0f ops/sec\n", throughput);
    printf("Checksum:    %lld\n", total);
    printf("\n");

    free(a_arr);
    free(b_arr);
    return 0;
}
