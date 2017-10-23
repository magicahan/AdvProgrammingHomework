#include<stdio.h>
#include<stdlib.h>

#define NUM_ARRAY 68
#define FILE_NAME "arrays.txt"

typedef struct array_original_{
	double** array;
} Array_original;

typedef struct union_array_{
	double* array;
	size_t** pointer_array;
} Union_array;

typedef struct augment_array_elem_{
	double* array;
	size_t** pointer_array;
} Augment_array_elem;

typedef struct augment_array_{
	Augment_array_elem** arrays;
	size_t size;
} Augment_array;

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

size_t merge_two_array(double* M,  double* L, double* M_prev, size_t** pointer_array, size_t len_L, size_t len_M){
	size_t length, L_index, M_index;

	length = 0;
	L_index = 0;
	M_index = 1;
	pointer_array[0][0]=0;
	pointer_array[1][0]=1;

	while(length < (len_L) + (len_M/2)){
		if(L_index < len_L && M_index < len_M){
			if(L[L_index] <= M_prev[M_index]){
				M[length] = L[L_index];
				L_index += 1;
				pointer_array[0][length+1]=pointer_array[0][length] + 1;
				pointer_array[1][length+1]=pointer_array[1][length];
				length += 1;
			}
			else{
				M[length] = M_prev[M_index];
				M_index += 2;
				pointer_array[0][length+1]=pointer_array[0][length];
				pointer_array[1][length+1]=pointer_array[1][length]+2;
				length += 1;
			}
		}
		else if(L_index >= len_L){
			for(int i = M_index; i < len_M; i+=2){
				M[length] = M_prev[i];
				if(length < (len_L) + (len_M/2) - 1){
					pointer_array[0][length+1] = pointer_array[0][length];
					pointer_array[1][length+1] = pointer_array[1][length] + 2;
				}
				length += 1;
			}
			break;
		}
		else if(M_index >= len_L){
			for(int i = L_index; i < len_L; i++){
				M[length] = L[i];
				// printf("now %d %f %zu\n",i , L[i], len_L);
				if(length < (len_L) + (len_M/2) - 1){
					pointer_array[0][length+1] = pointer_array[0][length] + 1;
					pointer_array[1][length+1] = pointer_array[1][length];
				}
				length += 1;
			}
			break;
		}
	}
	return length;
}

void construct_union(double* union_array, double** array_list, size_t** pointer_array, int*size_array, int max){
	/*keep track of the array counter */
	int* counter_array, *seq_array;
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

	// printf("heapify starts\n");
	heapify(heap_array, seq_array, NUM_ARRAY);

	printf("heapify succeed %f %d %zu\n", heap_array[0], size, pointer_array[1][6]);
	while(union_counter <= size - 1){
			/*firstly update the poihnter array*/
		for(int i = 0; i < NUM_ARRAY; i++){
			// printf("update pointer array");
			if(counter_array[i] < size_array[i]){
				pointer_array[i][union_counter] = counter_array[i];
			}
			else{
				pointer_array[i][union_counter] = size_array[i];
			}
		}
		/*add the smallest element to the union array*/
		union_array[union_counter] = heap_array[0];
		// change the smallest element of the heap array
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
		// printf("lalala %d\n", union_counter);

		union_counter += 1;
	}
}

void union_init(Union_array* union_array, double** array_list, int* size_array, int max){
	int s = 0;;
	double* total_array;
	size_t** pointer_array;

	/*firstly initialize the pointer array*/
	for(int i = 0; i < NUM_ARRAY; i++){
		s += size_array[i];
	}

	/*then construct the union list*/
	total_array = malloc(sizeof(double)*s);
	pointer_array = malloc(sizeof(size_t**)*s);

	for(int i = 0; i < NUM_ARRAY; i++){
		printf("at %d size %d\n", i, s);
		// int* temp = malloc(sizeof(int) * size);
		printf("temp set\n");
		pointer_array[i] = malloc(sizeof(size_t) * s);
	}

	construct_union(total_array, array_list, pointer_array, size_array, max);
	printf("succeed\n");
	union_array-> array = total_array;
	union_array-> pointer_array = pointer_array;
}

