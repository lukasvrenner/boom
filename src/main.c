#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "vector.h"

int main(void)
{
    struct BoomMatrix *vec_a = malloc(sizeof(struct BoomMatrix) + 3 * sizeof(double));
    assert(vec_a != NULL);
    vec_a->rows = 3;
    vec_a->cols = 1;

    struct BoomMatrix *vec_b = malloc(sizeof(struct BoomMatrix) + 3 * sizeof(double));
    assert(vec_b != NULL);
    vec_b->rows = 3;
    vec_b->cols = 1;


    double a[] = { 2, -1, 4 };
    double b[] = { 1, 1, 0 };


    memcpy(vec_a->data, a, sizeof(a));
    memcpy(vec_b->data, b, sizeof(b));

    /* boom_vec_cross(vec_a, vec_b, vec_b); */

    /* printf("%f\n", boom_vec_dot(vec_a, vec_b)); */
    boom_vec_cross(vec_a, vec_b, vec_b);
    boom_vec_print(vec_b, stdout);

    /* printf("Cross-product magnitude: %f\n", boom_vec_mag(vec_b)); */
    /* boom_vec_print(vec_b, stdout); */

    /* boom_vec_orth(vec_a, vec_b, vec_b); */
    /* puts("orth of a onto b:"); */
    /* boom_vec_print(vec_b, stdout); */

    /* boom_vec_normalize(vec_b, vec_b); */

    /* puts("Normalized orth:"); */
    /* boom_vec_print(vec_b, stdout); */

    /* printf("Normalized magnitude: %f\n", boom_vec_mag(vec_b)); */

    free(vec_a);
    free(vec_b);

    return 0;
}
