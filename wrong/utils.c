#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

void *malloc_or_fail(size_t size, const char *error_message){
    void *ptr = malloc(size);
    if (ptr == NULL) {
        // Open or create a log file in append mode
        FILE *log_file = fopen("error_log.txt", "a");
        if (log_file != NULL) {
            fprintf(log_file, "Memory allocation failed: %s\n", error_message);
            fclose(log_file);
        } else {
            // If unable to open the log file, print to stderr
            fprintf(stderr, "Error opening log file. Memory allocation failed: %s\n", error_message);
        }
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void log_error_and_die(const char *error_message) {
    // Open or create a log file in append mode
    FILE *log_file = fopen("error_log.txt", "a");
    if (log_file != NULL) {
        fprintf(log_file, "Error: %s\n", error_message);
        fclose(log_file);
    } else {
        // If unable to open the log file, print to stderr
        fprintf(stderr, "Error opening log file. Error: %s\n", error_message);
    }
    exit(EXIT_FAILURE);
}