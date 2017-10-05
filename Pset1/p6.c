#include <stdlib.h>
#include <stdio.h>
#include <string.h>

double ***dmatrix(size_t l, size_t m, size_t n);

int main(int argc, char **argv){
	int n, i, j, k;
	double counter = 0.0;
	double*** dmatrix_n;
	n = atoi(argv[1]);
	dmatrix_n = dmatrix(n, n, n);

	printf("Matrix with 2D indexing:\n");
	for(i = 0; i < n; ++i){
		for(j = 0; j < n; ++j){
			for(k = 0; k < n; ++k){
			dmatrix_n[i][j][k] = counter;
			counter += 1.0;
			printf("%f ", dmatrix_n[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}
	printf("Matrix with 1D indexing:\n");
	for(i = 0; i < n * n *n; ++i){
		printf("%f ", dmatrix_n[0][0][i]);
		if((i + 1) % n == 0){
			printf("\n");
		}
		if((i + 1) % (n * n) == 0){
			printf("\n");
		}
	}
	free(dmatrix_n);

}

double ***dmatrix(size_t l, size_t m, size_t n){
	double ***first_dim = malloc(l * sizeof(double***));
	double *third_dim = malloc(l * m * n * sizeof(double));
	int i, j;
	double **second_dim;
	double *subptr;

	for(i = 0; i < l; ++i){
		second_dim = malloc(m * sizeof(double*));
		for(j = 0; j < m; j++){
			subptr = &third_dim[i * m * n + j * n];
			second_dim[j] = subptr;
		}
		first_dim[i] = second_dim;
	}
	return first_dim;
}
