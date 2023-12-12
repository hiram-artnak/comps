#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>
#include "utils.h"


typedef struct linked_list linked_list;

// Function to create/allocate a new linked list
linked_list *create_linked_list();

// Function to add an element to the end of the linked list
void append_to_linked_list(linked_list *list, void *data);

// Function to insert an element at a specific position in the linked list
void insert_at_linked_list(linked_list *list, void *data, size_t position);

// Function to remove an element from a specific position in the linked list
void *remove_from_linked_list(linked_list *list, size_t position);

// Function to get the element at a specific position in the linked list
void *get_from_linked_list(const linked_list *list, size_t position);

// Function to destroy the linked list and free memory
void destroy_linked_list(linked_list *list);

// Function to print the linked list
void print_linked_list(linked_list *list, generic_print print_fn);

// Map over a linked list
linked_list *map_linked_list(linked_list *list, void*(map_function)(const void *));

// Reduce the linked list (folding from the left!)
void *reduce_linked_list(const linked_list *list, void *(*reduce_function)(const void *, const void *));

#endif //LINKED_LIST_H
