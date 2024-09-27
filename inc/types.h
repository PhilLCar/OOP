#ifndef TYPES_H
#define TYPES_H

// C
#include <stdlib.h>

// CUT
#include <diagnostic.h>

#define NATIVE_TYPE(NATIVE) (Type){ .name = #NATIVE, .size = sizeof(NATIVE) }
#define OBJECT_TYPE(OBJECT) _typeof_#OBJECT

typedef void  (*VirtualFunction)(void*, ...);

typedef void *(*Constructor)(void*);
typedef void  (*Destructor)(void*);

// This struct must be alignable on 16 both in x32 and x64 because 
// we depend on it being stacked properly for ve table iteration
typedef struct _virtual_entry {
  const char *method;
  const void *fptr;
} VirtualEntry;

typedef struct _type {
  const char         *name;
  const size_t        size;
  const Constructor   new;
  const Destructor    delete;
  const VirtualEntry *ve_start;
  const VirtualEntry *ve_stop;
} Type;

// A cast to allow for arbitrary use of parameters
VirtualFunction virtual(const Type *type, const char *name);


// Typed malloc
void       *talloc(Type *type);

// Typed free
void        tfree(void *object);

// Gets the type of an object
const Type *gettype(const void *object);

// Gets the typename of an object
const char *typename(void *object);

// True if the type represents an object
int         isobject(Type *type);

#endif