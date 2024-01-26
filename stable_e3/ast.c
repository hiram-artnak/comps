#include "ast.h"
#include "utils.h"
#include "linked_list.h"
#include <string.h>
#include <stdio.h>

typedef linked_list ast_node_list;

typedef struct lexeme{
    char *value;
    int line;
    lexeme_type type;
} lexeme;

lexeme *lexeme_create(char *value, int line, lexeme_type type){
    lexeme *l = f_malloc(sizeof(lexeme));
    // copy the string
    l->value = f_malloc(strlen(value) + 1);
    strcpy(l->value, value);
    l->line = line;
    l->type = type;
    return l;
}

void lexeme_destroy(lexeme *l){
    f_free(l->value);
    f_free(l);
}

void lexeme_print(lexeme *l){
    printf("%s", l->value);
}


void ast_node_type_to_string(ast_node_type type, char *out_str){
    switch (type) {
        case AST_NODE_TYPE_IDENTIFIER:
            strcpy(out_str, "AST_NODE_TYPE_IDENTIFIER");
            break;
        case AST_NODE_TYPE_LITERAL:
            strcpy(out_str, "AST_NODE_TYPE_LITERAL");
            break;
        default:
            strcpy(out_str, "AST_NODE_TYPE_UNKNOWN");
            break;
    }
}

typedef struct ast_node{
    lexeme *value;
    ast_node_list *children;
    ast_node_type type;
} ast_node;



ast_node *ast_node_create(ast_node_type type, lexeme *value){
    ast_node *node = f_malloc(sizeof(ast_node));
    node->value = value;
    node->children = ast_node_list_create();
    node->type = type;
    return node;
}
void ast_node_destroy(ast_node *node){
    lexeme_destroy(node->value);
    ast_node_list_destroy(node->children);
    f_free(node);
}
void ast_node_add_child(ast_node *node, ast_node *child){
    ast_node_list_push_back(node->children, child);
}


void ast_node_print(ast_node *node){
    if(node->type == AST_NODE_TYPE_EMPTY){
        return;
    }
    // prints pointer position [label="value"]
    char out_str[100];
    switch (node->type){
        case AST_NODE_TYPE_IDENTIFIER:
            strcpy(out_str, node->value->value);
            break;
        case AST_NODE_TYPE_LITERAL:
            strcpy(out_str, node->value->value);
            break;
        case AST_NODE_TYPE_LOGICAL_NEGATION:
            strcpy(out_str, "!");
            break;
        case AST_NODE_TYPE_NUMERICAL_NEGATION:
            strcpy(out_str, "-");
            break;
        case AST_NODE_TYPE_MULTIPLICATION:
            strcpy(out_str, "*");
            break;
        case AST_NODE_TYPE_DIVISION:
            strcpy(out_str, "/");
            break;
        case AST_NODE_TYPE_MODULO:
            strcpy(out_str, "%%");
            break;
        case AST_NODE_TYPE_ADDITION:
            strcpy(out_str, "+");
            break;
        case AST_NODE_TYPE_SUBTRACTION:
            strcpy(out_str, "-");
            break;
        case AST_NODE_TYPE_LESS_THAN:
            strcpy(out_str, "<");
            break;
        case AST_NODE_TYPE_GREATER_THAN:
            strcpy(out_str, ">");
            break;
        case AST_NODE_TYPE_LESS_EQUAL:
            strcpy(out_str, "<=");
            break;
        case AST_NODE_TYPE_GREATER_EQUAL:
            strcpy(out_str, ">=");
            break;
        case AST_NODE_TYPE_EQUAL:
            strcpy(out_str, "==");
            break;
        case AST_NODE_TYPE_NOT_EQUAL:
            strcpy(out_str, "!=");
            break;
        case AST_NODE_TYPE_LOGICAL_AND:
            strcpy(out_str, "&");
            break;
        case AST_NODE_TYPE_LOGICAL_OR:
            strcpy(out_str, "|");
            break;
        case AST_NODE_TYPE_IF:
            strcpy(out_str, "if");
            break;
        case AST_NODE_TYPE_WHILE:
            strcpy(out_str, "while");
            break;
        case AST_NODE_TYPE_ATTRIBUTION:
            strcpy(out_str, "=");
            break;
        case AST_NODE_TYPE_RETURN:
            strcpy(out_str, "return");
            break;
        case AST_NODE_TYPE_FUNCTION_CALL:
            sprintf(out_str, "call %s", node->value->value);
            break;
        case AST_NODE_TYPE_FUNCTION:
            sprintf(out_str, "%s", node->value->value);
            break;
        default:
            return;
    }
    printf("%p [label=\"%s\"];\n", node, out_str);
}

