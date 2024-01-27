#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

#include "ast.h"
#include "stack.h"
#include "symbol.h"


ast_node *make_binary_expression(ast_node_type type, ast_node *left, ast_node *right, stack *s);
ast_node *make_unary_expression(ast_node_type type, ast_node *op_node, stack *s);

void fail_if_not_declared(stack *stack, ast_node *node);
void fail_if_declared(stack *stack, ast_node *node);
void fail_if_not_variable(stack *stack, ast_node *node);
void fail_if_not_function(stack *stack, ast_node *node);
void fail_if_invalid_operator(stack *stack, ast_node *node);
void add_new_scope(stack *stack);
void remove_current_scope(stack *stack);
void add_symbol(stack *stack, symbol *symbol);
#endif