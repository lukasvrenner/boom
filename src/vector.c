#include "vector.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

double vec_dot_product(const struct VectorSlice *a, const struct VectorSlice *b)
{
    assert(a->len == b->len);
    double result = 0;
    for (ptrdiff_t i = 0; i < a->len; i++) {
        result += a->data[i * a->stride] * b->data[i * b->stride];
    }
    return result;
}

void vec_print(const struct VectorSlice *vec)
{
    fputs("[ ", stdout);
    for (ptrdiff_t i = 0; i < vec->len; i++) {
        printf("%f, ", vec->data[i * vec->stride]);
    }
    fputs("]\n", stdout);
}
