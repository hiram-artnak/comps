
#include "ast.h"
#include "ast.c"
#include  "hash.h"


void update_tree_types(ast_node* node_pointer)
{
    switch(node_pointer->type)
    {
        case AST_NODE_TYPE_LIT_FLOAT:
            node_pointer->type = FLOAT_TYPE;
            break;

        case AST_NODE_TYPE_LIT_INT:
            node_pointer->type = INT_TYPE;
            break;

        case AST_NODE_TYPE_LIT_FALSE:
        case AST_NODE_TYPE_LIT_TRUE:
            node_pointer->type = BOOL_TYPE;
            break;

        case AST_NODE_TYPE_OP_NOT:
        case AST_NODE_TYPE_OP_ADD:
        case AST_NODE_TYPE_OP_SUB:
        case AST_NODE_TYPE_OP_MUL:
        case AST_NODE_TYPE_OP_DIV:
        case AST_NODE_TYPE_OP_MOD:
            node_pointer->type = INT_TYPE;
            break;

        case AST_NODE_TYPE_OP_AND:
        case AST_NODE_TYPE_OP_OR:
        case AST_NODE_TYPE_OP_EQ:
        case AST_NODE_TYPE_OP_NE:
        case AST_NODE_TYPE_OP_LT:
        case AST_NODE_TYPE_OP_GT:
        case AST_NODE_TYPE_OP_LE:
        case AST_NODE_TYPE_OP_GE:
        case AST_NODE_TYPE_OP_NEG: 
            node_pointer->type = BOOL_TYPE;
            break;

        case AST_NODE_TYPE_IDENTIFIER:
            
            break;
            
        case AST_NODE_TYPE_PROGRAM:
        case AST_NODE_TYPE_FUNCTION:
        case AST_NODE_TYPE_STATEMENT:
        case AST_NODE_TYPE_EXPRESSION:
            break;

    }

}

            

        
        