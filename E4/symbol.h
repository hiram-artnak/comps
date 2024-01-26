#ifndef SYMBOL_H
#define SYMBOL_H

#include "ast.h"

typedef enum SymbolType{
    SYMBOL_TYPE_LITERAL,
    SYMBOL_TYPE_IDENTIFIER,
    SYMBOL_TYPE_FUNCTION
}SymbolType;

typedef enum Type{

}Type;  

typedef struct Symbol{
    unsigned int line;
    SymbolType symbol_type;
    Type data_type;
    lexeme *lexeme;
}Symbol;




#endif