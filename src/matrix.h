#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "vector.h"

/*
 * An arbitrarily-sized row-major matrix.
 */
struct Matrix {
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
 */
void mat_mul(const struct Matrix *a, const struct Matrix *b, struct Matrix *restrict out);

/**
 * Multiplies `a * b`, storing the result in `out`.
 *
 * `out` may not point to the same vector as `b`.
 *
 * Returns `-1` and does not perform the multiplication if `out` has incorrect dimensions.
 * Otherwise, returns `1`.
 */
void mat_mul_vec(const struct Matrix *a, const struct Vector *b, struct Vector *restrict out);

/**
 * Prints `matrix` to `stream`.
 */
void mat_print(const struct Matrix *a, FILE *stream);

/**
 * Sets `matrix` to the identity matrix.
 */
void mat_set_ident(struct Matrix *a);

/**
 * Returns `true` if `a` equals `b`.
 * Otherwise, returns false.
 */
bool mat_eq(const struct Matrix *a, const struct Matrix *b);

/**
 * Adds `a` and `b`, storing the result in `out`.
 *
 * `out` may point to the same matrix as `a` or `b`.
 *
 * Returns `-1` and does not perform the multiplication if `out` has incorrect dimensions.
 * Otherwise, returns `1`.
 */
void mat_add(const struct Matrix *a, const struct Matrix *b, struct Matrix *out);

/**
 * Subtracts `b` from `a`, storing the result in `out`.
 *
 * `out` may point to the same matrix as `a` or `b`.
 *
 * Returns `-1` and does not perform the multiplication if `out` has incorrect dimensions.
 * Otherwise, returns `1`.
 */
void mat_sub(const struct Matrix *a, const struct Matrix *b, struct Matrix *out);

/**
 * Multiplies `a` and `scalar`, storing the result in `out`.
 *
 * `out` may point to the same matrix as `a` or `b`.
 *
 * Returns `-1` and does not perform the multiplication if `out` has incorrect dimensions.
 * Otherwise, returns `1`.
 */
void mat_mul_scalar(const struct Matrix *a, double scalar, struct Matrix *out);

double mat_det(const struct Matrix *a);

#endif /* MATRIX_H */