void Array_original_init(Array_original* array_original, double** array_list){
	array_original->array = array_list;
}

void Augment_array_init(Augment_array* augment_array, double** array_list, int* size_array){
	Augment_array_elem* augment_array_elem;
	//augment_array->arrays = malloc(sizeof(Augment_array_elem*)*NUM_ARRAY);
	Augment_array_elem** temp = malloc(sizeof(Augment_array_elem*)*NUM_ARRAY);
	printf("allocatation stt\n");
	augment_array->arrays = temp;
	printf("allocatation stt\n");

	int size;
	size_t len_L, len_M;
	size_t** pointer_array = malloc(sizeof(size_t*)*2);
	double* M, *M_prev, *L;

	/*initialize the last array*/
	M = array_list[NUM_ARRAY-1];
	size = size_array[NUM_ARRAY - 1];
	augment_array_elem = malloc(sizeof(Augment_array_elem));
	augment_array_elem->array = M;
	printf("allocatation starts2\n");
	printf("allll\n");
	pointer_array = malloc(sizeof(size_t*)*2);
	printf("allll\n");
	printf("set\n");

	pointer_array[0] = malloc(sizeof(size_t)*size);
	pointer_array[1] = malloc(sizeof(size_t)*size);
	printf("allocatation succ %d\n", size);

	augment_array_elem->pointer_array = pointer_array;
	len_M = size;
	for(size_t i; i < size; i++){
		augment_array_elem->pointer_array[0][i] = i;
		augment_array_elem->pointer_array[1][i] = 0;
	}
	printf("finish\n");
	augment_array->arrays[NUM_ARRAY - 1] = augment_array_elem;
	printf("start\n");
	for(int j = NUM_ARRAY - 2; j >= 0; j--){
		printf("sss\n");
		L = array_list[j];
		len_L = size_array[j];
		size = len_L + len_M/2;
		printf("start again\n");
		/*reallocate pointer_array*/
		pointer_array = malloc(sizeof(size_t*)*2);
		pointer_array[0] = malloc(sizeof(size_t)*size);
		pointer_array[1] = malloc(sizeof(size_t)*size);
		printf("finish again\n");
		M_prev = augment_array_elem->array;
		M = malloc(sizeof(double)*size);
		/*reallocate augment_array element*/
		augment_array_elem = malloc(sizeof(Augment_array_elem));
		len_M = merge_two_array(M, L, M_prev, pointer_array, len_L, len_M);
		augment_array_elem->array = M;
		augment_array_elem->pointer_array = pointer_array;
		/*update the augment array*/
		augment_array->arrays[j] = augment_array_elem;
		printf("%d\n", j);
	}
	printf("ffffinsh");
	augment_array->size = len_M;
}

size_t binary_search(double* array, double target, size_t size){
	size_t index, max_index, min_index;
	double array_num;
	max_index = size - 1;
	min_index = 0;
	index = (max_index + min_index)/2;
	array_num = array[index];

	while(array_num != target){
		if(max_index - min_index > 1){
			if(array_num > target){
				max_index = index;
			}
			else{
				min_index = index;
			}
			index = (max_index + min_index)/2;
			array_num = array[index];
		}
		else{
			index = max_index;
			break;
		}
	}
	return index;
}

size_t* search_kernel_original(double target, Array_original* arrays, int* size_array){
	size_t* array_index;
	size_t index;

	array_index = malloc(sizeof(size_t)*NUM_ARRAY);
	for(int i = 0; i < NUM_ARRAY; i++){
		index = binary_search(arrays->array[i], target, size_array[i]);
		array_index[i] = index;
	}
	return array_index;
}

