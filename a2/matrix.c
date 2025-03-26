#include "matrix.h"
#include <math.h>   // for sqrt()

float norm(float *v, int n) {
    float sum = 0.0f;
    for (int i = 0; i < n; i++) {
        sum += v[i] * v[i];
    }
    return sqrt(sum);
}

float dot_product(float *v1, float *v2, int n) {
    float sum = 0.0f;
    for (int i = 0; i < n; i++) {
        sum += v1[i] * v2[i];
    }
    return sum;
}

void matrix_multiply_vector(float *m, float *v, float *vout, int n) {
    // m is an n-by-n matrix in row-major order:
    // element (i, j) is at m[i*n + j].
    for (int i = 0; i < n; i++) {
        float sum = 0.0f;
        for (int j = 0; j < n; j++) {
            sum += m[i * n + j] * v[j];
        }
        vout[i] = sum;
    }
}

void matrix_multiply_matrix(float *m1, float *m2, float *m3, int n) {
    // Each of m1, m2, m3 is n-by-n in row-major order.
    // m3[i*n + j] = sum of (m1[i*n + k] * m2[k*n + j]) for k=0..n-1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            float sum = 0.0f;
            for (int k = 0; k < n; k++) {
                sum += m1[i * n + k] * m2[k * n + j];
            }
            m3[i * n + j] = sum;
        }
    }
}
