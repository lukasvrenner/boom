#include "vector.h"
#include "matrix.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

static size_t boom_vec_len(const struct BoomMatrix *a)
{
    return a->rows * a->cols;
}

int boom_vec_proj(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *out)
{

    if (boom_vec_len(b) != boom_vec_len(out))
        return -1;

    double a_dot_b = boom_vec_dot_product(a, b);
    double b_dot_b = boom_vec_dot_product(b, b);
    double scalar = a_dot_b / b_dot_b;

    assert(boom_mat_mul_scalar(b, scalar, out) != -1);
    return 0;
}

int boom_vec_orth(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *out)
{
    if (boom_vec_proj(a, b, out) == -1)
        return -1;
    assert(boom_mat_sub(a, out, out) != -1);
    return 0;
}

double boom_vec_dot_product(const struct BoomMatrix *a, const struct BoomMatrix *b)
{
    size_t shortest_len;
    if (boom_vec_len(a) < boom_vec_len(b)) {
        shortest_len = boom_vec_len(a);
    } else {
        shortest_len = boom_vec_len(b);
    }

    double result = 0;
    for (size_t i = 0; i < shortest_len; i++) {
        result += a->data[i] * b->data[i];
    }
    return result;
}

int boom_vec_cross_product(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *out)
{
    if (boom_vec_len(a) != 3 || boom_vec_len(b) != 3 || boom_vec_len(out) != 3) {
        return -1;
    }
    double result[3];
    result[0] = a->data[1] * b->data[2] - b->data[1] * a->data[2];
    result[1] = a->data[2] * b->data[0] - b->data[2] * a->data[0];
    result[2] = a->data[0] * b->data[1] - b->data[0] * a->data[1];

    memcpy(out->data, result, sizeof(result));
    return 0;
}

void boom_vec_print(const struct BoomMatrix *vec)
{
    fputs("[ ", stdout);
    for (size_t i = 0; i < vec->rows * vec->cols; i++) {
        printf("%f, ", vec->data[i]);
    }
    fputs("]\n", stdout);
}
