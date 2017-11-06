typedef char* key_t;
typedef char object_t;
typedef struct tree_node_t
{
    key_t key;
    struct tree_node_t *left;
    struct tree_node_t *right;
} tree_node;

tree_node *create_tree(void);
tree_node *create_node(void);
object_t *find(tree_node *tree, key_t query_key);
object_t *delete(tree_node *tree, key_t delete_key);
int insert(tree_node *tree, key_t new_key, object_t *new_object);
int pre_print(tree_node *node);
int in_print(tree_node *node);
int post_print(tree_node *node);
