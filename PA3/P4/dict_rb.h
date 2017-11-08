#include "rbtree.h"

typedef struct dict2_{
	rbtree_node* words;
} dict2;

dict2* create_dict2(void);
object_rbt* find_dict2(dict2* dictionary, key_rbt query_key);
int insert_dict2_word(dict2* dictionary, key_rbt key, object_rbt* defn);
void in_print_dict2(dict2* dictionary);
void delete_dict2_word(dict2* dictionary, key_rbt delete_key);