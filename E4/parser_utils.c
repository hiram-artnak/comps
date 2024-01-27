#include "parser_utils.h"
#include <string.h>
ast_node *make_binary_expression(ast_node_type type, ast_node *left, ast_node *right, stack *s){
    fail_if_not_declared(s, left);
    fail_if_not_declared(s, right);
    fail_if_invalid_operator(s, left);
    fail_if_invalid_operator(s, right);
    ast_node *node = ast_node_create(type, NULL, type_infer(left->data_type, right->data_type));
    ast_node_add_child(node, left);
    ast_node_ad_child(node, right);
    return node;
}
ast_node *make_unary_expression(ast_node_type type, ast_node *op_node, stack *s){
    fail_if_not_declared(s, op_node);
    fail_if_invalid_operator(s, op_node);
    ast_node *node = ast_node_create(type, NULL, op_node->data_type);
    ast_node_add_child(node, op_node);
    return node;
}