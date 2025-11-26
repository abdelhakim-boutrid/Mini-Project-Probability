#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "vector.h"
#include "io.h"

int main() {
    Matrix *P = read_matrix_from_file("matrix.txt");
    if(!P) {
        printf("Erreur lecture matrice.\n");
        return 1;
    }

    int n = P->n;

    // Exemple : distribution initiale dans l’état 2
    double *pi = create_vector(n);
    pi[1] = 1.0;

    // Simulation 50 pas
    for(int step = 1; step <= 50; step++) {
        double *newPi = multiply_vector_matrix(pi, P);
        free_vector(pi);
        pi = newPi;

        if(step == 1 || step == 2 || step == 10 || step == 50) {
            printf("Pi(%d) : ", step);
            print_vector(pi, n);
        }
    }

    save_vector("distribution_finale.txt", pi, n);

    free_vector(pi);
    free_matrix(P);

    return 0;
}
