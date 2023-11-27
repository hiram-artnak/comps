#include "list.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

/*** node functions ***/
int node_init(node *n, void *data){
    if(data == NULL){
        return 1; // NULL data is not allowed
    }
    n->data = data;
    n->next = NULL;
    return 0;
}


int node_destroy(node *n){
    if(n == NULL){
        /* Tried to destroy a NULL node */
        /* No double frees allowed */
        return 1;
    }

    if(n->data != NULL){
    /* Tried to destroy a node with non-NULL data */ 
    /* This is a memory leak */
    /* The user should free the data before destroying the node */
        return 2; 
    }

    free(n);
    return 0;
}

void _simple_free(void *data){
    /* Useful for primitives */
    free(data);
    return;
}

int list_init(list *l, void (*free)(void *data)){
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    if(free == NULL){
        l->free = _simple_free;
    } else {
        l->free = free;
    }
    return 0;
}

int list_add(list *l, void *data){
    if (data == NULL){
        return 1; // NULL data is not allowed
    }
    
    node *n = malloc(sizeof(node));
    if(n == NULL) die("malloc failed");
    node_init(n, data);

    if(l->head == NULL){
        l->head = n;
        l->tail = n;
    } else {
        l->tail->next = n;
        l->tail = n;
    }
    l->size++;
    return 0;
}


int _do_remove(list *l, node *prev, node *curr){
    if(prev == NULL){
        l->head = curr->next;
    } else {
        prev->next = curr->next;
    }
    if(curr == l->tail){
        l->tail = prev;
    }
    l->free(curr->data);
    node_destroy(curr);
    l->size--;
    return 0;
}

int list_remove(list *l, void *data, int (*cmp)(void *a, void *b)){
    if(l->head == NULL){
        return 1; // Empty list
    }

    node *prev = NULL;
    node *curr = l->head;
    while(curr != NULL){
        if(cmp(curr->data, data) == 0){
            _do_remove(l, prev, curr);
            return 0;
        }
        prev = curr;
        curr = curr->next;
    }
    return 2; // Data not found
}

int list_destroy(list *l){
    node *curr = l->head;
    while(curr != NULL){
        node *next = curr->next;
        curr->next = NULL;
        l->free(curr->data);
        node_destroy(curr);
        curr = next;
        l->size--;
    }
    l->head = NULL;
    l->tail = NULL;
    if(l->size != 0){
        die("Tried to destroy list, but nodes still exist");
    }
    return 0;
}

int node_get_data(node *n, void **data){
    if(n == NULL){
        return 1; // NULL node is not allowed
    }

    if(data == NULL){
        return 2; // NULL pointer to data is not allowed
    }

    *data = n->data;
    return 0;
}

