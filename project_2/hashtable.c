#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int HT_SIZE = MAX_HT_SIZE;

/*
* Distraction function that assigns the specified key an index from the interval <0,HT_SIZE-1>.
*/
int get_hash(char *key) {
  int result = 1;
  int length = strlen(key);
  for (int i = 0; i < length; i++) {
    result += key[i];
  }
  return (result % HT_SIZE);
}

/*
 * Table initialization — called before the table is used for the first time.
 */
void ht_init(ht_table_t *table) {
    for (int i = 0; i < HT_SIZE; i++){
        (*table)[i] = NULL;
    }
}

/*
* Search for an element in a table.
* If successful, returns a pointer to the found element; otherwise returns NULL value.
 */
ht_item_t *ht_search(ht_table_t *table, char *key) {
    if(table != NULL){
        ht_item_t *item = (*table)[get_hash(key)];
        while(item != NULL){
            if(item->key == key){
                return item;
            }
            item = item->next;
        }
    }
    
    return NULL;
}

/*
* Inserting a new element into the table.
* If the element with the given key already exists in the table, replace its value.
 */
void ht_insert(ht_table_t *table, char *key, float value) {
    if(table != NULL){
        ht_item_t *item = ht_search(table, key); 

        if(item != NULL){
            item->value = value;
        }
        else{
            item = malloc(sizeof(ht_item_t));
            ht_item_t *tmp = (*table)[get_hash(key)];
            
            if(item != NULL){
                item->key = key;
                item->value = value;
                item->next = tmp;
                (*table)[get_hash(key)] = item;
            }
        }  
    }
}

/*
* Getting a value from a table.
*
* If successful, the function returns a pointer to the value of the element, otherwise NULL.
*/
float *ht_get(ht_table_t *table, char *key) {
    if(table != NULL){
        ht_item_t *item = ht_search(table, key);
        
        if(item != NULL){
            return &item->value;
        }
    }
    return NULL;
}

/*
* Deleting an element from the table.
* The function will correctly release all allocated resources assigned to the given element.
* If the element does not exist, do nothing.
*/
void ht_delete(ht_table_t *table, char *key) {
    if(table != NULL){
        ht_item_t *act_item = (*table)[get_hash(key)];
        ht_item_t *prev_item = act_item;

        while(act_item){
            if(act_item->key == key && prev_item == act_item){
                (*table)[get_hash(key)] = act_item->next;
                free(act_item);
                return;
            }
            else if(act_item->key == key && prev_item != act_item){
                prev_item->next = act_item->next;
                free(act_item);
                return;
            }

            act_item = act_item->next;
        }
    }
}

/*
* Deleting all elements from the table.
* The function will correctly free all allocated resources and bring the table to the po state initialization.
*/
void ht_delete_all(ht_table_t *table) {
    if(table != NULL){
        for (int i = 0; i < HT_SIZE; i++){
            while((*table)[i] != NULL){
                ht_delete(table, (*table)[i]->key);
            }
        }
    }
}