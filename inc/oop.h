#ifndef OOP_H
#define OOP_H

// C
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

// CUT
#include <macro.h>

// The _TYPENAME structure is the data structure
// The  TYPENAME typedef is the virtual class (including the pointer to virtual methods)
#define OBJECT(...) \
typedef struct EXPAND2(_, TYPENAME) EXPAND(TYPENAME); \
EXPAND(TYPENAME) *_(cons)(__VA_ARGS__); \
void _(free)() VIRTUAL (free); \
struct EXPAND2(_, TYPENAME) {

// Inheritance
#define INHERIT(TYPENAME) TYPENAME base;

#define END_OBJECT }

// Underscore to imply member method
#define _(NAME) EXPAND3(TYPENAME, _, NAME)(EXPAND(TYPENAME) *_this __CONT__
#define __CONT__(...) __VA_OPT__(,)__VA_ARGS__)

#define STATIC(NAME) EXPAND3(TYPENAME, _, NAME)

// Alias for shortnames
// #define ALIAS(NAME) __attribute__((weak, alias(#NAME)))

// Virtualization following this principle: https://stackoverflow.com/questions/3633896/append-items-to-an-array-with-a-macro-in-c
#define VIRTUAL(NAME) ; static struct _virtual_entry EXPAND2(_ve_, __COUNTER__) __attribute__((used, section("virtual_table"))) = { \
.object = STRINGIZE(TYPENAME), \
.method = #NAME, \
.fptr   = EXPAND3(TYPENAME, _, NAME) \
}

#define NEW(TYPENAME) TYPENAME ## _cons((TYPENAME*)_virtual(sizeof(TYPENAME), STRINGIZE(TYPENAME)) __NEW_CONT__
#define __NEW_CONT__(...) __VA_OPT__(,)__VA_ARGS__)

#define DELETE(VAR) \
if (VAR) { \
  void **typename = (void**)((char*)VAR + sizeof(*VAR)); \
  _v_call("free", *typename, NULL); \
  free(VAR); \
  VAR = NULL; \
}

// Since all members of the virtual entry are pointers, stack alignement should not be an issue
struct _virtual_entry {
  const char *object;
  const char *method;
  const void *fptr;
};

void *_virtual(size_t size, const char *name);
void *_v_args(int, ...);
void *_v_call(const char *name, void *typename, void *params);

#endif