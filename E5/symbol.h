#ifndef SYMBOL_H
#define SYMBOL_H

#include "ast.h"
#include "hash_table.h"
typedef enum symbol_type{
    SYMBOL_TYPE_LITERAL,
    SYMBOL_TYPE_IDENTIFIER,
    SYMBOL_TYPE_FUNCTION
}symbol_type;

typedef struct symbol symbol;

symbol *symbol_create(type_system_type data_type, symbol_type sym_type, lexeme *lexeme, int location);
void symbol_destroy(symbol *symbol);
int symbol_get_line(symbol *symbol);
int symbol_get_location(symbol *symbol);
char *symbol_get_value(symbol *symbol);
symbol_type symbol_get_type(symbol *symbol);
type_system_type symbol_get_data_type(symbol *symbol);
type_system_type type_infer(symbol *symbol_a, symbol *symbol_b);
hash_table *symbol_table_create();



#endif