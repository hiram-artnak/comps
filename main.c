/*
Função principal para realização da análise sintática.

Este arquivo será posterioremente substituído, não acrescente nada.
*/
#include <stdio.h>
#include "parser.tab.h" //arquivo gerado com bison -d parser.y

extern int yyparse(void);
extern int yylex_destroy(void);
void *arvore = NULL;
//void exporta (void *arvore);
int main (int argc, char **argv)
{
int ret = yyparse();
//exporta (arvore);
yylex_destroy();
return ret;
}