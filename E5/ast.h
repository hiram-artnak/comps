#ifndef AST_H
#define AST_H

#include "iloc.h"

typedef enum type_system_type{
    TYPE_SYSTEM_TYPE_INT,
    TYPE_SYSTEM_TYPE_FLOAT,
    TYPE_SYSTEM_TYPE_BOOL,
    TYPE_SYSTEM_TYPE_FAKE
} type_system_type;

typedef enum lexeme_type{
    LEXEME_TYPE_IDENTIFIER,
    LEXEME_TYPE_LITERAL
} lexeme_type;

typedef enum ast_node_type{
    // EXPRESSIONS
    AST_NODE_TYPE_IDENTIFIER,
    AST_NODE_TYPE_LITERAL,
    AST_NODE_TYPE_LOGICAL_NEGATION,
    AST_NODE_TYPE_NUMERICAL_NEGATION,
    AST_NODE_TYPE_MULTIPLICATION,
    AST_NODE_TYPE_DIVISION,
    AST_NODE_TYPE_MODULO,
    AST_NODE_TYPE_ADDITION,
    AST_NODE_TYPE_SUBTRACTION,
    AST_NODE_TYPE_LESS_THAN,
    AST_NODE_TYPE_GREATER_THAN,
    AST_NODE_TYPE_LESS_EQUAL,
    AST_NODE_TYPE_GREATER_EQUAL,
    AST_NODE_TYPE_EQUAL,
    AST_NODE_TYPE_NOT_EQUAL,
    AST_NODE_TYPE_LOGICAL_AND,
    AST_NODE_TYPE_LOGICAL_OR,
    //
    // CONTROL FLOW
    AST_NODE_TYPE_IF,
    AST_NODE_TYPE_ELSE,
    AST_NODE_TYPE_WHILE,
    //
    // COMMANDS
    AST_NODE_TYPE_ATTRIBUTION,
    AST_NODE_TYPE_RETURN,
    AST_NODE_TYPE_FUNCTION_CALL,
    //
    //FUNCTION
    AST_NODE_TYPE_FUNCTION,
    //
    // SPECIAL
    AST_NODE_TYPE_EMPTY,
    AST_NODE_TYPE_PROGRAM_START,
} ast_node_type;

typedef struct lexeme lexeme;

lexeme *lexeme_create(char *value, lexeme_type type, int line);
void lexeme_destroy(lexeme *l);
char* lexeme_get_value(lexeme *l);
lexeme_type lexeme_get_type(lexeme *l);
int lexeme_get_line(lexeme *l);

typedef struct ast_node ast_node;

ast_node *ast_node_create(ast_node_type node_type, lexeme *lex, type_system_type data_type);
void ast_node_destroy(ast_node *node);
void ast_node_add_child(ast_node *parent, ast_node *child);
void ast_node_set_node_type(ast_node *node, ast_node_type node_type);
void ast_node_set_data_type(ast_node *node, type_system_type data_type);
void ast_node_set_lexeme(ast_node *node, lexeme *lex);
ast_node_type ast_node_get_node_type(ast_node *node);
type_system_type ast_node_get_data_type(ast_node *node);
lexeme *ast_node_get_lexeme(ast_node *node);
char *ast_node_get_lexeme_value(ast_node *node);

// TO DO
char* ast_node_get_temporary(ast_node *node);
void ast_node_set_temporary(ast_node *node, char *temporary);
iloc_instr_list *ast_node_get_code(ast_node *node);
void ast_node_add_code(ast_node *node, iloc_instr *code);


ast_node *ast_node_get_child(ast_node *node, int index);
int ast_node_get_children_count(ast_node *node);
void ast_node_print(ast_node *node);
void ast_node_print_tree(ast_node *node);

typedef struct ast_node_list ast_node_list;

ast_node_list *ast_node_list_create();
void ast_node_list_destroy(ast_node_list *list);
void ast_node_list_push_front(ast_node_list *list, ast_node *node);
void ast_node_list_push_back(ast_node_list *list, ast_node *node);
ast_node *ast_node_list_pop_front(ast_node_list *list);
ast_node *ast_node_list_pop_back(ast_node_list *list);
ast_node *ast_node_list_front(ast_node_list *list);
ast_node *ast_node_list_back(ast_node_list *list);
ast_node *ast_node_list_get(ast_node_list *list, int index);
int ast_node_list_size(ast_node_list *list);

type_system_type ast_node_type_infer(ast_node *node_a, ast_node *node_b);
int ast_node_get_line_number(ast_node *node);

#endif