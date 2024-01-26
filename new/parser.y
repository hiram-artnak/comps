%{
int yylex(void);
void yyerror (char const *mensagem);
extern void *arvore;
%}

%code requires{
    #include "utils.h"
    #include "ast.h"
    #include "linked_list.h"
    #include <string.h>
}

%union{
    ast_node *node;
    linked_list *list;
    lexeme *lex;
}

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
%token<lex> TK_IDENTIFICADOR
%token<lex> TK_LIT_INT
%token<lex> TK_LIT_FLOAT
%token<lex> TK_LIT_FALSE
%token<lex> TK_LIT_TRUE
%token TK_ERRO

%type<node> primary
%type<node> literal
%type<node> unary
%type<node> factor
%type<node> term
%type<node> order
%type<node> identity
%type<node> and_expr
%type<node> expression

%type<node> if_command
%type<node> else_part
%type<node> while_command

%type<node> command
%type<node> attribution_command
%type<node> return_command
%type<node> function_call
%type<list> arguments

%type<list> command_block
%type<list> commands

%type<node> function
%type<lex> function_header
%type<list> function_list

%type<node> program
%%

program: /* empty */ { 
    $$ = ast_node_create(AST_NODE_TYPE_PROGRAM_START, NULL);
    arvore = $$;
}
    | program global_declaration { $$ = $1; }
    | program function_list { $$ = $1; ast_node_add_child($$, deconstruct_list($2));}
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

function_list: /* empty */ { $$ = ast_node_list_create();}
    | function_list function {ast_node_list_push_back($1, $2); $$ = $1;}
    ;

function: function_header command_block {
        ast_node *node = ast_node_create(AST_NODE_TYPE_FUNCTION, $1);
        ast_node_add_child(node, deconstruct_list($2));
        $$ = node;
}
    ;

function_header: parameter_list TK_OC_GE type '!' TK_IDENTIFICADOR {$$=$5;}
    ;

parameter_list: '('parameters')'
    ;

parameters: /* empty */
    | parameters ',' parameter
    | parameter
    ;

parameter: type TK_IDENTIFICADOR
    ;

commands: /* empty */ { $$ = ast_node_list_create();}
    | commands command {ast_node_list_push_back($1, $2); $$ = $1;}
    ;

command: command_block ';' { $$ = deconstruct_list($1);}
       | variable_declaration ';'
       | attribution_command ';' { $$ = $1;}
       | function_call ';' { $$ = $1;}
       | return_command ';' { $$ = $1;}
       | if_command ';' { $$ = $1;}
       | while_command ';' { $$ = $1;}
       ;

command_block: '{' commands '}' { $$ = $2;}
    ;

attribution_command: TK_IDENTIFICADOR '=' expression {
        ast_node *node = ast_node_create(AST_NODE_TYPE_ATTRIBUTION, $1);
        ast_node_add_child(node, $3);
        $$ = node;
}
    ;

return_command: TK_PR_RETURN expression{
        ast_node *node = ast_node_create(AST_NODE_TYPE_RETURN, NULL);
        ast_node_add_child(node, $2);
        $$ = node;
}
    ;

function_call: TK_IDENTIFICADOR '(' arguments ')'{
        ast_node *node = ast_node_create(AST_NODE_TYPE_FUNCTION_CALL, $1);
        ast_node_add_child(node, deconstruct_list($3));
        $$ = node;
}
    ;

arguments: /* empty */ { $$ = ast_node_list_create();}
    | expression {ast_node_list *list = ast_node_list_create(); ast_node_list_push_back(list, $1); $$ = list;}
    | arguments ',' expression {ast_node_list_push_back($1, $3); $$ = $1;}
    ;

if_command: TK_PR_IF '(' expression ')' command_block else_part{
            ast_node *node = ast_node_create(AST_NODE_TYPE_IF, NULL);
            ast_node_add_child(node, $3);
            ast_node_add_child(node, deconstruct_list($5));
            if($6 != NULL)
                ast_node_add_child(node, $6);
            $$ = node;
}
         ;

else_part: /* empty */ { $$ = NULL;}
         | TK_PR_ELSE command_block {
            ast_node *node = ast_node_create(AST_NODE_TYPE_ELSE, NULL);
            ast_node_add_child(node, deconstruct_list($2));
            $$ = node;
         }
         ;

while_command: TK_PR_WHILE '(' expression ')' command_block{
                ast_node *node = ast_node_create(AST_NODE_TYPE_WHILE, NULL);
                ast_node_add_child(node, $3);
                ast_node_add_child(node, deconstruct_list($5));
                $$ = node;
}
             ;

