#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINES 1000
#define MAX_CHAR_PER_LINE 1000

int read_file(char str_array[MAX_LINES][MAX_CHAR_PER_LINE], int argc, char **argv){
	/*if there is command line argument*/
	/*char **str_array = malloc(sizeof(char*) * 500);*/
	int row, col;
	char c;
	FILE* fp;
	row = 0;
	col = 0;
	fp = fopen(argv[1], "r");

	/*str_array[0] = malloc(sizeof(char) * 200);*/



	while((c = fgetc(fp)) != -1){
		if(c == '\n'){
			str_array[row][col] = '\0';
			row += 1;
			col = 0;
			/*str_array[row] = malloc(sizeof(char) * 200);*/
		}
		else{
			str_array[row][col] = c;
			col += 1;
		}
	} while(c != EOF);
	fclose(fp);
	return row + 1;
}

int main(int argc, char **argv){
	char str_array[MAX_LINES][MAX_CHAR_PER_LINE];
	int i, lines;
	lines = read_file(str_array, argc, argv);
	for(i = 0; i < lines; ++i){
		printf("%s\n", str_array[i]);
	}
}
