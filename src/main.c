#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "vector.h"

int main(void)
{
    struct BoomMatrix *vec_a = malloc(sizeof(struct BoomMatrix) + 3 * sizeof(double));
    assert(vec_a != NULL);
    vec_a->rows = 3;
    vec_a->cols = 1;

    vec_a->data[0] = 8;
    vec_a->data[1] = 2;
    vec_a->data[2] = 4;

    struct BoomMatrix *vec_b = malloc(sizeof(struct BoomMatrix) + 3 * sizeof(double));
    assert(vec_b != NULL);
    vec_b->rows = 3;
    vec_b->cols = 1;

    vec_b->data[0] = 1;
    vec_b->data[1] = 2;
    vec_b->data[2] = 3;

    boom_vec_cross(vec_a, vec_b, vec_b);
    boom_vec_print(vec_b, stdout);

    free(vec_a);
    free(vec_b);

    struct BoomMatrix *mat_a = malloc(sizeof(struct BoomMatrix) + 3 * 3 * sizeof(double));
    assert(mat_a != NULL);
    mat_a->rows = 3;
    mat_a->cols = 3;

    struct BoomMatrix *mat_b = malloc(sizeof(struct BoomMatrix) + 3 * 1 * sizeof(double));
    assert(mat_b != NULL);
    mat_b->rows = 3;
    mat_b->cols = 1;

    double a[3][3] = {
        {5, 2, 3},
        {1, 8, 9},
        {3, -8, 6},
    };

    double b[3] = {5, 2, -9};

    memcpy(mat_a->data, a, sizeof(a));
    memcpy(mat_b->data, b, sizeof(b));

    enum BoomErr err = boom_mat_gaus(mat_a, mat_b);
    if (err != BOOM_ERR_NONE) {
        puts(boom_err_str(err));
    }

    boom_mat_print(mat_a, stdout);
    boom_mat_print(mat_b, stdout);

    for (size_t i = 0; i < 3; i++) {
        double sum = 0;
        for (size_t j = 0; j < 3; j++) {
            sum += a[i][j] * mat_b->data[j];
        }
        assert(sum == b[i]);
    }

    free(mat_a);
    free(mat_b);

    return 0;
}
