#ifndef HASH_TABLE
#define HASH_TABLE

#include "linked_list.h"

typedef struct hash_table hash_table;
typedef struct key_value key_value;

void key_value_destroy(key_value *kv, destroy_data destroy); // Used in the destroy function of the hash table

typedef void (*destroy_data)(void *data);

hash_table *hash_table_create(destroy_data destroy);
void hash_table_destroy(hash_table *table);
void hash_table_insert(hash_table *table, char *key, void *value);
void *hash_table_get(hash_table *table, char *key);
void hash_table_remove(hash_table *table, char *key);
int hash_table_is_member(hash_table *table, char *key);


#endif