#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stddef.h>

#include "vector.h"

struct Matrix {
    size_t rows, cols;
    double data[];
};

int mat_mul(const struct Matrix *a, const struct Matrix *b, struct Matrix *restrict out);
int mat_mul_vec(const struct Matrix *a, const struct Vector *b, struct Vector *restrict out);

void mat_print(const struct Matrix *matrix);

void mat_set_ident(struct Matrix *matrix);

bool mat_eq(const struct Matrix *a, const struct Matrix *b);

#endif /* MATRIX_H */
