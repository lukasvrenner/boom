#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"

const char *boom_err_str(enum BoomErr err) {
    switch (err) {
    case BOOM_ERR_NONE:
        return "none";
    case BOOM_ERR_BAD_DIM:
        return "bad dimensions";
    case BOOM_ERR_DIV_ZERO:
        return "division by zero";
    case BOOM_ERR_NO_INV:
        return "no inverse";
    }
    // this should be unreachable.
    return "unknown";
}

struct BoomMatrix *boom_alloc(size_t cols, size_t rows)
{
    struct BoomMatrix *mat = malloc(sizeof(struct BoomMatrix) + rows * cols * sizeof(double));
    if (mat == NULL) {
        return NULL;
    }
    mat->rows = rows;
    mat->cols = cols;
    return mat;
}

enum BoomErr boom_add(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *out)
{
    if (a->rows != b->rows || a->rows != out->rows) {
        return BOOM_ERR_BAD_DIM;
    }
    if (a->cols != b->cols || a->cols != out->cols) {
        return BOOM_ERR_BAD_DIM;
    }
    for (size_t i = 0; i < a->rows * a->cols; i++) {
        out->data[i] = a->data[i] + b->data[i];
    }
    return BOOM_ERR_NONE;
}

enum BoomErr boom_sub(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *out)
{
    if (a->rows != b->rows || a->rows != out->rows) {
        return BOOM_ERR_BAD_DIM;
    }
    if (a->cols != b->cols || a->cols != out->cols) {
        return BOOM_ERR_BAD_DIM;
    }
    for (size_t i = 0; i < a->rows * a->cols; i++) {
        out->data[i] = a->data[i] - b->data[i];
    }
    return BOOM_ERR_NONE;
}

enum BoomErr boom_mul_scalar(const struct BoomMatrix *a, double scalar, struct BoomMatrix *out)
{
    if (a->rows != out->rows || a->cols != out->cols) {
        return BOOM_ERR_BAD_DIM;
    }
    for (size_t i = 0; i < a->rows * a->cols; i++) {
        out->data[i] = a->data[i] * scalar;
    }
    return BOOM_ERR_NONE;
}

enum BoomErr boom_mul(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *restrict out)
{
    if (a->cols != b->rows || out->rows != a->rows || out->cols != b->cols) {
        return BOOM_ERR_BAD_DIM;
    }

    for (size_t row = 0; row < a->rows; row++) {
        for (size_t b_col = 0; b_col < b->cols; b_col++) {
            double dot_product = 0;
            for (size_t a_col = 0; a_col < a->cols; a_col++) {
                dot_product += a->data[row * a->cols + a_col] * b->data[a_col * b->cols + b_col];
            }
            out->data[row * out->cols + b_col] = dot_product;
        }
    }
    return BOOM_ERR_NONE;
}

void boom_print(const struct BoomMatrix *a, FILE *stream)
{
    for (size_t row = 0; row < a->rows; row++) {
        fputs("[", stream);
        for (size_t col = 0; col < a->cols; col++) {
            fprintf(stream, "%+11.6f,", a->data[row * a->cols + col]);
        }
        fputs(" ]\n", stream);
    }
}

void boom_set_ident(struct BoomMatrix *a)
{
    memset(a->data, 0, sizeof(double) * a->rows * a->cols);
    for (size_t i = 0; i < a->rows && i < a->cols; i++) {
        a->data[i * a->cols + i] = 1;
    }
}

bool boom_eq(const struct BoomMatrix *a, const struct BoomMatrix *b)
{
    if (a->rows != b->rows || a->cols != b->cols) {
        return false;
    }
    return memcmp(a->data, b->data, a->rows * a->cols) == 0;
}

void boom_swap_rows(struct BoomMatrix *a, size_t row_a, size_t row_b)
{
    for (size_t col = 0; col < a->cols; col++) {
        double temp = a->data[row_a * a->cols + col];
        a->data[row_a * a->cols + col] = a->data[row_b * a->cols + col];
        a->data[row_b * a->cols + col] = temp;
    }
}

void boom_swap_cols(struct BoomMatrix *a, size_t col_a, size_t col_b)
{
    for (size_t row = 0; row < a->rows; row++) {
        double temp = a->data[row * a->cols + col_a];
        a->data[row * a->cols + col_a] = a->data[row * a->rows + col_b];
        a->data[row * a->cols + col_b] = temp;
    }
}

