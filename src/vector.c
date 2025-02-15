#include "vector.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

double vec_dot_product(const struct VectorSlice *a, const struct VectorSlice *b)
{
    assert(a->len == b->len);
    double result = 0;
    for (size_t i = 0; i < a->len; i ++) {
        result += a->data[i * a->stride] * b->data[i * b->stride];
    }
    return result;
}
