#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dict_naive.h"
#include "dict_rb.h"

#define MAX_WORD_LEN 50
#define MAX_LINE_LEN 550

#define FILE_NAME "sample_dict.txt"
#define WORD_NUM 254
#define ITER_TIME 5000000

int readcommand_dict1();
int readcommand_dict2();
dict1* readfile_dict1(char* file_name);
dict2* readfile_dict2(char* file_name);
char** readlist(char* file_name);

int main(int argc, char**argv){
	char** word_list = malloc(sizeof(char*)*WORD_NUM);
	word_list = readlist(FILE_NAME);
	int counter;
	float dict1_time = 0;
	float dict2_time = 0;
	dict1* dictionary1 = malloc(sizeof(dict1));
	dict2* dictionary2 = malloc(sizeof(dict2));

	if(1){
		dictionary1 = create_dict1();
		dictionary1 = readfile_dict1(FILE_NAME);
		dictionary2 = create_dict2();
		dictionary2 = readfile_dict2(FILE_NAME);

		printf("start testing;\n");
		/*look up for dict 1*/
		for(int i = 0; i<ITER_TIME; i++){
			counter = (float)rand()/RAND_MAX*WORD_NUM;
			clock_t t1 = clock();
			find_dict1(dictionary1, word_list[counter]);
			t1 = clock() - t1;
			dict1_time += (float)t1/CLOCKS_PER_SEC;
		}


		for(int i = 0; i<ITER_TIME; i++){
			counter = (float)rand()/RAND_MAX*WORD_NUM;
			clock_t t1 = clock();
			find_dict2(dictionary2, word_list[counter]);
			t1 = clock() - t1;
			dict2_time += (float)t1/CLOCKS_PER_SEC;
		}
	}
	printf("Model1 Dict takes %f s.\n", dict1_time);
	printf("Red Black Tree Dict takes %f s.\n", dict2_time);
	readcommand_dict2();
}

int readcommand_dict1(){
	dict1* dictionary;
	char* input;
	char* prompt;
	char* command;
	char* word;
	char* defn;
	int flag, counter, pointer;

	dictionary = create_dict1();
	input = malloc(sizeof(char)*MAX_LINE_LEN*MAX_WORD_LEN);
	prompt = malloc(sizeof(char)*MAX_WORD_LEN);
	command = malloc(sizeof(char)*MAX_WORD_LEN);
	word = malloc(sizeof(char)*MAX_WORD_LEN);
	defn = malloc(sizeof(char)*MAX_WORD_LEN*MAX_LINE_LEN);

	printf("Load existing dictioanry(y/n)?");
	fgets(input, MAX_WORD_LEN*MAX_LINE_LEN, stdin);
	if(strcmp(input,"y\n")==0){
		dictionary = readfile_dict1(FILE_NAME);
	}
	printf("Load complete\n");

	while((fgets(input, MAX_WORD_LEN*MAX_LINE_LEN, stdin))!=NULL){
		pointer = 0;
		sscanf(input, "%s%n", prompt, &counter);
		pointer += counter;
		if(strcmp(prompt, "%")==0){
			sscanf(input + pointer, "%s%n", command, &counter);
			pointer += counter;
			if(strcmp(command, "print")==0){
				if(dictionary->words->left!=NULL){
					in_print_dict1(dictionary);
				}
				else{
					printf("Empty Dictioanry!\n");
				}
			}
			else if(strcmp(command, "find")==0){
				sscanf(input + pointer, "%s%n", word, &counter);
				pointer += counter;
				strcpy(defn, find_dict1(dictionary, word));
				if(defn!=NULL){
					printf("%s: %s\n", word, defn);
				}
				else{
					printf("Definition not found: %s\n", word);
				}
			}
			else if(strcmp(command, "add")==0){
				sscanf(input + pointer, "%s %[^\t\n]%n", word, defn, &counter);
				pointer += counter;
				if(strcmp(word, "apple")==0){
					printf("now tree is %s\n", dictionary->words->key);
				}
				flag = insert_dict1_word(dictionary, word, defn);
			}
			else if(strcmp(command, "delete")==0){
				sscanf(input + pointer, "%s%n", word, &counter);
				pointer += counter;
				delete_dict1_word(dictionary, word);
			}
		}
		else{
			printf("Wrong prompt prfix!\n");
			break;
		}
	}
	return 0;
}

