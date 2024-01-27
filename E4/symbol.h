#ifndef SYMBOL_H
#define SYMBOL_H

#include "ast.h"
#include "hash_table.h"
typedef enum symbol_type{
    SYMBOL_TYPE_LITERAL,
    SYMBOL_TYPE_IDENTIFIER,
    SYMBOL_TYPE_FUNCTION
}symbol_type;

typedef struct symbol{
    type_system_type data_type;
    symbol_type sym_type;
    lexeme *lexeme;
}symbol;

symbol *symbol_create(type_system_type data_type, symbol_type sym_type, lexeme *lexeme);
void symbol_destroy(symbol *symbol);
type_system_type type_infer(symbol *symbol_a, symbol *symbol_b);

hash_table *symbol_table_create();
void destroy_symbol_key_value(void *data);

#endif