#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"

int main()
{
    struct Matrix *mat_a = malloc(sizeof(struct Matrix) + 9 * sizeof(double));
    mat_a->rows = 3;
    mat_a->cols = 3;

    struct Matrix *mat_b = malloc(sizeof(struct Matrix) + 9 * sizeof(double));
    mat_b->rows = 3;
    mat_b->cols = 3;

    struct Matrix *mat_product = malloc(sizeof(struct Matrix) + 9 * sizeof(double));
    mat_product->rows = 3;
    mat_product->cols = 3;

    for (int i = 0; i < 9; i++) {
        mat_a->data[i] = (double) i + 1;
        mat_b->data[8 - i] = (double) i + 1;
    }

    mat_mul(mat_a, mat_b, mat_product);
    mat_print(mat_product);

    mat_set_ident(mat_a);
    mat_print(mat_a);

    mat_mul(mat_a, mat_b, mat_product);
    printf("mat_a == mat_b: %d\n", mat_eq(mat_b, mat_product));
}
