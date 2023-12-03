%{
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
extern int get_line_number();
int yylex(void);
void yyerror (char const *mensagem);
%}

%code requires{
    #include "ast.h"
    #include "lexeme.h"
}

%union {
    ast_node *node;
    lexeme *lex;
}

%token<lex> TK_PR_INT
%token<lex> TK_PR_FLOAT
%token<lex> TK_PR_BOOL
%token<lex> TK_PR_IF
%token<lex> TK_PR_ELSE
%token<lex> TK_PR_WHILE
%token<lex> TK_PR_RETURN
%token<lex> TK_OC_LE
%token<lex> TK_OC_GE
%token<lex> TK_OC_EQ
%token<lex> TK_OC_NE
%token<lex> TK_OC_AND
%token<lex> TK_OC_OR
%token<lex> TK_IDENTIFICADOR
%token<lex> TK_LIT_INT
%token<lex> TK_LIT_FLOAT
%token<lex> TK_LIT_FALSE
%token<lex> TK_LIT_TRUE
%token<lex> TK_ERRO

%type<node> operand
%type<node> expr_0
%type<node> expr_1
%type<node> expr_2
%type<node> expr_3
%type<node> expr_4
%type<node> expr_5
%type<node> expr_6
%type<node> expr
%type<node> cmd
%type<node> cmd_list
%type<node> var_declaration
%type<node> id_list
%type<node> block
%type<node> expr_list
%type<node> control_flow
%type<node> f_header
%type<node> f_body
%type<node> function
%type<node> program
%define parse.error verbose
%define parse.trace

%%

/* A program is a list of variable declarations and functions, in any order */
/* The program may also be empty */
program: /* empty */ { $$ = ast_node_create(AST_NODE_TYPE_PROGRAM, NULL);}
    | program var_declaration ';' 
    | program function {ast_node_add_child($1, $2); $$ = $1;}
    ;

/* A variable declaration is a type followed by a list of identifiers */
var_declaration: type id_list {$$ = $2;}
    ;

/* A type is one of the primitive types */
type: TK_PR_INT
    | TK_PR_FLOAT
    | TK_PR_BOOL
    ;

/* A list of identifiers is a comma-separated list of identifiers */
id_list: TK_IDENTIFICADOR { $$ = ast_node_create(AST_NODE_TYPE_IDENTIFIER, $1); }
    | id_list ',' TK_IDENTIFICADOR {ast_node_add_child($1, ast_node_create(AST_NODE_TYPE_IDENTIFIER, $3)); $$ = $1;}
    ;

/* A function is made up of a header and a body*/
function: f_header f_body {ast_node_add_child($1, $2); $$ = $1;}
    ;

/* A function header is a parameter list, the TK_OC_GE token, a type, the '!' token and an identifier */    
f_header: '(' param_list ')' TK_OC_GE type '!' TK_IDENTIFICADOR { $$ = ast_node_create(AST_NODE_TYPE_FUNCTION, $7); }
/* the parameter list may be empty */
    | '(' ')' TK_OC_GE type '!' TK_IDENTIFICADOR { $$ = ast_node_create(AST_NODE_TYPE_FUNCTION, $6);}
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
block: '{' cmd_list '}' { $$ = $2;}
    /* A block may be empty */
    |'{''}' { $$ = ast_node_create(AST_NODE_TYPE_EMPTY_BLOCK, NULL);}
    ;

/* A list of commands is a list of commands separated by semicolons */
cmd_list: cmd ';'
    | cmd_list cmd ';' {ast_node_add_child($1, $2); $$ = $1;}
    ;

/* A command is one of the following */
/* A variable declaration */
cmd: var_declaration
/* An assignment */
    | TK_IDENTIFICADOR '=' expr {ast_node *node = ast_node_create(AST_NODE_TYPE_ATTRIBUTION, NULL); ast_node_add_child(node, ast_node_create(AST_NODE_TYPE_IDENTIFIER, $1)); ast_node_add_child(node, $3); $$ = node;}
/* A function call */
    | TK_IDENTIFICADOR '(' expr_list ')' {ast_node *node = ast_node_create(AST_NODE_TYPE_FUNCTION_CALL, $1); ast_node_add_child(node, $3); $$ = node;} 
    | TK_IDENTIFICADOR '(' ')' {ast_node *node = ast_node_create(AST_NODE_TYPE_FUNCTION_CALL, $1); $$ = node;}
/* A return statement */
    | TK_PR_RETURN expr {ast_node *node = ast_node_create(AST_NODE_TYPE_RETURN, NULL); ast_node_add_child(node, $2); $$ = node;}
/* A control flow statement */
    | control_flow 
/* A block */
    | block
    ;

expr: expr_6
    | expr TK_OC_OR expr_6 {ast_node *node = ast_node_create(AST_NODE_TYPE_OP_OR, NULL); ast_node_add_child(node, $1); ast_node_add_child(node, $3); $$ = node;}
    ;

expr_6: expr_5
    | expr_6 TK_OC_AND expr_5 {ast_node *node = ast_node_create(AST_NODE_TYPE_OP_AND, NULL); ast_node_add_child(node, $1); ast_node_add_child(node, $3); $$ = node;}
    ;

