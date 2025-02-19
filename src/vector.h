#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

struct Vector {
    size_t len;
    double data[];
};

double vec_dot_product(const struct Vector *a, const struct Vector *b);

void vec_print(const struct Vector *vec);

#endif /* VECTOR_H */
