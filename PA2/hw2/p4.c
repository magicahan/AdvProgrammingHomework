#include<stdio.h>
#include<stdlib.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef struct tree_node{
	struct tree_node *left, *right;
	int data;
} Tree_node;

typedef struct stack_elem_{
	Tree_node *data;
	struct stack_elem_ *next;
	//stack_elem *prev;
} stack_elem;

typedef struct stack_{
	stack_elem *head;
	stack_elem *tail;
	int size;
	int (*des)(void *data);
} stack;

int tree_des(void *data){
	Tree_node* p = (Tree_node*) data;
	free(p);
	return 0;
}

void stack_destroy(stack *stack_list){
  void *data;
  while (stack_list->size > 0){
  		data = stack_list->tail->data;
  		free(stack_list->tail);
    	stack_list->des(data);
    	stack_list->size -= 1;
  }
}

void stack_pop(stack *stack_list){
	void *data;
	stack_elem* temp;
	if(stack_list->size > 0){
		data = stack_list->head->data;
		temp = stack_list->head;
		stack_list->head = stack_list->head->next;
		stack_list->size -= 1;
		free(temp);
		free(data);
	}
}

void stack_push(Tree_node* tree, stack *stack_list){
	stack_elem* new_head;
	new_head = malloc(sizeof(stack_elem));
	if(stack_list->head != NULL){
		stack_elem* next = stack_list->head;
		new_head->data = tree;
		new_head->next = next;
		/*next->prev = new_head;*/
		stack_list->head = new_head;
		stack_list->size += 1;
	}
	else{
		new_head->data = tree;
		stack_list->head = new_head;
		stack_list->head->next = NULL;
		stack_list->size += 1;
	}
}

int test_binary_nonrec(Tree_node* cur_node){
	stack *stack_tree;
	stack_elem* cur_elem;
	stack_tree = malloc(sizeof(stack));

	int exit = 0;

	/*initialize the stack tree*/
	stack_tree->size = 0;
	stack_tree->head = NULL;

	cur_elem = malloc(sizeof(stack_elem));
	cur_elem->data = cur_node;
	//stack_push(cur_node, stack_tree);
	while(exit != 1){
		if(cur_node != NULL){
			stack_push(cur_node, stack_tree);
			cur_node = cur_node->left;
		}
		else{
			if(stack_tree->head->next != NULL){
			if(stack_tree->head->data->data > stack_tree->head->next->data->data){
				printf("bigger %d\n", stack_tree->size);
				return -1;
			}
		}
		printf("pass\n");
			stack_pop(stack_tree);
			cur_node = stack_tree->head->data->right;
			if(cur_node != NULL){
				if(cur_node->data < stack_tree->head->data->data){
					return -1;
				}
			}
			stack_pop(stack_tree);
			if(stack_tree->size == 0){
				exit = 1;
			}
		}
	}
	return 1;
}

int* traverse_inorder(Tree_node* cur_node){
	int* rv, *rv_left, *rv_right;
	rv = malloc(sizeof(int) * 3);
	Tree_node *left, *right;
	left = cur_node->left;
	right = cur_node->right;

	rv[0] = 1;
	rv[1] = cur_node->data;
	rv[2] = cur_node->data;
	if(left != NULL){
		printf("not\n");
		rv_left = traverse_inorder(left);
	}
	else{
		printf("empty\n");
	}
	if(right != NULL){
		rv_right = traverse_inorder(right);
	}
	/*the base case where the node is a leaf*/
	if(left == NULL && right == NULL){
		return rv;
	}
	if(rv_left != NULL){
		printf("yes\n");
		if(rv_left[1] > cur_node->data){
			rv[0] = 0;
		}
		rv[0] = MIN(rv[0], rv_left[0]);
		rv[1] = MAX(rv_left[1], rv[1]);
		rv[2] = MIN(rv_left[2], rv[2]);
	}
	if(rv_right != NULL){
		if(rv_right[2] < cur_node->data){
			rv[0] = 0;
		}
		rv[0] = MIN(rv[0], rv_right[0]);
		rv[1] = MAX(rv_right[1], rv[1]);
		rv[2] = MIN(rv_right[2], rv[2]);
	}
	free(rv_left);
	free(rv_right);
	return rv;
}

int test_binary_rec(Tree_node* cur_node){
	int* rv_list = traverse_inorder(cur_node);
	int rv = rv_list[0];
	return rv;
}

int main(int argc, char **argv){
	Tree_node *tree1, *tree2, *tree3, *tree4, *tree5;
	tree1 = malloc(sizeof(Tree_node));
	tree2 = malloc(sizeof(Tree_node));
	tree3 = malloc(sizeof(Tree_node));
	tree4 = malloc(sizeof(Tree_node));
	tree5 = malloc(sizeof(Tree_node));
	tree1->data = 1;
	tree2->data = -1;
	tree3->data = 3;
	tree4 -> data = -3;
	tree5 -> data = 0;
	tree1->left = tree2;
	tree1->right = tree3;
	tree2->left = tree4;
	tree2-> right = tree5;
	tree3->left = NULL;
	tree3->right = NULL;
	tree4->left = NULL;
	tree4->right = NULL;
	tree5->left = NULL;
	tree5->right = NULL;
	printf("pass");
	int rv = test_binary_rec(tree1);
	printf("%d pass\n", rv);
	int rv2 = test_binary_nonrec(tree1);
	printf("%d %d\n", rv, rv2);
	return 0;
}


