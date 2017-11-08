#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOAD_FACTOR 0.4

void remove_dup(char* f, int index, int size, int sz){
	memmove(f + index*sz, f + (index + 1)*sz, sz * (size - index - 1));
}

int uniq(void *f, int n, int sz, int (*equals)(void *data1, void *data2), int (*h)(void *key)){
	char* f_post = (char*)f;
	int array_size = n;
	int table_size = n/LOAD_FACTOR;
	int skip = sz/sizeof(char);
	int* index_array = malloc(sizeof(int)*n);
	List** hash_table = malloc(sizeof(List*)*table_size);

	for(int i = 0; i<table_size; i++){
		hash_table[i] = malloc(sizeof(List));
		list_init(hash_table[i]);
	}

	for(int i = 0; i < n; i++){
		int key = h(f+sz*i)%table_size;
		if(hash_table[key]->size==0){
			hash_table[key] = malloc(sizeof(List));
			list_init(hash_table[key]);
			list_append(hash_table[key], f_post+skip*i);
		}
		else{
			int append_flag = 1;
			for (ListElmt* element = list_head(hash_table[key]); element != NULL; element = list_next(element)){
				if(equals(element->data, f_post+skip*i)==1){
					index_array[n-array_size]=i;
					array_size -= 1;
					append_flag = 0;
					break;
				}
			}
			if(append_flag == 1){
				list_append(hash_table[key], f_post+skip*i);
			}
		}
	}

	/*Now delete the elements*/
	for(int j = 0;j < n - array_size; j++){
		remove_dup((char*)f, index_array[j]-j, n-j, sz);
	}
	return array_size;
}

int hash_string(void *s)
{
    int hashval;
    char* st = *(char**)s;

    for (hashval = 0; *st != '\0'; st++)
        hashval = *st + 31*hashval;
    hashval = abs(hashval);
    return hashval;
}


int hash_integer(void *s)
{
    int hashval;
    int st = *(int*)s;

    hashval = abs(st);
    return hashval;
}

int equals_string(void* data1, void* data2){
	char* temp_data1 = (char*)data1;
	char* temp_data2 = (char*)data2;
	int rv = strcmp((char*)data1, (char*)data2);
	rv = rv+1;
	return rv;
}

int equals_integer(void* data1, void* data2){
	int d1 = *(int*)data1;
	int d2 = *(int*)data2;
	int rv  = 0;
	if(d1 == d2){
		rv = 1;
	}
	return rv;
}

int main(){
	int **tt4 = malloc(sizeof(int*)*4);
	if(tt4[4] == NULL){
		printf("the integer is null\n");
	}
	int int_array_size = 8;
	int string_array_size = 6;
	char* string_array[6] = {"one", "two", "three", "four", "three", "two"};
	int int_array[8] = {1,2,3,4,4,6,7,2};
	// printf("string array i9s %s\n", *(char**)((char*)test+sizeof(char*)/sizeof(char)*1));
	// printf("%lu size\n", sizeof(char*)/sizeof(char));
	printf("List of string size is: %d.\n", string_array_size);
	printf("List of string is:\n");
	for(int i = 0; i<string_array_size; i++){
		printf("%s ", string_array[i]);
	}
	printf("\n");
	int new_string_array_size = uniq(string_array, string_array_size, sizeof(char*), equals_string, hash_string);
	printf("After removing duplicates:\n");
	printf("List of new string size is: %d.\n", new_string_array_size);
	printf("List of new string is:\n");
	for(int i = 0; i<new_string_array_size; i++){
		printf("%s ", string_array[i]);
	}
	printf("\n");

	printf("\n");
	printf("List of integer size is: %d.\n", int_array_size);
	printf("List of integer is:\n");
	for(int i = 0; i<int_array_size; i++){
		printf("%d ", int_array[i]);
	}
	printf("\n");
	int new_int_array_size = uniq(int_array, int_array_size, sizeof(int), equals_integer, hash_integer);
	printf("After removing duplicates:\n");
	printf("List of new integer size is: %d.\n", new_int_array_size);
	printf("List of new integer is:\n");
	for(int i = 0; i<new_int_array_size; i++){
		printf("%d ", int_array[i]);
	}
	printf("\n");
}