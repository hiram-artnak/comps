#ifndef LEXEME_H
#define LEXEME_H

typedef enum lexeme_type{
    IDENTIFIER,
    LITERAL,
} lexeme_type;

typedef struct lexeme{
    lexeme_type type;
    char *value;
    int line;
} lexeme;

lexeme *lexeme_create(lexeme_type type, char *value, int line);
void lexeme_print(lexeme *l);
void lexeme_free(lexeme *l);

#endif