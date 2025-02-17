#include "matrix.h"
#include <stdlib.h>

int main()
{
    const double mat_a[3 * 3] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    struct MatrixSlice mat_a_slice = {
        .rows = 3,
        .cols = 3,
        .row_stride = 3,
        .col_stride = 1,
        .data = mat_a,
    };
    const double mat_b[3 * 3] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };

    struct MatrixSlice mat_b_slice = {
        .rows = 3,
        .cols = 3,
        .row_stride = 3,
        .col_stride = 1,
        .data = mat_b,
    };

    struct MatrixSliceMut mat_product_slice = {
        .rows = 3,
        .cols = 3,
        .row_stride = 3,
        .col_stride = 1,
        .data = calloc(3 * 3, sizeof(double)),
    };
    mat_mul(&mat_product_slice, &mat_a_slice, &mat_b_slice);
    mat_print((struct MatrixSlice *) &mat_product_slice);
}
