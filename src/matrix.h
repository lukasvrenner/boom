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

enum BoomErr {

    /**
     * There were no errors.
     */
    BOOM_ERR_NONE,

    /**
     * The dimensions of the given matrices were incompatible.
     */
    BOOM_ERR_BAD_DIM,

    /**
     * A division by zero was attempted.
     */
    BOOM_ERR_DIV_ZERO,

    /**
     * The matrix has no inverse.
     */
    BOOM_ERR_NO_INV,
};

/**
 * Returns a text message describing `err`.
 */
const char *boom_err_str(enum BoomErr err);

struct BoomMatrix *boom_alloc(size_t rows, size_t cols);

enum BoomErr boom_add(const struct BoomMatrix *a, const struct BoomMatrix *b,
                      struct BoomMatrix *out);

enum BoomErr boom_sub(const struct BoomMatrix *a, const struct BoomMatrix *b,
                      struct BoomMatrix *out);

enum BoomErr boom_mul_scalar(const struct BoomMatrix *a, double scalar, struct BoomMatrix *out);

/**
 * Multiplies `a` and `b`, storing the result in `out`.
 *
 * `out` may not point to the same matrix as `a` or `b`.
 *
 * Returns `-1` if there are mismatched dimensions. Else returns `0`.
 */
enum BoomErr boom_mul(const struct BoomMatrix *a, const struct BoomMatrix *b,
                      struct BoomMatrix *restrict out);

/**
 * Prints `matrix` to `stream`.
 */
void boom_print(const struct BoomMatrix *a, FILE *stream);

/**
 * Returns `true` if `a` equals `b`.
 * This is different from `boom_vec_eq` because here the matrix is not unrolled into a vector.
*/
bool boom_eq(const struct BoomMatrix *a, const struct BoomMatrix *b);

/**
 * Sets `matrix` to the identity matrix.
 */
void boom_set_ident(struct BoomMatrix *a);

/**
 * Performs Gauss-Jordan elimanation on the augmented matrix of `a` and `b`.
 */
enum BoomErr boom_gauss(struct BoomMatrix *a, struct BoomMatrix *b);

/**
 * Performs LUP decomposition on `a` in-place.
 * The resulting matrix stored in `a` is both L and U.
 * The permutations are stored in `p`, and the number of swaps in `swaps`.
 */
enum BoomErr boom_lup_decomp(struct BoomMatrix *a, size_t *p, size_t *swaps);

#endif /* MATRIX_H */
