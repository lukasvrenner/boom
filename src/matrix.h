#ifndef MATRIX_H
#define MATRIX_H

/*#include "vector.h"*/
#include <stddef.h>

struct MatrixSlice {
    ptrdiff_t rows, cols;
    ptrdiff_t row_stride, col_stride;
    const double *data;
};

struct MatrixSliceMut {
    ptrdiff_t rows, cols;
    ptrdiff_t row_stride, col_stride;
    double *restrict data;
};

const double *mat_get_ref(const struct MatrixSlice *matrix, ptrdiff_t row, ptrdiff_t col);

double *mat_get_ref_mut(const struct MatrixSliceMut *matrix, ptrdiff_t row, ptrdiff_t col);

double mat_get(const struct MatrixSlice *matrix, ptrdiff_t row, ptrdiff_t col);

struct VectorSlice mat_get_row(const struct MatrixSlice *matrix, ptrdiff_t row);

struct VectorSlice mat_get_col(const struct MatrixSlice *matrix, ptrdiff_t col);

void mat_mul(
    const struct MatrixSliceMut *out, const struct MatrixSlice *a, const struct MatrixSlice *b
);

void mat_print(const struct MatrixSlice *matrix);

#endif /* MATRIX_H */
