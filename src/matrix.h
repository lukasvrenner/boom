#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "vector.h"

/*
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
 * Returns `-1` if there are mismatched dimensions. Otherwise returns `0`.
 */
int boom_mat_mul(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *restrict out);

/**
 * Prints `matrix` to `stream`.
 */
void boom_mat_print(const struct BoomMatrix *a, FILE *stream);

/**
 * Sets `matrix` to the identity matrix.
 */
void boom_mat_set_ident(struct BoomMatrix *a);

/**
 * Returns `true` if `a` equals `b`.
 * Otherwise returns false.
 */
bool boom_mat_eq(const struct BoomMatrix *a, const struct BoomMatrix *b);

/**
 * Adds `a` and `b`, storing the result in `out`.
 *
 * `out` may point to the same matrix as `a` or `b`.
 *
 * Returns `-1` and does not perform the multiplication if `out` has incorrect dimensions.
 * Otherwise, returns `1`.
 */
int boom_mat_add(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *out);

/**
 * Subtracts `b` from `a`, storing the result in `out`.
 *
 * `out` may point to the same matrix as `a` or `b`.
 *
 * Returns `-1` if there are mismatched dimensions. Otherwise returns `0`.
 */
int boom_mat_sub(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *out);

/**
 * Multiplies `a` and `scalar`, storing the result in `out`.
 *
 * `out` may point to the same matrix as `a` or `b`.
 *
 * Returns `-1` if there are mismatched dimensions. Otherwise returns `0`.
 */
int boom_mat_mul_scalar(const struct BoomMatrix *a, double scalar, struct BoomMatrix *out);

#endif /* MATRIX_H */
