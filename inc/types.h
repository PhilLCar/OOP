#ifndef TYPES_H
#define TYPES_H

// C
#include <stdlib.h>
#include <string.h>

// CUT
#include <diagnostic.h>
#include <macro.h>

#define TYPEOF(TYPE) IFNULL(findtype(#TYPE), &_typeof_natives[sizeof(TYPE)])
#define TYPE(T) &EXPAND2(_typeof_, T)

// This emulates an enum with the long data type, (required to pad the struct)
typedef long Types;
#define TYPES_DEFAULT 0L
#define TYPES_DECIMAL 1L
#define TYPES_POINTER 2L
#define TYPES_OBJECT  3L

typedef void *(*VirtualFunction)(void*, ...);
typedef void *(*ConstVirtualFunction)(const void*, ...);

typedef void *(*Constructor)(void*);
typedef void  (*Destructor)(void*);

// This struct must be alignable on 16 both in x32 and x64 because 
// we depend on it being stacked properly for ve table iteration
typedef struct _virtual_entry {
  const char *method;
  const void *fptr;
} VirtualEntry;

// This struct must also be alignable on 16
typedef struct _type {
  const char          *name;
  const size_t         size;
  const char         **basename;
  const Constructor    construct;
  const Destructor     destruct;
  const VirtualEntry  *ve_start;
  const VirtualEntry  *ve_stop;
  const Types          category;
} Type;

__attribute__((unused, section("reflection"))) static Type _typeof_natives[17] = {
  { .name = "void",  .size = 0,  .category = TYPES_DEFAULT },
  { .name = "byte",  .size = 1,  .category = TYPES_DEFAULT },
  { .name = "word",  .size = 2,  .category = TYPES_DEFAULT },
  { .name = "?3",    .size = 3,  .category = TYPES_DEFAULT },
  { .name = "dword", .size = 4,  .category = TYPES_DEFAULT },
  { .name = "?5",    .size = 5,  .category = TYPES_DEFAULT },
  { .name = "?6",    .size = 6,  .category = TYPES_DEFAULT },
  { .name = "?7",    .size = 7,  .category = TYPES_DEFAULT },
  { .name = "quad",  .size = 8,  .category = TYPES_DEFAULT },
  { .name = "?8",    .size = 9,  .category = TYPES_DEFAULT },
  { .name = "?10",   .size = 10, .category = TYPES_DEFAULT },
  { .name = "?11",   .size = 11, .category = TYPES_DEFAULT },
  { .name = "?12",   .size = 12, .category = TYPES_DEFAULT },
  { .name = "?13",   .size = 13, .category = TYPES_DEFAULT },
  { .name = "?14",   .size = 14, .category = TYPES_DEFAULT },
  { .name = "?15",   .size = 15, .category = TYPES_DEFAULT },
  { .name = "octo",  .size = 16, .category = TYPES_DEFAULT },
};

__attribute__((unused, section("reflection"))) static Type _typeof_pointer =
  { .name = "pointer", .size = sizeof(void*), .category = TYPES_POINTER };

__attribute__((unused, section("reflection"))) static Type _typeof_floats[3] = {
  { .name = "float",      .size = sizeof(float),       .category = TYPES_DECIMAL },
  { .name = "double",     .size = sizeof(double),      .category = TYPES_DECIMAL },
  { .name = "longdouble", .size = sizeof(long double), .category = TYPES_DECIMAL }
};


const Type *findtype(const char *typename);

// A cast to allow for arbitrary use of parameters
VirtualFunction      virtual     (const Type *type, const char *name);
ConstVirtualFunction constvirtual(const Type *type, const char *name);

#ifdef MEMORY_WATCH
void       *__talloc(const Type *type, const char *filename, int line);
#endif

// Typed malloc
void       *talloc(const Type *type);

// Typed free
void        tfree(void *object);

// Gets the type of an object
const Type *gettype(const void *object);

// Get the base of the specified type
const Type *getbase(const Type *type);

// Gets the typename of an object
const char *typename(const void *object);

// True if the type represents an object
int         isobject(const Type *type);

// Compares the two types
int         sametype(const Type *a, const Type *b);

// Search the inheritance tree for the type
int         castable(const Type *base, const Type *derived);

#endif