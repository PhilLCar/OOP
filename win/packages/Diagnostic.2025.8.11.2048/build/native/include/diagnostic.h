/* THIS FILE HAS TO BE INCLUDED IN EACH TRANSLATION UNIT, OR IT WILL NOT WORK */
#ifdef  MEMORY_WATCH
#ifndef DIAGNOSTIC_H
#define DIAGNOSTIC_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// This has the purpose of replacing normal memory management functions
// with these ones that track all allocated pointers, this allows to easily
// determine if the program has a memory leak.

#ifndef DIAGNOSTIC_INC

#define  malloc(SIZE)                   __malloc(SIZE, __FILE__, __LINE__)
#define  calloc(NMEMB, SIZE)            __calloc(NMEMB, SIZE, __FILE__, __LINE__)
#define  free(PTR)                      __free(PTR)
#define  realloc(PTR, SIZE)             __realloc(PTR, SIZE, __FILE__, __LINE__)
#define  reallocarray(PTR, NMEMB, SIZE) __reallocarray(PTR, NMEMB, SIZE, __FILE__, __LINE__)
#define  CHECK_MEMORY                   printf("Memory usage: %ld bytes\n", (long)__memuse());
#define  STOP_WATCHING                  __end();
#endif

#ifdef WIN
#define DIAGNOSTIC_EXPORT __declspec(dllexport)
#else
#define DIAGNOSTIC_EXPORT __attribute__((visibility("default")))
#endif

DIAGNOSTIC_EXPORT void   *__malloc(size_t, const char*, int);
DIAGNOSTIC_EXPORT void   *__calloc(size_t, size_t, const char*, int);
DIAGNOSTIC_EXPORT void    __free(void*);
DIAGNOSTIC_EXPORT void   *__realloc(void*, size_t, const char*, int);
DIAGNOSTIC_EXPORT void   *__reallocarray(void*, size_t, size_t, const char*, int);

// RETURNS the current size of allocated memory
DIAGNOSTIC_EXPORT size_t  __memuse();

// Prints a report for each unfreed block
DIAGNOSTIC_EXPORT void    __end();

#undef DIAGNOSTIC_EXPORT

#endif
#else
#define CHECK_MEMORY
#define STOP_WATCHING
#endif