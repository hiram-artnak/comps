#include "ast.h"
#include "llist.h"
#include "lexeme.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    llist_append(parent->children, child);
}
void ast_node_remove_child(ast_node *parent, void *key, ast_match_fn match){
    llist_remove(parent->children, key, match);
}


void _ast_node_print(void *data){
    ast_node *node = (ast_node *) data;
    ast_node_print(node);
}

void _ast_node_print_depth(ast_node *node, int depth){
    int i;
    for(i = 0; i < depth; i++){
        printf("   ");
    }
    if(node->lex != NULL){
        lexeme_print(node->lex);
        printf(" ");
    }
    printf("\n");
    for(int j = 0; j < llist_length(node->children); j++){
        _ast_node_print_depth(llist_get(node->children, j), depth + 1);
    }
}

void ast_node_print(ast_node *node){
    _ast_node_print_depth(node, 0);
    printf("\n");
}