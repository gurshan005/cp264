#include "polynomial.h"

/* Simple absolute value function to avoid <math.h>. */
static float my_abs(float x) {
    return (x < 0) ? -x : x;
}

/**
 * Horner's method for polynomial evaluation.
 * p(x) = p[0]*x^{n-1} + p[1]*x^{n-2} + ... + p[n-2]*x + p[n-1].
 */
float horner(float *p, int n, float x) {
    // Horner form: result = (((p[0]*x + p[1]) * x + p[2]) * x + ... ) 
    float result = p[0];
    for (int i = 1; i < n; i++) {
        result = result * x + p[i];
    }
    return result;
}

/**
 * Derivative of polynomial p(x):
 * p'(x) = (n-1)*p[0]*x^{n-2} + (n-2)*p[1]*x^{n-3} + ... + 1*p[n-2].
 */
void derivative(float *p, float *d, int n) {
    // The derivative polynomial has n-1 coefficients.
    // d[i] = (n-1-i)*p[i], for i from 0 to (n-2).
    for (int i = 0; i < n - 1; i++) {
        d[i] = (float)(n - 1 - i) * p[i];
    }
}

/**
 * Newton's method to find real root of p(x).
 * x_{k+1} = x_k - p(x_k)/p'(x_k).
 */
float newton(float *p, int n, float x0) {
    float tol = 1e-6;
    int max_iter = 100;

    // Compute derivative polynomial once (n-1 coefficients)
    float d[64];  // Assume n <= 64 or adjust as needed
    derivative(p, d, n);

    float xk = x0;
    for (int i = 0; i < max_iter; i++) {
        float fx = horner(p, n, xk);
        float fpx = horner(d, n - 1, xk); // p'(xk)

        // If derivative is 0 or extremely close to 0, we can't update
        if (my_abs(fpx) < tol) {
            return xk;
        }

        float x_next = xk - fx / fpx;

        // Check convergence
        if (my_abs(x_next - xk) < tol) {
            return x_next;
        }

        xk = x_next;
    }

    // If we get here, it didn't converge within 100 iterations
    // Return whatever we have as best guess
    return xk;
}
