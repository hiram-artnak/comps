#include "microtest.h"
#include "utils.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct test_result {
    char *name;
    int passed;
    list *msgs;
} test_result;

void init_test_result(test_result *r, char *name){
    r->name = forced_malloc(strlen(name) + 1);
    r->name = strcpy(r->name, name);
    r->passed = 1;
    r->msgs = forced_malloc(sizeof(list));
    list_init(r->msgs, NULL);
}

void free_test_result(test_result *r){
    free(r->name);
    list_destroy(r->msgs);
}

void add_msg(test_result *r, char *msg){
    char *new_msg = forced_malloc(strlen(msg) + 1);
    strcpy(new_msg, msg);
    list_add(r->msgs, new_msg);
}

test_fun *tests;
test_result *results;
int num_tests = 0;
int cur_test = 0;

void print_test_results(){
    int i;
    for(i = 0; i < num_tests; i++){
        if (results[i].passed){
            printf("\x1b[32m[PASS]\x1b[0m %s\n", results[i].name);
        } else {
            printf("\x1b[31m[FAIL]\x1b[0m %s", results[i].name);
            node *n = results[i].msgs->head;
            while(n != NULL){
                printf("\n\t%s", (char *)(n->data));
                n = n->next;
            }
        }
    }
}

void add_test(test_fun test, char *name){
    if(tests == NULL){
        tests = forced_malloc(sizeof(test_fun));
        results = forced_malloc(sizeof(test_result));
    } else {
        tests = realloc(tests, sizeof(test_fun) * (num_tests + 1));
        results = realloc(results, sizeof(test_result) * (num_tests + 1));
    }
    tests[num_tests] = test;
    init_test_result(&results[num_tests], name);
    num_tests++;
}

void run_tests(){
    int i;
    for(i = 0; i < num_tests; i++){
        cur_test = i;
        tests[i]();
    }
    print_test_results();
    int j;
    for(j = 0; j < num_tests; j++){
        free_test_result(&results[j]);
    }
    free(tests);
    free(results);
}

int assert_true(int condition, char *msg){
    if(!condition){
        add_msg(&results[cur_test], msg);
        results[cur_test].passed = 0;
        return 1;
    }
    return 0;
}