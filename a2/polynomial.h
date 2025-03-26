#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

/**
 * Compute and return the value of the (n-1)-th degree polynomial
 * p(x) = p[0]*x^{n-1} + p[1]*x^{n-2} + ... + p[n-2]*x + p[n-1]
 * using Horner's method.
 *
 * @param p   Pointer to array of polynomial coefficients
 * @param n   Number of coefficients (the polynomial is degree n-1)
 * @param x   The value at which to evaluate the polynomial
 * @return    p(x), evaluated via Horner's algorithm
 */
float horner(float *p, int n, float x);

/**
 * Compute the derivative coefficients of an (n-1)-th degree polynomial
 * p(x) = p[0]*x^{n-1} + p[1]*x^{n-2} + ... + p[n-2]*x + p[n-1].
 *
 * p'(x) = (n-1)*p[0]*x^{n-2} + (n-2)*p[1]*x^{n-3} + ... + p[n-2]*x^0.
 *
 * The derivative polynomial will have n-1 coefficients.
 *
 * @param p   Pointer to input polynomial coefficients
 * @param d   Pointer to output derivative polynomial coefficients
 * @param n   Number of input coefficients
 */
void derivative(float *p, float *d, int n);

/**
 * Approximate a real root of p(x) using Newton's method.
 * Use tolerance 1e-6 (0.000001) and maximum 100 iterations.
 *
 * Newton's iteration: x_{k+1} = x_k - p(x_k)/p'(x_k).
 *
 * If p'(x_k) == 0 at any step, or if it fails to converge, return the latest x.
 *
 * @param p   Pointer to coefficient array of polynomial p(x)
 * @param n   Number of coefficients (polynomial is degree n-1)
 * @param x0  Starting point for the iteration
 * @return    The approximate root (or x0 if it fails to converge)
 */
float newton(float *p, int n, float x0);

#endif
