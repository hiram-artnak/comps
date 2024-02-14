#include "symbol.h"
#include "utils.h"
#include "ast.h"
typedef struct symbol{
    type_system_type data_type;
    symbol_type sym_type;
    lexeme *lexeme;
    int location;
}symbol;

symbol *symbol_create(type_system_type data_type, symbol_type sym_type, lexeme *lexeme, int location){
    symbol *sym = f_malloc(sizeof(symbol));
    sym->data_type = data_type;
    sym->sym_type = sym_type;
    sym->lexeme = lexeme_create(lexeme_get_value(lexeme), lexeme_get_type(lexeme), lexeme_get_line(lexeme));
    sym->location = location;
    return sym;
}

void symbol_destroy(symbol *symbol){
    lexeme_destroy(symbol->lexeme);
    f_free(symbol);
}

int symbol_get_line(symbol *symbol){
    return lexeme_get_line(symbol->lexeme);
}
char *symbol_get_value(symbol *symbol){
    return lexeme_get_value(symbol->lexeme);
}
symbol_type symbol_get_type(symbol *symbol){
    return symbol->sym_type;
}
type_system_type symbol_get_data_type(symbol *symbol){
    return symbol->data_type;
}

type_system_type type_infer(symbol *symbol_a, symbol *symbol_b){
    if (symbol_a->data_type == TYPE_SYSTEM_TYPE_FLOAT || symbol_b->data_type == TYPE_SYSTEM_TYPE_FLOAT) {
        return TYPE_SYSTEM_TYPE_FLOAT;
    }
    if (symbol_a->data_type == TYPE_SYSTEM_TYPE_INT || symbol_b->data_type == TYPE_SYSTEM_TYPE_INT) {
        return TYPE_SYSTEM_TYPE_INT;
    }
    return TYPE_SYSTEM_TYPE_BOOL;
}

hash_table *symbol_table_create(){
    return hash_table_create((destroy_data)symbol_destroy);
}

