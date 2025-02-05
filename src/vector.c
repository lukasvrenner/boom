#include "vector.h"
#include <stddef.h>

double dot_product(const double *a, const double *b, size_t n)
{
    double result = 0;
    while (n--) {
        result += a[n] * b[n];
    }
    return result;
}
