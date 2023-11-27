#include "lexeme.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

lexeme *lexeme_new(lexeme_type type, char *value, int line){
    lexeme *l = forced_malloc(sizeof(lexeme));
    l->type = type;
    l->value = forced_malloc(sizeof(char) * (strlen(value) + 1));
    strcpy(l->value, value);
    l->line = line;
    return l;
}

void lexeme_free(lexeme *l){
    free(l->value);
    free(l);
}

char* lexeme_type_to_string(lexeme_type lt){
    if(lt == LEXEME_IDENTIFIER){
        return "IDENTIFIER";
    } else if(lt == LEXEME_LITERAL){
        return "LITERAL";
    }
    return NULL;
}

char* lexeme_to_string(lexeme *l){
    char *type = lexeme_type_to_string(l->type);
    char *str = forced_malloc(sizeof(char) * (strlen(type) + strlen(l->value) + 6));
    sprintf(str, "[%s - %d] %s", type, l->line, l->value);
    return str;
}
void lexeme_print(lexeme *l){
    char *str = lexeme_to_string(l);
    printf("%s\n", str);
    free(str);
}
