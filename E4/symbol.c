#include "symbol.h"
#include "utils.h"
symbol *symbol_create(unsigned int line, symbol_type symbol_type, type_system_type data_type, lexeme *lexeme){
    symbol *s = f_malloc(sizeof(symbol));
    s->line = line;
    s->symbol_type = symbol_type;
    s->data_type = data_type;
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