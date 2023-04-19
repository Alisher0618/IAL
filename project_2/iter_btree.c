#include "docs/btree.h"
#include "docs/stack.h"
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
* If successful, the function returns the value true and writes to the value variable
* the value of the given node. Otherwise, function returns false and a variable
* value remains unchanged.
*/
bool bst_search(bst_node_t *tree, char key, int *value) {
    if(tree != NULL && value != NULL){
        bst_node_t *ptr = tree;
        while(ptr != NULL){
            if(key == ptr->key){
                *value = ptr->value;
                return true;
            }else if(key < ptr->key){
                ptr = ptr->left;
            }else if(key > ptr->key){
                ptr = ptr->right;
            }
        }
    }else{
        return false;
    }
    
    return false;
}

/*
* Inserting a node into the tree.
*
* If the node with the specified key already exists in the tree, replace its value.
* Otherwise, insert a new leaf node.
*
* The resulting tree must satisfy the search tree condition — left subtree
* of the node contains only smaller keys, the right one contains larger ones.
*/
void bst_insert(bst_node_t **tree, char key, int value) {
    while(*tree != NULL){
        if(key == (*tree)->key){
            (*tree)->value = value;
            (*tree)->key = key;
            return;
        }
        else if(key < (*tree)->key){
            tree = &(*tree)->left;
        }
        else if(key > (*tree)->key){
            tree = &(*tree)->right;
        }
        
    }

    *tree = malloc(sizeof(bst_node_t));

    if(*tree != NULL){   
        (*tree)->key = key;
        (*tree)->value = value;
        (*tree)->left = NULL;
        (*tree)->right = NULL;
    }

        
}

/*
* Helper function that replaces the node with the rightmost child.
*
* The key and value of the target node will be replaced by the key and value of the rightmost node of subtree
* The truest child will be removed. Function correctly frees all allocated resources of the removed node.
*
*/
void bst_replace_by_rightmost(bst_node_t *target, bst_node_t **tree) {
    if(target != NULL && *tree != NULL){
        while((*tree)->right != NULL){
            tree = &(*tree)->right;
        }
        bst_node_t *node = (*tree);

        target->key = (*tree)->key;
        target->value = (*tree)->value;    
        bst_delete(tree, node->key);
    }
}

/*
* Deleting node in tree
*
* If the node with the specified key does not exist, the function does nothing.
* If the removed node has one subtree, it will be inherited by the removed node's father.
* If the removed node has both subtrees, it is replaced by the rightmost node of the left subtree. 
* The function will correctly release all allocated resources of the removed node.
*/
void bst_delete(bst_node_t **tree, char key) {
    while(*tree != NULL){
        if(key < (*tree)->key){
            tree = &(*tree)->left;
        }
        else if(key > (*tree)->key){
            tree = &(*tree)->right;
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
* Canceling the entire tree.
*
* After cancellation, the entire tree will be in the same state as after initialization. 
* The function will correctly release all allocated resources of the interrupted ones nodes.
*/
void bst_dispose(bst_node_t **tree) {
    if (*tree != NULL) {
        stack_bst_t *stack = malloc(sizeof(stack_bst_t));
        if (stack != NULL) {
            stack_bst_init(stack);

            stack_bst_push(stack, *tree);

            while (1) {
                if(!stack_bst_empty(stack)){
                    *tree = stack_bst_pop(stack);

                    if ((*tree)->right != NULL) {
                        stack_bst_push(stack, (*tree)->right);
                    }
                    if ((*tree)->left != NULL) {
                        stack_bst_push(stack, (*tree)->left);
                    }

                    free(*tree);
                    *tree = NULL;
                }else{
                    break;
                }

            }
            free(stack);
        }   
    }
}

/*
* Helper function for iterative preorder.
*
* Traverses the left branch to the leftmost node of the subtree.
* Call bst_print_node on the processed nodes and store them in the node stack.
*/
void bst_leftmost_preorder(bst_node_t *tree, stack_bst_t *to_visit) {
    while(tree != NULL){
        stack_bst_push(to_visit, tree);
        bst_print_node(tree);
        tree = tree->left;
    }
}

/*
* Preorder tree travelsal
*/
void bst_preorder(bst_node_t *tree) {
    stack_bst_t *stack = malloc(sizeof(stack_bst_t));

    if (stack != NULL) {
        stack_bst_init(stack);
        bst_leftmost_preorder(tree, stack);

        while (1){
            if(!stack_bst_empty(stack)){
                tree = stack_bst_top(stack);
                stack_bst_pop(stack);
                bst_leftmost_preorder(tree->right, stack);
            }else{
                break;
            }
        }
        free(stack);
    }
}

/*
* Helper function for iterative inorder.
*
* Walks the left branch to the leftmost node of the subtree and stores the nodes in
* node stack.
*/
void bst_leftmost_inorder(bst_node_t *tree, stack_bst_t *to_visit) {
    bst_node_t *node = tree;

    while (node != NULL) {
        stack_bst_push(to_visit, node);
        node = node->left;
    }
}

/*
* Inorder tree travelsal
*/
void bst_inorder(bst_node_t *tree) {
    stack_bst_t *stack = malloc(sizeof(stack_bst_t));

    if (stack != NULL) {
        stack_bst_init(stack);
        bst_leftmost_inorder(tree, stack);

        while (1) {
            if(!stack_bst_empty(stack)){
                tree = stack_bst_top(stack);
                stack_bst_pop(stack);
                bst_print_node(tree);
                bst_leftmost_inorder(tree->right, stack);
            }else{
                break;
            }
        }
        free(stack);
    }   
}

/*
* Helper function for iterative postorder.
*
* Walks the left branch to the leftmost node of the subtree and stores the nodes in node stack. 
* It stores the information that the node was visited for the first time.
*/
void bst_leftmost_postorder(bst_node_t *tree, stack_bst_t *to_visit, stack_bool_t *first_visit) {
    while (tree != NULL) {
        stack_bst_push(to_visit, tree);
        stack_bool_push(first_visit, true);
        tree = tree->left;
    }
}

/*
* Postorder tree travelsal
*/
void bst_postorder(bst_node_t *tree) {
    stack_bst_t *stack = malloc(sizeof(stack_bst_t));

    if(stack == NULL){
        return;
    }
    stack_bool_t *b_stack = malloc(sizeof(stack_bool_t));

    if(b_stack != NULL){
        stack_bst_init(stack);
        stack_bool_init(b_stack);
        bst_leftmost_postorder(tree, stack, b_stack);

        while(1){
            if(!stack_bst_empty(stack)){
                tree = stack_bst_top(stack);
                if(stack_bool_pop(b_stack)){                   
                    stack_bool_push(b_stack, false);
                    bst_leftmost_postorder(tree->right, stack, b_stack);
                }else{                                                
                    stack_bst_pop(stack);
                    bst_print_node(tree);
                }
            }else{
                break;
            }
            
        }

    }
    free(stack);
    free(b_stack);
    
}
