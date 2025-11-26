#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    int n;
    double **m;
} Matrix;

Matrix* create_matrix(int n);
void free_matrix(Matrix *A);

Matrix* read_matrix_from_file(const char *filename);
void print_matrix(Matrix *A);

Matrix* multiply_matrix(Matrix *A, Matrix *B);
double* multiply_vector_matrix(double *v, Matrix *A);

Matrix* power_matrix(Matrix *A, int k);

#endif
