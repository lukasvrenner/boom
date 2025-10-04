#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "matrix.h"
#include "vector.h"

double boom_vec_dot(const struct BoomMatrix *a, const struct BoomMatrix *b)
{
    size_t shortest = a->rows < b->rows ? a->rows : b->rows;
    double result = 0;

    for (size_t i = 0; i < shortest; i++) {
        result += a->data[i] * b->data[i];
    }
    return result;
}

double boom_vec_sqr(const struct BoomMatrix *a)
{
    double result = 0;

    for (size_t i = 0; i < a->rows; i++) {
        result += a->data[i] * a->data[i];
    }
    return result;
}

enum BoomErr boom_vec_proj(const struct BoomMatrix *a, const struct BoomMatrix *b,
                           struct BoomMatrix *out)
{
    double a_dot_b = boom_vec_dot(a, b);
    double b_dot_b = boom_vec_dot(b, b);
    double scalar = a_dot_b / b_dot_b;

    return boom_mul_scalar(b, scalar, out);
}

double boom_vec_comp(const struct BoomMatrix *a, const struct BoomMatrix *b)
{
    return boom_vec_dot(a, b) / boom_vec_mag(b);
}

enum BoomErr boom_vec_orth(const struct BoomMatrix *a, const struct BoomMatrix *b,
                           struct BoomMatrix *out)
{
    enum BoomErr err = boom_vec_proj(a, b, out);

    if (err != BOOM_ERR_NONE) {
        return err;
    }
    return boom_sub(a, out, out);
}

double boom_vec_mag(const struct BoomMatrix *a)
{
    return sqrt(boom_vec_sqr(a));
}

double boom_vec_cos(const struct BoomMatrix *a, const struct BoomMatrix *b)
{
    return boom_vec_dot(a, b) / sqrt(boom_vec_sqr(a) * boom_vec_sqr(b));
}

enum BoomErr boom_vec_cross(const struct BoomMatrix *a, const struct BoomMatrix *b,
                            struct BoomMatrix *out)
{
    if (a->rows != 3 || b->rows != 3 || out->rows != 3) {
        return BOOM_ERR_BAD_DIM;
    }
    double result[3];

    result[0] = a->data[1] * b->data[2] - b->data[1] * a->data[2];
    result[1] = a->data[2] * b->data[0] - b->data[2] * a->data[0];
    result[2] = a->data[0] * b->data[1] - b->data[0] * a->data[1];

    memcpy(out->data, result, sizeof(result));
    return BOOM_ERR_NONE;
}

enum BoomErr boom_vec_normalize(const struct BoomMatrix *a, struct BoomMatrix *out)
{
    double mag = boom_vec_mag(a);

    if (mag == 0)
        return BOOM_ERR_DIV_ZERO;
    return boom_mul_scalar(a, 1 / mag, out);
}

bool boom_vec_are_orth(const struct BoomMatrix *a, const struct BoomMatrix *b)
{
    return boom_vec_dot(a, b) == 0;
}
