#include "lexeme.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

lexeme *lexeme_create(lexeme_type type, char *value, int line){
    lexeme *l = malloc(sizeof(lexeme));
    if(l == NULL) {
        fprintf(stderr, "Error: malloc failed allocating lexeme\n");
        exit(1);
    }
    l->type = type;
    l->value = malloc(sizeof(char) * (strlen(value) + 1));
    if(l->value == NULL) {
        fprintf(stderr, "Error: malloc failed allocating lexeme value\n");
        exit(1);
    }
    strcpy(l->value, value);
    l->line = line;
    return l;
}
void lexeme_print(lexeme *l){
    printf("%s", l->value);
}
void lexeme_free(lexeme *l){
    if(l == NULL) {
        fprintf(stderr, "Error: tried to free lexeme, but lexeme is NULL\n");
        exit(1);
    }
    if(l->value == NULL) {
        fprintf(stderr, "Error: tried to free value from lexeme, but lexeme->value is NULL\n");
        exit(1);
    }
    free(l->value);
    free(l);
}
