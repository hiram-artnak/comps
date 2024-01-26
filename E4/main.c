#include <stdio.h>
#include "ast.h"
extern int yyparse(void);
extern int yylex_destroy(void);
void *arvore = NULL;
void exporta(void *arvore);

void exporta(void *arvore){
  ast_node_print_tree(arvore);
}
int main (int argc, char **argv)
{
  int ret = yyparse(); 
  exporta(arvore);
  yylex_destroy();
  return ret;
}
