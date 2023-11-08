%{
#include "parser.tab.h"
#include <stdio.h>
extern int get_line_number();
int yylex(void);
void yyerror (char const *mensagem);
%}

%token TK_PR_INT
%token TK_PR_FLOAT
%token TK_PR_BOOL
%token TK_PR_IF
%token TK_PR_ELSE
%token TK_PR_WHILE
%token TK_PR_RETURN
%token TK_OC_LE
%token TK_OC_GE
%token TK_OC_EQ
%token TK_OC_NE
%token TK_OC_AND
%token TK_OC_OR
%token TK_IDENTIFICADOR
%token TK_LIT_INT
%token TK_LIT_FLOAT
%token TK_LIT_FALSE
%token TK_LIT_TRUE
%token TK_ERRO

%define parse.error verbose

%%

programa: list;
programa: /* vazio */;

list: list element;
list: element;

element: function; 
element: global_variable_declaration;


type: TK_PR_INT;
type: TK_PR_BOOL;
type: TK_PR_FLOAT;




global_variable: type TK_IDENTIFICADOR;
global_variable_name: TK_IDENTIFICADOR; 



global_variable_declaration: type list_of_variable_names ';' ;

list_of_variable_names: global_variable_name ',' list_of_variable_names | global_variable_name ;


list_of_variables: global_variable ',' list_of_variables | global_variable;



function_name: TK_IDENTIFICADOR;

function_body: '{' '}';

function_header: list_of_parameters return_type function_name;

list_of_parameters: '(' list_of_variables ')';

return_type: type '!';

function: function_header function_body;

%%

void yyerror (char const *s) {
    fprintf (stderr, "In line %d... %s.\n", get_line_number(), s);
}