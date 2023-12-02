#ifndef LLIST_H
#define LLIST_H

/**
 * Linked List header file
*/

// Type definitions
typedef struct llist llist;
typedef void (*llist_free_fn)(void *data);
typedef int (*llist_compare_fn)(void *key, void *data);
typedef void (*llist_print_fn)(void *data);

// Function prototypes

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



#endif