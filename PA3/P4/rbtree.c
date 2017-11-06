#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "rbtree.h"

#define MAX_WORD_LEN 50
#define MAX_LINE_LEN 550

// int main(){
// 	return 0;
// }

void create_tree(rbtree_node* node){
    create_node(node);
}

void create_node(rbtree_node* node){
    node->key = NULL;
    node->color = red;
    node->left=malloc(sizeof(rbtree_node));
    node->left->color = black;
    node->left->key=NULL;
    node->left->parent=node;
    node->right=malloc(sizeof(rbtree_node));
    node->right->color=black;
    node->right->parent=node;
    node->right->key=NULL;
}

object_rbt* find(key_rbt query_key, rbtree_node *node){
  if (node->key == NULL || strcmp(node->key, query_key)==0)
    return node->data;
  else if (strcmp(node->key, node->key)<0)
    return find(query_key, node->left);
  else
    return find(query_key, node->right);
}


void insert(rbtree_node* root, key_rbt key, object_rbt* val){
	/*firstly insert in normal BST way*/
  if (root->key == NULL){
	create_node(root);
	root->key = malloc(sizeof(key_rbt)*MAX_WORD_LEN);
  	strcpy(root->key, key);
  	root->data = malloc(sizeof(key_rbt)*MAX_WORD_LEN*MAX_LINE_LEN);
  	strcpy(root->data, val);
  	/*then consider each case*/
  	insert_case1(root);
  }
  else if (strcmp(key, root->key)<0){
    insert(root->left, key, val);
}
  else if (strcmp(key, root->key)>0){
  	insert(root->right, key, val);
  }
}

void insert_case1(rbtree_node *n){ 
   if (n->parent == NULL) {
        n->color = black; 
   }
   else 
       insert_case2(n); 
} 

void insert_case2(rbtree_node *n){
 if (n->parent->color == black){
  return; /* Tree is still valid */
 }
 else{
  insert_case3(n);
}
}

void insert_case3(rbtree_node *n){
 rbtree_node *u = uncle(n);
 rbtree_node *g;

 if ((u->key != NULL) && (u->color == red)) {
  n->parent->color = black;
  u->color = black;
  g = grandparent(n);
  g->color = red;
  insert_case1(g);
 } 
 else {
  insert_case4(n);
 }
}

void insert_case4(rbtree_node *n){
  rbtree_node *g = grandparent(n);

  if(g == NULL){
  	return;
  }

  if ((n == n->parent->right) && (n->parent == g->left)) {
    left_rotation(n->parent);
    n = n->left;

  } else if ((n == n->parent->left) && (n->parent == g->right)) {
    right_rotation(n->parent);
    n = n->right;
  }
  insert_case5(n);
}


void insert_case5(rbtree_node *n){
  rbtree_node *g = grandparent(n);

  n->parent->color = black;
  g->color = red;
  if (n == n->parent->left)
    right_rotation(g);
  else
    left_rotation(g);
}


rbtree_node* grandparent(rbtree_node* n){
	rbtree_node* p;
	rbtree_node* g;
	if((p = n->parent)!=NULL){
		if((g = p->parent)!=NULL){
			return g;
		}
	}
return NULL;
}


rbtree_node* uncle(rbtree_node* n){
	rbtree_node* p;
	rbtree_node* g;
	rbtree_node* u;

	p = n->parent;
	g = grandparent(n);
if(g!=NULL){
		if(g->left == p){
			return g->right;
		}
		else if(g->right == p){
			return g->left;
		}
	}
 u = malloc(sizeof(rbtree_node));
 u->color = black;

 return u;
}

rbtree_node* sibling(rbtree_node* n){
	rbtree_node* p;
	rbtree_node* s;

	p = n->parent;
	if(p != NULL){
		if(n == p->left){
		 s = p->right;
		}
		else{
		s = p->left;
		}
	}
	else{
		s = malloc(sizeof(rbtree_node));
		s->color = black;
		s->key = NULL;
	}
	return s;
}

void left_rotation(rbtree_node *n){
     rbtree_node *tmp_node; 
     int temp_color;
     key_rbt tmp_key = malloc(sizeof(key_rbt)*MAX_WORD_LEN);
     tmp_node = n->left;
     strcpy(tmp_key, n->key);
     n->left = n->right; 
     strcpy(n->key, n->right->key);
     temp_color = n->right->color;
     n->left->color = n->color;
     n->color = temp_color;
     n->right = n->left->right; 
     n->right->parent=n;
     n->left->right = n->left->left; 
     n->left->left = tmp_node; 
     strcpy(n->left->key, tmp_key); 
}

