#include "llist.h"
#include <stdio.h>


typedef struct llist_node {
    void *data;
    struct llist_node *next;
    struct llist_node *prev;
} llist_node;

// Allocate a new node
llist_node *llist_node_create(void *data);

// Free a node
void llist_node_free(llist_node *node, llist_free_fn free_fn);

llist_node *llist_node_create(void *data) {

    llist_node *node = malloc(sizeof(llist_node));
    if(node == NULL) {
        fprintf(stderr, "Error: malloc failed allocating node\n");
        exit(1);
    }

    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}


void llist_node_free(llist_node *node, llist_free_fn free_fn) {
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

// Actual linked list structure
typedef struct llist {
    llist_node *head;
    llist_node *tail;
    llist_free_fn free_fn;
    int length;
} llist;

// Allocate a new linked list
llist *llist_create(llist_free_fn free_fn) {
    llist *list = malloc(sizeof(llist));
    if (list == NULL) {
        fprintf(stderr, "Error: malloc failed allocating list\n");
        exit(1);
    }
    list->head = NULL;
    list->tail = NULL;
    list->free_fn = free_fn;
    list->length = 0;
    return list;
}

// Free a linked list
void llist_free(llist *list){
    if (list == NULL) {
        fprintf(stderr, "Error: tried to free list, but list is NULL\n");
        exit(1);
    }
    llist_node *node = list->head;
    while (node != NULL) {
        llist_node *next = node->next;
        llist_node_free(node, list->free_fn);
        node = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    free(list);
}


// Append a node to the end of the list
void llist_append(llist *list, void *data){
    if(list == NULL) {
        fprintf(stderr, "Error: tried to append to list, but list is NULL\n");
        exit(1);
    }
    llist_node *node = llist_node_create(data);
    // If the list is empty then set the head and tail to the new node
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        // Otherwise, set the tail's next to the new node
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
    if(list == NULL) {
        fprintf(stderr, "Error: tried to get from list, but list is NULL\n");
        exit(1);
    }
    if(index < 0 || index >= list->length) {
        fprintf(stderr, "Error: tried to get from list, but index is out of bounds\n");
        exit(1);
    }
    llist_node *node = list->head;
    for(int i = 0; i < index; i++) {
        node = node->next;
    }
    return node->data;
}

// Remove a node from the list
void llist_remove(llist *list, void *key, llist_compare_fn compare_fn){
    if(list == NULL) {
        fprintf(stderr, "Error: tried to remove from list, but list is NULL\n");
        exit(1);
    }
    llist_node *node = list->head;
    while(node != NULL) {
        if(compare_fn(key, node->data) == 0) {
            // If the node is the head
            if(node == list->head) {
                list->head = node->next;
                if(list->head != NULL) {
                    list->head->prev = NULL;
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
}

// Print the list
void llist_print(llist *list, llist_print_fn print_fn){
    if(list == NULL) {
        fprintf(stderr, "Error: tried to print list, but list is NULL\n");
        exit(1);
    }
    llist_node *node = list->head;
    while(node != NULL) {
        print_fn(node->data);
        node = node->next;
    }
}

// Get the length of the list
int llist_length(llist *list){
    if(list == NULL) {
        fprintf(stderr, "Error: tried to get length of list, but list is NULL\n");
        exit(1);
    }
    return list->length;
}