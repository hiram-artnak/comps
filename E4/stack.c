#include "stack.h"
#include "hash_table.h"
#include "symbol.h"
#include <string.h>
#include <stdio.h>
#define ERR_UNDECLARED 10
#define ERR_DECLARED 11
#define ERR_VARIABLE 20
#define ERR_FUNCTION 21

stack *stack_create(destroy_data destroy){
    return (stack *)linked_list_create(destroy);

}
void stack_create_if_null(stack **stack, destroy_data destroy){
    if(*stack == NULL){
        *stack = stack_create(destroy);
        stack_push(*stack, symbol_table_create());
    }
}
void stack_destroy(stack *stack){
    linked_list_destroy(stack);
}
void stack_push(stack *stack, void *data){
    linked_list_push_front(stack, data);
}
void *stack_pop(stack *stack){
    return linked_list_pop_front(stack);
}
int stack_is_declared(stack *stack, char *identifier){
    for(int i = 0; i < linked_list_size(stack); i++){
        hash_table *table = linked_list_get(stack, i);
        if(hash_table_is_member(table, identifier)){
            return 1;
        }
    }
    return 0;
}
void *stack_get(stack *stack, char *identifier){
    for(int i = 0; i < linked_list_size(stack); i++){
        hash_table *table = linked_list_get(stack, i);
        if(hash_table_is_member(table, identifier)){
            return hash_table_get(table, identifier);
        }
    }
    return NULL;
}

void stack_push_to_top_scope(stack *stack, char *key, void *value){
    hash_table *table = linked_list_get(stack, 0);
    hash_table_insert(table, key, value);
}

void fail_if_not_declared(stack *stack, ast_node *node){
    if(!stack_is_declared(stack, node->value->value)){
        printf("Error: %s is used on line %d but it has not been declared\n", node->value->value, node->value->line);
        exit(ERR_UNDECLARED);
    }
}
void fail_if_declared(stack *stack, ast_node *node){
    if(stack_is_declared(stack, node->value->value)){
        symbol *sym = stack_get(stack, node->value->value);
        int sym_line = sym->lexeme->line;
        printf("Error: %s was declared in line %d is already declared on line %d\n", node->value->value, node->value->line, sym_line);
        exit(ERR_DECLARED);
    }
}

void fail_if_not_variable(stack *stack, ast_node *node){
    symbol *s = stack_get(stack, node->value->value);
    if (s->sym_type == SYMBOL_TYPE_IDENTIFIER) {
        printf("Error: %s in line %d is not a variable\n", node->value->value, node->value->line);
        exit(1);
    }
}

void fail_if_not_function(stack *stack, ast_node *node){
    symbol *s = stack_get(stack, node->value->value);
    if (s->sym_type != SYMBOL_TYPE_FUNCTION) {
        printf("Error: %s in line %d is not a function\n", node->value->value, node->value->line);
        exit(1);
    }
}

void fail_if_invalid_operator(stack *stack, ast_node *node){
    symbol *s = stack_get(stack, node->value->value);
    if (s->sym_type != SYMBOL_TYPE_IDENTIFIER && node->type != AST_NODE_TYPE_LITERAL && node->type != AST_NODE_TYPE_FUNCTION_CALL) {
        printf("Error: %s in line %d is not a variable or literal or function call\n", node->value->value, node->value->line);
        exit(1);
    }
}