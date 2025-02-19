#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "matrix.h"

void mat_mul(const struct Matrix *a, const struct Matrix *b, struct Matrix *restrict out)
{
    assert(a->cols == b->rows);
    assert(out->rows == a->rows && out->cols == b->cols);
    for (size_t i = 0; i < a->rows; i++) {
        for (size_t j = 0; j < b->cols; j++) {
            out->data[i * out->cols + j] = 0;
            for (size_t k = 0; k < a->cols; k++) {
                out->data[i * out->cols + j] += a->data[i * a->cols + k] * b->data[k * b->cols + j];
            }
        }
    }
}

void mat_print(const struct Matrix *matrix)
{
    for (size_t i = 0; i < matrix->rows; i++) {
        fputs("[ ", stdout);
        for (size_t j = 0; j < matrix->cols; j++) {
            printf("%f, ", matrix->data[i * matrix->cols + j]);
        }
        fputs("]\n", stdout);
    }
}

void mat_set_ident(struct Matrix *matrix)
{
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < i; j++) {
            matrix->data[i * matrix->cols + j] = 0;
        }

        matrix->data[i * matrix->cols + i] = 1;

        for (size_t j = i + 1; j < matrix->cols; j++) {
            matrix->data[i * matrix->cols + j] = 0;
        }
    }
}

bool mat_eq(const struct Matrix *a, const struct Matrix *b)
{
    bool eq = a->rows == b->rows && a->cols == b->cols;
    if (!eq)
        return false;
    for (size_t i = 0; i < a->rows * a->cols; i++) {
        eq &= a->data[i] == b->data[i];
    }
    return eq;
}
