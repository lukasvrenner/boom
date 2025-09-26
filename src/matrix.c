#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "matrix.h"

const char *boom_err_str(enum BoomErr err) {
    switch (err) {
    case BOOM_ERR_NONE:
        return "none";
    case BOOM_ERR_BAD_DIM:
        return "bad dimensions";
    case BOOM_ERR_DIV_ZERO:
        return "division by zero";
    }
    // this should be unreachable.
    return "unknown";
}

enum BoomErr boom_mat_mul(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *restrict out)
{
    if (a->cols != b->rows) {
        return BOOM_ERR_BAD_DIM;
    }
    if (out->rows != a->rows || out->cols != b->cols) {
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

void boom_mat_print(const struct BoomMatrix *a, FILE *stream)
{
    for (size_t row = 0; row < a->rows; row++) {
        fputs("[ ", stream);
        for (size_t col = 0; col < a->cols; col++) {
            fprintf(stream, "%f, ", a->data[row * a->cols + col]);
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

void boom_mat_swap_rows(struct BoomMatrix *a, size_t row_a, size_t row_b)
{
    for (size_t col = 0; col < a->cols; col++) {
        double temp = a->data[row_a * a->cols + col];
        a->data[row_a * a->cols + col] = a->data[row_b * a->cols + col];
        a->data[row_b * a->cols + col] = temp;
    }
}

void boom_mat_swap_cols(struct BoomMatrix *a, size_t col_a, size_t col_b)
{
    for (size_t row = 0; row < a->rows; row++) {
        double temp = a->data[row * a->cols + col_a];
        a->data[row * a->cols + col_a] = a->data[row * a->rows + col_b];
        a->data[row * a->cols + col_b] = temp;
    }
}

static void boom_mat_elim_for(struct BoomMatrix *a, struct BoomMatrix *b) {
    assert(a->rows == b->rows);
    size_t iters = (a->rows < a->cols) ? a->rows : a->cols;
    for (size_t i = 0; i < iters; i++) {

        // find the most stable pivot.
        size_t best_pivot = i;
        for (size_t row = i; row < a->rows; row++) {
            double current = a->data[row * a->cols + i];
            if (current == 1) {
                best_pivot = row;
                break;
            } 
            if (fabs(current) > fabs(a->data[best_pivot * a->cols + i])) {
                best_pivot = row;
            }
        }

        if (best_pivot != i) {
            boom_mat_swap_rows(a, i, best_pivot);
            boom_mat_swap_rows(b, i, best_pivot);
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

static void boom_mat_elim_bac(struct BoomMatrix *a, struct BoomMatrix *b) {
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

enum BoomErr boom_mat_gaus(struct BoomMatrix *a, struct BoomMatrix *b)
{
    if (a->rows != b->rows) {
        return BOOM_ERR_BAD_DIM;
    }
    boom_mat_elim_for(a, b);
    boom_mat_elim_bac(a, b);
    return BOOM_ERR_NONE;
}
