#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "tree.h"
#include "rbtree.h"

int main(){
	// tree_node* test, *test1, *test2, *test3, *test4;
	// test = malloc(sizeof(tree_node));
	// test1 = malloc(sizeof(tree_node));
	// test2 = malloc(sizeof(tree_node));
	// test3 = malloc(sizeof(tree_node));
	// test->left = test1;
	// test->key = "t1";
	// test1->key = "t2";
	// test2->key = "t3";
	// tree_node* temp;
	// temp = test1;
	// temp = test2;
	// printf("%s\n", test->left->key);
	// test3->key="test";
	// if(test3->key == NULL){
	// 	printf("this is null;\n");
	// }
	// if(test4==NULL){
	// 	tree_node* test5 = test4;
	// 	printf("test pointer\n");

	rbtree_node *tt1, *tt2;
	tt1 = malloc(sizeof(rbtree_node));
	create_node(tt1);
	tt1->parent=NULL;
	insert(tt1, "a", "working status");
	printf("tt1 is %s\n", tt1->key);
	insert(tt1, "b", "fruit");
	insert(tt1, "c", "working status");
	insert(tt1, "d", "fruit");
	insert(tt1, "e", "enter");
	insert(tt1, "f", "function");
	printf("insertion passed\n");
	Delete_rbt(tt1, "c");
	if(strcmp("a", "b")<0){
		printf("yes\n");
	}
	else{
		printf("no\n");
	}

	printf("tt1 right key is %s\n", tt1->right->key);
	printf("%s, %s %d\n", tt1->key, tt1->data, tt1->color);
	printf("%s, %s %d\n", tt1->left->key, tt1->left->data, tt1->left->color);
	printf("%s, %s %d\n", tt1->right->key, tt1->right->data, tt1->right->color);
	printf("%s, %s %d\n", tt1->right->left->key, tt1->right->left->data, tt1->right->left->color);
	printf("%s, %s %d\n", tt1->right->right->key, tt1->right->right->data, tt1->right->right->color);

	int test[5] = {1, 2, 3, 4, 5};
	&test[2] = test[3];
	printf("test the last elem is %d\n", test[3]);
	return 0;
}