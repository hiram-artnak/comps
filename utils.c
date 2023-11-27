#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
void die(char *msg){
    /* For unrecoverable errors */
    perror(msg);
    exit(1);
}

void *forced_malloc(unsigned int size){
    /* For malloc errors */
    void *ptr = malloc(size);
    if(ptr == NULL){
        die("malloc failed");
    }
    return ptr;
}