void right_rotation(rbtree_node *n){ 
   rbtree_node *tmp_node; 
   key_rbt tmp_key; 
   int temp_color;
   tmp_node = n->right; 
   strcpy(tmp_key, n->key); 
   n->right = n->left; 
   strcpy(n->key, n->left->key);
   temp_color = n->right->color; 
   n->right->color = n->color;
   n->color = temp_color;
   n->left = n->right->left; 
   n->left->parent=n;
   n->right->left = n->right->right; 
   n->right->right = tmp_node; 
   strcpy(n->right->key, tmp_key); 
}

rbtree_node *FindMin(rbtree_node* root){
	if(root->left->key == NULL){
		return root;
	}
	else{
		return FindMin(root->left);
	}
}


rbtree_node *Delete_BST(rbtree_node *root, key_rbt key){
 if (root->key == NULL) 
      return root;
 else if (strcmp(key, root->key)<0) 
       root = Delete_BST(root->left,key);
 else if (strcmp(key, root->key)>0) 
       root = Delete_BST(root->right,key);
 else{                                                            
    if (root->left->key != NULL && root->right->key != NULL){
    rbtree_node *temp = root;
    root = FindMin(root->right);
    strcpy(temp->key, root->key);
    strcpy(temp->data, root->data);
  }
  }
  return root;
}

void remove_dblack(rbtree_node* u){
		/*Now take the sibling*/
		rbtree_node* s = sibling(u);
		printf("color is %d %s\n", s->right->color, s->right->key);
		/*if s is black*/
		if(s->color == black){
			/*for left left case*/
			if((s == u->parent->left)&&(s->left->color==red)){
				s->left->color = black;
				printf("right key is %s\n", u->parent->right->key);
				right_rotation(u->parent);
			}
			/*for right right case*/
			else if((s == u->parent->right)&&(s->right->color==red)){
				//s->right->color = s->color;
				printf("right key is %s\n", u->parent->right->key);
				left_rotation(u->parent);
				//u->color = black;

			}
			/*for left right case*/
			else if((s == u->parent->left)&&(s->right->color==red)&&(s->left->color!=red)){
				s->left->color = black;
				printf("right key is %s\n", u->parent->right->key);
				left_rotation(s);
				right_rotation(u->parent);
			}
			/*for right left case*/
			else if((s == u->parent->left)&&(s->right->color==red)&&(s->left->color!=red)){
				s->right->color = black;
				printf("right key is %s\n", u->parent->right->key);
				right_rotation(s);
				left_rotation(u->parent);
			}
			
			/*s is black and both of its children are black*/
			if((s->left->color==black)&&(s->right->color==black)){
				s->color = red;
				remove_dblack(s->parent);
			}
		}
		else if(s->color==red){
			/*firstly recolor*/
			s->color = black;
			s->parent->color = red;

			/*for the left case*/
			if(s->parent->left == s){
				right_rotation(s->parent);
				if(u->left->key!=NULL){
					u->right->color = red;
				}
				u->color = black;
			}
			else if(s->parent->right == s){
				printf("right key is %s\n", u->right->key);
				left_rotation(s->parent);
				if(u->right->key!=NULL){
					u->right->color = red;
				}
				u->color = black;
			}

		}
}


void Delete_rbt(rbtree_node *root, key_rbt key){
	/*firstly get the BST result*/
	rbtree_node *del_v = Delete_BST(root, key);
	printf("BST del\n");
	rbtree_node *suc_u = (rbtree_node *)malloc(sizeof(rbtree_node));
	create_node(suc_u);
	suc_u->color=black;
	rbtree_node *s;
	printf("%s\n", del_v->key);

	if(del_v->left->key!=NULL){
		suc_u = del_v->left;
	}
	else if(del_v->right->key != NULL){
		suc_u = del_v->right;
	}

	printf("del_v\n");
	/*if we are at the root*/
	if(del_v->parent == NULL){
		suc_u->color = black;
		suc_u->parent = NULL;
		root = suc_u;
	}

	/*consider the second case*/
	if((suc_u->color==red)||(del_v->color==red)){
		suc_u->color = black;
		/*change the grandpareent's child*/
		if(del_v->parent->left==del_v){
			del_v->parent->left=suc_u;
		}
		else{
			del_v->parent->right=suc_u;
		}
		suc_u->parent = del_v->parent;
	}
	/*consider the last case*/
	else if((suc_u->color==black)&&(del_v->color==black)){
		suc_u->color = double_black;
		/*change the grandpareent's child*/
		if(del_v->parent->left==del_v){
			del_v->parent->left=suc_u;
		}
		else{
			del_v->parent->right=suc_u;
		}
		suc_u->parent = del_v->parent;
		printf("del v parent is %s\n", del_v->parent->key);
		printf("now remove dbblakc\n");
		remove_dblack(suc_u);
	}
	free_node(del_v);

	}

void free_node(rbtree_node* node){
	printf("enter freed\n");
	printf("%s\n", node->key);
	if(node->key!=NULL){
		printf("key free");
	free(node->key);
	printf("data free;\n");
	free(node->data);
	}
	printf("key freed\n");
	free(node);
}


