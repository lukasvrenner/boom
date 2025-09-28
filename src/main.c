#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "vector.h"
static int boom_vector_ex(void);
static int boom_matrix_ex(void);

int main(int argc, const char **argv)
{
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "matrix") == 0) {
            int result = boom_matrix_ex();
            if (result != 0) {
                perror("matrix");
                return result;
            }
        } else if (strcmp(argv[i], "vector") == 0) {

            int result = boom_vector_ex();
            if (result != 0) {
                perror("matrix");
                return result;
            }
        }
    }
    return 0;
}

static int boom_vector_ex(void)
{
    struct BoomMatrix *vec_a = boom_alloc(1, 3);
    if (vec_a == NULL) {
        return 1;
    }

    double a[] = {8, 2, 4};
    memcpy(vec_a->data, a, sizeof(a));

    vec_a->data[0] = 8;
    vec_a->data[1] = 2;
    vec_a->data[2] = 4;

    puts("\033[1ma:\033[0m");
    boom_print(vec_a, stdout);

    struct BoomMatrix *vec_b = boom_alloc(1, 3);
    if (vec_b == NULL) {
        return 1;
    }

    double b[] = {1, 2, 3};
    memcpy(vec_b->data, b, sizeof(b));

    puts("\033[1mb:\033[0m");
    boom_print(vec_b, stdout);

    puts("\033[1ma x b:\033[0m");
    boom_vec_cross(vec_a, vec_b, vec_b);
    boom_print(vec_b, stdout);

    memcpy(vec_b->data, b, sizeof(b));
    puts("\033[1mproj(a, b):\033[0m");
    boom_vec_proj(vec_a, vec_b, vec_b);
    boom_print(vec_b, stdout);

    free(vec_a);
    free(vec_b);
    return 0;
}

static int boom_matrix_ex(void)
{
    struct BoomMatrix *mat_a = boom_alloc(3, 3);
    if (mat_a == NULL) {
        return 1;
    }

    struct BoomMatrix *mat_b = boom_alloc(1, 3);
    if (mat_b == NULL) {
        return 1;
    }

    double a[3][3] = {
        {2, 1, 4},
        {1, 3, 2},
        {3, 2, 1},
    };

    double b[3] = {3, 2, -9};

    memcpy(mat_a->data, a, sizeof(a));
    puts("\033[1mA:\033[0m");
    boom_print(mat_a, stdout);

    memcpy(mat_b->data, b, sizeof(b));
    puts("\033[1mb:\033[0m");
    boom_print(mat_b, stdout);

    enum BoomErr err = boom_gaus(mat_a, mat_b);
    if (err != BOOM_ERR_NONE) {
        puts(boom_err_str(err));
    }

    puts("\033[1mAx=b\033[0m");
    puts("\033[1mx:\033[0m");
    boom_print(mat_b, stdout);


    struct BoomMatrix *mat_c = boom_alloc(1, 3);
    if (mat_c == NULL) {
        return 1;
    }

    memcpy(mat_a->data, a, sizeof(a));
    boom_mul(mat_a, mat_b, mat_c);

    memcpy(mat_a->data, a, sizeof(a));

    size_t p[] = {0, 1, 2};
    size_t swaps = 0;
    err = boom_lup_decomp(mat_a, p, &swaps);
    if (err != BOOM_ERR_NONE) {
        puts(boom_err_str(err));
    }
    puts("\033[1mLUP decomposition of A (in place):\033[0m");
    boom_print(mat_a, stdout);
    puts("\033[1mPermutation vector:\033[0m");
    fputs("{ ", stdout);
    for (size_t i = 0; i < 3; i++) {
        printf("%ld, ", p[i]);
    }
    puts("}");

    double det = 1;
    for (size_t i = 0; i < mat_a->rows; i++) {
        det *= mat_a->data[i * mat_a->rows + i];
    }
    if (swaps & 1) {
        det = -det;
    }
    printf("\033[1mdet(A) = \033[0m%f\n", det);
    free(mat_a);
    free(mat_b);
    free(mat_c);
    return 0;
}
