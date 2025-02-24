#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "matrix.h"
#include "vector.h"

int mat_mul(const struct Matrix *a, const struct Matrix *b, struct Matrix *restrict out)
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

int mat_mul_vec(const struct Matrix *a, const struct Vector *b, struct Vector *restrict out)
{
    if (a->cols != b->len) {
        return -1;
    }
    if (out->len != a->rows) {
        return -1;
    }
    for (size_t i = 0; i < a->rows; i++) {
        double dot_product = 0;
        for (size_t j = 0; j < a->cols; j++) {
            dot_product += a->data[i * a->cols + j] * b->data[j];
        }
        out->data[i] = dot_product;
    }
    return 0;
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

int mat_add(const struct Matrix *a, const struct Matrix *b, struct Matrix *out)
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

int mat_sub(const struct Matrix *a, const struct Matrix *b, struct Matrix *out)
{
    if (a->rows != b->rows || a->cols != b->cols) {
        return -1;
    }
    if (a->rows != out->rows || a->cols != out->cols) {
        return -1;
    }
    for (size_t i = 0; i < a->rows * a->cols; i++) {
        out->data[i] = a->data[i] - b->data[i];
    }
    return 0;
}

int mat_mul_scalar(const struct Matrix *a, double scalar, struct Matrix *out)
{
    if (a->rows != out->rows || a->cols != out->cols) {
        return -1;
    }
    for (size_t i = 0; i < a->rows * a->cols; i++) {
        out->data[i] = a->data[i] * scalar;
    }
    return 0;
}
