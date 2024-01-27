#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

#include "ast.h"
#include "stack.h"

ast_node *make_binary_expression(ast_node_type type, ast_node *left, ast_node *right, stack *s);
ast_node *make_unary_expression(ast_node_type type, ast_node *op_node, stack *s);

#endif