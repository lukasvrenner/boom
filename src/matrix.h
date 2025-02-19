#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>
#include <stdbool.h>

struct Matrix {
    size_t rows, cols;
    double data[];
};

void mat_mul(const struct Matrix *a, const struct Matrix *b, struct Matrix *restrict out);

void mat_print(const struct Matrix *matrix);

void mat_set_ident(struct Matrix *matrix);

bool mat_eq(const struct Matrix *a, const struct Matrix *b);

#endif /* MATRIX_H */
