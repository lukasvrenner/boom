#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "matrix.h"

enum BoomErr boom_mat_mul(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *restrict out)
{
    if (a->cols != b->rows) {
        return BOOM_ERR_BAD_DIM;
    }
    if (out->rows != a->rows || out->cols != b->cols) {
        return BOOM_ERR_BAD_DIM;
    }
    for (size_t i = 0; i < a->rows; i++) {
        for (size_t j = 0; j < b->cols; j++) {
            double dot_product = 0;
            for (size_t k = 0; k < a->cols; k++) {
                dot_product += a->data[i * a->cols + k] * b->data[k * b->cols + j];
            }
            out->data[i * out->cols + j] = dot_product;
        }
    }
    return BOOM_ERR_NONE;
}

void boom_mat_print(const struct BoomMatrix *a, FILE *stream)
{
    for (size_t i = 0; i < a->rows; i++) {
        fputs("[ ", stream);
        for (size_t j = 0; j < a->cols; j++) {
            fprintf(stream, "%f, ", a->data[i * a->cols + j]);
        }
        fputs("]\n", stream);
    }
}

void boom_mat_set_ident(struct BoomMatrix *a)
{
    memset(a->data, 0, sizeof(double) * a->rows * a->cols);
    for (size_t i = 0; i < a->rows && i < a->cols; i++) {
        a->data[i * a->cols + i] = 1;
    }
}

bool boom_mat_eq(const struct BoomMatrix *a, const struct BoomMatrix *b)
{
    if (a->rows != b->rows || a->cols != b->cols) {
        return false;
    }
    return memcmp(a->data, b->data, a->rows * a->cols) == 0;
}
