#include "stack.h"
#include "linked_list.h"


stack *stack_create(destroy_data destroy){
    return linked_list_create(destroy);
}

void stack_destroy(stack *s){
    linked_list_destroy(s);
}
void stack_push(stack *s, void *data){
    linked_list_push_front(s, data);
}
void *stack_pop(stack *s){
    return linked_list_pop_front(s);
}
void *stack_peek(stack *s){
    return linked_list_front(s);
}
void *stack_peek_further(stack *s, int index){
    return linked_list_get(s, index);
}

int stack_get_size(stack *s){
    return linked_list_size(s);
}