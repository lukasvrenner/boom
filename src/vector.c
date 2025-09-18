#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "matrix.h"
#include "vector.h"

static size_t boom_vec_len(const struct BoomMatrix *a)
{
    return a->rows * a->cols;
}

double boom_vec_dot(const struct BoomMatrix *a, const struct BoomMatrix *b)
{
    size_t shortest_len;
    if (boom_vec_len(a) < boom_vec_len(b)) {
        shortest_len = boom_vec_len(a);
    } else {
        shortest_len = boom_vec_len(b);
    }

    double result = 0;
    for (size_t i = 0; i < shortest_len; i++) {
        result += a->data[i] * b->data[i];
    }
    return result;
}

double boom_vec_sqr(const struct BoomMatrix *a)
{
    double result = 0;
    for (size_t i = 0; i < boom_vec_len(a); i++) {
        result += a->data[i] * a->data[i];
    }
    return result;
}

int boom_vec_proj(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *out)
{

    if (boom_vec_len(b) != boom_vec_len(out))
        return -1;

    double a_dot_b = boom_vec_dot(a, b);
    double b_dot_b = boom_vec_dot(b, b);
    double scalar = a_dot_b / b_dot_b;

    assert(boom_vec_mul_scalar(b, scalar, out) >= 0);
    return 0;
}

double boom_vec_comp(const struct BoomMatrix *a, const struct BoomMatrix *b)
{
    return boom_vec_dot(a, b) / boom_vec_mag(b);
}

int boom_vec_orth(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *out)
{
    if (boom_vec_proj(a, b, out) < 0)
        return -1;
    assert(boom_vec_sub(a, out, out) >= 0);
    return 0;
}

double boom_vec_mag(const struct BoomMatrix *a)
{
    double dot_product = 0;
    for (size_t i = 0; i < boom_vec_len(a); i++) {
        dot_product += a->data[i] * a->data[i];
    }
    return sqrt(boom_vec_sqr(a));
}

double boom_vec_cos(const struct BoomMatrix *a, const struct BoomMatrix *b)
{
    return boom_vec_dot(a, b) / sqrt(boom_vec_sqr(a) * boom_vec_sqr(b));
}

int boom_vec_cross(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *out)
{
    if (boom_vec_len(a) != 3 || boom_vec_len(b) != 3 || boom_vec_len(out) != 3) {
        return -1;
    }
    double result[3];
    result[0] = a->data[1] * b->data[2] - b->data[1] * a->data[2];
    result[1] = a->data[2] * b->data[0] - b->data[2] * a->data[0];
    result[2] = a->data[0] * b->data[1] - b->data[0] * a->data[1];

    memcpy(out->data, result, sizeof(result));
    return 0;
}

int boom_vec_normalize(const struct BoomMatrix *a, struct BoomMatrix *out)
{
    double mag = boom_vec_mag(a);
    if (mag == 0)
        return -2;
    return boom_vec_mul_scalar(a, 1 / mag, out);
}

bool boom_vec_eq(const struct BoomMatrix *a, const struct BoomMatrix *b)
{
    if (boom_vec_len(a) != boom_vec_len(b)) {
        return false;
    }
    return memcmp(a->data, b->data, boom_vec_len(a) * sizeof(double)) == 0;
}

int boom_vec_add(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *out)
{
    if (boom_vec_len(a) != boom_vec_len(b) || boom_vec_len(a) != boom_vec_len(out))
        return -1;
    for (size_t i = 0; i < boom_vec_len(a); i++) {
        out->data[i] = a->data[i] + b->data[i];
    }
    return 0;
}

int boom_vec_sub(const struct BoomMatrix *a, const struct BoomMatrix *b, struct BoomMatrix *out)
{
    if (boom_vec_len(a) != boom_vec_len(b) || boom_vec_len(a) != boom_vec_len(out))
        return -1;
    for (size_t i = 0; i < boom_vec_len(a); i++) {
        out->data[i] = a->data[i] - b->data[i];
    }
    return 0;
}

int boom_vec_mul_scalar(const struct BoomMatrix *a, double scalar, struct BoomMatrix *out)
{
    if (boom_vec_len(a) != boom_vec_len(out)) {
        return -1;
    }
    for (size_t i = 0; i < boom_vec_len(a); i++) {
        out->data[i] = a->data[i] * scalar;
    }
    return 0;
}

void boom_vec_print(const struct BoomMatrix *a, FILE *stream)
{
    fputs("< ", stream);
    for (size_t i = 0; i < boom_vec_len(a); i++) {
        fprintf(stream, "%f, ", a->data[i]);
    }
    fputs(">\n", stream);
}

bool boom_vec_are_orth(const struct BoomMatrix *a, const struct BoomMatrix *b)
{
    return boom_vec_dot(a, b) == 0;
}
