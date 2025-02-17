#include "matrix.h"
#include "vector.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

/*#include <stdlib.h>*/

const double *mat_get_ref(const struct MatrixSlice *matrix, ptrdiff_t row, ptrdiff_t col)
{
    return matrix->data + row * matrix->row_stride + col * matrix->col_stride;
}

double *mat_get_ref_mut(const struct MatrixSliceMut *matrix, ptrdiff_t row, ptrdiff_t col)
{
    return matrix->data + row * matrix->row_stride + col * matrix->col_stride;
}

double mat_get(const struct MatrixSlice *matrix, ptrdiff_t row, ptrdiff_t col)
{
    return matrix->data[row * matrix->row_stride + col * matrix->col_stride];
}

struct VectorSlice mat_get_row(const struct MatrixSlice *matrix, ptrdiff_t row)
{
    return (struct VectorSlice) {
        .len = matrix->cols,
        .stride = matrix->col_stride,
        .data = matrix->data + row * matrix->row_stride,
    };
}

struct VectorSlice mat_get_col(const struct MatrixSlice *matrix, ptrdiff_t col)
{
    return (struct VectorSlice) {
        .len = matrix->rows,
        .stride = matrix->row_stride,
        .data = matrix->data + col * matrix->col_stride,
    };
}

void mat_mul(
    const struct MatrixSliceMut *out, const struct MatrixSlice *a, const struct MatrixSlice *b
)
{
    assert(a->cols == b->rows);
    assert(out->rows == a->rows && out->cols == b->cols);
    for (ptrdiff_t i = 0; i < a->rows; i++) {
        for (ptrdiff_t j = 0; j < b->cols; j++) {
            struct VectorSlice a_row = mat_get_row(a, i);
            struct VectorSlice b_col = mat_get_col(b, j);
            *mat_get_ref_mut(out, i, j) = vec_dot_product(&a_row, &b_col);
        }
    }
}

void mat_print(const struct MatrixSlice *matrix)
{
    for (ptrdiff_t i = 0; i < matrix->rows; i++) {
        fputs("[ ", stdout);
        for (ptrdiff_t j = 0; j < matrix->cols; j++) {
            printf("%f, ", mat_get(matrix, i, j));
        }
        fputs("]\n", stdout);
    }
}
