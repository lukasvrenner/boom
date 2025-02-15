#ifndef MATRIX_H
#define MATRIX_H

/*#include "vector.h"*/
#include <stddef.h>

struct MatrixSlice {
    size_t rows, cols;
    ptrdiff_t row_stride, col_stride;
    const double *data;
};

struct MatrixSliceMut {
    size_t rows, cols;
    ptrdiff_t row_stride, col_stride;
    double *data;
};

#endif /* MATRIX_H */
