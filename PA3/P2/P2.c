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
	printf("table size is %d\n", table_size);
	int* index_array = malloc(sizeof(int)*n);
	List** hash_table = malloc(sizeof(List*)*table_size);

	for(int i = 0; i<table_size; i++){
		hash_table[i] = malloc(sizeof(List));
		list_init(hash_table[i]);
	}

	for(int i = 0; i < n; i++){
		printf("key is %d\n", *(int*)(f_post+skip*i));
		int key = h(f+sz*i)%table_size;
		if(hash_table[key]->size==0){
			printf("yes");
		}
		else{
			printf("no");
		}
		if(hash_table[key]->size==0){
			printf("appending\n");
			hash_table[key] = malloc(sizeof(List));
			list_init(hash_table[key]);
			list_append(hash_table[key], f_post+skip*i);
		}
		else{
			int append_flag = 1;
			for (ListElmt* element = list_head(hash_table[key]); element != NULL; element = list_next(element)){
				if(equals(element->data, f_post+skip*i)==1){
					printf("find dup;\n");
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

int hash2(void *s)
{
    int hashval;
    int st = *(int*)s;
    printf("st is %d", st);

    hashval = abs(st);
    return hashval;
}

int equals(void* data1, void* data2){
	char* temp_data1 = (char*)data1;
	char* temp_data2 = (char*)data2;
	int rv = strcmp((char*)data1, (char*)data2);
	rv = rv+1;
	return rv;
}

int hash(void *s)
{
    int hashval;
    char* st = *(char**)s;

    for (hashval = 0; *st != '\0'; st++)
        hashval = *st + 31*hashval;
    hashval = abs(hashval);
    return hashval;
}

int equals2(void* data1, void* data2){
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
	char* string_array[5] = {"abc", "three", "four", "second", "four"};
	int int_array[8] = {1,2,3,4,4,6,7,3};
	int tt[4] = {1,2,3,4};
	// void* test = (void*)string_array;
	// //char* first = *(&string_array[1]);
	// char* first = *(char**)(&(test[1]));
	// printf("test is %s", first);
	void *test = (void*)string_array;
	// test = (char*)test;
	// int* tt3= test+sizeof(int)*1;
	// int tt2 = (int)((int**)test)[1];
	// int* tt2 = test;
	// printf("test is %d\n", *tt3);
	// int tt2 = *((int*)(&test[1]));
	// printf();
	printf("string array i9s %s\n", *(char**)((char*)test+sizeof(char*)/sizeof(char)*1));
	printf("%lu size\n", sizeof(char*)/sizeof(char));
	int list_size = uniq(string_array, 5, sizeof(char*), equals, hash);
	for(int i = 0; i<4; i++){
		printf("word is %s\n", string_array[i]);
	}
	printf("now list size is %d\n", list_size);
	int list_size2 = uniq(int_array, 8, sizeof(int), equals2, hash2);
	printf("now list size is %d\n", list_size2);
	for(int i = 0; i<6; i++){
		printf("element is %d\n", int_array[i]);
	}
}