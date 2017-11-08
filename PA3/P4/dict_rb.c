#include <stdio.h>
#include <stdlib.h>

#include "dict_rb.h"

dict2* create_dict2(void){
	dict2* dictionary;
	dictionary = malloc(sizeof(dict2));
	dictionary->words = malloc(sizeof(rbtree_node));
	create_rbtree(dictionary-> words);
	return dictionary;
}

object_rbt* find_dict2(dict2* dictionary, key_rbt query_key){
	object_rbt* find_obj;
	find_obj = find_rb(dictionary->words, query_key);
	return find_obj;
}

int insert_dict2_word(dict2* dictionary, key_rbt key, object_rbt* defn){
	int succ_flag;
	insert_rb(dictionary->words, key, defn);
	return 0;
}

void in_print_dict2(dict2* dictionary){
	in_print_rb(dictionary->words);
}

void delete_dict2_word(dict2* dictionary, key_rbt delete_key){
	Delete_rbt(dictionary->words, delete_key);
}