void ast_node_print_tree(ast_node *node){

    if(node->type == AST_NODE_TYPE_PROGRAM_START || node->type == AST_NODE_TYPE_EMPTY){
        for(int i = 0; i < ast_node_list_size(node->children); i++){
            ast_node *child = ast_node_list_get(node->children, i);
            ast_node_print_tree(child);
        }
        return;
    }
    ast_node_print(node);
    for(int i = 0; i < ast_node_list_size(node->children); i++){
        ast_node *child = ast_node_list_get(node->children, i);
        if(child->type != AST_NODE_TYPE_EMPTY) printf("%p, %p\n", node, child);
    }
    for(int i = 0; i < ast_node_list_size(node->children); i++){
        ast_node *child = ast_node_list_get(node->children, i);
        ast_node_print_tree(child);
    }
}


void ast_node_set_children(ast_node *node, ast_node_list *children){
    ast_node_list_destroy(node->children);
    node->children = children;
}

ast_node *deconstruct_list(ast_node_list *list){
    if(ast_node_list_size(list) == 0){
        ast_node *node = ast_node_create(AST_NODE_TYPE_EMPTY, NULL);
        ast_node_list_destroy(list);
        return node;
    }
    ast_node *first = ast_node_list_pop_front(list);
    ast_node *current = first;
    while(ast_node_list_size(list) > 0){
        ast_node *next = ast_node_list_pop_front(list);
        ast_node_add_child(current, next);
        current = next;
    }
    ast_node_list_destroy(list);
    return first;
}


// List


ast_node_list *ast_node_list_create(){
    return linked_list_create((destroy_data)ast_node_destroy);
}
void ast_node_list_destroy(ast_node_list *list){
    linked_list_destroy(list);
}

void ast_node_list_clear(ast_node_list *list){
    linked_list_clear(list);
}
int ast_node_list_size(ast_node_list *list){
    return linked_list_size(list);
}
int ast_node_list_empty(ast_node_list *list){
    return linked_list_empty(list);
}
void ast_node_list_push_front(ast_node_list *list, ast_node *value){
    linked_list_push_front(list, value);
}
void ast_node_list_push_back(ast_node_list *list, ast_node *value){
    linked_list_push_back(list, value);
}
ast_node *ast_node_list_pop_front(ast_node_list *list){
    return linked_list_pop_front(list);
}
ast_node *ast_node_list_pop_back(ast_node_list *list){
    return linked_list_pop_back(list);
}
ast_node *ast_node_list_front(ast_node_list *list){
    return linked_list_front(list);
}
ast_node *ast_node_list_back(ast_node_list *list){
    return linked_list_back(list);
}
void ast_node_list_insert(ast_node_list *list, int index, ast_node *value){
    linked_list_insert(list, index, value);
}
void ast_node_list_delete(ast_node_list *list, int index){
    linked_list_delete(list, index);
}
ast_node *ast_node_list_get(ast_node_list *list, int index){
    return linked_list_get(list, index);
}
void ast_node_list_print(ast_node_list *list){
    linked_list_print(list, (print_data)ast_node_print);
}
