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
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void llist_node_free(llist_node *node, llist_free_fn free_fn) {
    if (free_fn != NULL) {
        free_fn(node->data);
    }
    free(node);
}


// Allocate a new linked list
llist *llist_create(llist_free_fn free_fn);

// Free a linked list
void llist_free(llist *list);

// Append a node to the end of the list
void llist_append(llist *list, void *data);

// Get the data based on index
void *llist_get(llist *list, int index);

// Remove a node from the list
void llist_remove(llist *list, void *key, llist_compare_fn compare_fn);

// Print the list
void llist_print(llist *list, llist_print_fn print_fn);

// Get the length of the list
int llist_length(llist *list);