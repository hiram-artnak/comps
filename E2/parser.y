%{
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
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
%define parse.trace

%%

/* A program is a list of variable declarations and functions, in any order */
/* The program may also be empty */
program: /* empty */
    | program var_declaration ';'
    | program function
    ;

/* A variable declaration is a type followed by a list of identifiers */
var_declaration: type id_list
    ;

/* A type is one of the primitive types */
type: TK_PR_INT
    | TK_PR_FLOAT
    | TK_PR_BOOL
    ;

/* A list of identifiers is a comma-separated list of identifiers */
id_list: TK_IDENTIFICADOR
    | id_list ',' TK_IDENTIFICADOR
    ;

/* A function is made up of a header and a body*/
function: f_header f_body
    ;

/* A function header is a parameter list, the TK_OC_GE token, a type, the '!' token and an identifier */    
f_header: '(' param_list ')' TK_OC_GE type '!' TK_IDENTIFICADOR
/* the parameter list may be empty */
    | '(' ')' TK_OC_GE type '!' TK_IDENTIFICADOR
    ;

/* A parameter list is a list of parameters separated by commas */
param_list: param
    | param_list ',' param
    ;

/* A parameter is a type and an identifier */
param: type TK_IDENTIFICADOR
    ;

/* A function body is a command block */
f_body: block
    ;

/* A command block is a list of commands enclosed by curly braces, followed by a semicolon*/
block: '{' cmd_list '}'
    /* A block may be empty */
    |'{''}'
    ;

/* A list of commands is a list of commands separated by semicolons */
cmd_list: cmd ';'
    | cmd_list cmd ';'
    ;

/* A command is one of the following */
/* A variable declaration */
cmd: var_declaration
/* An assignment */
    | TK_IDENTIFICADOR '=' expr
/* A function call */
    | TK_IDENTIFICADOR '(' expr_list ')'
    | TK_IDENTIFICADOR '(' ')'
/* A return statement */
    | TK_PR_RETURN expr 
/* A control flow statement */
    | control_flow 
/* A block */
    | block
    ;

expr: expr_6
    | expr TK_OC_OR expr_6
    ;

expr_6: expr_5
    | expr_6 TK_OC_AND expr_5
    ;

expr_5: expr_4
    | expr_5 TK_OC_EQ expr_4
    | expr_5 TK_OC_NE expr_4
    ;

expr_4: expr_3
    | expr_4 '<' expr_3
    | expr_4 '>' expr_3
    | expr_4 TK_OC_LE expr_3
    | expr_4 TK_OC_GE expr_3
    ;

expr_3: expr_2
    | expr_3 '+' expr_2
    | expr_3 '-' expr_2
    ;

expr_2: expr_1
    | expr_2 '*' expr_1
    | expr_2 '/' expr_1
    | expr_2 '%' expr_1
    ;

expr_1: expr_0
    | '!' expr_0
    | '-' expr_0
    ;

expr_0: '(' expr ')'
    | operand
    ;

operand: TK_IDENTIFICADOR
    | TK_LIT_INT
    | TK_LIT_FLOAT
    | TK_LIT_FALSE
    | TK_LIT_TRUE
    ;

expr_list: expr
    | expr_list ',' expr
    ;

/* A control flow statement is one of the following */
/* An if statement */
control_flow: TK_PR_IF '(' expr ')' block
    | TK_PR_IF '(' expr ')' block TK_PR_ELSE block
/* A while statement */
    | TK_PR_WHILE '(' expr ')' block
    ;

%%

void yyerror (char const *s) {
    fprintf (stderr, "In line %d... %s.\n", get_line_number(), s);
} 