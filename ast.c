#include "ast.h"
#include "list.h"
#include "lexeme.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ast_node_destroy(void *data){
    ast_node *node = (ast_node *) data;
    ast_node_free(node);
}

ast_node *ast_node_new(char* label, lexeme *value){
    ast_node *node = forced_malloc(sizeof(ast_node));
    node->label = forced_malloc(sizeof(char) * (strlen(label) + 1));
    strcpy(node->label, label);
    node->value = value;
    node->children = forced_malloc(sizeof(list));
    list_init(node->children, ast_node_destroy);
    return node;
}

void ast_node_free(ast_node *node){
    free(node->label);
    if (node->value != NULL){
        lexeme_free(node->value);
    }
    list_destroy(node->children);
    free(node);
}

void ast_node_add_child(ast_node *parent, ast_node *child){
    if(child == NULL) return;
    list_add(parent->children, child);
}

void ast_node_print(ast_node *node){
    printf("%p [label=\"%s\"]", node, node->label);
}

void exporta(void *arvore){
    if(arvore == NULL) return;
    // Depth first search
    ast_node *tree_node = (ast_node *) arvore;
    ast_node_print(tree_node);
    node *child = tree_node->children->head;
    while(child != NULL){
        printf("%p %p\n", tree_node, child->data);
        child = child->next;
    }
    child = tree_node->children->head;
    while(child != NULL){
        exporta(child->data);
        child = child->next;
    }
}