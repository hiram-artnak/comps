#include "iloc.h"
#include <string.h>
#include <stdio.h>
#include "utils.h"


typedef struct iloc_instr{
    char *label;
    ILOC_OP op;
    char *src1;
    char *src2;
    char *dst;
}iloc_instr;

// Strings are copied to avoid memory leaks
iloc_instr* iloc_instr_create(ILOC_OP op, char* label, char* src1, char* src2, char* dst){
    iloc_instr* instr = f_malloc(sizeof(iloc_instr));
    instr->op = op;
    instr->label = f_malloc(strlen(label) + 1);
    strcpy(instr->label, label);
    instr->src1 = f_malloc(strlen(src1) + 1);
    strcpy(instr->src1, src1);
    instr->src2 = f_malloc(strlen(src2) + 1);
    strcpy(instr->src2, src2);
    instr->dst = f_malloc(strlen(dst) + 1);
    strcpy(instr->dst, dst);
    return instr;
}

void iloc_instr_destroy(iloc_instr* instr){
    f_free(instr->label);
    f_free(instr->src1);
    f_free(instr->src2);
    f_free(instr->dst);
    f_free(instr);
}

ILOC_OP iloc_instr_get_op(iloc_instr* instr){
    return instr->op;
}

char* iloc_instr_get_src1(iloc_instr* instr){
    return instr->src1;
}

char* iloc_instr_get_src2(iloc_instr* instr){
    return instr->src2;
}

char* iloc_instr_get_dst(iloc_instr* instr){
    return instr->dst;
}

char* iloc_instr_get_label(iloc_instr* instr){
    return instr->label;
}



iloc_instr_list* iloc_instr_list_create(){
    return linked_list_create((destroy_data)iloc_instr_destroy);
}
void iloc_instr_list_destroy(iloc_instr_list* list){
    linked_list_destroy(list);
}
void iloc_instr_list_push_front(iloc_instr_list* list, iloc_instr* instr){
    linked_list_push_front(list, instr);
}
void iloc_instr_list_push_back(iloc_instr_list* list, iloc_instr* instr){
    linked_list_push_back(list, instr);
}
iloc_instr* iloc_instr_list_pop_front(iloc_instr_list* list){
    return linked_list_pop_front(list);
}
iloc_instr* iloc_instr_list_pop_back(iloc_instr_list* list){
    return linked_list_pop_back(list);
}
iloc_instr_list* iloc_instr_list_concat(iloc_instr_list* list1, iloc_instr_list* list2){
    while(linked_list_size(list2) > 0){
        iloc_instr_list_push_back(list1, iloc_instr_list_pop_front(list2));
    }
    iloc_instr_list_destroy(list2);
    return list1;
}
iloc_instr* iloc_instr_list_get(iloc_instr_list* list, int index){
    return linked_list_get(list, index);
}
int iloc_instr_list_size(iloc_instr_list* list){
    return linked_list_size(list);
}

char* iloc_make_label(){
    static int label_count = 0;
    char *label = f_malloc(10);
    sprintf(label, "L%d", label_count++);
    return label;
}

char* iloc_make_temp(){
    static int temp_count = 0;
    char *temp = f_malloc(10);
    sprintf(temp, "r%d", temp_count++);
    return temp;
}

