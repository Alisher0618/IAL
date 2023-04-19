#include "docs/btree.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Initialization of tree
 */
void bst_init(bst_node_t **tree) {  
    *tree = NULL;
}

/*
 * Searching node in tree
 */
bool bst_search(bst_node_t *tree, char key, int *value) {
    if(tree != NULL){
        if(tree->key == key){
            *value = tree->value;
            return true;
        }else if(tree->key < key){
            return bst_search(tree->right, key, value);
        }else{
            return bst_search(tree->left, key, value);
        }
    }
    return false;
}

/*
* Inserting node into tree
*/
void bst_insert(bst_node_t **tree, char key, int value) {
    if(*tree != NULL){
        if(key == (*tree)->key){
            (*tree)->value = value;
        }
        else if(key < (*tree)->key){
            bst_insert(&(*tree)->left, key, value);
        }
        else if(key > (*tree)->key){
            bst_insert(&(*tree)->right, key, value);
        }
        
    }else{
        *tree = malloc(sizeof(struct bst_node));
        (*tree)->key = key;
        (*tree)->value = value;
        (*tree)->left = NULL;
        (*tree)->right = NULL;
    }
}

/*
* Helper function that replaces the node with the rightmost child.
*/
void bst_replace_by_rightmost(bst_node_t *target, bst_node_t **tree) {
    bst_node_t *node = *tree;
    if((*tree)->right == NULL){
        target->key = (node)->key;
        target->value = (node)->value;
        (*tree) = (node)->left;     
        free(node);
    }else{
        bst_replace_by_rightmost(target, &(*tree)->right);
    }
}

/*
* Deleting node from tree
*/
void bst_delete(bst_node_t **tree, char key) {
    if(*tree != NULL){
        if(key < (*tree)->key){
            bst_delete(&(*tree)->left, key);
        }
        else if(key > (*tree)->key){
            bst_delete(&(*tree)->right, key);
        }      
        else{
            if((*tree)->right != NULL && (*tree)->left != NULL){
                bst_replace_by_rightmost(*tree, &(*tree)->left);
            }
            else if((*tree)->right == NULL && (*tree)->left == NULL){
                free(*tree);
                *tree = NULL;
            }
            else{
                bst_node_t *node;
                if((*tree)->left != NULL){
                    node = (*tree)->left;
                    free(*tree);
                    *tree = node;
                }else if((*tree)->right != NULL){
                    node = (*tree)->right; 
                    free(*tree);
                    *tree = node;
                }
                
            }
        }
    }
}

/*
* Cancelling the entire tree
*/
void bst_dispose(bst_node_t **tree) {
    if(*tree != NULL){
        bst_dispose(&(*tree)->left);
        bst_dispose(&(*tree)->right);
        free(*tree);
        bst_init(tree);
    }
}

/*
* Preorder tree travelsal
*/
void bst_preorder(bst_node_t *tree) {
    if(tree != NULL){
        bst_print_node(tree);
        bst_preorder(tree->left);
        bst_preorder(tree->right);
    }
}

/*
* Inorder tree travelsal
*/
void bst_inorder(bst_node_t *tree) {
    if(tree != NULL){
        bst_inorder(tree->left);
        bst_print_node(tree);
        bst_inorder(tree->right);
    }
}
/*
* Postorder tree travelsal
*/
void bst_postorder(bst_node_t *tree) {
    if(tree != NULL){
        bst_postorder(tree->left);
        bst_postorder(tree->right);
        bst_print_node(tree);
    }
}
