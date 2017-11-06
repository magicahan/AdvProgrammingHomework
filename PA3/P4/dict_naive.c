#include <stdio.h>
#include <stdlib.h>

#include "dict_naive.h"

dict1* create_dict1(void){
	dict1* dictionary;
	dictionary = malloc(sizeof(dict1));
	dictionary-> words = create_tree();
	return dictionary;
}

object_t* find_dict1(dict1* dictionary, key_t query_key){
	object_t* find_obj;
	find_obj = find(dictionary->words, query_key);
	return find_obj;
}

int insert_dict1_word(dict1* dictionary, key_t key, object_t* defn){
	int succ_flag;
	succ_flag = insert(dictionary->words, key, defn);
	return succ_flag;
}

void in_print_dict1(dict1* dictionary){
	int rv = in_print(dictionary->words);
}

void delete_dict1_word(dict1* dictionary, key_t delete_key){
	object_t* del_obj = delete(dictionary->words, delete_key);
	free(del_obj);
}