#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


extern void log_msg(char *msg){
    // Logs a message to the log file
    // Opens the log file in append mode (creates it if it doesn't exist)
    FILE *logFile = fopen("log.txt", "a");
    
    if (logFile != NULL) {
        // Print the message to the log file
        fprintf(logFile, "%s\n", msg);
        
        // Close the log file
        fclose(logFile);
    } else {
        // If unable to open the log file, print an error message to stderr
        fprintf(stderr, "Error: Could not open log file for writing\n");
    }
}

void internal_die(char *msg) {
    // Internal die function
    // Prints error to log file and exits
    char *logMsg = f_malloc(strlen(msg) + 100);
    sprintf(logMsg, "Internal error: %s", msg);
    log_msg(logMsg);
    free(logMsg);
    // Exit the program with an error status
    exit(1);
}


void *f_safe_malloc(uint size){
    // Safe malloc function
    // Dies if malloc fails
    
    void *ptr = malloc(size);
    if (ptr == NULL) {
        internal_die("malloc failed");
    }
    return ptr;
}

void *f_safe_realloc(void *ptr, uint size){
    // Safe realloc function
    // Dies if realloc fails
    ptr = realloc(ptr, size);
    if (ptr == NULL) {
        internal_die("realloc failed");
    }
    return ptr;
}

void f_safe_free(void *ptr){
    // Safe free function
    // Does nothing if ptr is NULL
    if (ptr != NULL) {
        free(ptr);
    }
}


// Debug memory functions
void *f_debug_mem_malloc(uint size, char *file, uint line){
    // Debug memory malloc function
    // Logs every malloc call to a file
    void *ptr = f_safe_malloc(size);
    // Logs file and line number of malloc call
    char *logMsg = f_safe_malloc(strlen(file) + 100);
    sprintf(logMsg, "malloc called from %s:%d for %p", file, line, ptr);
    log_msg(logMsg);
    f_safe_free(logMsg);
    if (ptr == NULL) {
        internal_die("malloc failed");
    }
    return ptr;
}
void *f_debug_mem_realloc(void *ptr, uint size, char *file, uint line){
    // Debug memory realloc function
    // Logs every realloc call to a file
    void *new_ptr = realloc(ptr, size);
    // Logs file and line number of realloc call
    char *logMsg = f_safe_malloc(strlen(file) + 150);
    sprintf(logMsg, "realloc called from %s:%d for %p -> %p", file, line, ptr, new_ptr);
    log_msg(logMsg);
    f_safe_free(logMsg);
    if (ptr == NULL) {
        internal_die("realloc failed");
    }
    return ptr;
}
void f_debug_mem_free(void *ptr, char *file, uint line){
    // Debug memory free function
    // Logs every free call to a file
    // Does nothing if ptr is NULL
    if (ptr != NULL) {
        f_safe_free(ptr);
        // Logs file and line number of free call
        char *logMsg = f_safe_malloc(strlen(file) + 100);
        sprintf(logMsg, "free called from %s:%d for %p", file, line, ptr);
        log_msg(logMsg);
        f_safe_free(logMsg);
    }
}
