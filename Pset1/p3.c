#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
void heapify_spot(int *f, int i, int n);

void heapify(int *f, int n){
	int i;
	int index = (n - 2) / 2;
	for(i = index; i >= 0; --i){
		heapify_spot(f, i, n);
	}
}

void heapify_spot(int *f, int i, int n){
	if(2 * i + 1 <= n - 1){
		int smaller;
		if(2 * i + 2 < n){
		if(f[2 * i + 1] < f[2 * i + 2]){
			if(f[i] < f[2 * i + 2]){
				smaller = f[i];
				f[i] = f[2 * i + 2];
				f[2 * i + 2] = smaller;
				heapify_spot(f, 2 * i + 2, n);
			}
			}
		else{
			if(f[i] < f[2 * i + 1]){
				smaller = f[i];
				f[i] = f[2 * i + 1];
				f[2 * i + 1] = smaller;
				heapify_spot(f, 2 * i + 1, n);
			}
		}
		}
		else{
			if(f[i] < f[2 * i + 1]){
				smaller = f[i];
				f[i] = f[2 * i + 1];
				f[2 * i + 1] = smaller;
				heapify_spot(f, 2 * i + 1, n);
			}
		}
	}
}

int * allocate_array( int argc, char * argv[])
{
	int *array = malloc((argc - 1) * sizeof(int));
	int i;
	for(i = 1; i <= argc - 1; i++){
		array[i - 1] = atoi(argv[i]);
	}
	return array;
}

int test_heap( int * f, int n)
{
	int i;
	int child_A, child_B;

	for( i = 0; i < n; i++ )
	{
		child_A = ( 2 * i ) + 1;
		child_B = ( 2 * i ) + 2;

		if( child_A < n )
			if( f[i] < f[child_A] )
				return -1;
		
		if( child_B < n )
			if( f[i] < f[child_B] )
				return -1;
	}

	return 1;
}

int main(int argc, char * argv[])
{
	int result;
	int i;
	int n = argc - 1;
	int * arr = allocate_array( argc, argv );

	heapify( arr, n );
	result = test_heap( arr, n );

	for( i = 0; i < n; i++ )
		printf("%d ", arr[i]);
	printf("\n");

	if( result == 1 )
		printf("Heap test success!\n");
	else
		printf("Heap test failed.\n");

	free(arr);

	return 0;
}
