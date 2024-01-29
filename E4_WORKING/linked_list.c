#include "linked_list.h"
#include "utils.h"

typedef struct linked_list_node {
    void *value;
    struct linked_list_node *next;
} linked_list_node;


linked_list_node *linked_list_node_create(void *value){
    linked_list_node *node = f_malloc(sizeof(linked_list_node));
    node->value = value;
    node->next = NULL;
    return node;
}

typedef struct linked_list {
    linked_list_node *head;
    linked_list_node *tail;
    int size;
    destroy_data destroy;
} linked_list;

linked_list *linked_list_create(destroy_data destroy){
    linked_list *list = f_malloc(sizeof(linked_list));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->destroy = destroy;
    return list;
}

void linked_list_destroy(linked_list *list){
    linked_list_clear(list);
    f_free(list);
}

void linked_list_clear(linked_list *list){
    linked_list_node *node = list->head;
    while (node != NULL) {
        linked_list_node *next = node->next;
        if (list->destroy != NULL) {
            list->destroy(node->value);
        }
        f_free(node);
        node = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

int linked_list_size(linked_list *list){
    return list->size;
}

int linked_list_empty(linked_list *list){
    return list->size == 0;
}

void linked_list_push_front(linked_list *list, void *value){
    linked_list_node *node = linked_list_node_create(value);
    node->next = list->head;
    list->head = node;
    if (list->tail == NULL) {
        list->tail = node;
    }
    list->size++;
}

void linked_list_push_back(linked_list *list, void *value){
    linked_list_node *node = linked_list_node_create(value);
    if (list->tail != NULL) {
        list->tail->next = node;
    }
    list->tail = node;
    if (list->head == NULL) {
        list->head = node;
    }
    list->size++;
}
void *linked_list_pop_front(linked_list *list){
    if (list->head == NULL) {
        return NULL;
    }
    linked_list_node *node = list->head;
    void *value = node->value;
    list->head = node->next;
    if (list->head == NULL) {
        list->tail = NULL;
    }
    f_free(node);
    list->size--;
    return value;
}
void *linked_list_pop_back(linked_list *list){
    if (list->tail == NULL) {
        return NULL;
    }
    linked_list_node *node = list->tail;
    void *value = node->value;
    if (list->head == node) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        linked_list_node *prev = list->head;
        while (prev->next != node) {
            prev = prev->next;
        }
        prev->next = NULL;
        list->tail = prev;
    }
    f_free(node);
    list->size--;
    return value;
}

void *linked_list_front(linked_list *list){
    if (list->head == NULL) {
        return NULL;
    }
    return list->head->value;
}
void *linked_list_back(linked_list *list){
    if (list->tail == NULL) {
        return NULL;
    }
    return list->tail->value;
}
void linked_list_insert(linked_list *list, int index, void *value){
    if (index < 0 || index > list->size) {
        return;
    }
    if (index == 0) {
        linked_list_push_front(list, value);
        return;
    }
    if (index == list->size) {
        linked_list_push_back(list, value);
        return;
    }
    linked_list_node *prev = list->head;
    for (int i = 0; i < index - 1; i++) {
        prev = prev->next;
    }
    linked_list_node *node = linked_list_node_create(value);
    node->next = prev->next;
    prev->next = node;
    list->size++;
}

void linked_list_delete(linked_list *list, int index){
    if (index < 0 || index >= list->size) {
        return;
    }
    if (index == 0) {
        linked_list_pop_front(list);
        return;
    }
    if (index == list->size - 1) {
        linked_list_pop_back(list);
        return;
    }
    linked_list_node *prev = list->head;
    for (int i = 0; i < index - 1; i++) {
        prev = prev->next;
    }
    linked_list_node *node = prev->next;
    prev->next = node->next;
    f_free(node);
    list->size--;
}

void *linked_list_get(linked_list *list, int index){
    if (index < 0 || index >= list->size) {
        return NULL;
    }
    linked_list_node *node = list->head;
    for (int i = 0; i < index; i++) {
        node = node->next;
    }
    return node->value;
}

void linked_list_print(linked_list *list, print_data print){
    linked_list_node *node = list->head;
    while (node != NULL) {
        print(node->value);
        node = node->next;
    }
}