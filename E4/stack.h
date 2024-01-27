#ifndef STACK_H
#define STACK_H

#include "linked_list.h"
#include "ast.h"
typedef linked_list stack;

stack *stack_create(destroy_data destroy);
void stack_create_if_null(stack **stack, destroy_data destroy);
void stack_destroy(stack *stack);
void stack_push(stack *stack, void *data);
void *stack_pop(stack *stack);
int stack_is_declared(stack *stack, char *identifier);
void *stack_get(stack *stack, char *identifier);
void fail_if_not_declared(stack *stack, ast_node *node);
void fail_if_declared(stack *stack, ast_node *node);
void fail_if_not_variable(stack *stack, ast_node *node);
void fail_if_not_function(stack *stack, ast_node *node);
void fail_if_invalid_operator(stack *stack, ast_node *node);
#endif