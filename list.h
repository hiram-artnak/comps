#ifndef LIST_H
#define LIST_H

/**
 * Header file for a linked list data structure.
**/

typedef struct _node{
    void *data;
    struct _node *next; // Is null if node is last in list
} node;

int node_init(node *n, void *data); // Will fail if data is null
int node_destroy(node *n); // Will fail if data is not freed

int node_get_data(node *n, void **data); // Will fail if node is null

typedef struct _list{
    node *head;  // Is null if list is empty
    node *tail;  // Is null if list is empty
    int size;
    void (*free)(void *data); // Function to free data
} list;

int list_init(list *l, void (*free)(void *data));
int list_add(list *l, void *data);
int list_remove(list *l, void *data, int (*cmp)(void *a, void *b));
int list_destroy(list *l);

#define list_size(l) ((l)->size)
#define list_head(l) ((l)->head)
#define list_tail(l) ((l)->tail)
#define node_next(n) ((n != NULL) ? (n)->next : NULL)

#endif