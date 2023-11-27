#include "ast.h"
#include "list.h"
#include <stdlib.h>
#include <string.h>



/*** Lexeme functions ***/
int lexeme_init(lexeme *l, char *value, lexeme_type type, int line){
    l->value = forced_malloc(strlen(value) + 1);
    strcpy(l->value, value);
    l->type = LEXEME_TYPE_UNKNOWN;
    l->line = line;
    return 0;
}

int lexeme_destroy(lexeme *l){
    if(l->value == NULL){
        // Already destroyed
        return 1;
    }
    free(l->value);
    l->value = NULL;
    l->type = -1;
    l->line = -1;
    return 0;
}

void _ast_node_destroy(void *data){
    ast_node_destroy((ast_node *)data);
    return;
}

/*** ast_node fuctions ***/
int ast_node_destroy(ast_node *n){
    if(n == NULL){
        // Tried to destroy a NULL node
        // No double frees allowed
        return 1;
    }

    if(n->lexeme != NULL){
        lexeme_destroy(n->lexeme);
        free(n->lexeme);
        n->lexeme = NULL;
    }

    if(n->children != NULL){
        list_destroy(n->children);
        free(n->children);
        n->children = NULL;
    }

    free(n);
    return 0;
}

int ast_node_init(ast_node *n, lexeme *l){
    n->lexeme = forced_malloc(sizeof(lexeme));
    lexeme_init(n->lexeme, l->value, l->type, l->line);
    n->parent = NULL;
    n->children = forced_malloc(sizeof(list));
    list_init(n->children, _ast_node_destroy);
    return 0;
}

int ast_node_add_child(ast_node *parent, ast_node *child){
    if(parent == NULL || child == NULL){
        return 1; // NULL nodes are not allowed
    }
    if(child->parent != NULL){
        return 2; // child already has a parent
    }
    child->parent = parent;
    list_add(parent->children, child);
    return 0;
}

int _ast_node_compare(void *data1, void *data2){
    ast_node *n1 = (ast_node *)data1;
    ast_node *n2 = (ast_node *)data2;
    int same_type = n1->lexeme->type == n2->lexeme->type;
    int same_value = strcmp(n1->lexeme->value, n2->lexeme->value) == 0;
    int same_line = n1->lexeme->line == n2->lexeme->line;
    return same_type && same_value && same_line;
}

int ast_node_remove_child(ast_node *parent, ast_node *child){
    if(parent == NULL || child == NULL){
        return 1; // NULL nodes are not allowed
    }
    if(child->parent != parent){
        return 2; // child does not have parent
    }
    child->parent = NULL;
    list_remove(parent->children, child, _ast_node_compare);
    return 0;
}

int ast_node_add_sibling(ast_node *n, ast_node *sibling){
    if(n == NULL || sibling == NULL){
        return 1; // NULL nodes are not allowed
    }
    if(n->parent == NULL){
        return 2; // n has no parent
    }
    return ast_node_add_child(n->parent, sibling);
}

int ast_node_remove_sibling(ast_node *n, ast_node *sibling){
    if(n == NULL || sibling == NULL){
        return 1; // NULL nodes are not allowed
    }
    if(n->parent == NULL){
        return 2; // n has no parent
    }
    return ast_node_remove_child(n->parent, sibling);
}

void print_ast_node(ast_node *n){
    printf("%p [label=\"%s\"];", n, n->lexeme->value);
    if(n->children->size == 0){
        return;
    }
    node *curr = n->children->head;
    while(curr != NULL){
        printf("%p, %p", n, curr->data);
        curr = curr->next;
    }
    return;
}

// Depth first print of the tree
int _ast_node_print(ast_node *n){
    if(n == NULL){
        return 1;
    }
    printf("%s\n", n->lexeme->value);
    node *curr = n->children->head;
    while(curr != NULL){
        _ast_node_print((ast_node *)curr->data);
        curr = curr->next;
    }
    return 0;
}