#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "vector.h"

int main(void)
{
    struct BoomMatrix *vec_a = boom_alloc(1, 3);
    if (vec_a == NULL) {
        perror("allocation error");
        return 1;
    }

    vec_a->data[0] = 8;
    vec_a->data[1] = 2;
    vec_a->data[2] = 4;

    struct BoomMatrix *vec_b = boom_alloc(1, 3);
    if (vec_b == NULL) {
        perror("allocation error");
        return 1;
    }

    vec_b->data[0] = 1;
    vec_b->data[1] = 2;
    vec_b->data[2] = 3;

    boom_vec_cross(vec_a, vec_b, vec_b);
    boom_print(vec_b, stdout);

    free(vec_a);
    free(vec_b);

    struct BoomMatrix *mat_a = boom_alloc(3, 3);
    if (mat_a == NULL) {
        perror("allocation error");
        return 1;
    }

    struct BoomMatrix *mat_b = boom_alloc(1, 3);
    if (mat_b == NULL) {
        perror("allocation error");
        return 1;
    }

    double a[3][3] = {
        {5, 2, 3},
        {1, 8, 9},
        {3, -8, 6},
    };

    double b[3] = {3, 2, -9};

    memcpy(mat_a->data, a, sizeof(a));
    memcpy(mat_b->data, b, sizeof(b));

    enum BoomErr err = boom_gaus(mat_a, mat_b);
    if (err != BOOM_ERR_NONE) {
        puts(boom_err_str(err));
    }

    puts("solution:");
    boom_print(mat_b, stdout);


    struct BoomMatrix *mat_c = boom_alloc(1, 3);
    if (mat_c == NULL) {
        perror("allocation error");
        return 1;
    }

    memcpy(mat_a->data, a, sizeof(a));
    boom_mul(mat_a, mat_b, mat_c);

    puts("test:");
    boom_print(mat_c, stdout);
    puts("=");
    memcpy(mat_b->data, b, sizeof(b));
    boom_print(mat_b, stdout);

    free(mat_a);
    free(mat_b);
    free(mat_c);

    return 0;
}
