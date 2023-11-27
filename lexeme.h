/**
 * Header file for a lexeme struct
 **/

#ifndef LEXEME_H
#define LEXEME_H

typedef enum lexeme_type{
    LEXEME_IDENTIFIER,
    LEXEME_LITERAL
} lexeme_type;

char* lexeme_type_to_string(lexeme_type type);

typedef struct lexeme {
    lexeme_type type;
    char *value;
    int line;
} lexeme;


lexeme *lexeme_new(lexeme_type type, char *value, int line);
#define lexeme_identifier(value, line) (lexeme_new(LEXEME_IDENTIFIER, value, line))
#define lexeme_literal(value, line) (lexeme_new(LEXEME_LITERAL, value, line))

void lexeme_free(lexeme *l);
char* lexeme_to_string(lexeme *l);
void lexeme_print(lexeme *l);


#define lexeme_get_type(l) (l->type)
#define lexeme_get_value(l) (l->value)
#define lexeme_get_line(l) (l->line)


#endif