size_t* search_kernel_union(double target, Union_array* arrays, size_t size){
	size_t* array_index;
	int index;

	array_index = malloc(sizeof(size_t)*NUM_ARRAY);

	index = binary_search(arrays->array, target, size);

	for(int i = 0; i < NUM_ARRAY; i++){
		array_index[i]=arrays->pointer_array[i][index];
	}
	return array_index;
}

size_t* search_kernel_augment(double target, Augment_array* augment_array){
	size_t* array_index;
	size_t index;

	array_index = malloc(sizeof(size_t)*NUM_ARRAY);

	for(int i = 0; i < NUM_ARRAY; i++){
		if(i == 0){
			index = binary_search(augment_array->arrays[0]->array, target, augment_array->size);
			array_index[i] = augment_array->arrays[i]->pointer_array[0][index];
			index = augment_array->arrays[i]->pointer_array[1][index];
		}
		else{
			if(target > augment_array->arrays[i]->array[index - 1]){
				array_index[i] = augment_array->arrays[i]->pointer_array[0][index];
				index = augment_array->arrays[i]->pointer_array[1][index];
			}
			else{
				array_index[i] = array_index[i] = augment_array->arrays[i]->pointer_array[0][index-1];;
				index = augment_array->arrays[i]->pointer_array[1][index-1];
			}
		}
	}
	return array_index;
}

void destroy_union(Union_array* union_array){
	free(union_array->array);
	for(int i = 0; i < NUM_ARRAY; i++){
		free(union_array->pointer_array[i]);
	}
	free(union_array->pointer_array);
}


int main(int argc, char** argv){
	size_t size;
	double target = 4.0;
	double** array_list = malloc(sizeof(double*) * NUM_ARRAY);
	int* size_array = malloc(sizeof(int) * NUM_ARRAY);
	int max = readin(array_list, size_array);
	printf("max is %d\n", max);
	printf("test size %i\n", size_array[0]);

	Union_array *test = malloc(sizeof(Union_array));
	printf("size array %u\n", size_array[1]);
	/*Get the total size of the array*/
	size = 0;
	for(int i = 0; i < NUM_ARRAY; i++){
		size += size_array[i];
	}
	printf("size array read\n");
	union_init(test, array_list, size_array, max);
	printf("init sccuess\n");
	size_t* array_index = search_kernel_union(target, test, size);

	for(int i =0; i < NUM_ARRAY; i++){
		printf("index for %d is %zu\n", i, array_index[i]);
	}
	destroy_union(test);
	free(array_index);

	Augment_array* augment_array = malloc(sizeof(Augment_array));

	Augment_array_init(augment_array, array_list, size_array);
	printf("init succc");
 	array_index = search_kernel_augment(target, augment_array);
 	for(int i =0; i < NUM_ARRAY; i++){
		printf("augment index for %d is %zu\n", i, array_index[i]);
	}


	
	// double L[5] = {1, 3, 5, 7, 9};
	// double M_prev[5] = {2, 4, 6, 8, 10};
	// double M[7];
	// size_t** pointer_array = malloc(sizeof(size_t*)*2);
	// pointer_array[0]=malloc(sizeof(size_t)*7);
	// pointer_array[1]=malloc(sizeof(size_t)*7);

	// size_t test_size = merge_two_array(M, L, M_prev, pointer_array, 5, 5);

	// for(int i = 0; i < 7; i++){
	// 	printf("test M is %f\n", M[i]);
	// 	printf("L index is %zu\n", pointer_array[0][i]);
	// }
	// printf("M size is %zu\n", test_size);


	// Augment_array* augment_array = malloc(sizeof(Augment_array));

	// Augment_array_init(augment_array, array_list, size_array);

	// /*test the augment list*/
	// for(int i = 0; i < 6; i++){
	// 	printf("the element is %zu\n", augment_array->arrays[1]->pointer_array[0][i]);
	// }

	return 0;
}