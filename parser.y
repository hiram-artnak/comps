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

/* A program is a list of variable declarations and functions, in any order */
/* The program may also be empty */
program: /* empty */
    | program var_declaration
    | program function
    ;

/* A variable declaration is a type followed by a list of identifiers */
/* The identifiers are separated by commas */
var_declaration:
    type id_list ';'
    ;

/* An identifier list is a list of identifiers separated by commas */
id_list:
    TK_IDENTIFICADOR
    | id_list ',' TK_IDENTIFICADOR
    ;

/* A type is one of the primitive types */
type:
    TK_PR_INT
    | TK_PR_FLOAT
    | TK_PR_BOOL
    ;

/* A function is a parameter list followed by TK_OC_GE, followed by the return type, followed by the '!' token, followed by a block */
function:
    '(' param_list ')' TK_OC_GE type '!' TK_IDENTIFICADOR block
    ;

/* A parameter list is a (possibly empty) list of parameters separated by commas */
param_list:
    /* empty */
    | param
    | param_list ',' param
    ;

/* A parameter is a type followed by an identifier */
param: type TK_IDENTIFICADOR
    ;

/* A block is a list of statements surrounded by curly braces */
/* The list of statements may be empty */
block: '{' statement_list '}'
    ;

/* A statement list is a (possibly empty) list of statements */
statement_list:
    /* empty */
    | statement
    | statement_list statement
    ;

/* A statement is either a variable declaration, a block, a function call, attribution, return or a control statement */
statement:
    var_declaration
    | block
    | function_call ';'
    | attribution ';'
    | return_statement ';'
    | control_statement
    ;

/* A function call is an identifier followed by a list of expressions surrounded by parentheses */
function_call:
    TK_IDENTIFICADOR '(' expr_list ')'
    ;


/* An attribution is an identifier followed by the '=' token followed by an expression */
attribution:
    TK_IDENTIFICADOR '=' expr
    ;


/* A return statement is the TK_PR_RETURN token followed by an expression */
return_statement:
    TK_PR_RETURN expr
    ;


/* A control statement is an if statement or a while statement */
control_statement:
    if_statement
    | while_statement
    ;

/* An if statement is the TK_PR_IF token followed by an expression, followed by a block, followed by an optional else statement */
if_statement: TK_PR_IF '(' expr ')' block else_statement
            | TK_PR_IF '(' expr ')' block
            ;

/* An else statement is the TK_PR_ELSE token followed by a block */
else_statement: TK_PR_ELSE block;

/* A while statement is the TK_PR_WHILE token followed by an expression, followed by a block */
while_statement: TK_PR_WHILE '(' expr ')' block
                ;


/* An expression list is a (possibly empty) list of expressions separated by commas */
expr_list:
    /* empty */
    | expr
    | expr_list ',' expr
    ;


/* An operand is an identifier, a literal or a function call */
operand:
    TK_IDENTIFICADOR
    | literal
    | function_call
    ;

/* A literal is an integer, a float, false or true */
literal:
    TK_LIT_INT
    | TK_LIT_FLOAT
    | TK_LIT_FALSE
    | TK_LIT_TRUE
    ;

/* A parenthesis expression is an expression surrounded by parentheses */
parenthesis_expr: operand
    | '(' expr ')'
    ;

/* An unary expression is a unary operator followed by an expression */
unary_expr: parenthesis_expr
    | '-' expr
    | '!' expr
    ;

/* a factor is a multiplication, division or modulo operation */
factor: unary_expr
    | factor '*' unary_expr
    | factor '/' unary_expr
    | factor '%' unary_expr
    ;

/* a term is an addition or subtraction operation */
term: factor
    | term '+' factor
    | term '-' factor
    ;


/* an ordering expression is less than, greater than, less than or equal to, greater than or equal to */
ordering_expr: term
    | ordering_expr '<' term
    | ordering_expr '>' term
    | ordering_expr TK_OC_LE term
    | ordering_expr TK_OC_GE term
    ;


/* an equality expression is equal to or not equal to*/
equality_expr: ordering_expr
    | equality_expr TK_OC_EQ ordering_expr
    | equality_expr TK_OC_NE ordering_expr
    ;

/* an and expression uses the AND token */
and_expr: equality_expr
    | and_expr TK_OC_AND equality_expr
    ;

/* an or expression uses the OR token */
or_expr: and_expr
    | or_expr TK_OC_OR and_expr
    ;

/* an expression is an or expression */
expr: or_expr
    ;
%%

void yyerror (char const *s) {
    fprintf (stderr, "In line %d... %s.\n", get_line_number(), s);
} 