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

typedef enum ast_node_type{
    AST_NODE_FUNCTION,
    AST_NODE_COMMAND,
    AST_NODE_EXPRESSION,
    AST_NODE_ATTRIBUTION,
    AST_NODE_FUNCTION_CALL,
    AST_NODE_RETURN,
    AST_NODE_IF,
    AST_NODE_WHILE,
} ast_node_type;

typedef struct _lexeme {
    char *value;
    lexeme_type type;
    int line;
} lexeme;

int lexeme_init(lexeme *l, char *value, lexeme_type type, int line);
int lexeme_destroy(lexeme *l);



typedef struct ast_node {
    lexeme *lexeme;
    ast_node_type type;
    struct ast_node *parent;
    list *children; // list of ast_node
} ast_node;

typedef struct ast {
    ast_node *root;
} ast;


int ast_init(ast *a);
int ast_destroy(ast *a);
int ast_set_root(ast *a, ast_node *root);
int ast_node_init(ast_node *n, ast_node_type type, lexeme *l);
int ast_node_destroy(ast_node *n);
int ast_node_add_child(ast_node *parent, ast_node *child);
int ast_node_remove_child(ast_node *parent, ast_node *child);
void ast_node_print(ast_node *n);
int ast_node_add_sibling(ast_node *n, ast_node *sibling);
int ast_node_remove_sibling(ast_node *n, ast_node *sibling);
void ast_print(ast *a);
void exporta(void *p);

#endif
