#ifndef STACK_H
#define STACK_H

#include "linked_list.h"

typedef linked_list stack;

stack *stack_create(destroy_data destroy);
void stack_destroy(stack *stack);
void stack_push(stack *stack, void *data);
void *stack_pop(stack *stack);
int stack_is_declared(stack *stack, char *identifier);
void *stack_get(stack *stack, char *identifier);

#endif