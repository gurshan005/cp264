#include "fibonacci.h"

/**
 * Compute F(n) iteratively.
 * Example sequence: 0, 1, 1, 2, 3, 5, 8, 13, ...
 */
int iterative_fibonacci(int n) {
    if (n < 2) {
        return n;  // F(0)=0, F(1)=1
    }

    int fib0 = 0;  // F(0)
    int fib1 = 1;  // F(1)
    int fibN;

    for(int i = 2; i <= n; i++) {
        fibN = fib0 + fib1; // Compute F(i) = F(i-1) + F(i-2)
        fib0 = fib1;        // Move the window
        fib1 = fibN;
    }

    return fib1;  // This is F(n)
}

/**
 * Compute F(n) recursively.
 */
int recursive_fibonacci(int n) {
    // Base cases
    if (n < 2) {
        return n;  // F(0)=0, F(1)=1
    }
    // Recursive definition
    return recursive_fibonacci(n - 1) + recursive_fibonacci(n - 2);
}

/**
 * Compute F(n) using dynamic programming (bottom-up) 
 * with an external array f[] of size n+1, initialized to -1 by the caller.
 * The function will fill up f[0] through f[n].
 */
int dpbu_fibonacci(int *f, int n) {
    // Base cases
    f[0] = 0;
    if (n > 0) {
        f[1] = 1;
    }

    // Fill the array in a bottom-up manner
    for(int i = 2; i <= n; i++) {
        f[i] = f[i - 2] + f[i - 1];
    }

    return f[n];
}

/**
 * Compute F(n) using dynamic programming (top-down) 
 * with an external array f[] of size n+1, initialized to -1 by the caller.
 * Uses recursion (memoization).
 */
int dptd_fibonacci(int *f, int n) {
    // If the value is already computed, just return it
    if (f[n] != -1) {
        return f[n];
    }

    // Base cases
    if (n == 0) {
        f[n] = 0;
        return 0;
    } else if (n == 1) {
        f[n] = 1;
        return 1;
    }

    // Otherwise, compute the two subproblems if needed
    int fibNm1 = dptd_fibonacci(f, n - 1);
    int fibNm2 = dptd_fibonacci(f, n - 2);

    // Store the result in f[n] and return
    f[n] = fibNm1 + fibNm2;
    return f[n];
}
