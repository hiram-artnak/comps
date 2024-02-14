#ifndef HASH_TABLE
#define HASH_TABLE

#include "linked_list.h"
#include "types.h"
typedef struct hash_table hash_table;
typedef struct hash_table_entry hash_table_entry;


hash_table *hash_table_create(destroy_data destroy);
void hash_table_destroy(hash_table *table);
void hash_table_insert(hash_table *table, char *key, void *value);
void *hash_table_get(hash_table *table, char *key);
void hash_table_delete(hash_table *table, char *key);
int hash_table_is_member(hash_table *table, char *key);


#endif