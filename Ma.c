#include "m.h"
#include "1.h"

/* ========== matrix functions ========== */

void matrix_init(struct matrix *m, unsigned int rows, unsigned int cols) {
    m->rows = rows;
    m->cols = cols;
    for (unsigned int i = 0; i < rows * cols; i++) {
        m->data[i] = 0.0;
    }
}

void matrix_set(struct matrix *m, unsigned int row, unsigned int col, double val) {
    if (row < m->rows && col < m->cols) {
        m->data[row * m->cols + col] = val;
    }
}

double matrix_get(struct matrix *m, unsigned int row, unsigned int col) {
    if (row < m->rows && col < m->cols) {
        return m->data[row * m->cols + col];
    }
    return 0.0;
}

/* ========== implementations for 1.h functions ========== */

/* Null pointer constant */
void *N0 = 0;

/* ptrdiff_t: difference between pointers in bytes */
int pd_t(void *a, void *b) {
    return (char *)a - (char *)b;
}

/* size_t equivalent: return size given (ptr unused) */
unsigned int s_t(void *ptr, unsigned int size) {
    (void)ptr;
    return size;
}

/* Return a fixed wide char codepoint for Omega (U+03A9 = 937 decimal) */
unsigned int wc_t(void) {
    return 937;
}

/* Manually defined offsets of members in struct example */
unsigned int o_a(void) {
    return 0;
}

unsigned int o_b(void) {
    return 4;
}

unsigned int o_c(void) {
    return 8;
}

