#ifndef MATRIX_H
#define MATRIX_H

/**
 * Compute and return the norm of vector v, i.e., 
 * the square root of the sum of the squares of its elements.
 *
 * @param v - pointer to the first element of the vector array
 * @param n - the length of vector v
 * @return   the norm of vector v
 */
float norm(float *v, int n);

/**
 * Compute and return the dot product of vectors v1[n] and v2[n],
 * i.e., sum of products of corresponding elements.
 *
 * @param v1 - pointer to the first element of the first vector array
 * @param v2 - pointer to the first element of the second vector array
 * @param n  - the length of both vectors
 * @return   the dot product of v1 and v2
 */
float dot_product(float *v1, float *v2, int n);

/**
 * Compute the multiplication of an n-by-n matrix m by an n-element vector v.
 * The result is placed in vout, which also has length n.
 *
 * @param m    - pointer to the first element of the n-by-n matrix
 * @param v    - pointer to the vector
 * @param vout - pointer to the output vector
 * @param n    - the dimension of the matrix and vector
 */
void matrix_multiply_vector(float *m, float *v, float *vout, int n);

/**
 * Compute the multiplication of two n-by-n matrices m1 and m2.
 * The result is stored in m3, which is also n-by-n.
 *
 * @param m1 - pointer to the first element of the first matrix
 * @param m2 - pointer to the first element of the second matrix
 * @param m3 - pointer to the output matrix
 * @param n  - the row/column dimension for the square matrices
 */
void matrix_multiply_matrix(float *m1, float *m2, float *m3, int n);

#endif
