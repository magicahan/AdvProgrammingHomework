#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define M 1000
#define N 1000

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

double **dmatrix_cont(size_t m, size_t n){
	int i;
	double **pptr;
	double *ptr;
	pptr = malloc(m * sizeof(double**));
	ptr = malloc(m *n * sizeof(double));
	for(i = 0; i < m; ++i){
		double *sub_ptr = &ptr[i * m];
		pptr[i] = sub_ptr;
	}
	return pptr;
}

void initialize_array_dynamic(double **dmatrix, int m, int n){
	int i, j;
	for(i = 0; i < m; ++i){
		for(j = 0; j < n; ++j){
			dmatrix[i][j] = 1;
		}
	}
}

void initialize_array_static(double dmatrix[M][N], int m, int n){
	int i, j;
	for(i = 0; i < m; ++i){
		for(j = 0; j < n; ++j){
			dmatrix[i][j] = 1;
		}
	}
}

void work_kernel_dynamic(double **U, int m, int n)
{
	int i,j;
	double a = 1.0, b = 0.5, c __attribute__((unused));


	for( i=1; i < (m-1); i++)
		for( j=1; j < (n-1); j++)
		{
			c = ( a * (U[i+1][j] + U[i-1][j]) ) +
		            ( b * (U[i][j+1] + U[i][j-1]) ) +
	                    ( (1 - (2*a) - (2*b)) * U[i][j] );
		}
	
	/*(void)c;*/
	return;
}

void work_kernel_static(double U[M][N], int m, int n)
{
	int i,j;
	double a = 1.0, b = 0.5, c __attribute__((unused));


	for( i=1; i < (m-1); i++)
		for( j=1; j < (n-1); j++)
		{
			c = ( a * (U[i+1][j] + U[i-1][j]) ) +
		            ( b * (U[i][j+1] + U[i][j-1]) ) +
	                    ( (1 - (2*a) - (2*b)) * U[i][j] );
		}
	/*(void) c;*/
	return;
}



int main(int argc, char * argv[])
{
	
	int m = 1000;
	int n = 1000;

	/* Declare and allocate your arrays A,B,C */
	double **B, **C;
	double A[M][N];

	clock_t t1;
	clock_t t2;
	clock_t t3;

	B = dmatrix(m, n);
	C = dmatrix_cont(m, n);
	
	/* Initialize arrays */
	initialize_array_static(A, m, n);
	initialize_array_dynamic(B, m, n);
	initialize_array_dynamic(C, m, n);

	t1 = clock();
	/* time A */
	work_kernel_static( A, m, n);
	t1 = clock() - t1;

	/* time B */
	t2 = clock();
	work_kernel_dynamic( B, m, n);
	t2 = clock() - t2;

	/* time C */
	t3 = clock();
	work_kernel_dynamic( C, m, n);
	t3 = clock() - t3;

	/* Print out timing to stdout in seconds for each array */
	printf("Statically Allocated Array Kernel takes %f seconds;\n", ((float)t1)/CLOCKS_PER_SEC);
	printf("Dynamically Allocated Array Kernel with Contiguous Memory takes %f seconds;\n", ((float)t3)/CLOCKS_PER_SEC);
	printf("Dynamically Allocated Array Kernel with Distributed Memory takes %f seconds;\n", ((float)t2)/CLOCKS_PER_SEC);

	/* Free memory*/
	free(B);
	free(C);
	
	return 0;

}
