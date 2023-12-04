#include "llist.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct llist_node {
    void *data;
    struct llist_node *next;
    struct llist_node *prev;
} llist_node;

// Allocate a new node
llist_node *llist_node_create(void *data);

// Free a node
void llist_node_free(llist_node *node, llist_free_fn free_fn);
void llist_node_free_wo_destroy(llist_node *node);

llist_node *llist_node_create(void *data) {
    // Allocate Memory //
    llist_node *node = malloc(sizeof(llist_node));
    if(node == NULL) {
        fprintf(stderr, "Error: malloc failed allocating node\n");
        exit(1);
    }
    // Set node attributes //
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}


void llist_node_free(llist_node *node, llist_free_fn free_fn) {
    // Validate inputs //
    if(node == NULL) {
        fprintf(stderr, "Error: tried to free node, but node is NULL\n");
        exit(1);
    }
    if(node->data == NULL) {
        fprintf(stderr, "Error: tried to free data from node, but node->data is NULL\n");
        exit(1);
    }
    // Use the free function if it exists, otherwise use free
    if (free_fn != NULL) {
        free_fn(node->data);
    } else {
        free(node->data);
    }

    free(node);
}

void llist_node_free_wo_destroy(llist_node *node){
    // Validate inputs //
    if(node == NULL) {
        fprintf(stderr, "Error: tried to free node, but node is NULL\n");
        exit(1);
    }
    if(node->data == NULL) {
        fprintf(stderr, "Error: tried to free data from node, but node->data is NULL\n");
        exit(1);
    }
    free(node);
}

// Actual linked list structure
typedef struct llist {
    llist_node *head;
    llist_node *tail;
    llist_free_fn free_fn;
    int length;
} llist;

// Allocate a new linked list
llist *llist_create(llist_free_fn free_fn) {
    // Allocate Memory //
    llist *list = malloc(sizeof(llist));
    if (list == NULL) {
        fprintf(stderr, "Error: malloc failed allocating list\n");
        exit(1);
    }
    // Set list attributes //
    list->head = NULL;
    list->tail = NULL;
    list->free_fn = free_fn;
    list->length = 0;
    return list;
}

// Free a linked list
void llist_free(llist *list){
    // Validate inputs //
    if (list == NULL) {
        fprintf(stderr, "Error: tried to free list, but list is NULL\n");
        exit(1);
    }
    // Loop through the list and free each node //
    llist_node *node = list->head;
    while (node != NULL) {
        llist_node *next = node->next;
        llist_node_free(node, list->free_fn);
        node = next;
        list->length--;
    }
    // Check invariant //
    if(list->length != 0) {
        fprintf(stderr, "Error: list length is not zero after freeing all nodes\n");
        exit(1);
    }
    // Set the head and tail to NULL//
    list->head = NULL;
    list->tail = NULL;
    free(list);
}


void llist_free_wo_destroy(llist *list){
    // Validate inputs //
    if (list == NULL) {
        fprintf(stderr, "Error: tried to free list, but list is NULL\n");
        exit(1);
    }
    // Loop through the list and free each node //
    llist_node *node = list->head;
    while (node != NULL) {
        llist_node *next = node->next;
        llist_node_free_wo_destroy(node);
        node = next;
        list->length--;
    }
    // Check invariant //
    if(list->length != 0) {
        fprintf(stderr, "Error: list length is not zero after freeing all nodes\n");
        exit(1);
    }
    // Set the head and tail to NULL//
    list->head = NULL;
    list->tail = NULL;
    free(list);


}

// Append a node to the end of the list
void llist_append(llist *list, void *data){
    // Validate inputs //
    if(list == NULL) {
        fprintf(stderr, "Error: tried to append to list, but list is NULL\n");
        exit(1);
    }
    
    llist_node *node = llist_node_create(data);
    
    // If the list is empty then set the head and tail to the new node
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else { // Otherwise, set the tail's next to the new node
        list->tail->next = node;
        // Set the new node's prev to the tail
        node->prev = list->tail;
        // Set the tail to the new node
        list->tail = node;
    }
    
    list->length++;
}

// Get the data based on index
void *llist_get(llist *list, int index){
    // Validate inputs //
    if(list == NULL) {
        fprintf(stderr, "Error: tried to get from list, but list is NULL\n");
        exit(1);
    }
    if(index < 0 || index >= list->length) {
        fprintf(stderr, "Error: tried to get from list, but index is out of bounds\n");
        exit(1);
    }
    // Loop through the list until we get to the index //
    llist_node *node = list->head;
    for(int i = 0; i < index; i++) {
        node = node->next;
    }
    return node->data;
}

void *llist_get_tail(llist *list){
    // Validate inputs //
    if(list == NULL) {
        fprintf(stderr, "Error: tried to get from list, but list is NULL\n");
        exit(1);
    }
    if(list->length == 0) {
        fprintf(stderr, "Error: tried to get from list, but list is empty\n");
        exit(1);
    }
    return list->tail->data;
}

// Remove a node from the list
void llist_remove(llist *list, void *key, llist_match_fn match_fn){
    // Validate inputs //
    if(list == NULL) {
        fprintf(stderr, "Error: tried to remove from list, but list is NULL\n");
        exit(1);
    }
    if(match_fn == NULL) {
        fprintf(stderr, "Error: tried to remove from list, but match function is NULL\n");
        exit(1);
    }
    // Loop through the list until we find the key //
    llist_node *node = list->head;
    while(node != NULL) {
        if(match_fn(key, node->data) == 0) {
            // If the node is the head
            if(node == list->head) {
                list->head = node->next;
                if(list->head != NULL) {
                    list->head->prev = NULL;
                }else{
                    // The list is now empty
                    list->tail = NULL;
                }
            } else {
                // If the node is the tail
                if(node == list->tail) {
                    list->tail = node->prev;
                    if(list->tail != NULL) {
                        list->tail->next = NULL;
                    }
                } else {
                    // If the node is in the middle
                    node->prev->next = node->next;
                    node->next->prev = node->prev;
                }
            }
            llist_node_free(node, list->free_fn);
            list->length--;
            return;
        }
        node = node->next;
    }
    // If we get here, the key was not found
    fprintf(stderr, "Error: tried to remove from list, but data with matching key was not found\n");
    exit(1);
}


// Print the list
void llist_print(llist *list, llist_print_fn print_fn){
    // Validate inputs //
    
    if(list == NULL) {
        fprintf(stderr, "Error: tried to print list, but list is NULL\n");
        exit(1);
    }
    if(print_fn == NULL) {
            fprintf(stderr, "Error: tried to print list, but print function is NULL\n");
            exit(1);
    }
    // Loop and print //
    llist_node *node = list->head;
    while(node != NULL) {
        if(node->data == NULL) {
            fprintf(stderr, "Error: tried to print list, but data is NULL\n");
            exit(1);
        }
        print_fn(node->data);
        node = node->next;
    }
}

// Get the length of the list
int llist_length(llist *list){
    // Validate inputs //
    if(list == NULL) {
        fprintf(stderr, "Error: tried to get length of list, but list is NULL\n");
        exit(1);
    }
    return list->length;
}