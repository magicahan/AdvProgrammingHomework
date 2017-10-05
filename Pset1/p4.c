#include <stdlib.h>
#include <stdio.h>
#include <string.h>

double **dmatrix(size_t m, size_t n);

int main(int argc, char **argv){
	int n, i;
	double **dmatrix_n = dmatrix(n, n);
	double counter = 0.0;
	n = atoi(argv[1]);
	for(i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			dmatrix_n[i][j] = counter;
			counter += 1.0;
			printf("%f ", dmatrix_n[i][j]);
		}
		printf("\n");
	}
	free(dmatrix_n);

}

double **dmatrix(size_t m, size_t n){
	int i;
	double **pptr;
	pptr = malloc(m * sizeof(double**));
	for(i = 0; i < m; ++i){
		double *ptr;
		ptr = malloc(n * sizeof(double));
		pptr[i] = ptr;
	}
	return pptr;
}