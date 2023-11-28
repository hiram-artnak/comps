%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern int get_line_number();
extern void *arvore;
int yylex(void);
void yyerror (char const *mensagem);
%}
%code requires { #include "lexeme.h" 
                 #include "ast.h"
                }
%union{
    lexeme *lexeme;
    ast_node *ast_node;
}

%token<lexeme> TK_PR_INT
%token<lexeme> TK_PR_FLOAT
%token<lexeme> TK_PR_BOOL
%token<lexeme> TK_PR_IF
%token<lexeme> TK_PR_ELSE
%token<lexeme> TK_PR_WHILE
%token<lexeme> TK_PR_RETURN
%token<lexeme> TK_OC_LE
%token<lexeme> TK_OC_GE
%token<lexeme> TK_OC_EQ
%token<lexeme> TK_OC_NE
%token<lexeme> TK_OC_AND
%token<lexeme> TK_OC_OR
%token<lexeme> TK_IDENTIFICADOR
%token<lexeme> TK_LIT_INT
%token<lexeme> TK_LIT_FLOAT
%token<lexeme> TK_LIT_FALSE
%token<lexeme> TK_LIT_TRUE
%token<lexeme> TK_ERRO


%type<ast_node> program
%type<ast_node> var_declaration
%type<lexeme> type
%type<ast_node> id_list
%type<ast_node> function
%type<lexeme> f_header
%type<ast_node> f_body
%type<lexeme> param_list
%type<lexeme> param
%type<ast_node> block
%type<ast_node> cmd_list
%type<ast_node> cmd
%type<ast_node> expr
%type<ast_node> expr_6
%type<ast_node> expr_5
%type<ast_node> expr_4
%type<ast_node> expr_3
%type<ast_node> expr_2
%type<ast_node> expr_1
%type<ast_node> expr_0
%type<ast_node> operand
%type<ast_node> expr_list
%type<ast_node> control_flow


%define parse.error verbose
%define parse.trace

%%

/* A program is a list of variable declarations and functions, in any order */
/* The program may also be empty */
program: /* empty */ {arvore = NULL;}
    | program var_declaration ';' 
    | program function {ast_node_add_child($1, $2); $$ = $1; arvore = (void*)$1;}
    ;

/* A variable declaration is a type followed by a list of identifiers */
var_declaration: type id_list { $$ = $2;}
    ;

/* A type is one of the primitive types */
type: TK_PR_INT
    | TK_PR_FLOAT
    | TK_PR_BOOL
    ;

/* A list of identifiers is a comma-separated list of identifiers */
id_list: TK_IDENTIFICADOR { $$ = ast_node_new($1->value, $1);}
    | id_list ',' TK_IDENTIFICADOR {ast_node* id = ast_node_new($3->value, $3); ast_node_add_child($1, id); $$ = $1;}
    ;

/* A function is made up of a header and a body*/
function: f_header f_body { ast_node* n = _ast_node($1->value); ast_node_add_child(n,$2); $$ = n;}
    ;

/* A function header is a parameter list, the TK_OC_GE token, a type, the '!' token and an identifier */    
f_header: '(' param_list ')' TK_OC_GE type '!' TK_IDENTIFICADOR {$$ = $7;}
/* the parameter list may be empty */
    | '(' ')' TK_OC_GE type '!' TK_IDENTIFICADOR {$$ = $6;}
    ;

/* A parameter list is a list of parameters separated by commas */
param_list: param
    | param_list ',' param
    ;

/* A parameter is a type and an identifier */
param: type TK_IDENTIFICADOR { $$ = $2;}
    ;

/* A function body is a command block */
f_body: block
    ;

/* A command block is a list of commands enclosed by curly braces, followed by a semicolon*/
block: '{' cmd_list '}' { $$ = $2;}
    /* A block may be empty */
    |'{''}' { $$ = NULL;}
    ;

/* A list of commands is a list of commands separated by semicolons */
cmd_list: cmd ';'
    | cmd_list cmd ';' {ast_node_add_child($1, $2); $$ = $1;}
    ;

/* A command is one of the following */
/* A variable declaration */
cmd: var_declaration
/* An assignment */
    | TK_IDENTIFICADOR '=' expr { ast_node* n = _ast_node("="); ast_node *id = ast_node_new($1->value, $1); ast_node_add_child(n, id); ast_node_add_child(n,$3); $$ = n;}
/* A function call */
    | TK_IDENTIFICADOR '(' expr_list ')' {char* value = forced_malloc(strlen($1->value) + 6); 
                                        sprintf(value, "call %s", $1->value); 
                                        ast_node* n = _ast_node(value);
                                        ast_node* id = ast_node_new($1->value, $1);
                                        ast_node_add_child(n, id); ast_node_add_child(n,$3); $$ = n;}

    | TK_IDENTIFICADOR '(' ')' {char* value = forced_malloc(strlen($1->value) + 6); 
                                sprintf(value, "call %s", $1->value); 
                                ast_node* n = _ast_node(value);
                                ast_node* id = ast_node_new($1->value, $1);
                                ast_node_add_child(n, id); $$ = n;}
