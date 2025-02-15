#include "matrix.h"
#include "vector.h"
#include <assert.h>
#include <stddef.h>
/*#include <stdlib.h>*/

struct VectorSlice mat_get_row(struct MatrixSlice *matrix, int row)
{
    return (struct VectorSlice) { .len = matrix->rows,
                                  .stride = matrix->row_stride,
                                  .data = &matrix->data[row * matrix->row_stride] };
}
