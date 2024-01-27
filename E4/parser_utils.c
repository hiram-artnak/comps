#include "parser_utils.h"
#include "symbol.h"
#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define ERR_UNDECLARED 10
#define ERR_DECLARED 11
#define ERR_VARIABLE 20
#define ERR_FUNCTION 21

ast_node *make_binary_expression(ast_node_type type, ast_node *left, ast_node *right, stack *s){
    fail_if_not_declared(s, left);
    fail_if_not_declared(s, right);
    fail_if_invalid_operator(s, left);
    fail_if_invalid_operator(s, right);
    symbol *left_sym = stack_get(s, left->lexeme->value);
    symbol *right_sym = stack_get(s, right->lexeme->value);
    ast_node *node = ast_node_create(type, NULL, type_infer(left_sym, right_sym));
    ast_node_add_child(node, left);
    ast_node_add_child(node, right);
    return node;
}
ast_node *make_unary_expression(ast_node_type type, ast_node *op_node, stack *s){
    fail_if_not_declared(s, op_node);
    fail_if_invalid_operator(s, op_node);
    ast_node *node = ast_node_create(type, NULL, op_node->data_type);
    ast_node_add_child(node, op_node);
    return node;
}

void fail_if_not_declared(stack *stack, ast_node *node){
    if(!stack_is_declared(stack, node->lexeme->value)){
        printf("Error: %s is used on line %d but it has not been declared\n", node->lexeme->value, node->lexeme->line);
        exit(ERR_UNDECLARED);
    }
}
void fail_if_declared(stack *stack, ast_node *node){
    if(stack_is_declared(stack, node->lexeme->value)){
        symbol *sym = stack_get(stack, node->lexeme->value);
        int sym_line = sym->lexeme->line;
        printf("Error: %s was declared in line %d is already declared on line %d\n", node->lexeme->value, node->lexeme->line, sym_line);
        exit(ERR_DECLARED);
    }
}

void fail_if_not_variable(stack *stack, ast_node *node){
    symbol *s = stack_get(stack, node->lexeme->value);
    if (s->sym_type == SYMBOL_TYPE_IDENTIFIER) {
        printf("Error: %s in line %d is not a variable\n", node->lexeme->value, node->lexeme->line);
        exit(1);
    }
}

void fail_if_not_function(stack *stack, ast_node *node){
    symbol *s = stack_get(stack, node->lexeme->value);
    if (s->sym_type != SYMBOL_TYPE_FUNCTION) {
        printf("Error: %s in line %d is not a function\n", node->lexeme->value, node->lexeme->line);
        exit(1);
    }
}

void fail_if_invalid_operator(stack *stack, ast_node *node){
    symbol *s = stack_get(stack, node->lexeme->value);
    if (s->sym_type != SYMBOL_TYPE_IDENTIFIER && node->type != AST_NODE_TYPE_LITERAL && node->type != AST_NODE_TYPE_FUNCTION_CALL) {
        printf("Error: %s in line %d is not a variable or literal or function call\n", node->lexeme->value, node->lexeme->line);
        exit(1);
    }
}


void destroy_symbol_key_value(void *data){
    key_value *kv = (key_value *)data;
    symbol_destroy((symbol *)kv->value);
    f_free(kv->key);
    f_free(kv);
}

void add_new_scope(stack *stack){
    stack_push(stack, symbol_table_create());
}
void remove_current_scope(stack *stack){
    hash_table *table = stack_pop(stack);
    hash_table_destroy(table);
}

void add_symbol(stack *stack, symbol *symbol){
    hash_table *table = stack_get(stack, 0);
    hash_table_insert(table, symbol->lexeme->value, symbol);
}