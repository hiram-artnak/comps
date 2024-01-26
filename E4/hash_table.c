#include "hash_table.h"
#include "linked_list.h"
#include <string.h>

#define HASH_TABLE_SIZE 1051

typedef struct key_value{
    char *key;
    void *value;
    key_value *next;
} key_value;

typedef struct key_valueList{
    key_value *head;
    key_value *tail;
    int size;
    destroy_data destroy;
} key_valueList;

key_value *key_value_create(char *key, void *value){
    key_value *kv = f_malloc(sizeof(key_value));
    kv->key = f_malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(kv->key, key);
    kv->value = value;
    return kv;
}

void key_value_destroy(key_value *kv,  destroy_data destroy){
    if (destroy != NULL) {
        destroy(kv->value);
    }
    f_free(kv->key);
    f_free(kv);
}


key_valueList *key_value_list_create(destroy_data destroy){
    key_valueList *list = f_malloc(sizeof(key_valueList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->destroy = destroy;
    return list;
}

void key_value_list_destroy(key_valueList *list){
    key_value *node = list->head;
    while (node != NULL) {
        key_value *next = node->next;
        key_value_destroy(node, list->destroy);
        node = next;
    }
    f_free(list);
}

void key_value_list_push_back(key_valueList *list, char *key, void *value){
    key_value *kv = key_value_create(key, value);
    if (list->tail != NULL) {
        list->tail->next = kv;
    }
    list->tail = kv;
    if (list->head == NULL) {
        list->head = kv;
    }
    list->size++;
}

void key_value_list_remove(key_valueList *list, char *key){
    key_value *node = list->head;
    key_value *prev = NULL;
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            if (prev != NULL) {
                prev->next = node->next;
            }
            if (list->head == node) {
                list->head = node->next;
            }
            if (list->tail == node) {
                list->tail = prev;
            }
            key_value_destroy(node, list->destroy);
            list->size--;
            return;
        }
        prev = node;
        node = node->next;
    }
}

void *key_value_list_get(key_valueList *list, char *key){
    key_value *node = list->head;
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

typedef struct hash_table{
    int buckets;
    void (*destroy)(void *data);
    key_valueList **table;
} hash_table;

unsigned int hash(char *key){
    const char *c = key;
    unsigned int hash = 0;
    while(*c != '\0'){
        unsigned int aux;
        hash = (hash << 4) + (*c);
        if((aux & 0xF0000000) != 0){
            hash = hash ^ (aux >> 24);
            hash = hash ^ aux;
        }
        c++;
    }
}

hash_table *hash_table_create(destroy_data destroy){
    hash_table *table = f_malloc(sizeof(hash_table));
    table->buckets = HASH_TABLE_SIZE;
    table->destroy = destroy;
    table->table = f_malloc(sizeof(key_valueList *) * table->buckets);
    for (int i = 0; i < table->buckets; i++) {
        table->table[i] = key_value_list_create(destroy);
    }
    return table;
}

void hash_table_destroy(hash_table *table){
    for (int i = 0; i < table->buckets; i++) {
        key_value_list_destroy(table->table[i]);
    }
    f_free(table->table);
    f_free(table);
}
void hash_table_insert(hash_table *table, char *key, void *value){
    unsigned int index = hash(key) % table->buckets;
    key_value_list_push_back(table->table[index], key, value);
}

void *hash_table_get(hash_table *table, char *key){
    unsigned int index = hash(key) % table->buckets;
    return key_value_list_get(table->table[index], key);
}
void hash_table_remove(hash_table *table, char *key){
    unsigned int index = hash(key) % table->buckets;
    key_value_list_remove(table->table[index], key);
}

int hash_table_is_member(hash_table *table, char *key){
    unsigned int index = hash(key) % table->buckets;
    return key_value_list_get(table->table[index], key) != NULL;
}