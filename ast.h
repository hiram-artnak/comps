#ifndef AST_H
#define AST_H

#include "list.h"
#include "lexeme.h"

typedef enum ast_node_type{
    AST_NODE_FUNCTION, 
    AST_NODE_COMMAND,
    AST_NODE_EXPRESSION,
    AST_NODE_ATTRIBUTION,
    AST_NODE_CALL,
    AST_NODE_RETURN,
    AST_NODE_IF,
    AST_NODE_WHILE,
    AST_NODE_LITERAL,
    AST_NODE_IDENTIFIER,
} ast_node_type;


typedef struct ast_node{
    lexeme *lex;
    ast_node_type type;
    list *children;
} ast_node;

/**  **/
ast_node *ast_node_create(ast_node_type type, lexeme *lex);

#define ast_node_create(type) (ast_node_create(type, NULL))
#define ast_node_function() (ast_node_create(AST_NODE_FUNCTION))
#define ast_node_command() (ast_node_create(AST_NODE_COMMAND))
#define ast_node_expression() (ast_node_create(AST_NODE_EXPRESSION))
#define ast_node_attribution() (ast_node_create(AST_NODE_ATTRIBUTION))
#define ast_node_call() (ast_node_create(AST_NODE_CALL))
#define ast_node_return() (ast_node_create(AST_NODE_RETURN))
#define ast_node_if() (ast_node_create(AST_NODE_IF))
#define ast_node_while() (ast_node_create(AST_NODE_WHILE))
#define ast_node_literal(value, line_n) (ast_node_create(AST_NODE_LITERAL, lexeme_literal(value, line_n)))
#define ast_node_identifier(value, line_n) (ast_node_create(AST_NODE_IDENTIFIER, lexeme_identifier(value, line_n)))

/** Dispatcher function **/
void ast_node_print(ast_node *node);

/** Actual print functions **/
void ast_node_function_print(ast_node *node);
void ast_node_command_print(ast_node *node);
void ast_node_expression_print(ast_node *node);
void ast_node_attribution_print(ast_node *node);
void ast_node_call_print(ast_node *node);
void ast_node_return_print(ast_node *node);
void ast_node_if_print(ast_node *node);
void ast_node_while_print(ast_node *node);

/** Unsafe add child **/
int ast_node_add_child(ast_node *parent, ast_node *child);

/** Add child with checks **/
int ast_node_function_add_child(ast_node *parent, ast_node *child);
int ast_node_command_add_child(ast_node *parent, ast_node *child);
int ast_node_expression_add_child(ast_node *parent, ast_node *child);
int ast_node_attribution_add_child(ast_node *parent, ast_node *child);
int ast_node_call_add_child(ast_node *parent, ast_node *child);
int ast_node_return_add_child(ast_node *parent, ast_node *child);
int ast_node_if_add_child(ast_node *parent, ast_node *child);
int ast_node_while_add_child(ast_node *parent, ast_node *child);

/** Unsafe remove child **/
int ast_node_remove_child(ast_node *parent, ast_node *child);

/** Print whole ast depth-first **/
void ast_dfprint(ast_node *node);

/** Free Node **/
void ast_node_free(ast_node *node);

/** Free whole ast **/
void ast_free(ast_node *node);

#endif