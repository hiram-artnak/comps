#ifndef AST_H
#define AST_H

/**
 * Header file for an AST data-structure
**/
#include "list.h"

typedef enum lexeme_type{
    LEXEME_TYPE_UNKNOWN,
    LEXEME_TYPE_IDENTIFIER,
    LEXEME_TYPE_LITERAL,
} lexeme_type;

typedef struct _lexeme {
    char *value;
    lexeme_type type;
    int line;
} lexeme;

int lexeme_init(lexeme *l, char *value, lexeme_type type, int line);
int lexeme_destroy(lexeme *l);



typedef struct ast_node {
    lexeme *lexeme;
    struct ast_node *parent;
    list *children; // list of ast_node
} ast_node;

typedef struct ast {
    ast_node *root;
} ast;


int ast_init(ast *a);
int ast_destroy(ast *a);
int ast_node_init(ast_node *n, lexeme *l);
int ast_node_destroy(ast_node *n);
int ast_node_add_child(ast_node *parent, ast_node *child);
int ast_node_remove_child(ast_node *parent, ast_node *child);
int ast_node_print(ast_node *n);
int ast_node_add_sibling(ast_node *n, ast_node *sibling);
int ast_node_remove_sibling(ast_node *n, ast_node *sibling);
int ast_print(ast *a);

#endif
