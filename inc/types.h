#ifndef TYPES_H
#define TYPES_H

// C
#include <stdlib.h>

// CUT
#include <diagnostic.h>
#include <macro.h>

#define OBJECTIFY(NATIVE) \
static void *EXPAND2(NATIVE,_Construct)(void *mem) { return mem; } \
static void  EXPAND2(NATIVE,_Destruct)(void *mem) {} \
static Type EXPAND2(_typeof_,NATIVE) =  { \
  .name      = STRINGIZE(NATIVE), \
  .size      = sizeof(NATIVE), \
  .construct = EXPAND2(NATIVE,_Construct), \
  .destruct  = EXPAND2(NATIVE,_Destruct) \
}

#define TYPEOF(TYPE) IFNULL(findtype(#TYPE), &_typeof_natives[sizeof(TYPE)])
#define TYPE(T) &EXPAND2(_typeof_, T)

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
  const struct _type **base;
  const Constructor    construct;
  const Destructor     destruct;
  const VirtualEntry  *ve_start;
  const VirtualEntry  *ve_stop;
  const long           decimal;
} Type;

__attribute__((unused, section("reflection"))) static Type _typeof_natives[17] = {
  { .name = "void",  .size = 0,  .decimal = 0 },
  { .name = "byte",  .size = 1,  .decimal = 0 },
  { .name = "word",  .size = 2,  .decimal = 0 },
  { .name = "?3",    .size = 3,  .decimal = 0 },
  { .name = "dword", .size = 4,  .decimal = 0 },
  { .name = "?5",    .size = 5,  .decimal = 0 },
  { .name = "?6",    .size = 6,  .decimal = 0 },
  { .name = "?7",    .size = 7,  .decimal = 0 },
  { .name = "quad",  .size = 8,  .decimal = 0 },
  { .name = "?8",    .size = 9,  .decimal = 0 },
  { .name = "?10",   .size = 10, .decimal = 0 },
  { .name = "?11",   .size = 11, .decimal = 0 },
  { .name = "?12",   .size = 12, .decimal = 0 },
  { .name = "?13",   .size = 13, .decimal = 0 },
  { .name = "?14",   .size = 14, .decimal = 0 },
  { .name = "?15",   .size = 15, .decimal = 0 },
  { .name = "octo",  .size = 16, .decimal = 0 },
};

__attribute__((unused, section("reflection"))) static Type _floats[3] = {
  { .name = "float",       .size = sizeof(float),       .decimal = 1 },
  { .name = "double",      .size = sizeof(double),      .decimal = 1 },
  { .name = "long double", .size = sizeof(long double), .decimal = 1 }
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

// Gets the typename of an object
const char *typename(const void *object);

// True if the type represents an object
int         isobject(const Type *type);

// Compares the two types
int         sametype(const Type *a, const Type *b);

// Search the inheritance tree for the type
int         castable(const Type *base, const Type *derived);

#endif