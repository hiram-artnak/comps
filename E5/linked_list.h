#ifndef LINKE_LIST_H
#define LINKE_LIST_H

#include "types.h"
// api for linked list

typedef struct linked_list linked_list;


linked_list *linked_list_create(destroy_data destroy);
void linked_list_destroy(linked_list *list);
void linked_list_clear(linked_list *list);
int linked_list_size(linked_list *list);
int linked_list_empty(linked_list *list);
void linked_list_push_front(linked_list *list, void *value);
void linked_list_push_back(linked_list *list, void *value);
void *linked_list_pop_front(linked_list *list);
void *linked_list_pop_back(linked_list *list);
void *linked_list_front(linked_list *list);
void *linked_list_back(linked_list *list);
void linked_list_insert(linked_list *list, int index, void *value);
void linked_list_delete(linked_list *list, int index);
void *linked_list_get(linked_list *list, int index);
void linked_list_print(linked_list *list, print_data print);

#endif