/* A return statement */
    | TK_PR_RETURN expr  { ast_node* n = _ast_node("return"); ast_node_add_child(n, $2); $$ = n;}
/* A control flow statement */
    | control_flow 
/* A block */
    | block
    ;

expr: expr_6
    | expr TK_OC_OR expr_6 { ast_node* n = _ast_node("|"); ast_node_add_child(n, $1); ast_node_add_child(n,$3); $$ = n;}
    ;

expr_6: expr_5
    | expr_6 TK_OC_AND expr_5 { ast_node* n = _ast_node("&"); ast_node_add_child(n, $1); ast_node_add_child(n,$3); $$ = n;}
    ;

expr_5: expr_4
    | expr_5 TK_OC_EQ expr_4 { ast_node* n = _ast_node("=="); ast_node_add_child(n, $1); ast_node_add_child(n,$3); $$ = n;}
    | expr_5 TK_OC_NE expr_4 { ast_node* n = _ast_node("!="); ast_node_add_child(n, $1); ast_node_add_child(n,$3); $$ = n;}
    ;

expr_4: expr_3
    | expr_4 '<' expr_3 { ast_node* n = _ast_node("<"); ast_node_add_child(n, $1); ast_node_add_child(n,$3); $$ = n;}
    | expr_4 '>' expr_3 { ast_node* n = _ast_node(">"); ast_node_add_child(n, $1); ast_node_add_child(n,$3); $$ = n;}
    | expr_4 TK_OC_LE expr_3 { ast_node* n = _ast_node("<="); ast_node_add_child(n, $1); ast_node_add_child(n,$3); $$ = n;}
    | expr_4 TK_OC_GE expr_3 { ast_node* n = _ast_node(">="); ast_node_add_child(n, $1); ast_node_add_child(n,$3); $$ = n;}
    ;

expr_3: expr_2
    | expr_3 '+' expr_2 { ast_node* n = _ast_node("+"); ast_node_add_child(n, $1); ast_node_add_child(n,$3); $$ = n;}
    | expr_3 '-' expr_2 { ast_node* n = _ast_node("-"); ast_node_add_child(n, $1); ast_node_add_child(n,$3); $$ = n;}
    ;

expr_2: expr_1
    | expr_2 '*' expr_1 { ast_node* n = _ast_node("*"); ast_node_add_child(n, $1); ast_node_add_child(n,$3); $$ = n;}
    | expr_2 '/' expr_1 { ast_node* n = _ast_node("/"); ast_node_add_child(n, $1); ast_node_add_child(n,$3); $$ = n;}
    | expr_2 '%' expr_1 { ast_node* n = _ast_node("%"); ast_node_add_child(n, $1); ast_node_add_child(n,$3); $$ = n;}
    ;

expr_1: expr_0
    | '!' expr_0 { ast_node* n = _ast_node("!"); ast_node_add_child(n, $2); $$ = n;}
    | '-' expr_0 { ast_node* n = _ast_node("-"); ast_node_add_child(n, $2); $$ = n;}
    ;

expr_0: '(' expr ')' { $$ = $2;}
    | operand
    ;

operand: TK_IDENTIFICADOR {$$ = ast_node_new($1->value, $1);}
    | TK_LIT_INT {$$ = ast_node_new($1->value, $1);}
    | TK_LIT_FLOAT {$$ = ast_node_new($1->value, $1);}
    | TK_LIT_FALSE {$$ = ast_node_new($1->value, $1);}
    | TK_LIT_TRUE {$$ = ast_node_new($1->value, $1);}
    ;

expr_list: expr
    | expr_list ',' expr {ast_node_add_child($1, $3); $$ = $1;}
    ;

/* A control flow statement is one of the following */
/* An if statement */
control_flow: TK_PR_IF '(' expr ')' block { ast_node* n = _ast_node("if"); ast_node_add_child(n, $3); if($5 != NULL) ast_node_add_child(n,$5); $$ = n;}
    | TK_PR_IF '(' expr ')' block TK_PR_ELSE block { ast_node* n = _ast_node("if"); ast_node_add_child(n, $3); if($5!=NULL) ast_node_add_child(n,$5); ast_node_add_child(n,$7); $$ = n;}
/* A while statement */
    | TK_PR_WHILE '(' expr ')' block { ast_node* n = _ast_node("while"); ast_node_add_child(n, $3); if($5!=NULL) ast_node_add_child(n,$5); $$ = n;}
    ;

%%

void yyerror (char const *s) {
    fprintf (stderr, "In line %d... %s.\n", get_line_number(), s);
} 