#include "stack.h"
#include "hash_table.h"
#include "symbol.h"
#include <string.h>
#include <stdio.h>


stack *stack_create(destroy_data destroy){
    return (stack *)linked_list_create(destroy);

}
void stack_create_if_null(stack **stack, destroy_data destroy){
    if(*stack == NULL){
        *stack = stack_create(destroy);
        stack_push(*stack, symbol_table_create());
    }
}
void stack_destroy(stack *stack){
    linked_list_destroy(stack);
}
void stack_push(stack *stack, void *data){
    linked_list_push_front(stack, data);
}
void *stack_pop(stack *stack){
    return linked_list_pop_front(stack);
}
int stack_is_declared(stack *stack, char *identifier){
    for(int i = 0; i < linked_list_size(stack); i++){
        hash_table *table = linked_list_get(stack, i);
        if(hash_table_is_member(table, identifier)){
            return 1;
        }
    }
    return 0;
}
void *stack_get(stack *stack, char *identifier){
    for(int i = 0; i < linked_list_size(stack); i++){
        hash_table *table = linked_list_get(stack, i);
        if(hash_table_is_member(table, identifier)){
            return hash_table_get(table, identifier);
        }
    }
    return NULL;
}

hash_table *stack_get_top(stack *stack){
    return (hash_table*) linked_list_get(stack, 0);
}