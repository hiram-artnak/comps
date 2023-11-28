#ifndef AST_H
#define AST_H

#include "list.h"
#include "lexeme.h"
#include "utils.h"

typedef struct ast_node{
    lexeme *value;
    char* label;
    list *children;
} ast_node;

ast_node *ast_node_new(char* label, lexeme *value);
#define _ast_node(label) (ast_node_new(label, NULL))
void ast_node_free(ast_node *node);
void ast_node_add_child(ast_node *parent, ast_node *child);
void ast_node_print(ast_node *node);
void exporta(void * arvore);

#endif