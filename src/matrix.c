#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "matrix.h"

int boom_mat_mul(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *restrict out)
{
    if (a->cols != b->rows) {
        return -1;
    }
    if (out->rows != a->rows || out->cols != b->cols) {
        return -1;
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
    return 0;
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

int boom_mat_add(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *out)
{
    if (a->rows != b->rows || a->cols != b->cols) {
        return -1;
    }
    if (a->rows != out->rows || a->cols != out->cols) {
        return -1;
    }
    for (size_t i = 0; i < a->rows * a->cols; i++) {
        out->data[i] = a->data[i] + b->data[i];
    }
    return 0;
}

int boom_mat_sub(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *out)
{
    if ((a->rows * a->cols != b->rows * b->cols) || (a->rows * a->cols != out->rows * out->cols))
        return -1;
    for (size_t i = 0; i < a->rows * a->cols; i++) {
        out->data[i] = a->data[i] - b->data[i];
    }
    return 0;
}

int boom_mat_mul_scalar(const struct BoomMatrix *a, double scalar, struct BoomMatrix *out)
{
    if (a->rows != out->rows || a->cols != out->cols) {
        return -1;
    }
    for (size_t i = 0; i < a->rows * a->cols; i++) {
        out->data[i] = a->data[i] * scalar;
    }
    return 0;
}
