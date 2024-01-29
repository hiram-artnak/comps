#include "parser_utils.h"
#include "hash_table.h"
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "stdlib.h"
void stack_create_if_null(stack **s){
    if (*s == NULL) {
        *s = stack_create((destroy_data)hash_table_destroy);
    }
    // global scope
    add_new_scope(*s);
}

int symbol_was_declared(stack *s, char *symbol_value){
    for (int i = 0; i < stack_get_size(s); i++) {
        hash_table *table = stack_peek_further(s, i);
        if (hash_table_is_member(table, symbol_value)) {
            return 1;
        }
    }
    return 0;
}
symbol *get_symbol_globally(stack *s, char *symbol_value){
    for (int i = 0; i < stack_get_size(s); i++) {
        hash_table *table = stack_peek_further(s, i);
        if (hash_table_is_member(table, symbol_value)) {
            return hash_table_get(table, symbol_value);
        }
    }
    return NULL;
}
ast_node *unwind_ast_node_list(ast_node_list *list){
    if (ast_node_list_size(list) > 0) {
        ast_node *node = ast_node_list_pop_front(list);
        ast_node *cur = node;
        while (ast_node_list_size(list) > 0) {
            ast_node *next = ast_node_list_pop_front(list);
            ast_node_add_child(cur, next);
            cur = next;
        }
        return node;
    }
    return NULL;
}

ast_node *make_binary_expression(ast_node_type type, ast_node *left, ast_node *right, stack *s){
    fail_if_not_declared(s, left);
    fail_if_not_declared(s, right);
    fail_if_invalid_operator(s, left);
    fail_if_invalid_operator(s, right);
    ast_node *node = ast_node_create(type, NULL, ast_node_type_infer(left, right));
    ast_node_add_child(node, left);
    ast_node_add_child(node, right);
    return node;
}

ast_node *make_unary_expression(ast_node_type type, ast_node *node, stack *s){
    fail_if_not_declared(s, node);
    fail_if_invalid_operator(s, node);
    ast_node *new_node = ast_node_create(type, NULL, ast_node_get_data_type(node));
    ast_node_add_child(new_node, node);
    return new_node;
}

void fail_if_not_declared(stack *s, ast_node *node){
    if (!symbol_was_declared(s, ast_node_get_lexeme_value(node))) {
        fprintf(stderr, "Error: Symbol %s was used on line %d but it was not declared\n", ast_node_get_lexeme_value(node), ast_node_get_line_number(node));
        exit(1);
    }
}
void fail_if_declared(stack *s, ast_node *node){
    if (symbol_was_declared(s, ast_node_get_lexeme_value(node))) {
        symbol *symbol = get_symbol_globally(s, ast_node_get_lexeme_value(node));
        fprintf(stderr, "Error: Symbol %s was declared on line %d but it was already declared on line %d\n", ast_node_get_lexeme_value(node), ast_node_get_line_number(node), symbol_get_line(symbol));
        exit(1);
    }

}
void fail_if_not_variable(stack *s, ast_node *node){
    symbol *symbol = get_symbol_globally(s, ast_node_get_lexeme_value(node));
    if (symbol_get_type(symbol) != SYMBOL_TYPE_IDENTIFIER) {
        fprintf(stderr, "Error: Symbol %s was used on line %d but it is not a variable\n", ast_node_get_lexeme_value(node), ast_node_get_line_number(node));
        exit(1);
    }
}
void fail_if_not_function(stack *s, ast_node *node){
    symbol *symbol = get_symbol_globally(s, ast_node_get_lexeme_value(node));
    if (symbol_get_type(symbol) != SYMBOL_TYPE_FUNCTION) {
        fprintf(stderr, "Error: Symbol %s was used on line %d but it is not a function\n", ast_node_get_lexeme_value(node), ast_node_get_line_number(node));
        exit(1);
    }
}
void fail_if_invalid_operator(stack *s, ast_node *node){
    symbol *symbol = get_symbol_globally(s, ast_node_get_lexeme_value(node));
    if (symbol_get_type(symbol) == SYMBOL_TYPE_FUNCTION && ast_node_get_node_type(node) != AST_NODE_TYPE_FUNCTION_CALL) {
        fprintf(stderr, "Error: Symbol %s was used on line %d as an operator but it is a function\n", ast_node_get_lexeme_value(node), ast_node_get_line_number(node));
        exit(1);
    }

}
void add_new_scope(stack *s){
    hash_table *table = hash_table_create((destroy_data)symbol_destroy);
    stack_push(s, table);
}
void remove_current_scope(stack *s){
    hash_table *table = stack_pop(s);
    hash_table_destroy(table);
}

void add_symbol_to_current_scope(stack *s, symbol *symbol){
    hash_table *table = stack_peek(s);
    hash_table_insert(table, symbol_get_value(symbol), symbol);
}