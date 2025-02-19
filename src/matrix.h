#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

struct Matrix {
    size_t rows, cols;
    double data[];
};

const double *mat_get_ref(const struct Matrix *matrix, size_t row, size_t col);

double *mat_get_ref_mut(struct Matrix *matrix, size_t row, size_t col);

double mat_get(const struct Matrix *matrix, size_t row, size_t col);

struct Vector mat_get_row(const struct Matrix *matrix, size_t row);

struct Vector mat_get_col(const struct Matrix *matrix, size_t col);

void mat_mul(const struct Matrix *a, const struct Matrix *b, struct Matrix *restrict out);

void mat_print(const struct Matrix *matrix);

#endif /* MATRIX_H */
