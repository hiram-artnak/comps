#include "ast.h"
#include "llist.h"
#include "lexeme.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void _ast_node_print_by_type(ast_node *node);

typedef struct ast_node {
    lexeme *lex;
    ast_node_type type;
    llist *children;
} ast_node;

void _ast_node_destroy(void *data){
    ast_node *node = (ast_node *) data;
    ast_node_free(node);
}

ast_node *ast_node_create(ast_node_type type, lexeme *lex){
    // Allocate Memory //
    ast_node *node = malloc(sizeof(ast_node));
    if(node == NULL) {
        fprintf(stderr, "Error: malloc failed allocating node\n");
        exit(1);
    }
    // Set node attributes //
    node->lex = lex;
    node->type = type;
    node->children = llist_create(_ast_node_destroy);
    return node;
}

void ast_node_free(ast_node *node){
    // Validate inputs //
    if(node == NULL) {
        fprintf(stderr, "Error: tried to free node, but node is NULL\n");
        exit(1);
    }
    // Free the lexeme //
    if(node->lex != NULL){
        lexeme_free(node->lex);
    }
    // Free the children //
    llist_free(node->children);
    // Free the node //
    free(node);
}

void ast_node_add_child(ast_node *parent, ast_node *child){
    if (parent == NULL) {
        fprintf(stderr, "Error: tried to add child to NULL parent\n");
        exit(1);
    }
    if (child == NULL) {
        fprintf(stderr, "Error: tried to add NULL child to parent\n");
        exit(1);
    }
    llist_append(parent->children, child);
}
void ast_node_remove_child(ast_node *parent, void *key, ast_match_fn match){
    llist_remove(parent->children, key, match);
}



void _ast_node_print(ast_node *node){
    if(node->type != AST_NODE_TYPE_EMPTY_BLOCK){
        _ast_node_print_by_type(node);
        printf("\n");
        for(int j = 0; j < llist_length(node->children); j++){
            if( ((ast_node *) llist_get(node->children, j))->type != AST_NODE_TYPE_EMPTY_BLOCK)
                printf("%p, %p\n", node, llist_get(node->children, j));
        }
    }
    for(int j = 0; j < llist_length(node->children); j++){
        _ast_node_print(llist_get(node->children, j));
    }
}

void ast_node_print(ast_node *node){
    if (node == NULL) {
        return;
    }
    _ast_node_print(node);
}

void exporta(void *arvore){
    if (arvore == NULL) {
        return;
    }
    ast_node *node = (ast_node *) arvore;
    _ast_node_print(node);
}

void _ast_node_print_by_type(ast_node *node){
    switch(node->type){
        case AST_NODE_TYPE_FUNCTION:
            printf("%p [label=\"%s\"];", node, node->lex->value);
            break;
        case AST_NODE_TYPE_ATTRIBUTION:
            printf("%p [label=\"=\"];", node);
            break;
        case AST_NODE_TYPE_FUNCTION_CALL:
            printf("%p [label=\"call %s\"];", node, node->lex->value);
            break;
        case AST_NODE_TYPE_OP_ADD:
            printf("%p [label=\"+\"];", node);
            break;
        case AST_NODE_TYPE_OP_SUB:
            printf("%p [label=\"-\"];", node);
            break;
        case AST_NODE_TYPE_OP_MUL:
            printf("%p [label=\"*\"];", node);
            break;
        case AST_NODE_TYPE_OP_DIV:
            printf("%p [label=\"/\"];", node);
            break;
        case AST_NODE_TYPE_OP_MOD:
            printf("%p [label=\"%%\"];", node);
            break;
        case AST_NODE_TYPE_OP_AND:
            printf("%p [label=\"&\"];", node);
            break;
        case AST_NODE_TYPE_OP_OR:
            printf("%p [label=\"|\"];", node);
            break;
        case AST_NODE_TYPE_OP_EQ:
            printf("%p [label=\"==\"];", node);
            break;
        case AST_NODE_TYPE_OP_NE:
            printf("%p [label=\"!=\"];", node);
            break;
        case AST_NODE_TYPE_OP_LT:
            printf("%p [label=\"<\"];", node);
            break;
        case AST_NODE_TYPE_OP_GT:
            printf("%p [label=\">\"];", node);
            break;
        case AST_NODE_TYPE_OP_LE:
            printf("%p [label=\"<=\"];", node);
            break;
        case AST_NODE_TYPE_OP_GE:
            printf("%p [label=\">=\"];", node);
            break;
        case AST_NODE_TYPE_OP_NEG:
            printf("%p [label=\"-\"];", node);
            break;
        case AST_NODE_TYPE_OP_NOT:
            printf("%p [label=\"!\"];", node);
            break;
        case AST_NODE_TYPE_LIT_INT:
            printf("%p [label=\"%s\"];", node, node->lex->value);
            break;
        case AST_NODE_TYPE_LIT_FLOAT:
            printf("%p[label=\"%s\"];", node, node->lex->value);
            break;
        case AST_NODE_TYPE_LIT_TRUE:
            printf("%p[label=\"true\"];", node);
            break;
        case AST_NODE_TYPE_LIT_FALSE:
            printf("%p[label=\"false\"];", node);
            break;
        case AST_NODE_TYPE_IDENTIFIER:
            printf("%p[label=\"%s\"];", node, node->lex->value);
            break;
        case AST_NODE_TYPE_IF:
            printf("%p[label=\"if\"];", node);
            break;
        case AST_NODE_TYPE_WHILE:
            printf("%p[label=\"while\"];", node);
            break;
        default:
            printf("%p[label=\"unknown\"];", node);
            break;
    }
}