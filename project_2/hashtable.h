#ifndef IAL_HASHTABLE_H
#define IAL_HASHTABLE_H

#include <stdbool.h>

/*
* Maximum field size for table implementation.
* Functions working with the table consider the size HT_SIZE.
*/
#define MAX_HT_SIZE 101

/*
* The size of the table with which the implemented functions work.
*/
extern int HT_SIZE;

typedef struct ht_item {
  char *key;            
  float value;         
  struct ht_item *next;
} ht_item_t;

typedef ht_item_t *ht_table_t[MAX_HT_SIZE];

int get_hash(char *key);
void ht_init(ht_table_t *table);
ht_item_t *ht_search(ht_table_t *table, char *key);
void ht_insert(ht_table_t *table, char *key, float data);
float *ht_get(ht_table_t *table, char *key);
void ht_delete(ht_table_t *table, char *key);
void ht_delete_all(ht_table_t *table);

#endif
