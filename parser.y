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

    /* Types*/
type: TK_PR_INT;
type: TK_PR_BOOL;
type: TK_PR_FLOAT;


    /* Literals*/
literal: TK_LIT_INT | TK_LIT_FLOAT | TK_LIT_FALSE | TK_LIT_TRUE;


    /* GLOBAL VARIABLE DECLARATION */

global_variable: type TK_IDENTIFICADOR;
global_variable_name: TK_IDENTIFICADOR; 
list_of_variable_names: global_variable_name ',' list_of_variable_names | global_variable_name ;


global_variable_declaration: type list_of_variable_names ';' ;




    /* FUNCTION HEADER */

function_name: TK_IDENTIFICADOR; 
list_of_variables: global_variable ',' list_of_variables | global_variable;
list_of_parameters: '(' list_of_variables ')';
return_type: type '!';

function_header: list_of_parameters return_type function_name;


    /* FUNCTION BODY */

    /* COMMAND */ 

command:  variable_declaration | attribution | function_call | return_command | flux_control_commands;

attribution: TK_IDENTIFICADOR '=' expression;

return_command: TK_PR_RETURN expression;

arguments: list_of_variable_names | expression | arguments; 
function_call: function_name '(' arguments ')' ;

variable_declaration: type list_of_variable_names ;



    /* FLUX CONTROL COMMANDS */

flux_control_commands: if_command | while_command;

while_command: TK_PR_WHILE '(' expression ')' '{' command_block '}';

if_command: TK_PR_IF '(' expression ')' '{' command_block '}'
if_command: TK_PR_IF '(' expression ')' '{' command_block '}' TK_PR_ELSE '(' expression ')' '{' command_block '}';



    /*COMMAND BLOCK */

list_of_commands: command ';' list_of_commands |  /* vazio*/; 

command_block: list_of_commands;







    /* EXPRESSION */

operand: TK_IDENTIFICADOR | function_call | literal; 

operator: operator first_priority_operator | operator binary_operator | /*vazio*/;


expression: expression| operand | first_priority_operator;

binary_operator: second_priority_operator | third_priority_operator | fourth_priority_operator | fifth_priority_operator | sixth_priority_operator | seventh_priority_operator;


first_priority_operator: '-' operand  | '!' operand  | second_priority_operator; 


second_priority_operator: '*' operand | '/' operand | '%' operand | third_priority_operator ;


third_priority_operator: '+' operand | '+' operator | '-' operand  ; 


fourth_priority_operator: '>' operand | '<' operand | TK_OC_LE operand | TK_OC_GE operand ;


fifth_priority_operator: TK_OC_EQ operand | TK_OC_NE operand ;


sixth_priority_operator: TK_OC_AND operand ;


seventh_priority_operator: TK_OC_OR operand ;


    /* FUNCTION BODY */
function_body: '{' command_block '}';



    /* FUNCTION */
/* function: function_header function_body; */

function: expression;

%%

void yyerror (char const *s) {
    fprintf (stderr, "In line %d... %s.\n", get_line_number(), s);
} 