/**
 * Ad-hoc unit testing framework for C.
*/
#ifndef MICROTEST_H
#define MICROTEST_H

#include <string.h>
#include <stdlib.h>

typedef int (*test_fun)();

void run_tests();

void add_test(test_fun test, char *name);

int assert_true(int condition, char *msg);

void print_test_results();





#endif