#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

typedef void (*generic_print)(const void *);

void *malloc_or_fail(size_t size, const char *error_message);

void log_error_and_die(const char *error_message);

#endif // UTILS_H