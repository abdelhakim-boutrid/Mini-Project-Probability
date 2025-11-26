
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

Matrix* create_matrix(int n) {
    Matrix *A = malloc(sizeof(Matrix));
    A->n = n;
    A->m = malloc(n * sizeof(double*));
    for(int i = 0; i < n; i++)
        A->m[i] = calloc(n, sizeof(double));
    return A;
}

void free_matrix(Matrix *A) {
    for(int i = 0; i < A->n; i++) free(A->m[i]);
    free(A->m);
    free(A);
}

Matrix* read_matrix_from_file(const char *filename) {
    FILE *f = fopen(filename, "r");
    if(!f) return NULL;

    int n;
    fscanf(f, "%d", &n);

    Matrix *A = create_matrix(n);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            fscanf(f, "%lf", &A->m[i][j]);

    fclose(f);
    return A;
}

Matrix* multiply_matrix(Matrix *A, Matrix *B) {
    int n = A->n;
    Matrix *C = create_matrix(n);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            for(int k = 0; k < n; k++)
                C->m[i][j] += A->m[i][k] * B->m[k][j];

    return C;
}

double* multiply_vector_matrix(double *v, Matrix *A) {
    int n = A->n;
    double *r = calloc(n, sizeof(double));

    for(int j = 0; j < n; j++)
        for(int k = 0; k < n; k++)
            r[j] += v[k] * A->m[k][j];

    return r;
}

Matrix* power_matrix(Matrix *A, int k) {
    int n = A->n;
    Matrix *R = create_matrix(n);

    for(int i = 0; i < n; i++)
        R->m[i][i] = 1.0;

    Matrix *temp = A;

    while(k > 0) {
        if(k % 2 == 1) {
            Matrix *newR = multiply_matrix(R, temp);
            free_matrix(R);
            R = newR;
        }
        Matrix *newTemp = multiply_matrix(temp, temp);
        temp = newTemp;
        k /= 2;
    }

    return R;
}
