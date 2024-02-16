#ifndef ILOC_H
#define ILOC_H

#include "linked_list.h"

typedef enum ILOC_OP{
    ILOC_ADD,
    ILOC_ADDI,
    ILOC_SUB,
    ILOC_SUBI,
    ILOC_MULT,
    ILOC_DIV,
    ILOC_LOAD,
    ILOC_LOADAI,
    ILOC_STORE,
    ILOC_I2I,
    ILOC_C2C,
    ILOC_C2I,
    ILOC_I2C,
    ILOC_CMP_LT,
    ILOC_CMP_LE,
    ILOC_CMP_EQ,
    ILOC_CMP_GE,
    ILOC_CMP_GT,
    ILOC_CMP_NE,
    ILOC_CBR,
    ILOC_JUMP,
    ILOC_LABEL,
    ILOC_NOP,
    ILOC_HALT
} ILOC_OP;


typedef struct iloc_instr iloc_instr;

iloc_instr* iloc_instr_create(ILOC_OP op, char* label, char* src1, char* src2, char* dst, int displacement);
void iloc_instr_destroy(iloc_instr* instr);



ILOC_OP iloc_instr_get_op(iloc_instr* instr);
char* iloc_instr_get_src1(iloc_instr* instr);
char* iloc_instr_get_src2(iloc_instr* instr);
char* iloc_instr_get_dst(iloc_instr* instr);
char* iloc_instr_get_label(iloc_instr* instr);
int iloc_instr_get_displacement(iloc_instr* instr);
char* iloc_make_label();
char* iloc_make_temp();

typedef linked_list iloc_instr_list;

iloc_instr_list* iloc_instr_list_create();
void iloc_instr_list_destroy(iloc_instr_list* list);
void iloc_instr_list_push_front(iloc_instr_list* list, iloc_instr* instr);
void iloc_instr_list_push_back(iloc_instr_list* list, iloc_instr* instr);
iloc_instr* iloc_instr_list_pop_front(iloc_instr_list* list);
iloc_instr* iloc_instr_list_pop_back(iloc_instr_list* list);
iloc_instr_list* iloc_instr_list_concat(iloc_instr_list* list1, iloc_instr_list* list2);
iloc_instr* iloc_instr_list_get(iloc_instr_list* list, int index);
int iloc_instr_list_size(iloc_instr_list* list);


// Helper build functions
iloc_instr* iloc_loadAI(char* src, int offset, char* dst, char* label);
iloc_instr* iloc_sub(char* src1, char* src2, char* dst, char* label);
iloc_instr* iloc_add(char* src1, char* src2, char* dst, char* label);
iloc_instr* iloc_mult(char* src1, char* src2, char* dst, char* label);
iloc_instr* iloc_div(char* src1, char* src2, char* dst, char* label);
iloc_instr* iloc_addI(char* src, char* value, char* dst, char* label);
iloc_instr* iloc_subI(char* src, char* value, char* dst, char* label);
iloc_instr* iloc_cmp_LT(char* src1, char* src2, char* dst, char* label);
iloc_instr* iloc_cmp_LE(char* src1, char* src2, char* dst, char* label);
iloc_instr* iloc_cmp_EQ(char* src1, char* src2, char* dst, char* label);
iloc_instr* iloc_cmp_GE(char* src1, char* src2, char* dst, char* label);
iloc_instr* iloc_cmp_GT(char* src1, char* src2, char* dst, char* label);
iloc_instr* iloc_cmp_NE(char* src1, char* src2, char* dst, char* label);


#endif