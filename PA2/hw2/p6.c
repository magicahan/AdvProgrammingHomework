#include<stdio.h>
#include<stdlib.h>

#define NUM_ARRAY 3
#define FILE_NAME "array_test.txt"

typedef struct array_original_{
	double** array;
} array_original;

typedef struct union_array_{
	double* array;
	int** pointer_array;
} Union_array;

void heapify_spot(double *f, int* seq_array, int i, int n);

double readin(double** array_list, int* size_array){
	double* num_array;
	//num_array = malloc(sizeof(int)*10);
	FILE* array_file;
	char temp_char[256];
	double temp;
	int num_elem, array_counter;
	double max;
	max = 0;
	//int read_flag = 1;

	array_counter = 0;
	array_file = fopen(FILE_NAME, "r");
	while(fscanf(array_file, "%s", temp_char) == 1){
		num_elem = atoi(temp_char);
		num_array = malloc(sizeof(double)*num_elem);
		for(int i = 0; i < num_elem; i++){
			fscanf(array_file, "%s", temp_char);
			temp = atof(temp_char);
			num_array[i] = temp;
			if(temp >= max){
				max = temp;
			}
		}
		array_list[array_counter] = num_array;
		size_array[array_counter] = num_elem;
		array_counter += 1;
	}
	return max;
}

void heapify(double *f, int* seq_array, int n){
	int i;
	int index = (n - 2) / 2;
	for(i = index; i >= 0; --i){
		heapify_spot(f, seq_array, i, n);
	}
}

void heapify_spot(double *f, int* seq_array, int i, int n){
	if(2 * i + 1 <= n - 1){
		double smaller;
		int smaller_index;
		if(2 * i + 2 < n){
		if(f[2 * i + 1] > f[2 * i + 2]){
			if(f[i] > f[2 * i + 2]){
				smaller = f[i];
				smaller_index = seq_array[i];
				f[i] = f[2 * i + 2];
				seq_array[i] = seq_array[2*i+2];
				f[2 * i + 2] = smaller;
				seq_array[2*i+2] = smaller_index;
				heapify_spot(f, seq_array, 2 * i + 2, n);
			}
			}
		else{
			if(f[i] > f[2 * i + 1]){
				smaller = f[i];
				smaller_index = seq_array[i];
				f[i] = f[2 * i + 1];
				seq_array[i] = seq_array[2*i+1];
				f[2 * i + 1] = smaller;
				seq_array[2*i+1] = smaller_index;
				heapify_spot(f, seq_array, 2 * i + 1, n);
			}
		}
		}
		else{
			if(f[i] > f[2 * i + 1]){
				smaller = f[i];
				smaller_index = seq_array[i];
				f[i] = f[2 * i + 1];
				seq_array[i] = seq_array[2*i+1];
				f[2 * i + 1] = smaller;
				seq_array[2*i+1] = smaller_index;
				heapify_spot(f, seq_array, 2 * i + 1, n);
			}
		}
	}
}

int** construct_union(double* union_array, double** array_list, int*size_array, int max){
	/*keep track of the array counter */
	int* counter_array, *seq_array, **pointer_array;
	double* heap_array;
	int union_counter, size;
	counter_array = malloc(sizeof(int) * NUM_ARRAY);
	seq_array = malloc(sizeof(int) * NUM_ARRAY);
	heap_array = malloc(sizeof(int) * NUM_ARRAY);

	size = 0;
	union_counter = 0;

	/*initialize the counter array and the heap array*/
	for(int i = 0; i < NUM_ARRAY; i++){
		seq_array[i] = i;
		counter_array[i] = 0;
		heap_array[i] = array_list[i][0];
		size += size_array[i];
	}

	printf("heapify starts\n");
	heapify(heap_array, seq_array, NUM_ARRAY);

	pointer_array = malloc(sizeof(int*)*NUM_ARRAY);
	printf("iniiazlize\n");
	for(int i = 0; i < NUM_ARRAY; i++){
		pointer_array[i] = malloc(sizeof(int*) * size);
	}

	printf("heapify succeed %f %d %d\n", heap_array[0], size, pointer_array[1][6]);
	do{
		printf("heapify succeed %f %d %d\n", heap_array[0], size, union_counter);
		/*firstly update the poihnter array*/
		for(int i = 0; i < NUM_ARRAY; i++){
			printf("update pointer array");
			if(counter_array[i] < size_array[i]){
				pointer_array[i][union_counter] = counter_array[i];
			}
			else{
				pointer_array[i][union_counter] = size_array[i];
			}
		}
		/*add the smallest element to the union array*/
		union_array[union_counter] = heap_array[0];
		// change the smalles element of the heap array
		counter_array[seq_array[0]] += 1;
		if(counter_array[seq_array[0]] < size_array[seq_array[0]]){
			heap_array[0] = array_list[seq_array[0]][counter_array[seq_array[0]]];
			/*Now we update the pointer array*/
		}
		else{
			heap_array[0] = max + 1;

		}
		// /*Now reheapify the array*/
		heapify_spot(heap_array, seq_array, 0, NUM_ARRAY);
		printf("lalala %d\n", union_counter);

		union_counter += 1;
	}while(union_counter <= size - 1);
	return pointer_array;
}

void union_init(Union_array* union_array, double** array_list, int* size_array, int max){
	int s = 0;;
	double* total_array;
	int** pointer_array;

	/*firstly initialize the pointer array*/
	for(int i = 0; i < NUM_ARRAY; i++){
		s += size_array[i];
	}

	// printf("pass the first point %i\n", s);
	// for(int i = 0; i < NUM_ARRAY; i++){
	// 	int* temp = malloc(sizeof(int) * s);
	// 	pointer_array[i] = temp;
	// 	printf("tttest %d\n", pointer_array[0][6]);
	// }
	/*then construct the union list*/
	total_array = malloc(sizeof(double)*s);

	pointer_array = construct_union(total_array, array_list, size_array, max);

	union_array-> array = total_array;
	union_array-> pointer_array = pointer_array;
}


int main(int argc, char** argv){
	double** array_list = malloc(sizeof(double*) * NUM_ARRAY);
	int* size_array = malloc(sizeof(int) * NUM_ARRAY);
	int max = readin(array_list, size_array);
	printf("max is %d\n", max);
	printf("test size %i\n", size_array[0]);

	Union_array test;
	printf("size array %u\n", size_array[1]);
	union_init(&test, array_list, size_array, max);
	for(int i = 0; i < 12; i++){
		printf("the element is %d\n", test.pointer_array[0][i]);
	}
}