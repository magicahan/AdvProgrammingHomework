#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void alphabetize(char *text[], int nlines);

int readfile(char **str_array, int argc, char **argv){
	/*if there is command line argument*/
	/*char **str_array = malloc(sizeof(char*) * 500);*/
	int row, col;
	char c;
	row = 0;
	col = 0;

	str_array[0] = malloc(sizeof(char) * 200);

	do{
		c = getchar();
		if(c == '\n'){
			str_array[row][col] = c;
			row += 1;
			col =0;
			str_array[row] = malloc(sizeof(char) * 200);
		}
		else{
			str_array[row][col] = c;
			col += 1;
		}
	} while(c != EOF);
	return row + 1;
}

int main(int argc, char **argv){
	/*char **str_array = readfile(argc, argv);*/
	char **str_array;
	int i;
	int nlines;

	str_array = malloc(sizeof(char**) * 500);
	nlines = readfile(str_array, argc, argv);

	alphabetize(str_array, nlines);
	for(i = 0; i < 500; ++i){
		if(str_array[i] != NULL){
		printf("%s", str_array[i]);
		}
	}
	free(str_array);
}

int alphabet_compare(const void* a, const void* b);

void alphabetize(char *text[], int nlines){
	qsort(text, nlines, sizeof(char *), alphabet_compare);
}

int alphabet_compare(const void* a, const void* b){
	char** a_str = (char **) a;
	char** b_str = (char **) b;
	int i, rv;
	rv = 0;
	*a_str = (char *) *a_str;
	for(i = 0; i < 200; ++i){
		if(a_str[0][i] > b_str[0][i]){
			rv = 1;
			break;
		}
		else if(a_str[0][i] < b_str[0][i]){
			rv = -1;
			break;
		}
	}
	return rv;
}
