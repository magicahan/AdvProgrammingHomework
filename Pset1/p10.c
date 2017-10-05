#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define max_word_length 200
#define max_line 1000

int get_index(char ** word_list, char * word, int num_words){
	int index, i;
	index = -1;
	for(i = 0; i < num_words; ++i){
		if(strcasecmp(word_list[i], word) == 0){
			index = i;
			break;
		}
	}
	return index;
}

int construct(char** word_list, int* count_list, char* file_input, int word_counter){
	char *word = malloc(sizeof(char) * max_word_length);
	char c;
	int i, j, index, add_flag;
	j = 0;
	add_flag = 0;

	for(i = 0; i < max_line * max_word_length; ++i){
		c = file_input[i];
		if(c == EOF | c == '\n'){
			/*printf("%s", word);*/
			break;
		}
		else if((c >= 'a' & c <= 'z') | (c >= 'A' & c <= 'Z')){
			word[j] = tolower(c);
			j += 1;
			if(tolower(c) == tolower(file_input[i + 1])){
				add_flag = 1;
			}
		}
		else{
			if(add_flag == 1){
			index = get_index(word_list, word, word_counter);
			if(index == -1){
				word_list[word_counter] = malloc(sizeof(char) * max_word_length);
				memcpy(word_list[word_counter], word, j * sizeof(char));
				count_list[word_counter] = 1;
				word_counter += 1;
			}
			else{
				count_list[index] += 1;
			}
		}
			/*redelcare and clear the word*/
			memset(word,0,sizeof(char)*max_word_length);
			/*redelcare the counter for the word */
			j = 0;
			add_flag = 0;
		}
	}
	free(word);
	return word_counter;
}

int main(int argc, char ** argv){
	char string_file[max_line*max_word_length];
	char *word_list[max_line];
	int count_list[max_line];
	int word_counter, i;
	FILE* fp;
	fp = fopen(argv[1], "r");
	word_counter = 0;
	while(fgets(string_file, max_word_length*max_line, fp)){
		word_counter = construct(word_list, count_list, string_file, word_counter);
	}
	for(i = 0; i < word_counter; ++i){
		printf("%s : %d\n", word_list[i], count_list[i]);
	}
	fclose(fp);
}
