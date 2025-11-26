#include <stdio.h>
#include "io.h"

void save_vector(const char *filename, double *v, int n) {
    FILE *f = fopen(filename, "w");
    for(int i = 0; i < n; i++)
        fprintf(f, "%.10lf\n", v[i]);
    fclose(f);
}
