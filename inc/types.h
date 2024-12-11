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

#define NATIVE(TYPE) natives[sizeof(TYPE)]

#define TYPEOF(TYPE) &EXPAND2(_typeof_,TYPE)

typedef void *(*VirtualFunction)(void*, ...);

typedef void *(*Constructor)(void*);
typedef void  (*Destructor)(void*);

// This struct must be alignable on 16 both in x32 and x64 because 
// we depend on it being stacked properly for ve table iteration
typedef struct _virtual_entry {
  const char *method;
  const void *fptr;
} VirtualEntry;

typedef struct _type {
  const char          *name;
  const size_t         size;
  const struct _type **base;
  const Constructor    construct;
  const Destructor     destruct;
  const VirtualEntry  *ve_start;
  const VirtualEntry  *ve_stop;
} Type;

__attribute__((unused)) static Type _typeof_natives[17] = {
  { .name = "void",   .size = 0  },
  { .name = "byte",   .size = 1  },
  { .name = "word",   .size = 2  },
  { .name = "?",      .size = 3  },
  { .name = "double", .size = 4  },
  { .name = "?",      .size = 5  },
  { .name = "?",      .size = 6  },
  { .name = "?",      .size = 7  },
  { .name = "quad",   .size = 8  },
  { .name = "?",      .size = 9  },
  { .name = "?",      .size = 10 },
  { .name = "?",      .size = 11 },
  { .name = "?",      .size = 12 },
  { .name = "?",      .size = 13 },
  { .name = "?",      .size = 14 },
  { .name = "?",      .size = 15 },
  { .name = "octo",   .size = 16 },
};

// A cast to allow for arbitrary use of parameters
VirtualFunction virtual(const Type *type, const char *name);

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