#include "vector.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

double vec_dot_product(const struct Vector *a, const struct Vector *b)
{
    assert(a->len == b->len);
    double result = 0;
    for (size_t i = 0; i < a->len; i++) {
        result += a->data[i] * b->data[i];
    }
    return result;
}

void vec_print(const struct Vector *vec)
{
    fputs("[ ", stdout);
    for (size_t i = 0; i < vec->len; i++) {
        printf("%f, ", vec->data[i]);
    }
    fputs("]\n", stdout);
}