/**
 * Returns the index of the ideal pivot.
 */
static size_t boom_find_pivot(const struct BoomMatrix *a, size_t i)
{
    size_t pivot = i;
    for (size_t row = i; row < a->rows; row++) {
        double current = a->data[row * a->cols + i];
        if (fabs(current) > fabs(a->data[pivot * a->cols + i])) {
            pivot = row;
        }
    }
    return pivot;
}

static void boom_elim_for(struct BoomMatrix *a, struct BoomMatrix *b) {
    assert(a->rows == b->rows);
    size_t iters = (a->rows < a->cols) ? a->rows : a->cols;
    for (size_t i = 0; i < iters; i++) {

        size_t pivot = boom_find_pivot(a, i);

        if (pivot != i) {
            boom_swap_rows(a, i, pivot);
            boom_swap_rows(b, i, pivot);
        }

        double div = a->data[i * a->cols + i];
        // skip empty columns
        if (div == 0) {
            continue;
        }

        // set the pivot to `1`.
        for (size_t col = i; col < a->cols; col++) {
            a->data[i * a->cols + col] /= div;
        }
        assert(a->data[i * a->cols + i] == 1);
        for (size_t col = 0; col < b->cols; col++) {
            b->data[i * b->cols + col] /= div;
        }

        // set everything below the pivot to `0`.
        for (size_t row = i + 1; row < a->rows; row++) {
            double mul = -1 * a->data[row * a->cols + i];

            for (size_t col = i; col < a->cols; col++) {
                a->data[row * a->cols + col] += mul * a->data[i * a->cols + col];
            }
            assert(a->data[row * a->cols + i] == 0);

            for (size_t col = 0; col < b->cols; col++) {
                b->data[row * b->cols + col] += mul * b->data[i * b->cols + col];
            }
        }
    }
}

static void boom_elim_bac(struct BoomMatrix *a, struct BoomMatrix *b) {
    assert(a->rows == b->rows);
    size_t iters = (a->rows < a->cols) ? a->rows : a->cols;

    // avoid overflow.
    if (iters == 0) {
        return;
    }
    for (size_t i = iters - 1; i > 0; i--) {
        if (a->data[i * a->cols + i] == 0) {
            continue;
        }
        for (size_t row = 0; row < i; row++) {
            double mul = a->data[row * a->cols + i];

            for (size_t col = i; col < a->cols; col++) {
                a->data[row * a->cols + col] -= mul * a->data[i * a->cols + col];
            }
            assert(a->data[row * a->cols + i] == 0);

            for (size_t col = 0; col < b->cols; col++) {
                b->data[row * b->cols + col] -= mul * b->data[i * b->cols + col];
            }
        }
    }
}

enum BoomErr boom_gaus(struct BoomMatrix *a, struct BoomMatrix *b)
{
    if (a->rows != b->rows) {
        return BOOM_ERR_BAD_DIM;
    }
    boom_elim_for(a, b);
    boom_elim_bac(a, b);
    return BOOM_ERR_NONE;
}

enum BoomErr boom_lup_decomp(struct BoomMatrix *a, size_t *p, size_t *swaps)
{
    if (a->rows != a->cols) {
        return BOOM_ERR_BAD_DIM;
    }
    for (size_t i = 0; i < a->rows; i++) {
        p[i] = i;
    }
    for (size_t i = 0; i < a->rows; i++) {
        size_t pivot = boom_find_pivot(a, i);
        if (pivot != i) {
            boom_swap_rows(a, i, pivot);
            size_t temp = p[i];
            p[i] = p[pivot];
            p[pivot] = temp;
           (*swaps)++;
        }

        double div = a->data[i * a->cols + i];
        if (div == 0) {
            return BOOM_ERR_NO_INV;
        }
        for (size_t row = i + 1; row < a->rows; row++) {
            a->data[row * a->cols + i] /= div;
            for (size_t col = i + 1; col < a->cols; col++) {
                a->data[row * a->cols + col] -= 
                    a->data[row * a->cols + i] * a->data[i * a->cols + col];
            }
        }
    }
    return BOOM_ERR_NONE;
}
