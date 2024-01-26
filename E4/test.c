#define MEMORY_DEBUG
#include <stdio.h>
#include "utils.h"
#include "linked_list.h"
#include "ast.h"

int main(void){
    char *ptr = f_malloc(10);
    *ptr = 'a';
    char *ptr2 = f_realloc(ptr, 20);
    f_free(ptr2);
    return 0;
}