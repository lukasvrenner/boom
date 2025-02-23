#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "matrix.h"
#include "vector.h"

void mat_mul(const struct Matrix *a, const struct Matrix *b, struct Matrix *restrict out)
{
    assert(a->cols == b->rows && out->rows == a->rows && out->cols == b->cols);
    for (size_t i = 0; i < a->rows; i++) {
        for (size_t j = 0; j < b->cols; j++) {
            double dot_product = 0;
            for (size_t k = 0; k < a->cols; k++) {
                dot_product += a->data[i * a->cols + k] * b->data[k * b->cols + j];
            }
            out->data[i * out->cols + j] = dot_product;
        }
    }
}

void mat_mul_vec(const struct Matrix *a, const struct Vector *b, struct Vector *restrict out)
{
    assert(a->cols == b->len && out->len == a->rows);
    for (size_t i = 0; i < a->rows; i++) {
        double dot_product = 0;
        for (size_t j = 0; j < a->cols; j++) {
            dot_product += a->data[i * a->cols + j] * b->data[j];
        }
        out->data[i] = dot_product;
    }
}

void mat_print(const struct Matrix *a, FILE *stream)
{
    for (size_t i = 0; i < a->rows; i++) {
        fputs("[ ", stream);
        for (size_t j = 0; j < a->cols; j++) {
            fprintf(stream, "%f, ", a->data[i * a->cols + j]);
        }
        fputs("]\n", stream);
    }
}

void mat_set_ident(struct Matrix *a)
{
    memset(a->data, 0, sizeof(double) * a->rows * a->cols);
    for (size_t i = 0; i < a->rows && i < a->cols; i++) {
        a->data[i * a->cols + i] = 1;
    }
}

bool mat_eq(const struct Matrix *a, const struct Matrix *b)
{
    if (a->rows != b->rows || a->cols != b->cols) {
        return false;
    }
    return memcmp(a->data, b->data, a->rows * a->cols) == 0;
}

void mat_add(const struct Matrix *a, const struct Matrix *b, struct Matrix *out)
{
    assert(a->rows == b->rows && a->cols == b->cols && a->rows == out->rows && a->cols == out->cols);
    for (size_t i = 0; i < a->rows * a->cols; i++) {
        out->data[i] = a->data[i] + b->data[i];
    }
}

void mat_sub(const struct Matrix *a, const struct Matrix *b, struct Matrix *out)
{
    assert(a->rows == b->rows && a->cols == b->cols && a->rows == out->rows && a->cols == out->cols);
    for (size_t i = 0; i < a->rows * a->cols; i++) {
        out->data[i] = a->data[i] - b->data[i];
    }
}

void mat_mul_scalar(const struct Matrix *a, double scalar, struct Matrix *out)
{
    assert(a->rows == out->rows && a->cols == out->cols);
    for (size_t i = 0; i < a->rows * a->cols; i++) {
        out->data[i] = a->data[i] * scalar;
    }
}
