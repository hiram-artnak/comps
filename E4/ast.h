#ifndef AST_H
#define AST_H

#include "linked_list.h"

typedef enum type_system_type{
    TYPE_SYSTEM_TYPE_INT,
    TYPE_SYSTEM_TYPE_FLOAT,
    TYPE_SYSTEM_TYPE_BOOL,
    TYPE_SYSTEM_TYPE_FAKE
}type_system_type;  

typedef struct lexeme lexeme;

typedef enum lexeme_type{
    LEXEME_TYPE_IDENTIFIER,
    LEXEME_TYPE_LITERAL
}lexeme_type;

lexeme *lexeme_create(char *value, int line, lexeme_type type);
void lexeme_destroy(lexeme *l);

typedef struct ast_node ast_node;
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
}ast_node_type;

// Special list for ast_node
typedef linked_list ast_node_list;

ast_node *ast_node_create(ast_node_type type, lexeme *value, type_system_type data_type);
void ast_node_destroy(ast_node *node);
void ast_node_add_child(ast_node *node, ast_node *child);
void ast_node_print(ast_node *node);
void ast_node_print_tree(ast_node *node);
void ast_node_set_children(ast_node *node, ast_node_list *children);
ast_node *deconstruct_list(ast_node_list *list);
void ast_node_set_type(ast_node *node, ast_node_type type);


ast_node_list *ast_node_list_create();
void ast_node_list_destroy(ast_node_list *list);
void ast_node_list_clear(ast_node_list *list);
int ast_node_list_size(ast_node_list *list);
int ast_node_list_empty(ast_node_list *list);
void ast_node_list_push_front(ast_node_list *list, ast_node *value);
void ast_node_list_push_back(ast_node_list *list, ast_node *value);
ast_node *ast_node_list_pop_front(ast_node_list *list);
ast_node *ast_node_list_pop_back(ast_node_list *list);
ast_node *ast_node_list_front(ast_node_list *list);
ast_node *ast_node_list_back(ast_node_list *list);
void ast_node_list_insert(ast_node_list *list, int index, ast_node *value);
void ast_node_list_delete(ast_node_list *list, int index);
ast_node *ast_node_list_get(ast_node_list *list, int index);
void ast_node_list_print(ast_node_list *list);



#endif