#include "vector.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

double vec_dot_product(const struct Vector *a, const struct Vector *b)
{
    assert(a->len == b->len);
    double result = 0;
    for (size_t i = 0; i < a->len; i++) {
        result += a->data[i] * b->data[i];
    }
    return result;
}

void vec_cross_product(const struct Vector *a, const struct Vector *b, struct Vector *restrict out)
{
    assert(a->len == 3 && b->len == 3 && out->len == 3);
    out->data[0] = a->data[1] * b->data[2] - b->data[1] * a->data[2];
    out->data[1] = a->data[2] * b->data[0] - b->data[2] * a->data[0];
    out->data[2] = a->data[0] * b->data[1] - b->data[0] * a->data[1];
}

void vec_cross_product_assign(struct Vector *a, const struct Vector *b)
{
    assert(a->len == 3 && b->len == 3);
    double result[3];
    result[0] = a->data[1] * b->data[2] - b->data[1] * a->data[2];
    result[1] = a->data[2] * b->data[0] - b->data[2] * a->data[0];
    result[2] = a->data[0] * b->data[1] - b->data[0] * a->data[1];

    memcpy(a->data, result, sizeof(result));
}

void vec_print(const struct Vector *vec)
{
    fputs("[ ", stdout);
    for (size_t i = 0; i < vec->len; i++) {
        printf("%f, ", vec->data[i]);
    }
    fputs("]\n", stdout);
}
