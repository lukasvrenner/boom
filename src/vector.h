#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

struct VectorSlice {
    /* The number of elements in the vector */
    size_t len;
    /* The distance between each element in units of doubles */
    ptrdiff_t stride;
    const double *data;
};

struct VectorSliceMut {
    /* The number of elements in the vector */
    size_t len;
    /* The distance between each element in units of doubles */
    ptrdiff_t stride;
    double *data;
};

double vec_dot_product(const struct VectorSlice *a, const struct VectorSlice *b);
#endif /* VECTOR_H */
