#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dict_naive.h"

#define MAX_WORD_LEN 50
#define MAX_LINE_LEN 550

int readfile_dict1();

int main(int argc, char**argv){
	readfile_dict1();
}

int readfile_dict1(){
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

	while((input=fgets(input, MAX_WORD_LEN*MAX_LINE_LEN, stdin))!=NULL){
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
				if(flag==0){
					printf("Insertion fails.\n");
				}
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