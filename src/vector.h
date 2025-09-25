#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdio.h>

#include "matrix.h"

/**
 * BOOM represents vectors as "unraveled" matrices.
 * An nxm matrix is therefore treated as a vector with length n * m.
 *
 * This has the effect that vectors can be either column or row vectors
 * and vector operations work the same regardless.
 */

/**
 * Returns the dot-product of `a` and `b`.
 */
double boom_vec_dot(const struct BoomMatrix *a, const struct BoomMatrix *b);

/**
 * Returns `a` dot `a`. This might be more efficient than `boom_vec_dot(a, a)`
 * because it doesn't check any bounds.
 *
 * TODO: verify performance improvement.
 */
double boom_vec_sqr(const struct BoomMatrix *a);

/**
 * Calculates the projection of `a` onto `b`, storing the result in `out`.
 * Returns `-1` if `b` and `out` don't have the same number of dimensions, else returns `0`.
 */
enum BoomErr boom_vec_proj(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *out);

/**
 * Calculates the component of `a` onto `b`
 */
double boom_vec_comp(const struct BoomMatrix *a, const struct BoomMatrix *b);

enum BoomErr boom_vec_orth(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *out);

/**
 * Returns the magnitude (Euclidean norm) of `a`.
 */
double boom_vec_mag(const struct BoomMatrix *a);

/*
 * Returns the cosine of the angle between `a` and `b`.
 */
double boom_vec_cos(const struct BoomMatrix *a, const struct BoomMatrix *b);

enum BoomErr boom_vec_cross(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *out);

/**
 * Computes the normalized version of `a`, storing the result in `out`.
 *
 * Returns `-2` if `a` is the zero-vector.
 * Returns `-1` if `a` and `out don't have the same length.
 * Else returns 0.
 */
enum BoomErr boom_vec_normalize(const struct BoomMatrix *a, struct BoomMatrix *out);

/**
 * Returns `true` if `a` equals `b`.
 * Else returns false.
 */
bool boom_vec_eq(const struct BoomMatrix *a, const struct BoomMatrix *b);

/**
 * Adds `a` and `b`, storing the result in `out`.
 *
 * `out` may point to the same vector as `a` or `b`.
 *
 * Returns `-1` and does not perform the multiplication if `out` has incorrect dimensions.
 * Else returns `1`.
 */
enum BoomErr boom_vec_add(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *out);

/**
 * Subtracts `b` from `a`, storing the result in `out`.
 *
 * `out` may point to the same vector as `a` or `b`.
 *
 * Returns `-1` if there are misvecched dimensions. Else returns `0`.
 */
enum BoomErr boom_vec_sub(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *out);

/**
 * Multiplies `a` and `scalar`, storing the result in `out`.
 *
 * `out` may point to the same vector as `a` or `b`.
 *
 * Returns `-1` if there are misvecched dimensions. Else returns `0`.
 */
enum BoomErr boom_vec_mul_scalar(const struct BoomMatrix *a, double scalar, struct BoomMatrix *out);

void boom_vec_print(const struct BoomMatrix *a, FILE *stream);

/**
 * Returns `true` if `a` and `b` are orthogonal. Else returns false.
 */
bool boom_vec_are_orth(const struct BoomMatrix *a, const struct BoomMatrix *b);

#endif /* VECTOR_H */
