#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

#include "stack.h"
#include "symbol.h"
#include "ast.h"


void stack_create_if_null(stack **s);
int symbol_was_declared(stack *s, char *symbol_value);
symbol *get_symbol_globally(stack *stack, char *symbol_value);
ast_node *unwind_ast_node_list(ast_node_list *list);

ast_node *make_binary_expression(ast_node_type type, ast_node *left, ast_node *right, stack *s);
ast_node *make_unary_expression(ast_node_type type, ast_node *node, stack *s);

void fail_if_not_declared(stack *s, ast_node *node);
void fail_if_declared(stack *s, ast_node *node);
void fail_if_not_variable(stack *s, ast_node *node);
void fail_if_not_function(stack *s, ast_node *node);
void fail_if_invalid_operator(stack *s, ast_node *node);
void add_new_scope(stack *s);
void remove_current_scope(stack *s);
void add_symbol_to_current_scope(stack *s, symbol *symbol);
#endif