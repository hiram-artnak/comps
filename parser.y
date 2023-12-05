%{
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
extern int get_line_number();
int yylex(void);
void yyerror (char const *mensagem);
extern void* arvore;
%}

%code requires{
    #include "ast.h"
    #include "lexeme.h"
    #include "llist.h"
}

%union {
    ast_node *node;
    lexeme *lex;
    llist *list;
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
%type<list> cmd_list
%type<node> var_declaration
%type<node> id_list
%type<node> block
%type<list> expr_list
%type<node> control_flow
%type<node> f_header
%type<node> f_body
%type<node> function
%type<node> program
%type<node> null_program
%type<node> actual_program_1
%type<node> actual_program_2
%type<list> function_list
%define parse.error verbose
%define parse.trace

%%

/* A program is a list of variable declarations and functions, in any order */
/* The program may also be empty */
program: null_program { $$ = NULL;}
    | actual_program_1
    | actual_program_2 { $$ = $1;}
    ;

null_program: /* empty */
    ;

actual_program_1: var_declaration ';' {$$ = NULL;}
    | actual_program_2 var_declaration ';' {$$ = $1;}
    | actual_program_1 var_declaration ';'{$$ = $1;}
    ;

actual_program_2: function_list {ast_node *func = (ast_node *)llist_get($1, 0); arvore = func; $$ = func; llist_free_wo_destroy($1);}
    | actual_program_1 function_list {
        ast_node *func = (ast_node *)llist_get($2, 0);
        llist_free_wo_destroy($2);
        if($1 == NULL){
            $$ = func;
        } else {
        ast_node_add_child($1, func); $$ = $1;
        arvore = $1;
        }
    }
    ;


function_list: function { llist* list = llist_create(NULL); llist_append(list, (void*) $1); $$ = list;}
    | function_list function {ast_node *last = (ast_node *)llist_get_tail($1); ast_node_add_child(last, $2); llist_append($1, (void *) $2); $$ = $1;}
    ;

/* A variable declaration is a type followed by a list of identifiers */
var_declaration: type id_list {$$ = NULL;}
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
function: f_header f_body {
    if ($2 != NULL){
    ast_node_add_child($1, $2);
    }
    $$ = $1;
}
    ;

/* A function header is a parameter list, the TK_OC_GE token, a type, the '!' token and an identifier */    
f_header: '(' param_list ')' TK_OC_GE type '!' TK_IDENTIFICADOR { $$ = ast_node_create(AST_NODE_TYPE_FUNCTION, $7);}
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
f_body: block {$$ = $1;}
    ;

/* A command block is a list of commands enclosed by curly braces, followed by a semicolon*/
block: '{' cmd_list '}' {
    if ($2 == NULL){
        $$ = NULL;
    } else {
    ast_node *cmds = llist_get($2, 0); $$ = cmds; llist_free_wo_destroy($2);
    }
}
    /* A block may be empty */
    |'{''}' { $$ = ast_node_create(AST_NODE_TYPE_EMPTY_BLOCK, NULL);}
    ;

/* A list of commands is a list of commands separated by semicolons */
cmd_list: cmd ';' {
    if ($1 == NULL) {
        $$ = NULL;
    } else {
    llist* list = llist_create(NULL); llist_append(list, (void*) $1); $$ = list;
    }
}
    | cmd_list cmd ';' {
        if ($2 == NULL) {
            $$ = $1;
        } else if ($1 == NULL){
            llist* list = llist_create(NULL); llist_append(list, (void*) $2); $$ = list;
        } else {
        ast_node *last = (ast_node *)llist_get_tail($1);
        ast_node_add_child(last, $2);
        llist_append($1, (void *) $2); $$ = $1;
    }
}
    ;

/* A command is one of the following */
/* A variable declaration */
cmd: var_declaration
/* An assignment */
    | TK_IDENTIFICADOR '=' expr {ast_node *node = ast_node_create(AST_NODE_TYPE_ATTRIBUTION, NULL); ast_node_add_child(node, ast_node_create(AST_NODE_TYPE_IDENTIFIER, $1)); ast_node_add_child(node, $3); $$ = node;}
/* A function call */
    | TK_IDENTIFICADOR '(' expr_list ')' {ast_node *expr = (ast_node*)llist_get($3, 0); ast_node *node = ast_node_create(AST_NODE_TYPE_FUNCTION_CALL, $1); ast_node_add_child(node, expr); $$ = node; llist_free_wo_destroy($3);} 
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
    | TK_IDENTIFICADOR '(' expr_list ')' {ast_node *expr = (ast_node*)llist_get($3, 0); ast_node *node = ast_node_create(AST_NODE_TYPE_FUNCTION_CALL, $1); ast_node_add_child(node, expr); $$ = node; llist_free_wo_destroy($3);} 
    | TK_IDENTIFICADOR '(' ')' {ast_node *node = ast_node_create(AST_NODE_TYPE_FUNCTION_CALL, $1); $$ = node;}
    ;

expr_list: expr { llist* list = llist_create(NULL); llist_append(list, (void*) $1); $$ = list;}
    | expr_list ',' expr {ast_node *last = (ast_node *)llist_get_tail($1); ast_node_add_child(last, $3); llist_append($1, (void *) $3); $$ = $1;}
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