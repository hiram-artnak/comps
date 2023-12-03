#ifndef AST_H
#define AST_H

#include "lexeme.h"

typedef struct ast_node ast_node;

typedef char (*ast_match_fn)(void *key, void *data);

ast_node *ast_node_create(lexeme *lex);
void ast_node_free(ast_node *node);
void ast_node_add_child(ast_node *parent, ast_node *child);
void ast_node_remove_child(ast_node *parent, void *key, ast_match_fn match);
void ast_node_print(ast_node *node);
#endif