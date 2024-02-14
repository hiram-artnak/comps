#ifndef STACK_H
#define STACK_H

#include "types.h"
#include "linked_list.h"

typedef linked_list stack;

stack *stack_create();


stack *stack_create(destroy_data destroy);
void stack_destroy(stack *s);
void stack_push(stack *s, void *data);
void *stack_pop(stack *s);
void *stack_peek(stack *s);
void *stack_peek_further(stack *s, int index);
int stack_get_size(stack *s);

#endif