int readcommand_dict2(){
	dict2* dictionary;
	char* input;
	char* prompt;
	char* command;
	char* word;
	char* defn;
	int flag, counter, pointer;

	dictionary = create_dict2();
	input = malloc(sizeof(char)*MAX_LINE_LEN*MAX_WORD_LEN);
	prompt = malloc(sizeof(char)*MAX_WORD_LEN);
	command = malloc(sizeof(char)*MAX_WORD_LEN);
	word = malloc(sizeof(char)*MAX_WORD_LEN);
	defn = malloc(sizeof(char)*MAX_WORD_LEN*MAX_LINE_LEN);

	printf("Load existing dictioanry(y/n)?");
	fgets(input, MAX_WORD_LEN, stdin);
	if(strcmp(input,"y\n")==0){
		dictionary = readfile_dict2(FILE_NAME);
	}
	printf("Load complete\n");

	while((input=fgets(input, MAX_WORD_LEN*MAX_LINE_LEN, stdin))!=NULL){
		pointer = 0;
		sscanf(input, "%s%n", prompt, &counter);
		pointer += counter;
		if(strcmp(prompt, "%")==0){
			sscanf(input + pointer, "%s%n", command, &counter);
			pointer += counter;
			if(strcmp(command, "print")==0){
				if(dictionary->words->left!=NULL){
					in_print_dict2(dictionary);
				}
				else{
					printf("Empty Dictioanry!\n");
				}
			}
			else if(strcmp(command, "find")==0){
				sscanf(input + pointer, "%s%n", word, &counter);
				pointer += counter;
				strcpy(defn, find_dict2(dictionary, word));
				if(defn!=NULL){
					printf("%s: %s\n", word, defn);
				}
				else{
					printf("Definition not found: %s\n", word);
				}
			}
			else if(strcmp(command, "add")==0){
				sscanf(input + pointer, "%s %[^\t\n]%n", word, defn, &counter);
				pointer += counter;
				flag = insert_dict2_word(dictionary, word, defn);
			}
			else if(strcmp(command, "delete")==0){
				sscanf(input + pointer, "%s%n", word, &counter);
				pointer += counter;
				delete_dict2_word(dictionary, word);
			}
		}
		else{
			printf("Wrong prompt prfix!\n");
			break;
		}
	}
	return 0;
}

dict1* readfile_dict1(char* file_name){
	dict1* dictionary = malloc(sizeof(dict1));
	dictionary = create_dict1();

	FILE* fp;
	char* string_line = malloc(sizeof(char)*MAX_LINE_LEN*MAX_WORD_LEN);
	char* word = malloc(sizeof(char)*MAX_WORD_LEN);
	char* defn = malloc(sizeof(char)*MAX_WORD_LEN*MAX_LINE_LEN);

	fp = fopen(file_name, "r");

	while(fgets(string_line, MAX_WORD_LEN*MAX_LINE_LEN, fp)!=NULL){
		sscanf(string_line, "%s %[^\t\n]", word, defn);
		int flag = insert_dict1_word(dictionary, word, defn);
	}

	fclose(fp);
	return dictionary;
}

dict2* readfile_dict2(char* file_name){
	dict2* dictionary = malloc(sizeof(dict2));
	dictionary = create_dict2();

	FILE* fp;
	char* string_line = malloc(sizeof(char)*MAX_LINE_LEN*MAX_WORD_LEN);
	char* word = malloc(sizeof(char)*MAX_WORD_LEN);
	char* defn = malloc(sizeof(char)*MAX_WORD_LEN*MAX_LINE_LEN);

	fp = fopen(file_name, "r");

	while(fgets(string_line, MAX_WORD_LEN*MAX_LINE_LEN, fp)!=NULL){
		sscanf(string_line, "%s %[^\t\n]", word, defn);
		int flag = insert_dict2_word(dictionary, word, defn);
	}

	fclose(fp);
	return dictionary;
}

char** readlist(char* file_name){
	char** rv = malloc(sizeof(char*)*WORD_NUM);
	int counter = 0;

	FILE* fp;
	char* string_line = malloc(sizeof(char)*MAX_LINE_LEN*MAX_WORD_LEN);
	char* word = malloc(sizeof(char)*MAX_WORD_LEN);
	char* defn = malloc(sizeof(char)*MAX_WORD_LEN*MAX_LINE_LEN);

	fp = fopen(file_name, "r");

	while(fgets(string_line, MAX_WORD_LEN*MAX_LINE_LEN, fp)!=NULL){
		sscanf(string_line, "%s %[^\t\n]", word, defn);
		rv[counter] = malloc(sizeof(char)*MAX_WORD_LEN);
		strcpy(rv[counter], word);
		counter += 1;
	}

	fclose(fp);
	return rv;
}
