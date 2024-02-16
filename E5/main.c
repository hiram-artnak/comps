#include <stdio.h>
#include "ast.h"
#include "iloc.h"
extern int yyparse(void);
extern int yylex_destroy(void);
void *arvore = NULL;
void exporta(void *arvore);

int main (int argc, char **argv)
{
  int ret = yyparse(); 
  //exporta(arvore);
  iloc_instr_list *list = ast_node_get_code(arvore);
  for(int i = 0; i < iloc_instr_list_size(list); i++){
    iloc_instr *instr = iloc_instr_list_get(list, i);
    printf("%s\n", iloc_instr_to_string(instr));
  }
  yylex_destroy();
  return ret;
}
