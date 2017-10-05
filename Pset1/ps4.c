#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
	n = atoi(argv[1]);
	dmatrix_n = dmatrix(n, n);
	double counter = 0.0;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++i){
			dmatrix_n[i][j] = counter;
			counter += 1.0;
			printf("%d ", dmatrix_n[i][j]);
		}
		printf("\n");
	}

}

double **dmatrix(size_t m, size_t n){
	double **pptr;
	pptr = malloc(m * sizeof(double**));
	for(int i = 0; i < m; ++i){
		double ptr;
		ptr = malloc(n * sizeof(double))
		pptr[i] = ptr;
	}
	return pptr;
}