#include <stdlib.h>
#include <stdio.h>
#include <string.h>

double **dmatrix(size_t m, size_t n);

int main(int argc, char **argv){
	int n, i , j;
	double counter = 0.0;
	double** dmatrix_n;
	n = atoi(argv[1]);
	dmatrix_n = dmatrix(n, n);

	for(i = 0; i < n; ++i){
		for(j = 0; j < n; ++j){
			dmatrix_n[i][j] = counter;
			counter += 1.0;
		}
	}

	printf("Matrix with 1D indexing:\n");
	for(i = 0; i < n * n; ++i){
		printf("%f ", dmatrix_n[0][i]);
		if((i + 1) % n == 0){
			printf("\n");
		}
	}
	
	printf("\n");
	printf("Matrix with 2D indexing:\n");
	for(i = 0; i < n; ++i){
		for(j = 0; j < n; ++j){
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
	double *ptr;
	pptr = malloc(m * sizeof(double*));
	ptr = malloc(m *n * sizeof(double));
	for(i = 0; i < m; ++i){
		double *sub_ptr = &ptr[i * m];
		pptr[i] = sub_ptr;
	}
	return pptr;
}
