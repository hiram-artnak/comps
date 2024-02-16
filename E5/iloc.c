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
    int displacement;
}iloc_instr;

// Strings are copied to avoid memory leaks
iloc_instr* iloc_instr_create(ILOC_OP op, char* label, char* src1, char* src2, char* dst, int displacement){
    iloc_instr* instr = f_malloc(sizeof(iloc_instr));
    instr->op = op;
    if (label != NULL){
        instr->label = f_malloc(strlen(label) + 1);
        strcpy(instr->label, label);
    } else {
        instr->label = NULL;
    }
    if (src1 != NULL){
        instr->src1 = f_malloc(strlen(src1) + 1);
        strcpy(instr->src1, src1);
    } else {
        instr->src1 = NULL;
    }
    if (src2 != NULL){
        instr->src2 = f_malloc(strlen(src2) + 1);
        strcpy(instr->src2, src2);
    } else {
        instr->src2 = NULL;
    }
    if (dst != NULL){
        instr->dst = f_malloc(strlen(dst) + 1);
        strcpy(instr->dst, dst);
    } else {
        instr->dst = NULL;
    }
    instr->displacement = displacement;
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

int iloc_instr_get_displacement(iloc_instr* instr){
    return instr->displacement;
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


iloc_instr* iloc_loadAI(char* src, int offset, char* dst, char* label){
    return iloc_instr_create(ILOC_LOADAI, label, src, NULL, dst, offset);
}

iloc_instr* iloc_sub(char* src1, char* src2, char* dst, char* label){
    return iloc_instr_create(ILOC_SUB, label, src1, src2, dst, 0);
}

iloc_instr* iloc_addI(char* src, char* value, char* dst, char* label){
    return iloc_instr_create(ILOC_ADDI, label, src, value, dst, 0);
}

iloc_instr* iloc_subI(char* src, char* value, char* dst, char* label){
    return iloc_instr_create(ILOC_SUBI, label, src, value, dst, 0);
}

iloc_instr* iloc_add(char* src1, char* src2, char* dst, char* label){
    return iloc_instr_create(ILOC_ADD, label, src1, src2, dst, 0);
}
iloc_instr* iloc_mult(char* src1, char* src2, char* dst, char* label){
    return iloc_instr_create(ILOC_MULT, label, src1, src2, dst, 0);
}
iloc_instr* iloc_div(char* src1, char* src2, char* dst, char* label){
    return iloc_instr_create(ILOC_DIV, label, src1, src2, dst, 0);
}
iloc_instr* iloc_cmp_LT(char* src1, char* src2, char* dst, char* label){
    return iloc_instr_create(ILOC_CMP_LT, label, src1, src2, dst, 0);
}
iloc_instr* iloc_cmp_LE(char* src1, char* src2, char* dst, char* label){
    return iloc_instr_create(ILOC_CMP_LE, label, src1, src2, dst, 0);
}
iloc_instr* iloc_cmp_EQ(char* src1, char* src2, char* dst, char* label){
    return iloc_instr_create(ILOC_CMP_EQ, label, src1, src2, dst, 0);
}
iloc_instr* iloc_cmp_GE(char* src1, char* src2, char* dst, char* label){
    return iloc_instr_create(ILOC_CMP_GE, label, src1, src2, dst, 0);
}
iloc_instr* iloc_cmp_GT(char* src1, char* src2, char* dst, char* label){
    return iloc_instr_create(ILOC_CMP_GT, label, src1, src2, dst, 0);
}
iloc_instr* iloc_cmp_NE(char* src1, char* src2, char* dst, char* label) {
    return iloc_instr_create(ILOC_CMP_NE, label, src1, src2, dst, 0);
}
iloc_instr* iloc_and(char* src1, char* src2, char* dst, char* label){
    return iloc_instr_create(ILOC_AND, label, src1, src2, dst, 0);
}
iloc_instr* iloc_or(char* src1, char* src2, char* dst, char* label){
    return iloc_instr_create(ILOC_OR, label, src1, src2, dst, 0);
}

iloc_instr* iloc_storeAI(char* src, char* dst, int offset, char* label){
    return iloc_instr_create(ILOC_STOREAI, label, src, dst, NULL, offset);
}