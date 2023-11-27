#include "ast.h"
#include "lexeme.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void ast_node_destroy(void *data){
    ast_node *node = (ast_node *) data;
    if(node == NULL){
        return;
    }
    ast_node_free(node);
}

ast_node *_ast_node_create(ast_node_type type, lexeme *lex){
    ast_node *node = forced_malloc(sizeof(ast_node));
    node->type = type;
    node->lex = lex;
    node->children = forced_malloc(sizeof(list));
    list_init(node->children, ast_node_destroy);
    return node;
}

/** Dispatcher function **/
void ast_node_print(ast_node *node){
    if (node == NULL){
        return;
    }
    switch(node->type){
        case AST_NODE_FUNCTION:
            ast_node_function_print(node);
            break;
        case AST_NODE_COMMAND:
            ast_node_command_print(node);
            break;
        case AST_NODE_EXPRESSION:
            ast_node_expression_print(node);
            break;
        case AST_NODE_ATTRIBUTION:
            ast_node_attribution_print(node);
            break;
        case AST_NODE_CALL:
            ast_node_call_print(node);
            break;
        case AST_NODE_RETURN:
            ast_node_return_print(node);
            break;
        case AST_NODE_IF:
            ast_node_if_print(node);
            break;
        case AST_NODE_WHILE:
            ast_node_while_print(node);
            break;
        case AST_NODE_LITERAL:
            lexeme_print(node->lex);
            break;
        case AST_NODE_IDENTIFIER:
            lexeme_print(node->lex);
            break;
        default:
            printf("Unknown node type\n");
            break;
    }
}

/** Actual print functions **/
void ast_node_function_print(ast_node *node){
    
}
void ast_node_command_print(ast_node *node);
void ast_node_expression_print(ast_node *node);
void ast_node_attribution_print(ast_node *node);
void ast_node_call_print(ast_node *node);
void ast_node_return_print(ast_node *node);
void ast_node_if_print(ast_node *node);
void ast_node_while_print(ast_node *node);