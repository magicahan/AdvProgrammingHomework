#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tree.h"

#define MAX_WORD_LEN 50
#define MAX_LINE_LEN 550

tree_node *create_tree(void)
{
    tree_node *node = create_node();
    node->left = NULL;
    return node;
}

tree_node *create_node(void)
{
    tree_node *node = (tree_node *)malloc(sizeof(tree_node));
    node->key = 0;
    return node;
}

object_t *find(tree_node *tree, key_t query_key){
    tree_node *tmp_node;
    int flag;
    if( tree->left == NULL)
        return "\0";
    else{
        tmp_node = tree;
        while( tmp_node->right != NULL ){
            if( (flag = strcmp(query_key, tmp_node->key))<0 )
                tmp_node = tmp_node->left;
            else
                tmp_node = tmp_node->right;
        }
        if( (flag=strcmp(tmp_node->key, query_key))==0 )
            return( (object_t *) tmp_node->left );
        else
            return "\0";
    }
}

int insert(tree_node *tree, key_t new_key, object_t *new_object){
    tree_node *tmp_node;
    int flag;

    if (tree->left == NULL){     /* insert data if only root node */
        //tree->left = malloc(sizeof(object_t *));
        printf("init\n");
        tree->left = malloc(sizeof(char)*MAX_WORD_LEN);
        strcpy((char*)tree->left, new_object);
        tree->key = malloc(sizeof(object_t)*MAX_WORD_LEN);
        strcpy(tree->key, new_key);
        tree->right = NULL;
    }
    else{                       /* else traverse tree to leaf node */
        tmp_node = tree;
        printf("tmp node is %s\n", tmp_node->key);
        while (tmp_node->right != NULL){
            if ( (flag = strcmp(new_key, tmp_node->key))<0 )
                tmp_node = tmp_node->left;
            else
                tmp_node = tmp_node->right;
        }

        printf("new old start\n");
        printf("%s %s %d\n", new_key, tmp_node->key, strcmp(new_key, tmp_node->key));
        if ( (flag = strcmp(new_key, tmp_node->key))==0  )  /* if key exists don't insert */
            return -1;

        tree_node *old_leaf, *new_leaf;

        printf("new old pass\n");
        old_leaf = create_node();
        old_leaf->left = malloc(sizeof(char)*MAX_LINE_LEN*MAX_WORD_LEN);
        old_leaf->key = malloc(sizeof(char)*MAX_WORD_LEN);
        strcpy((char*)old_leaf->left, (char*)tmp_node->left);
        strcpy(old_leaf->key, tmp_node->key);
        old_leaf->right = NULL;

        new_leaf = create_node();
        if(!new_leaf)
            return -2;
        new_leaf->left = malloc(sizeof(char)*MAX_LINE_LEN*MAX_WORD_LEN);
        new_leaf->key = malloc(sizeof(char)*MAX_WORD_LEN);
        strcpy((char*)new_leaf->left, (char*)new_object);
        strcpy(new_leaf->key, new_key);
        new_leaf->right = NULL;

        if ( (flag = strcmp(new_key, tmp_node->key))>0  )
        {
            tmp_node->left = old_leaf;
            tmp_node->right = new_leaf;
            strcpy(tmp_node->key, new_key);
        }
        else
        {
            tmp_node->left = new_leaf;
            tmp_node->right = old_leaf;
        }
    }
    return 0;
}

object_t *delete(tree_node *tree, key_t delete_key){
  
 tree_node  *tmp_node, *upper_node, *other_node;
 object_t  *deleted_object;
 int flag;

  if( tree->left == NULL )
    return( NULL );
  else if( tree->right == NULL ){
    if (strcmp(tree->key, delete_key)==0){
      deleted_object = (object_t *) tree->left;
      tree->left = NULL;
      return( deleted_object );
    }
    else
      return( NULL );}
else{
    tmp_node = tree;
    while( tmp_node->right != NULL ){
      upper_node = tmp_node;
      if( (flag=strcmp(delete_key, tmp_node->key))<0 ){
        tmp_node   = upper_node->left;
        other_node = upper_node->right;
      }
      else{
        tmp_node   = upper_node->right;
        other_node = upper_node->left;
      }
    }
if( strcmp(tmp_node->key, delete_key)!=0 )
      return( NULL );
else{
      upper_node->key   = other_node->key;
      upper_node->left  =  other_node->left;
      upper_node->right = other_node->right;
      deleted_object = (object_t *) tmp_node->left;
      return( deleted_object );
    }}}

int in_print(tree_node *node)
{
    if(node!=NULL && node->right!=NULL)
    {
        in_print(node->left);
        in_print(node->right);
    }
    else if(node!=NULL)
    {
        printf("%s: %s\n",node->key, (object_t*)node->left);
    }
    return 0;
}

