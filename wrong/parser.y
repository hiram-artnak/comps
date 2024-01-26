%{
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

%%

program: /* empty */
    | program global_declaration
    | program function
    ;

global_declaration: variable_declaration ';'
    ;

variable_declaration: type identifier_list

type: TK_PR_INT
    | TK_PR_FLOAT
    | TK_PR_BOOL
    ;

identifier_list: TK_IDENTIFICADOR
    | identifier_list ',' TK_IDENTIFICADOR
    ;

function: function_header command_block
    ;

function_header: parameter_list TK_OC_GE type '!' TK_IDENTIFICADOR
    ;

parameter_list: '('parameters')'
    ;

parameters: /* empty */
    | parameters ',' parameter
    | parameter
    ;

parameter: type TK_IDENTIFICADOR
    ;

commands: /* empty */
    | commands command
    ;

command: command_block ';'
       | variable_declaration ';'
       | attribution_command ';'
       | function_call ';'
       | return_command ';'
       | if_command ';'
       | while_command ';'
       ;

command_block: '{' commands '}'
    ;

attribution_command: TK_IDENTIFICADOR '=' expression
    ;

return_command: TK_PR_RETURN expression
    ;

function_call: TK_IDENTIFICADOR '(' arguments ')'
    ;

arguments: /* empty */
    | expression
    | arguments ',' expression
    ;

if_command: TK_PR_IF '(' expression ')' command_block else_part
         ;

else_part: /* empty */
         | TK_PR_ELSE command_block
         ;

while_command: TK_PR_WHILE '(' expression ')' command_block
             ;

literal: TK_LIT_FALSE
    | TK_LIT_TRUE
    | TK_LIT_INT
    | TK_LIT_FLOAT
    ;

primary: TK_IDENTIFICADOR
    | literal
    | function_call
    | '(' expression ')'
    ;

unary: primary
    | '!' primary
    | '-' primary
    ;

factor: unary
    | factor '*' unary
    | factor '/' unary
    | factor '%' unary
    ;

term: factor
    | term '+' factor
    | term '-' factor
    ;

order: term
    | order '<' term
    | order '>' term
    | order TK_OC_GE term
    | order TK_OC_LE term
    ;

identity: order
    | identity TK_OC_EQ order
    | identity TK_OC_NE order
    ;

and_expr: identity
    | and_expr TK_OC_AND identity
    ;

expression: and_expr
    | expression TK_OC_OR and_expr
    ;

%%
