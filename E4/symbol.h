#ifndef SYMBOL_H
#define SYMBOL_H

#include "ast.h"

typedef enum symbol_type{
    SYMBOL_TYPE_LITERAL,
    SYMBOL_TYPE_IDENTIFIER,
    SYMBOL_TYPE_FUNCTION
}symbol_type;

typedef struct symbol{
    unsigned int line;
    symbol_type symbol_type;
    type_system_type data_type;
    lexeme *lexeme;
}symbol;

symbol *symbol_create(unsigned int line, symbol_type symbol_type, type_system_type data_type, lexeme *lexeme);
void symbol_destroy(symbol *symbol);
type_system_type type_infer(symbol *symbol_a, symbol *symbol_b);

#endif