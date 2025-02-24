#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

struct Vector {
    size_t len;
    double data[];
};

/**
 * Returns `a * b`.
 */
double vec_dot_product(const struct Vector *a, const struct Vector *b);

int vec_cross_product(const struct Vector *a, const struct Vector *b, struct Vector *restrict out);

int vec_cross_product_assign(struct Vector *a, const struct Vector *b);

void vec_print(const struct Vector *vec);

#endif /* VECTOR_H */
