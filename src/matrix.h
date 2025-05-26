#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

/**
 * An arbitrarily-sized row-major matrix.
 */
struct BoomMatrix {
    size_t rows, cols;
    /**
     * The raw data of the matrix. The length must equal `rows * cols`.
     */
    double data[];
};

/**
 * Multiplies `a` and `b`, storing the result in `out`.
 *
 * `out` may not point to the same matrix as `a` or `b`.
 *
 * Returns `-1` if there are mismatched dimensions. Else returns `0`.
 */
int boom_mat_mul(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *restrict out);

/**
 * Prints `matrix` to `stream`.
 */
void boom_mat_print(const struct BoomMatrix *a, FILE *stream);

/**
 * Returns `true` if `a` equals `b`.
 * This is different from `boom_vec_eq` because here the matrix is not unrolled into a vector.
*/
bool boom_mat_eq(const struct BoomMatrix *a, const struct BoomMatrix *b);

/**
 * Sets `matrix` to the identity matrix.
 */
void boom_mat_set_ident(struct BoomMatrix *a);

#endif /* MATRIX_H */
