#ifndef OOP_H
#define OOP_H

// C
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

// CUT
#include "macro.h"
#include <diagnostic.h>

// The _TYPENAME structure is the data structure
// The  TYPENAME typedef is the virtual class (including the pointer to virtual methods)
// The prnciple behind the virtual free method is for use it in object array deletion
#define OBJECT(...) \
typedef struct EXPAND2(_, TYPENAME) EXPAND(TYPENAME); \
EXPAND(TYPENAME) *_(cons)(__VA_ARGS__); \
void _(free)() VIRTUAL (free); \
struct EXPAND2(_, TYPENAME) {

// Inherit from an object
#define INHERIT(NAME) NAME base;

#define END_OBJECT }

// Underscore to imply member method
#define _(NAME) EXPAND3(TYPENAME, _, NAME)(EXPAND(TYPENAME) *_this __CONT__
#define __CONT__(...) __VA_OPT__(,)__VA_ARGS__)

// Replace underscore with static for static method
#define STATIC(NAME) EXPAND3(TYPENAME, _, NAME)

// TODO: Shortname builder

// Virtualization following this principle: https://stackoverflow.com/questions/3633896/append-items-to-an-array-with-a-macro-in-c
#define VIRTUAL(NAME) ; static struct _virtual_entry EXPAND2(_ve_, __COUNTER__) __attribute__((used, section("virtual_table"))) = { \
.object = STRINGIZE(TYPENAME), \
.method = #NAME, \
.fptr   = EXPAND3(TYPENAME, _, NAME) \
}

#define FOREIGN_VIRTUAL(NAME, FNAME) static struct _virtual_entry EXPAND2(_fe_, __COUNTER__) __attribute__((used, section("virtual_table"))) = { \
.object = STRINGIZE(TYPENAME), \
.method = #NAME, \
.fptr   = FNAME \
}

// Creates a new instance of the object
#define NEW(TYPENAME) TYPENAME ## _cons((TYPENAME*)_valloc(sizeof(TYPENAME), STRINGIZE(TYPENAME)) __NEW_CONT__
#define __NEW_CONT__(...) __VA_OPT__(,)__VA_ARGS__)

#define VCALL(THIS, VAR) _virtual(#VAR, *(char**)((char*)THIS + sizeof(*THIS)))

#define DELETE(VAR) \
if (VAR) { \
  VCALL(VAR, free)(VAR); \
  free(VAR); \
  VAR = NULL; \
}

#define BASE_0 &_this->base
#define BASE_1 BASE_0##.base
#define BASE_2 BASE_1##.base
#define BASE_3 BASE_2##.base
#define BASE_4 BASE_3##.base
#define BASE_5 BASE_4##.base
#define BASE_6 BASE_5##.base
#define BASE_7 BASE_6##.base
#define BASE_8 BASE_7##.base
#define BASE_9 BASE_8##.base
#define BASE(N) EXPAND2(BASE_, N)

// Since all members of the virtual entry are pointers, stack alignement should not be an issue
struct _virtual_entry {
  const char *object;
  const char *method;
  const void *fptr;
};

typedef void (*VirtualFunction)(void*);

void            *_valloc(size_t size, const char *name);
VirtualFunction  _virtual(const char *name, const char *typename);

#endif