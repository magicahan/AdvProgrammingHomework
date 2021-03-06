#include <stdlib.h>
#include <stdio.h>
#include <string.h>

double **dmatrix(size_t m, size_t n);

int main(int argc, char **argv){
	int n, i, j;
	double **dmatrix_n;
	double counter = 0.0;
	n = atoi(argv[1]);
	dmatrix_n = dmatrix(n, n);
	for(i = 0; i < n; ++i){
		for(j = 0; j < n; ++j){
			dmatrix_n[i][j] = counter;
			counter += 1.0;
			printf("%f ", dmatrix_n[i][j]);
		}
		printf("\n");
	}
	free(dmatrix_n);
	return 0;

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
