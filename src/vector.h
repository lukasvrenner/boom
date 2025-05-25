#ifndef VECTOR_H
#define VECTOR_H

#include "matrix.h"

#include <stddef.h>

/**
 * Calculates the projection of `a` onto `b`, storing the result in `out`.
 * Returns `-1` if `b` and `out` don't have the same number of dimensions, else returns `0`.
 */
int boom_vec_proj(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *out);

int boom_vec_orth(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *out);

/**
 * Returns the dot-product of `a` and `b`.
 */
double boom_vec_dot_product(const struct BoomMatrix *a, const struct BoomMatrix *b);

int boom_vec_cross_product(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *restrict out);

void boom_vec_print(const struct BoomMatrix *vec);

#endif /* VECTOR_H */
