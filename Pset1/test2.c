#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
	char *p;
	// int i;
	// int int_ptr[3] = {1,2,3};
	// int *int_ptr2 = &int_ptr;
	// char *p = "ddd";
	int i1 = 1;
	int *i2 = &i1;
	int **i3 = &i2;
	**i3 = 2;
	// int **i4;
	// **i4 = 1;
	// p = malloc(sizeof(char) * 3);
	p = "hello word";
	// i = 10;
	// int_ptr = {1,2,3};
	// printf("lllll %d;", int_ptr[0]);
	printf("%c", p[1]);
	// p[0] = 'H';
	printf("%c", p[0]);
	for(int j =0; j < 5; ++j){
		printf("%d\n", j);
	}
}