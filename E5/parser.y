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
int rbss = 0;
int rfp = 0;
%}

%code requires{
    
    #include "utils.h"
    #include "ast.h"
    #include "stack.h"
    #include "iloc.h"
    #include "symbol.h"
    #include "hash_table.h"
    #include "linked_list.h"
    #include "parser_utils.h"
    #include <string.h>
    #include <stdio.h>
}

%union{
    ast_node *node;
    ast_node_list *list;
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
%type<node> parameter
%type<list> parameters
%type<list> parameter_list
%type<list> command_block
%type<list> commands
%type<list> function_body
%type<node> function
%type<node> function_header

%type<node> identifier

%type<node> program

%type<data_type> type
%type<list> identifier_list

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



global_declaration: variable_declaration ';' {
    rbss += 4;
}
    ;

variable_declaration: type identifier_list {
    $$ = ast_node_create(AST_NODE_TYPE_EMPTY, NULL, $1); 
    // Add list of identifiers to the symbol table
    int size = ast_node_list_size($2); 
    for(int i = 0; i < size; i++){
        ast_node *cur_node = ast_node_list_pop_front($2); 
        fail_if_declared(scope_stack, cur_node); 
        ast_node_set_data_type(cur_node, $1);
        symbol *sym = symbol_create($1, SYMBOL_TYPE_IDENTIFIER, ast_node_get_lexeme(cur_node), rfp);
        rfp += 4;
        add_symbol_to_current_scope(scope_stack, sym);
    }
}

type: TK_PR_INT {
    stack_create_if_null(&scope_stack);
    $$ = TYPE_SYSTEM_TYPE_INT;
    }
    | TK_PR_FLOAT{
    stack_create_if_null(&scope_stack);
    $$ = TYPE_SYSTEM_TYPE_FLOAT;
    }
    | TK_PR_BOOL{
    stack_create_if_null(&scope_stack);
    $$ = TYPE_SYSTEM_TYPE_BOOL;
    }
    ;

function: function_header function_body {
        ast_node *node = $1;
        add_child_from_list(node, $2);
        $$ = node; 
}
    ;

function_body: '{' commands close_block { $$ = $2; rfp = rbss; } // A little hack to preserve the value of rfp in the global scope (:
    ;                                                            // Of course, this would stop working if we had nested functions
                                                                 // But we don't, so it's fine
function_header: parameter_list TK_OC_GE type '!' identifier {
    // Add function name
    fail_if_declared(scope_stack, $5); 
    symbol *sym = symbol_create($3, SYMBOL_TYPE_FUNCTION, ast_node_get_lexeme($5), 0); // Does not matter where the function is stored
    add_symbol_to_current_scope(scope_stack, sym); 
    $$=$5; ast_node_set_node_type($$, AST_NODE_TYPE_FUNCTION); 

    // Scope args
    add_new_scope(scope_stack); 
    // Add list of identifiers to the symbol table
    int size = ast_node_list_size($1); 
    for(int i = 0; i < size; i++){ 
        ast_node *cur_node = ast_node_list_pop_front($1);  
        fail_if_declared(scope_stack, cur_node); 
        symbol *sym = symbol_create(ast_node_get_data_type(cur_node), SYMBOL_TYPE_IDENTIFIER, ast_node_get_lexeme(cur_node), rfp);
        rfp += 4; 
        add_symbol_to_current_scope(scope_stack, sym); 
    }
    rfp = 0; // Reset rfp as a new scope was created 
}
;

parameter_list: '('parameters')'{ stack_create_if_null(&scope_stack); $$ = $2;}
    ;

parameters: /* empty */{ $$ = ast_node_list_create();}
    | parameters ',' parameter {ast_node_list_push_back($1, $3); $$ = $1;}
    | parameter {ast_node_list *list = ast_node_list_create(); ast_node_list_push_back(list, $1); $$ = list;}
    ;

parameter: type identifier {
    fail_if_declared(scope_stack, $2);
    lexeme *lex = ast_node_get_lexeme($2);
    $$ = ast_node_create(AST_NODE_TYPE_IDENTIFIER, lex, $1);
    }
    ;

commands: /* empty */ { $$ = ast_node_list_create();}
    | commands command {
        if($2 != NULL){
            ast_node_list_push_back($1, $2); $$ = $1;
        }
    }
    ;

command: command_block ';' {
    $$ = unwind_ast_node_list($1);
}
    | variable_declaration ';' { $$ = $1;}
    | attribution_command ';' { $$ = $1;}
    | function_call ';' { $$ = $1;}
    | return_command ';' { $$ = $1;}
    | if_command ';' { $$ = $1;}
    | while_command ';' { $$ = $1;}
    ;

open_block: '{' {add_new_scope(scope_stack);}
    ;

close_block: '}' {remove_current_scope(scope_stack);} 

command_block: open_block commands close_block {
    $$ = $2;
    }
    ;

attribution_command: identifier '=' expression {
        fail_if_not_declared(scope_stack, $1);
        fail_if_not_variable(scope_stack, $1);
        symbol *sym = get_symbol_globally(scope_stack, ast_node_get_lexeme_value($1));
        
        if(sym == NULL){printf("Unexpected error: symbol not found\n"); exit(1);}
        
        ast_node *node = ast_node_create(AST_NODE_TYPE_ATTRIBUTION, NULL, symbol_get_data_type(sym));
        ast_node_add_child(node, $1);
        ast_node_add_child(node, $3);
        $$ = node;
    }
    ;

return_command: TK_PR_RETURN expression{
        ast_node *node = ast_node_create(AST_NODE_TYPE_RETURN, NULL, ast_node_get_data_type($2));
        ast_node_add_child(node, $2);
        $$ = node;
    }
    ;

arguments: /* empty */ { $$ = ast_node_list_create();}
    | expression {
        ast_node_list *list = ast_node_list_create();
        ast_node_list_push_back(list, $1);
        $$ = list;
    }
    | arguments ',' expression {
        ast_node_list_push_back($1, $3);
        $$ = $1;
    };

function_call: identifier '(' arguments ')'{
    fail_if_not_declared(scope_stack, $1);
    fail_if_not_function(scope_stack, $1);
    ast_node *node = $1;
    symbol *sym = get_symbol_globally(scope_stack, ast_node_get_lexeme_value($1));

    if(sym == NULL){printf("Unexpected error: symbol not found\n"); exit(1);}

    ast_node_set_node_type(node, AST_NODE_TYPE_FUNCTION_CALL);
    ast_node_set_data_type(node, symbol_get_data_type(sym));
    add_child_from_list(node, $3);
    $$ = node;
};

while_command: TK_PR_WHILE '(' expression ')' command_block{
    ast_node *node = ast_node_create(AST_NODE_TYPE_WHILE, NULL, ast_node_get_data_type($3));
    ast_node_add_child(node, $3);
    add_child_from_list(node, $5);
    $$ = node;
};

if_command: TK_PR_IF '(' expression ')' command_block else_part{
    ast_node *node = ast_node_create(AST_NODE_TYPE_IF, NULL, ast_node_get_data_type($3));
    ast_node_add_child(node, $3);
    add_child_from_list(node, $5);
    if($6 != NULL)
        ast_node_set_data_type($6, ast_node_get_data_type($3));
        ast_node_add_child(node, $6);
    $$ = node;
};

else_part: /* empty */ { $$ = NULL;}
    | TK_PR_ELSE command_block {
    ast_node *node = ast_node_create(AST_NODE_TYPE_ELSE, NULL, TYPE_SYSTEM_TYPE_FAKE);
    add_child_from_list(node, $2);
    $$ = node;
};


identifier_list: identifier {$$ = ast_node_list_create(); ast_node_list_push_back($$, $1);}
    | identifier_list ',' identifier {ast_node_list_push_back($1, $3); $$ = $1;}
    ;
identifier: TK_IDENTIFICADOR { ast_node *node = ast_node_create(AST_NODE_TYPE_IDENTIFIER, $1, TYPE_SYSTEM_TYPE_FAKE); $$ = node;}

literal: TK_LIT_FALSE { ast_node *node = ast_node_create(AST_NODE_TYPE_LITERAL, $1, TYPE_SYSTEM_TYPE_BOOL); $$ = node;}
    | TK_LIT_TRUE { ast_node *node = ast_node_create(AST_NODE_TYPE_LITERAL, $1, TYPE_SYSTEM_TYPE_BOOL); $$ = node;}
    | TK_LIT_INT { ast_node *node = ast_node_create(AST_NODE_TYPE_LITERAL, $1, TYPE_SYSTEM_TYPE_INT); $$ = node;}
    | TK_LIT_FLOAT { ast_node *node = ast_node_create(AST_NODE_TYPE_LITERAL, $1, TYPE_SYSTEM_TYPE_FLOAT); $$ = node;}
    ;
primary: identifier {
    // Check if identifier is declared
    fail_if_not_declared(scope_stack, $1);
    // Check if identifier is not a function
    fail_if_not_variable(scope_stack, $1);
    $$ = $1;
    symbol *sym = get_symbol_globally(scope_stack, ast_node_get_lexeme_value($1));
    if(sym == NULL){printf("Unexpected error: symbol not found\n"); exit(1);} // Fail if symbol is not found
    ast_node_set_data_type($$, symbol_get_data_type(sym));
    char *temporary = iloc_make_temp();
    ast_node_set_temporary($$, temporary);
    iloc_instr* load_into_temp = iloc_loadAI("rfp", symbol_get_location(sym), temporary, NULL);
    ast_node_add_code($$, load_into_temp);
    }
    | literal {
        $$ = $1;
        char *temporary = iloc_make_temp();
        ast_node_set_temporary($$, temporary);
        iloc_instr* zero_the_register = iloc_sub(temporary, temporary, temporary, NULL);
        ast_node_add_code($$, zero_the_register);

        iloc_instr* load_into_temp = iloc_addI(temporary, ast_node_get_lexeme_value($1), temporary, NULL);
        ast_node_add_code($$, load_into_temp);
    }
    | function_call { $$ = $1;}
    | '(' expression ')' {
        $$ = $2;
    }
    ;

unary: primary { $$ = $1; }
    | '!' primary { $$ =  make_unary_expression(AST_NODE_TYPE_LOGICAL_NEGATION, $2, scope_stack);}
    | '-' primary {
        $$ = make_unary_expression(AST_NODE_TYPE_NUMERICAL_NEGATION, $2, scope_stack);
        iloc_list_concat(ast_node_get_code($$), ast_node_get_code($2));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary($$, temporary);
        iloc_instr* neg = iloc_subI(temporary, "0", ast_node_get_temporary($2), NULL);
        ast_node_add_code($$, neg);
        }
    ;

factor: unary { $$ = $1; }
    | factor '*' unary {
        $$ = make_binary_expression(AST_NODE_TYPE_MULTIPLICATION, $1, $3, scope_stack);
        iloc_list_concat(ast_node_get_code($$), ast_node_get_code($1));
        iloc_list_concat(ast_node_get_code($$), ast_node_get_code($3));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary($$, temporary);
        iloc_instr* mult = iloc_mult(ast_node_get_temporary($1), ast_node_get_temporary($3), temporary, NULL);
        ast_node_add_code($$, mult);
        }
    | factor '/' unary {
        $$ = make_binary_expression(AST_NODE_TYPE_DIVISION, $1, $3, scope_stack);
        iloc_list_concat(ast_node_get_code($$), ast_node_get_code($1));
        iloc_list_concat(ast_node_get_code($$), ast_node_get_code($3));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary($$, temporary);
        iloc_instr* div = iloc_div(ast_node_get_temporary($1), ast_node_get_temporary($3), temporary, NULL);
        ast_node_add_code($$, div);
        }
    | factor '%' unary { $$ = make_binary_expression(AST_NODE_TYPE_MODULO, $1, $3, scope_stack);}
    ;

term: factor { $$ = $1; }
    | term '+' factor {
        $$ = make_binary_expression(AST_NODE_TYPE_ADDITION, $1, $3, scope_stack);
        iloc_list_concat(ast_node_get_code($$), ast_node_get_code($1));
        iloc_list_concat(ast_node_get_code($$), ast_node_get_code($3));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary($$, temporary);
        iloc_instr* add = iloc_add(ast_node_get_temporary($1), ast_node_get_temporary($3), temporary, NULL);
        ast_node_add_code($$, add);
    }
    | term '-' factor {
        $$ = make_binary_expression(AST_NODE_TYPE_SUBTRACTION, $1, $3, scope_stack);
        iloc_list_concat(ast_node_get_code($$), ast_node_get_code($1));
        iloc_list_concat(ast_node_get_code($$), ast_node_get_code($3));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary($$, temporary);
        iloc_instr* sub = iloc_sub(ast_node_get_temporary($1), ast_node_get_temporary($3), temporary, NULL);
        ast_node_add_code($$, sub);
    }
    ;

order: term { $$ = $1; }
    | order '<' term {
        $$ = make_binary_expression(AST_NODE_TYPE_LESS_THAN, $1, $3, scope_stack);
        iloc_list_concat(ast_node_get_code($$), ast_node_get_code($1));
        iloc_list_concat(ast_node_get_code($$), ast_node_get_code($3));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary($$, temporary);
        iloc_instr* less_than = iloc_cmp_LT(ast_node_get_temporary($1), ast_node_get_temporary($3), temporary, NULL);
        ast_node_add_code($$, less_than);
        }
    | order '>' term {
        $$ = make_binary_expression(AST_NODE_TYPE_GREATER_THAN, $1, $3, scope_stack);
        iloc_list_concat(ast_node_get_code($$), ast_node_get_code($1));
        iloc_list_concat(ast_node_get_code($$), ast_node_get_code($3));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary($$, temporary);
        iloc_instr* greater_than = iloc_cmp_GT(ast_node_get_temporary($1), ast_node_get_temporary($3), temporary, NULL);
        ast_node_add_code($$, greater_than);
    }
    | order TK_OC_GE term{ 
        $$ = make_binary_expression(AST_NODE_TYPE_GREATER_EQUAL, $1, $3, scope_stack);
        iloc_list_concat(ast_node_get_code($$), ast_node_get_code($1));
        iloc_list_concat(ast_node_get_code($$), ast_node_get_code($3));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary($$, temporary);
        iloc_instr* greater_equal = iloc_cmp_GE(ast_node_get_temporary($1), ast_node_get_temporary($3), temporary, NULL);
        ast_node_add_code($$, greater_equal);
    }
    | order TK_OC_LE term{ 
        $$ = make_binary_expression(AST_NODE_TYPE_LESS_EQUAL, $1, $3, scope_stack);
        iloc_list_concat(ast_node_get_code($$), ast_node_get_code($1));
        iloc_list_concat(ast_node_get_code($$), ast_node_get_code($3));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary($$, temporary);
        iloc_instr* less_equal = iloc_cmp_LE(ast_node_get_temporary($1), ast_node_get_temporary($3), temporary, NULL);
        ast_node_add_code($$, less_equal);
    }
    ;

identity: order { $$ = $1; }
    | identity TK_OC_EQ order{ 
        $$ = make_binary_expression(AST_NODE_TYPE_EQUAL, $1, $3, scope_stack);
        iloc_list_concat(ast_node_get_code($$), ast_node_get_code($1));
        iloc_list_concat(ast_node_get_code($$), ast_node_get_code($3));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary($$, temporary);
        iloc_instr* equal = iloc_cmp_EQ(ast_node_get_temporary($1), ast_node_get_temporary($3), temporary, NULL);
        ast_node_add_code($$, equal);
    }
    | identity TK_OC_NE order{ 
        $$ = make_binary_expression(AST_NODE_TYPE_NOT_EQUAL, $1, $3, scope_stack);
        iloc_list_concat(ast_node_get_code($$), ast_node_get_code($1));
        iloc_list_concat(ast_node_get_code($$), ast_node_get_code($3));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary($$, temporary);
        iloc_instr* not_equal = iloc_cmp_NE(ast_node_get_temporary($1), ast_node_get_temporary($3), temporary, NULL);
        ast_node_add_code($$, not_equal);
        }
    ;

and_expr: identity { $$ = $1; }
    | and_expr TK_OC_AND identity{
        $$ = make_binary_expression(AST_NODE_TYPE_LOGICAL_AND, $1, $3, scope_stack);
        iloc_list_concat(ast_node_get_code($$), ast_node_get_code($1));
        iloc_list_concat(ast_node_get_code($$), ast_node_get_code($3));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary($$, temporary);
        iloc_instr* and = iloc_and(ast_node_get_temporary($1), ast_node_get_temporary($3), temporary, NULL);
        ast_node_add_code($$, and);
        }
    ;

expression: and_expr { $$ = $1; }
    | expression TK_OC_OR and_expr{
        $$ = make_binary_expression(AST_NODE_TYPE_LOGICAL_OR, $1, $3, scope_stack);
        iloc_list_concat(ast_node_get_code($$), ast_node_get_code($1));
        iloc_list_concat(ast_node_get_code($$), ast_node_get_code($3));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary($$, temporary);
        iloc_instr* or = iloc_or(ast_node_get_temporary($1), ast_node_get_temporary($3), temporary, NULL);
        ast_node_add_code($$, or);
        }
    ;

%%
void yyerror (char const *s) {
    fprintf (stderr, "In line %d... %s.\n", get_line_number(), s);
} 