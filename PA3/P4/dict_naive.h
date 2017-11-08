#include "tree.h"

typedef struct dict1_{
	tree_node* words;
} dict1;

dict1* create_dict1(void);
object_t* find_dict1(dict1* dictionary, key_t query_key);
int insert_dict1_word(dict1* dictionary, key_t key, object_t* defn);
void in_print_dict1(dict1* dictionary);
void delete_dict1_word(dict1* dictionary, key_t delete_key);