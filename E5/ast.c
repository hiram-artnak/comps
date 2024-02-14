#include "ast.h"
#include "linked_list.h"
#include "utils.h"
#include <string.h>
#include <stdio.h>
#include "iloc.h"
typedef struct lexeme{
    char *value;
    int line;
    lexeme_type type;
} lexeme;

typedef struct ast_node{
    lexeme *lexeme;
    ast_node_list *children;
    ast_node_type type;
    char* temporary;
    iloc_instr_list *code;
    type_system_type data_type;
} ast_node;

lexeme *lexeme_create(char *value, lexeme_type type,  int line){
    lexeme *l = f_malloc(sizeof(lexeme));
    l->type = type;
    l->value = f_malloc(strlen(value) + 1);
    strcpy(l->value, value);
    l->line = line;
    return l;
}

void lexeme_destroy(lexeme *l){
    f_free(l->value);
    f_free(l);
}

char* lexeme_get_value(lexeme *l){
    return l->value;
}
lexeme_type lexeme_get_type(lexeme *l){
    return l->type;
}
int lexeme_get_line(lexeme *l){
    return l->line;
}

ast_node *ast_node_create(ast_node_type node_type, lexeme *lex, type_system_type data_type){
    ast_node *node = f_malloc(sizeof(ast_node));
    node->children = ast_node_list_create((destroy_data)ast_node_destroy);
    node->type = node_type;
    node->data_type = data_type;
    node->lexeme = lex;
    node->temporary = NULL;
    node->code = iloc_instr_list_create();
    return node;

}
void ast_node_destroy(ast_node *node){
    ast_node_list_destroy(node->children);
    lexeme_destroy(node->lexeme);
    f_free(node->temporary);
    iloc_instr_list_destroy(node->code);
    f_free(node);
}

void ast_node_add_child(ast_node *parent, ast_node *child){
    ast_node_list_push_back(parent->children, child);
}
void ast_node_set_node_type(ast_node *node, ast_node_type node_type){
    node->type = node_type;
}

void ast_node_set_data_type(ast_node *node, type_system_type data_type){
    node->data_type = data_type;
}

void ast_node_set_lexeme(ast_node *node, lexeme *lex){
    node->lexeme = lex;
}
ast_node_type ast_node_get_node_type(ast_node *node){
    return node->type;
}
type_system_type ast_node_get_data_type(ast_node *node){
    return node->data_type;
}
lexeme *ast_node_get_lexeme(ast_node *node){
    return node->lexeme;
}
char *ast_node_get_lexeme_value(ast_node *node){
    return lexeme_get_value(node->lexeme);
}
ast_node *ast_node_get_child(ast_node *node, int index){
    return ast_node_list_get(node->children, index);
}
int ast_node_get_children_count(ast_node *node){
    return ast_node_list_size(node->children);
}
void ast_node_print(ast_node *node){
    if(node->type == AST_NODE_TYPE_EMPTY){
        return;
    }
    // prints pointer position [label="value"]
    char out_str[100];
    switch (node->type){
        case AST_NODE_TYPE_IDENTIFIER:
            strcpy(out_str, node->lexeme->value);
            break;
        case AST_NODE_TYPE_LITERAL:
            strcpy(out_str, node->lexeme->value);
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
            strcpy(out_str, "%");
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
            sprintf(out_str, "call %s", node->lexeme->value);
            break;
        case AST_NODE_TYPE_FUNCTION:
            sprintf(out_str, "%s", node->lexeme->value);
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

void exporta(void *arvore){
  ast_node_print_tree(arvore);
}


typedef ast_node_list ast_node_list;

ast_node_list *ast_node_list_create(){
    return (ast_node_list*) linked_list_create((destroy_data) ast_node_destroy);

}
void ast_node_list_destroy(ast_node_list *list){
    linked_list_destroy((linked_list*)list);
}
void ast_node_list_push_front(ast_node_list *list, ast_node *node){
    linked_list_push_front((linked_list*)list, (void *) node);
}
void ast_node_list_push_back(ast_node_list *list, ast_node *node){
    linked_list_push_back((linked_list*)list, (void *) node);

}
ast_node *ast_node_list_pop_front(ast_node_list *list){
    return (ast_node *) linked_list_pop_front((linked_list*)list);
}
ast_node *ast_node_list_pop_back(ast_node_list *list){
    return (ast_node *) linked_list_pop_back((linked_list*)list);
}
ast_node *ast_node_list_front(ast_node_list *list){
    return (ast_node *) linked_list_front((linked_list*)list);
}
ast_node *ast_node_list_back(ast_node_list *list){
    return (ast_node *) linked_list_back((linked_list*)list);
}
ast_node *ast_node_list_get(ast_node_list *list, int index){
    return (ast_node *) linked_list_get((linked_list*)list, index);
}
int ast_node_list_size(ast_node_list *list){
    return linked_list_size((linked_list*)list);
}

type_system_type ast_node_type_infer(ast_node *node_a, ast_node *node_b){
    if(node_a->data_type == TYPE_SYSTEM_TYPE_FLOAT || node_b->data_type == TYPE_SYSTEM_TYPE_FLOAT){
        return TYPE_SYSTEM_TYPE_FLOAT;
    }
    if(node_a->data_type == TYPE_SYSTEM_TYPE_INT || node_b->data_type == TYPE_SYSTEM_TYPE_INT){
        return TYPE_SYSTEM_TYPE_INT;
    }
    return TYPE_SYSTEM_TYPE_BOOL;
}


int ast_node_get_line_number(ast_node *node){
    return lexeme_get_line(node->lexeme);
}

char* ast_node_get_temporary(ast_node *node){
    return node->temporary;
}
void ast_node_set_temporary(ast_node *node, char *temporary){
    // Copy the string
    node->temporary = f_malloc(strlen(temporary) + 1);
    strcpy(node->temporary, temporary);
}
iloc_instr_list *ast_node_get_code(ast_node *node){
    return node->code;
}
void ast_node_add_code(ast_node *node, iloc_instr *code){
    iloc_instr_list_push_back(node->code, code);
}