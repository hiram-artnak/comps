#include "ast.h"
#include "llist.h"
#include "lexeme.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ast_node {
    lexeme *lex;
    llist *children;
} ast_node;

void _ast_node_destroy(void *data){
    ast_node *node = (ast_node *) data;
    ast_node_free(node);
}

ast_node *ast_node_create(lexeme *lex){
    // Allocate Memory //
    ast_node *node = malloc(sizeof(ast_node));
    if(node == NULL) {
        fprintf(stderr, "Error: malloc failed allocating node\n");
        exit(1);
    }
    // Set node attributes //
    node->lex = lex;
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
    llist_append(parent->children, child);
}
void ast_node_remove_child(ast_node *parent, void *key, ast_match_fn match){
    llist_remove(parent->children, key, match);
}

void ast_node_print(ast_node *node){
    printf("(");
    lexeme_print(node->lex);
    printf(" ");
    llist_print(node->children, ast_node_print);
    printf(")");
}