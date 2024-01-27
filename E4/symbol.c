#include "symbol.h"
#include "utils.h"

symbol *symbol_create(type_system_type data_type, symbol_type sym_type, lexeme *lexeme){
    symbol *s = f_malloc(sizeof(symbol));
    s->data_type = data_type;
    s->sym_type = sym_type;
    s->lexeme = lexeme;
    return s;

}
void symbol_destroy(symbol *symbol){
    lexeme_destroy(symbol->lexeme);
    f_free(symbol);
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
    return hash_table_create(destroy_symbol_key_value);
}