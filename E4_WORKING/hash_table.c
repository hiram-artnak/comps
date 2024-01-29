#include "hash_table.h"
#include <string.h>
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

#define HASH_TABLE_SIZE 1051


typedef struct hash_table_entry{
    char *key;
    void *value;
    struct hash_table_entry *next;
} hash_table_entry;

typedef struct hash_table_list{
    hash_table_entry *head;
    hash_table_entry *tail;
    int size;
    destroy_data destroy;
} hash_table_list;

typedef struct hash_table{
    hash_table_list **table;
    int size;
    destroy_data destroy;
} hash_table;

hash_table_entry *hash_table_entry_create(char *key, void *value){
    hash_table_entry *entry = f_malloc(sizeof(hash_table_entry));
    // Copy the key
    entry->key = f_malloc(strlen(key) + 1);
    strcpy(entry->key, key);
    entry->value = value;
    entry->next = NULL;
    return entry;
}

hash_table_list *hash_table_list_create(destroy_data destroy){
    hash_table_list *list = f_malloc(sizeof(hash_table_list));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->destroy = destroy;
    return list;
}

hash_table *hash_table_create(destroy_data destroy){
    hash_table *table = f_malloc(sizeof(hash_table));
    table->table = f_malloc(sizeof(hash_table_list *) * HASH_TABLE_SIZE);
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        table->table[i] = hash_table_list_create(destroy);
    }
    table->size = 0;
    table->destroy = destroy;
    return table;
}

void hash_table_entry_destroy(hash_table_entry *entry, destroy_data destroy){
    if (destroy != NULL) {
        destroy(entry->value);
    }
    f_free(entry->key);
    f_free(entry);
}

void hash_table_list_destroy(hash_table_list *list){
    hash_table_entry *entry = list->head;
    while (entry != NULL) {
        hash_table_entry *next = entry->next;
        hash_table_entry_destroy(entry, list->destroy);
        entry = next;
    }
    f_free(list);
}

void hash_table_destroy(hash_table *table){
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        hash_table_list_destroy(table->table[i]);
    }
    f_free(table->table);
    f_free(table);
}

int hash_table_size(hash_table *table){
    return table->size;
}

int hash_table_empty(hash_table *table){
    return table->size == 0;
}

unsigned int hash(char *key){
    char *c = key; 
    unsigned int hash_value = 0;
    int i = 0; 
    while(*c != '\0'){
        unsigned int aux = 0;
        hash_value = (hash_value << 4) + (*c);
        if((aux & 0xF0000000) != 0){ 
            hash_value = hash_value ^ (aux >> 24); 
            hash_value = hash_value ^ aux; 
        }
        c++;
    }
    return hash_value;
}

void hash_table_list_push_back(hash_table_list *list, char *key, void *value){
    hash_table_entry *entry = hash_table_entry_create(key, value);
    if (list->head == NULL) {
        list->head = entry;
        list->tail = entry;
    } else {
        list->tail->next = entry;
        list->tail = entry;
    }
    list->size++;
}

void hash_table_insert(hash_table *table, char *key, void *value){
    if(table == NULL || key == NULL){
        printf("table or key is null\n");
        if(table == NULL){
            printf("table is null\n");
        }
        if(key == NULL){
            printf("key is null\n");
        }
        exit(1);
    }
    unsigned int index = hash(key) % HASH_TABLE_SIZE;
    hash_table_list *list = table->table[index];
    if (list == NULL){
        printf("list is null\n");
        exit(1);
    }
    hash_table_list_push_back(list, key, value);
    table->size++;
}

void *hash_table_list_get(hash_table_list *list, char *key){
    hash_table_entry *entry = list->head;
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;
}

void *hash_table_get(hash_table *table, char *key){
    unsigned int index = hash(key) % HASH_TABLE_SIZE;
    hash_table_list *list = table->table[index];
    return hash_table_list_get(list, key);
}

void hash_table_list_delete(hash_table_list *list, char *key){
    hash_table_entry *prev = NULL;
    hash_table_entry *entry = list->head;
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            if (prev == NULL) {
                list->head = entry->next;
            } else {
                prev->next = entry->next;
            }
            if (entry == list->tail) {
                list->tail = prev;
            }
            hash_table_entry_destroy(entry, list->destroy);
            list->size--;
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}

void hash_table_delete(hash_table *table, char *key){
    unsigned int index = hash(key) % HASH_TABLE_SIZE;
    hash_table_list *list = table->table[index];
    hash_table_list_delete(list, key);
    table->size--;
}

int hash_table_is_member(hash_table *table, char *key){
    unsigned int index = hash(key) % HASH_TABLE_SIZE;
    hash_table_list *list = table->table[index];
    return hash_table_list_get(list, key) != NULL;
}