expr_5: expr_4
    | expr_5 TK_OC_EQ expr_4 {ast_node *node = ast_node_create(AST_NODE_TYPE_OP_EQ, NULL); ast_node_add_child(node, $1); ast_node_add_child(node, $3); $$ = node;}
    | expr_5 TK_OC_NE expr_4 {ast_node *node = ast_node_create(AST_NODE_TYPE_OP_NE, NULL); ast_node_add_child(node, $1); ast_node_add_child(node, $3); $$ = node;}
    ;

expr_4: expr_3
    | expr_4 '<' expr_3 {ast_node *node = ast_node_create(AST_NODE_TYPE_OP_LT, NULL); ast_node_add_child(node, $1); ast_node_add_child(node, $3); $$ = node;}
    | expr_4 '>' expr_3 {ast_node *node = ast_node_create(AST_NODE_TYPE_OP_GT, NULL); ast_node_add_child(node, $1); ast_node_add_child(node, $3); $$ = node;}
    | expr_4 TK_OC_LE expr_3 {ast_node *node = ast_node_create(AST_NODE_TYPE_OP_LE, NULL); ast_node_add_child(node, $1); ast_node_add_child(node, $3); $$ = node;}
    | expr_4 TK_OC_GE expr_3 {ast_node *node = ast_node_create(AST_NODE_TYPE_OP_GE, NULL); ast_node_add_child(node, $1); ast_node_add_child(node, $3); $$ = node;}
    ;

expr_3: expr_2
    | expr_3 '+' expr_2 {ast_node *node = ast_node_create(AST_NODE_TYPE_OP_ADD, NULL); ast_node_add_child(node, $1); ast_node_add_child(node, $3); $$ = node;}
    | expr_3 '-' expr_2 {ast_node *node = ast_node_create(AST_NODE_TYPE_OP_SUB, NULL); ast_node_add_child(node, $1); ast_node_add_child(node, $3); $$ = node;}
    ;

expr_2: expr_1
    | expr_2 '*' expr_1 {ast_node *node = ast_node_create(AST_NODE_TYPE_OP_MUL, NULL); ast_node_add_child(node, $1); ast_node_add_child(node, $3); $$ = node;}
    | expr_2 '/' expr_1 {ast_node *node = ast_node_create(AST_NODE_TYPE_OP_DIV, NULL); ast_node_add_child(node, $1); ast_node_add_child(node, $3); $$ = node;}
    | expr_2 '%' expr_1 {ast_node *node = ast_node_create(AST_NODE_TYPE_OP_MOD, NULL); ast_node_add_child(node, $1); ast_node_add_child(node, $3); $$ = node;}
    ;

expr_1: expr_0
    | '!' expr_0 {ast_node *node = ast_node_create(AST_NODE_TYPE_OP_NOT, NULL); ast_node_add_child(node, $2); $$ = node;}
    | '-' expr_0 {ast_node *node = ast_node_create(AST_NODE_TYPE_OP_NEG, NULL); ast_node_add_child(node, $2); $$ = node;}
    ;

expr_0: '(' expr ')' {$$ = $2;}
    | operand
    ;

operand: TK_IDENTIFICADOR { ast_node *node = ast_node_create(AST_NODE_TYPE_IDENTIFIER, $1); $$ = node; }
    | TK_LIT_INT {ast_node *node = ast_node_create(AST_NODE_TYPE_LIT_INT, $1); $$ = node; }
    | TK_LIT_FLOAT {ast_node *node = ast_node_create(AST_NODE_TYPE_LIT_FLOAT, $1); $$ = node;}
    | TK_LIT_FALSE {ast_node *node = ast_node_create(AST_NODE_TYPE_LIT_FALSE, $1); $$ = node;}
    | TK_LIT_TRUE {ast_node *node = ast_node_create(AST_NODE_TYPE_LIT_TRUE, $1); $$ = node;}
    ;

expr_list: expr { $$ = $1;}
    | expr_list ',' expr {ast_node_add_child($1, $3); $$ = $1;}
    ;

/* A control flow statement is one of the following */
/* An if statement */
control_flow: TK_PR_IF '(' expr ')' block {ast_node *node = ast_node_create(AST_NODE_TYPE_IF, NULL); ast_node_add_child(node, $3); ast_node_add_child(node, $5); $$ = node;}
    | TK_PR_IF '(' expr ')' block TK_PR_ELSE block {ast_node *node = ast_node_create(AST_NODE_TYPE_IF, NULL); ast_node_add_child(node, $3); ast_node_add_child(node, $5); ast_node_add_child(node, $7); $$ = node;}
/* A while statement */
    | TK_PR_WHILE '(' expr ')' block {ast_node *node = ast_node_create(AST_NODE_TYPE_WHILE, NULL); ast_node_add_child(node, $3); ast_node_add_child(node, $5); $$ = node;}
    ;

%%

void yyerror (char const *s) {
    fprintf (stderr, "In line %d... %s.\n", get_line_number(), s);
} 