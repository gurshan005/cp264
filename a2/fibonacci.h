#ifndef FIBONACCI_H
#define FIBONACCI_H

/**
 * Compute and return the nth Fibonacci number F(n) using an iterative algorithm. 
 * This uses a simple loop and tracks two consecutive Fibonacci numbers.
 *
 * @param n - The n for F(n)
 * @return The nth Fibonacci number
 */
int iterative_fibonacci(int n);

/**
 * Compute and return the nth Fibonacci number F(n) using a recursive algorithm. 
 * This directly uses the definition F(n) = F(n-2) + F(n-1).
 *
 * @param n - The n for F(n)
 * @return The nth Fibonacci number
 */
int recursive_fibonacci(int n);

/**
 * Compute and return the nth Fibonacci number F(n) using dynamic programming 
 * bottom-up method with external array f[n+1] of initial value -1 for all elements.
 * Fills up f[] by f[0] = 0, f[1] = 1, f[i] = f[i-2] + f[i-1] for i=2,...,n.
 *
 * @param f - The external array of size n+1 (initialized to -1 by the caller)
 * @param n - The n for F(n)
 * @return The nth Fibonacci number
 */
int dpbu_fibonacci(int *f, int n);

/**
 * Compute and return the nth Fibonacci number F(n) using dynamic programming 
 * top-down method with external array f[n+1] of initial value -1 for all elements.
 * Uses recursion with memoization. Specifically:
 * 1) Returns f[n] if f[n] != -1
 * 2) Else sets f[n] = dptd_fibonacci(f, n-2) + dptd_fibonacci(f, n-1)
 * 3) Then returns f[n].
 *
 * @param f - The external array of size n+1 (initialized to -1 by the caller)
 * @param n - The n for F(n)
 * @return The nth Fibonacci number
 */
int dptd_fibonacci(int *f, int n);

#endif
