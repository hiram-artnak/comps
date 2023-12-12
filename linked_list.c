#include "linked_list.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

// Define a structure for a node in the linked list
typedef struct _linked_list_node {
    void *data;          // Pointer to the data of the node.
    struct _linked_list_node *next;   // Pointer to the next node in the list.
    struct _linked_list_node *prev;   // Pointer to the previous node in the list.
} linked_list_node;

linked_list_node *create_linked_list_node(){
    linked_list_node *node = malloc_or_fail(sizeof(linked_list_node), "Could not allocate linked_list_node\n");
    node->data = NULL;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void *destroy_linked_list_node(linked_list_node *node){
    if(node == NULL){
        log_error_and_die("Tried to destroy NULL linked_list_node\n");
    }
    void *data = node->data;
    node->next = NULL;
    node->prev = NULL;
    free(node);
    return data;
}

// Define a structure for the linked list
typedef struct linked_list{
    linked_list_node *head;     // Pointer to the first node in the list
    linked_list_node *tail;     // Pointer to the last node in the list
    size_t size;                // Number of nodes in the list
} linked_list;

// Function to create/allocate a new linked list
linked_list *create_linked_list(){
    linked_list *list = malloc_or_fail(sizeof(linked_list), "Could not allocate linked_list\n");
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

// Function to add an element to the end of the linked list
void append_to_linked_list(linked_list *list, void *data){
    if(list == NULL){
        log_error_and_die("Tried to append data to a NULL list\n");
    }

    // Make a node and set its values
    linked_list_node *new_node = create_linked_list_node();
    new_node->prev = list->tail;
    new_node->data = data;

    // Make this the tail of the list
    list->tail = new_node;

    // If the list was empty, make it the head
    if(list->size == 0) list->head = new_node;

    // Increase the size of the list
    list->size++;
}

// Function to insert an element at a specific position in the linked list
void insert_at_linked_list(linked_list *list, void *data, size_t position){
    if(list == NULL){
        log_error_and_die("Tried to insert data in a NULL list\n");
    }

    linked_list_node *new_node = create_linked_list_node();
    new_node->data = data;
    if (list->size == 0){ // Insert in empty list
        list->head = new_node;
        list->tail = new_node;
    }
    else if (position == 0){ // Insert at head
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
    }
    else if( position >= list->size){ // Insert at tail
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
    }
    else {
        // Traverse
        linked_list_node *curr = list->head;
        for(size_t i = 0; i < position; ++i){
            curr = curr->next;
        }
        // Insert
        new_node->prev = curr->prev;
        new_node->next = curr->next;
        curr->prev->next = new_node;
        curr->prev = new_node;
    }

    // Increase size
    list->size++;
}

// Function to remove an element from a specific position in the linked list
void *remove_from_linked_list(linked_list *list, size_t position){
    if(list == NULL){
        log_error_and_die("Tried to destroy element from a NULL list\n");
    }
    if(list->head == NULL){
        log_error_and_die("Tried to destroy element from list, but HEAD of list is NULL\n");
    }
    if(position >= list->size){
        log_error_and_die("Tried to remove element from list but index is out of bound\n");
    }

    linked_list_node* curr = list->head;
    if(position == 0){                  // Remove at head
        list->head = curr->next;
        if(list->head != NULL){
            list->head->prev = NULL;
        } else {                        // Was the only element
            list->tail = NULL;
        }
    }
    else if(position == list->size-1){  // Remove at tail
        curr = list->tail;
        list->tail = curr->prev;
        if(list->tail != NULL){
            list->tail->next = NULL;
        } else {                        // Was the only element
            list->head = NULL;
        }
    }
    else{
        // Traverse
        for(size_t i = 0; i < position; ++i){
            curr = curr->next;
        }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }
    
    void *data = destroy_linked_list_node(curr);
    list->size--;
    return data;
}

// Function to get the element at a specific position in the linked list
void *get_from_linked_list(const linked_list *list, size_t position){
    if(list == NULL){
        log_error_and_die("Tried to get element from a NULL list\n");
    }
    if(list->head == NULL){
        log_error_and_die("Tried to get element from list, but HEAD of list is NULL\n");
    }
    if(position >= list->size){
        log_error_and_die("Tried to get element from list but index is out of bound\n");
    }

    // Traverse
    linked_list_node *curr = list->head;
    for(size_t i = 0; i < position; ++i){
        curr = curr->next;
    }
    return curr->data;
}

// Function to destroy the linked list and free memory
void destroy_linked_list(linked_list *list){
    if(list == NULL){
        log_error_and_die("Tried to destroy NULL linked list\n");
    }
    if(list->size != 0 || list->head != NULL || list->tail != NULL){
        log_error_and_die("Tried to destroy non-empty list\n");
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    free(list);
}

// Function to print the linked list
void print_linked_list(linked_list *list, generic_print print_fn){
    if(list == NULL){
        log_error_and_die("Tried to print NULL list_list\n");
    }
    if(list->size == 0){
        printf("[]\n");
        return;
    }
    printf("[");
    // Traverse
    linked_list_node *curr = list->head;
    for(size_t i = 0; i < list->size; ++i){
        print_fn(curr->data);
        if(curr != list->tail){
            printf(", ");
        }
    }
    printf("]\n");
}

// Function to map over a linked list
linked_list *map_linked_list(linked_list *list, void*(map_function)(const void *)){
    if(list==NULL){
        log_error_and_die("Tried to map over a NULL list\n");
    }
    linked_list *result_list = create_linked_list();

    // Traverse and apply
    linked_list_node *curr = list->head;

    while(curr != NULL){
        void *mapped_data = map_function(curr->data);
        append_to_linked_list(list, mapped_data);
        curr = curr->next;
    }

    return result_list;
}

// Function to reduce a linked list (folding from the left)
void *reducel_linked_list(const linked_list *list, void *(*reduce_function)(const void *, const void *)){
    if(list == NULL){
        log_error_and_die("Tried to reduce a NULL list\n");
    }
    if(list->head == NULL){
        log_error_and_die("Tried to reduce a list but head is NULL\n");
    }

    linked_list_node *curr = list->head;
    void *acc = curr->data;

    while(curr->next != NULL){
        curr = curr->next;
        acc = reduce_function(acc, curr->data);
    }
    return acc;
}

// Reduce the linked list (folding from the right!)
void *reducer_linked_list(const linked_list *list, void *(*reduce_function)(const void *, const void *)){
    if(list == NULL){
        log_error_and_die("Tried to reduce a NULL list\n");
    }
    if(list->head == NULL){
        log_error_and_die("Tried to reduce a list but head is NULL\n");
    }
    if(list->tail == NULL){
        log_error_and_die("Tried to reduce a list but tail is NULL\n");
    }

    linked_list_node *curr = list->tail;
    void *acc = curr->data;

    while(curr != list->head){
        curr = curr->prev;
        acc = reduce_function(acc, curr->data);
    }
    return acc;
}
