#ifndef AST_H
#define AST_H

#include "lexeme.h"

typedef enum ast_node_type{
    AST_NODE_TYPE_PROGRAM,
    AST_NODE_TYPE_FUNCTION,
    AST_NODE_TYPE_STATEMENT,
    AST_NODE_TYPE_EXPRESSION,
    AST_NODE_TYPE_IDENTIFIER, 
    AST_NODE_TYPE_LIT_INT,      //foi
    AST_NODE_TYPE_LIT_FLOAT,    //foi       
    AST_NODE_TYPE_LIT_TRUE,     //foi
    AST_NODE_TYPE_LIT_FALSE,    //foi   
    AST_NODE_TYPE_OP_NOT,       //foi   
    AST_NODE_TYPE_OP_ADD,       //foi   
    AST_NODE_TYPE_OP_SUB,       //foi
    AST_NODE_TYPE_OP_MUL,       //foi
    AST_NODE_TYPE_OP_DIV,       //foi
    AST_NODE_TYPE_OP_MOD,          //foi
    AST_NODE_TYPE_OP_AND,       //foi
    AST_NODE_TYPE_OP_OR,        //foi
    AST_NODE_TYPE_OP_EQ,        //foi
    AST_NODE_TYPE_OP_NE,        //foi   
    AST_NODE_TYPE_OP_LT,        //foi
    AST_NODE_TYPE_OP_GT,        //foi
    AST_NODE_TYPE_OP_LE,        //foi
    AST_NODE_TYPE_OP_GE,        //foi   
    AST_NODE_TYPE_OP_NEG,       //foi
    AST_NODE_TYPE_DECLARATION,
    AST_NODE_TYPE_ATTRIBUTION,
    AST_NODE_TYPE_ASSIGNMENT,
    AST_NODE_TYPE_FUNCTION_CALL,
    AST_NODE_TYPE_RETURN,
    AST_NODE_TYPE_IF,
    AST_NODE_TYPE_WHILE,
    AST_NODE_TYPE_UNKNOWN,
    AST_NODE_TYPE_EMPTY_BLOCK,
} ast_node_type;

typedef struct ast_node ast_node;
typedef char (*ast_match_fn)(void *key, void *data);

ast_node *ast_node_create(ast_node_type type, lexeme *lex);
void ast_node_free(ast_node *node);
void ast_node_add_child(ast_node *parent, ast_node *child);
void ast_node_remove_child(ast_node *parent, void *key, ast_match_fn match);
void ast_node_print(ast_node *node);
void exporta(void *arvore);
#endif