literal: TK_LIT_FALSE { ast_node *node = ast_node_create(AST_NODE_TYPE_LITERAL, $1); $$ = node;}
    | TK_LIT_TRUE { ast_node *node = ast_node_create(AST_NODE_TYPE_LITERAL, $1); $$ = node;}
    | TK_LIT_INT { ast_node *node = ast_node_create(AST_NODE_TYPE_LITERAL, $1); $$ = node;}
    | TK_LIT_FLOAT { ast_node *node = ast_node_create(AST_NODE_TYPE_LITERAL, $1); $$ = node;}
    ;

primary: TK_IDENTIFICADOR { ast_node *node = ast_node_create(AST_NODE_TYPE_IDENTIFIER, $1); $$ = node;}
    | literal { $$ = $1;}
    | function_call { $$ = $1;}
    | '(' expression ')' { $$ = $2;}
    ;

unary: primary { $$ = $1; }
    | '!' primary { ast_node *node = ast_node_create(AST_NODE_TYPE_LOGICAL_NEGATION, NULL); $$ = node;}
    | '-' primary { ast_node *node = ast_node_create(AST_NODE_TYPE_NUMERICAL_NEGATION, NULL); $$ = node;}
    ;

factor: unary { $$ = $1; }
    | factor '*' unary { 
        ast_node *node = ast_node_create(AST_NODE_TYPE_MULTIPLICATION, NULL);
        ast_node_add_child(node, $1);
        ast_node_add_child(node, $3);
        $$ = node;
        }
    | factor '/' unary {
        ast_node *node = ast_node_create(AST_NODE_TYPE_DIVISION, NULL);
        ast_node_add_child(node, $1);
        ast_node_add_child(node, $3);
        $$ = node;
    }
    | factor '%' unary{
        ast_node *node = ast_node_create(AST_NODE_TYPE_MODULO, NULL);
        ast_node_add_child(node, $1);
        ast_node_add_child(node, $3);
        $$ = node;
    }
    ;

term: factor { $$ = $1; }
    | term '+' factor {
        ast_node *node = ast_node_create(AST_NODE_TYPE_ADDITION, NULL);
        ast_node_add_child(node, $1);
        ast_node_add_child(node, $3);
        $$ = node;
    }
    | term '-' factor{
        ast_node *node = ast_node_create(AST_NODE_TYPE_SUBTRACTION, NULL);
        ast_node_add_child(node, $1);
        ast_node_add_child(node, $3);
        $$ = node;
    }
    ;

order: term { $$ = $1; }
    | order '<' term{
        ast_node *node = ast_node_create(AST_NODE_TYPE_LESS_THAN, NULL);
        ast_node_add_child(node, $1);
        ast_node_add_child(node, $3);
        $$ = node;
    }
    | order '>' term{
        ast_node *node = ast_node_create(AST_NODE_TYPE_GREATER_THAN, NULL);
        ast_node_add_child(node, $1);
        ast_node_add_child(node, $3);
        $$ = node;
    }
    | order TK_OC_GE term{
        ast_node *node = ast_node_create(AST_NODE_TYPE_GREATER_EQUAL, NULL);
        ast_node_add_child(node, $1);
        ast_node_add_child(node, $3);
        $$ = node;
    }
    | order TK_OC_LE term{
        ast_node *node = ast_node_create(AST_NODE_TYPE_LESS_EQUAL, NULL);
        ast_node_add_child(node, $1);
        ast_node_add_child(node, $3);
        $$ = node;
    }
    ;

identity: order { $$ = $1; }
    | identity TK_OC_EQ order{
        ast_node *node = ast_node_create(AST_NODE_TYPE_EQUAL, NULL);
        ast_node_add_child(node, $1);
        ast_node_add_child(node, $3);
        $$ = node;
    }
    | identity TK_OC_NE order{
        ast_node *node = ast_node_create(AST_NODE_TYPE_NOT_EQUAL, NULL);
        ast_node_add_child(node, $1);
        ast_node_add_child(node, $3);
        $$ = node;
    }
    ;

and_expr: identity { $$ = $1; }
    | and_expr TK_OC_AND identity{
        ast_node *node = ast_node_create(AST_NODE_TYPE_LOGICAL_AND, NULL);
        ast_node_add_child(node, $1);
        ast_node_add_child(node, $3);
        $$ = node;
    }
    ;

expression: and_expr { $$ = $1; }
    | expression TK_OC_OR and_expr{
        ast_node *node = ast_node_create(AST_NODE_TYPE_LOGICAL_OR, NULL);
        ast_node_add_child(node, $1);
        ast_node_add_child(node, $3);
        $$ = node;
    }
    ;

%%
