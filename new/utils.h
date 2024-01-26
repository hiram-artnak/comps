#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdint.h>

typedef unsigned int uint;

// Log function
extern void log_msg(char *msg);

// Safe malloc
extern void *f_safe_malloc(uint size);
extern void *f_safe_realloc(void *ptr, uint size);
extern void f_safe_free(void *ptr);

#ifndef MEMORY_DEBUG
#define f_malloc(size) f_safe_malloc(size)
#define f_realloc(ptr, size) f_safe_realloc(ptr, size)
#define f_free(ptr) f_safe_free(ptr)
#endif

// DEBUG
// This idea was stolen from Eskil
// I have no idea how he actually implements these tho, since his code is closed source
// I'm just taking the idea and implementing it myself
extern void *f_debug_mem_malloc(uint size, char *file, uint line);
extern void *f_debug_mem_realloc(void *ptr, uint size, char *file, uint line);
extern void f_debug_mem_free(void *ptr, char *file, uint line);

#ifdef MEMORY_DEBUG
#define f_malloc(size) f_debug_mem_malloc(size, __FILE__, __LINE__)
#define f_realloc(ptr, size) f_debug_mem_realloc(ptr, size, __FILE__, __LINE__)
#define f_free(ptr) f_debug_mem_free(ptr, __FILE__, __LINE__)
#endif


#endif