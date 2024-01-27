%{
int yylex(void);
void yyerror (char const *mensagem);
extern void *arvore;
extern int get_line_number();
#include <string.h>
#include "ast.h"
#include "stack.h"
#include "hash_table.h"

stack *scope_stack = NULL;
ast_node* current_function = NULL;
%}

%code requires{
    
    #include "utils.h"
    #include "ast.h"
    #include "stack.h"
    #include "symbol.h"
    #include "hash_table.h"
    #include "linked_list.h"
    #include "parse_utils.h"
    #include <string.h>
    #include <stdio.h>
}

%union{
    ast_node *node;
    linked_list *list;
    lexeme *lex;
    type_system_type data_type;
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
%type<node> variable_declaration
%type<node> attribution_command
%type<node> return_command
%type<node> function_call
%type<list> arguments

%type<list> command_block
%type<list> commands

%type<node> function
%type<node> function_header

%type<node> identifier

%type<node> program

%type<data_type> type
%%

program: /* empty */ { 
    $$ = ast_node_create(AST_NODE_TYPE_PROGRAM_START, NULL, TYPE_SYSTEM_TYPE_FAKE);
    arvore = $$;
}
    | program global_declaration { $$ = $1; }
    | program function {
        if(current_function != NULL){
            ast_node_add_child(current_function, $2);
        }else{
            ast_node_add_child($1, $2);

        }
        current_function = $2; $$ = $1;
    }
    ;



global_declaration: variable_declaration ';'
    ;

variable_declaration: type identifier_list {
    $$ = ast_node_create(AST_NODE_TYPE_EMPTY, NULL, $1);
    // Add list of identifiers to the symbol table
    int size = linked_list_size($2);
    for(int i = 0; i < size; i++){

        ast_node *cur_node = linked_list_get($2, i);
        fail_if_declared(scope_stack, cur_node);
        symbol *sym = symbol_create($1, SYMBOL_TYPE_IDENTIFIER, cur_node->lexeme);
    }
}
    ;

type: TK_PR_INT {
    stack_create_if_null(&scope_stack, (destroy_data)hash_table_destroy);
    $$ = TYPE_SYSTEM_TYPE_INT;
    }
    | TK_PR_FLOAT{
    stack_create_if_null(&scope_stack, (destroy_data)hash_table_destroy);
    $$ = TYPE_SYSTEM_TYPE_FLOAT;
    }
    | TK_PR_BOOL{
    stack_create_if_null(&scope_stack, (destroy_data)hash_table_destroy);
    $$ = TYPE_SYSTEM_TYPE_BOOL;
    }
    ;

identifier: TK_IDENTIFICADOR { ast_node *node = ast_node_create(AST_NODE_TYPE_IDENTIFIER, $1, TYPE_SYSTEM_TYPE_FAKE); $$ = node;}
    ;

identifier_list: identifier
    | identifier_list ',' identifier
    ;

function: function_header command_block {
        ast_node *node = $1;
        ast_node_add_child(node, deconstruct_list($2));
        $$ = node;
}
    ;

function_header: parameter_list TK_OC_GE type '!' identifier {$$=$5; ast_node_set_type($$, AST_NODE_TYPE_FUNCTION);}
    ;

parameter_list: '('parameters')'{ stack_create_if_null(&scope_stack, (destroy_data)hash_table_destroy);}
    ;

parameters: /* empty */
    | parameters ',' parameter
    | parameter
    ;

parameter: type identifier
    ;

commands: /* empty */ { $$ = ast_node_list_create();}
    | commands command {ast_node_list_push_back($1, $2); $$ = $1;}
    ;

command: command_block ';' { $$ = deconstruct_list($1);}
       | variable_declaration ';' { $$ = $1;}
       | attribution_command ';' { $$ = $1;}
       | function_call ';' { $$ = $1;}
       | return_command ';' { $$ = $1;}
       | if_command ';' { $$ = $1;}
       | while_command ';' { $$ = $1;}
       ;

command_block: '{' commands '}' { $$ = $2;}
    ;

attribution_command: identifier '=' expression {
        ast_node *node = ast_node_create(AST_NODE_TYPE_ATTRIBUTION, NULL, TYPE_SYSTEM_TYPE_FAKE);
        ast_node_add_child(node, $1);
        ast_node_add_child(node, $3);
        $$ = node;
}
    ;

return_command: TK_PR_RETURN expression{
        ast_node *node = ast_node_create(AST_NODE_TYPE_RETURN, NULL, TYPE_SYSTEM_TYPE_FAKE);
        ast_node_add_child(node, $2);
        $$ = node;
}
    ;

function_call: identifier '(' arguments ')'{
        ast_node *node = $1;
        ast_node_set_type(node, AST_NODE_TYPE_FUNCTION_CALL);
        ast_node_add_child(node, deconstruct_list($3));
        $$ = node;
}
    ;

arguments: /* empty */ { $$ = ast_node_list_create();}
    | expression {ast_node_list *list = ast_node_list_create(); ast_node_list_push_back(list, $1); $$ = list;}
    | arguments ',' expression {ast_node_list_push_back($1, $3); $$ = $1;}
    ;

if_command: TK_PR_IF '(' expression ')' command_block else_part{
            ast_node *node = ast_node_create(AST_NODE_TYPE_IF, NULL, TYPE_SYSTEM_TYPE_FAKE);
            ast_node_add_child(node, $3);
            ast_node_add_child(node, deconstruct_list($5));
            if($6 != NULL)
                ast_node_add_child(node, $6);
            $$ = node;
}
         ;

else_part: /* empty */ { $$ = NULL;}
         | TK_PR_ELSE command_block {
            ast_node *node = ast_node_create(AST_NODE_TYPE_ELSE, NULL, TYPE_SYSTEM_TYPE_FAKE);
            ast_node_add_child(node, deconstruct_list($2));
            $$ = node;
         }
         ;

while_command: TK_PR_WHILE '(' expression ')' command_block
{
                ast_node *node = ast_node_create(AST_NODE_TYPE_WHILE, NULL, TYPE_SYSTEM_TYPE_FAKE);
                ast_node_add_child(node, $3);
                ast_node_add_child(node, deconstruct_list($5));
                $$ = node;
}
             ;

literal: TK_LIT_FALSE { ast_node *node = ast_node_create(AST_NODE_TYPE_LITERAL, $1, TYPE_SYSTEM_TYPE_BOOL); $$ = node;}
    | TK_LIT_TRUE { ast_node *node = ast_node_create(AST_NODE_TYPE_LITERAL, $1, TYPE_SYSTEM_TYPE_BOOL); $$ = node;}
    | TK_LIT_INT { ast_node *node = ast_node_create(AST_NODE_TYPE_LITERAL, $1, TYPE_SYSTEM_TYPE_INT); $$ = node;}
    | TK_LIT_FLOAT { ast_node *node = ast_node_create(AST_NODE_TYPE_LITERAL, $1, TYPE_SYSTEM_TYPE_FLOAT); $$ = node;}
    ;

primary: identifier {
    // Check if identifier is declared
    if(!stack_is_declared(scope_stack, $1)){
        printf("Error: Variable %s in line %d not declared.\n", $1, $1->value->line);
        exit(11);
    }
    // Check if identifier is not a function
    symbol *sym = stack_get(scope_stack, $1->value->value);
    if(sym->type == SYMBOL_TYPE_FUNCTION){
        printf("Error: Variable %s in line %d is a function.\n", $1, $1->value->line);
        exit(11);
    }
    $$ = $1;
}
    | literal { $$ = $1;}
    | function_call { $$ = $1;}
    | '(' expression ')' { $$ = $2;}
    ;

unary: primary { $$ = $1; }
    | '!' primary { $$ make_unary_expression(AST_NODE_TYPE_LOGICAL_NEGATION, $2, scope_stack);}
    | '-' primary { $$ make_unary_expression(AST_NODE_TYPE_NUMERICAL_NEGATION, $2, scope_stack);}
    ;

factor: unary { $$ = $1; }
    | factor '*' unary { $$ = make_binary_expression(AST_NODE_TYPE_MULTIPLICATION, $1, $3, scope_stack);}
    | factor '/' unary { $$ = make_binary_expression(AST_NODE_TYPE_DIVISION, $1, $3, scope_stack);}
    | factor '%' unary { $$ = make_binary_expression(AST_NODE_TYPE_MODULO, $1, $3, scope_stack);}
    ;

term: factor { $$ = $1; }
    | term '+' factor {$$ = make_binary_expression(AST_NODE_TYPE_ADDITION, $1, $3, scope_stack);}
    | term '-' factor {$$ = make_binary_expression(AST_NODE_TYPE_SUBTRACTION, $1, $3, scope_stack);}
    ;

order: term { $$ = $1; }
    | order '<' term { $$ = make_binary_expression(AST_NODE_TYPE_LESS_THAN, $1, $3, scope_stack);}
    | order '>' term { $$ = make_binary_expression(AST_NODE_TYPE_GREATER_THAN, $1, $3, scope_stack);}
    | order TK_OC_GE term{ $$ = make_binary_expression(AST_NODE_TYPE_GREATER_EQUAL, $1, $3, scope_stack);}
    | order TK_OC_LE term{ $$ = make_binary_expression(AST_NODE_TYPE_LESS_EQUAL, $1, $3, scope_stack);}
    ;

identity: order { $$ = $1; }
    | identity TK_OC_EQ order{ $$ = make_binary_expression(AST_NODE_TYPE_EQUAL, $1, $3, scope_stack);}
    | identity TK_OC_NE order{ $$ = make_binary_expression(AST_NODE_TYPE_NOT_EQUAL, $1, $3, scope_stack);}
    ;

and_expr: identity { $$ = $1; }
    | and_expr TK_OC_AND identity{ $$ = make_binary_expression(AST_NODE_TYPE_LOGICAL_AND, $1, $3, scope_stack);}
    ;

expression: and_expr { $$ = $1; }
    | expression TK_OC_OR and_expr{ $$ = make_binary_expression(AST_NODE_TYPE_LOGICAL_OR, $1, $3, scope_stack);}
    ;

%%
void yyerror (char const *s) {
    fprintf (stderr, "In line %d... %s.\n", get_line_number(), s);
} 