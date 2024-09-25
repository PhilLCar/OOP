#ifndef OOP_H
#define OOP_H

// C
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

// CUT
#include "macro.h"
#include <diagnostic.h>

/* Quick overview:
 * ===============
 * Object-oriented programming (OOP) in C is not natively supported, but it can simplify a lot of issues
 * especially when dealing with complex sequences of memory allocations and freeing.
 * 
 * This library has the aim of providing an easy-to-use, but even more importantly reliable, framework
 * for OOP in C. The idea is that all objects initialized using the macros defined in this header can be
 * predictable in their format, so that the utility functions defined in it can manipulate them in a safe 
 * way, hopefully freeing the programmer of memory-leak concerns.
 * 
 * Additionnaly:
 * - it can provide some nice naming collision prevention through automated prefixes
 * - it can provide more advanced OOP features like virtual adressing and inheritance
 * 
 * Usage:
 * ======
 * This library is heavily inspired by how OOP works in C++, this is why to demonstrate its usage, we will 
 * compare the examples in C with C++ equivalents.
 * 
 * Definition:
 * -----------
 * The macros provided aim to make the definition of objects as simple as possible:
 * 
 * C++:
 * class Object : Base {
 *   type member1;
 *   type member2;
 * 
 *   Object(params...) : Base(params[x:y])
 *   {
 *     ...
 *   }
 *   
 *   ~Object()
 *   {
 *     ...
 *   }
 * };
 * 
 * C:
 * #define TYPENAME Object
 * OBJECT(params...) INHERIT (Base)
 *   type member1;
 *   type member2;
 * END_OBJECT;
 * 
 * Object_cons(params...)
 * {
 *   Base_cons(BASE(0), params[x:y]);
 * }
 * 
 * Object_free()
 * {
 *   Base_free(BASE(0));
 * }
 * 
 * Note: the BASE(N) macro gets the Nth level inheritance pointer
 * 
 * Obviously, it's a little less sleek, but the information provided is essentially the same. The main
 * difference is that there is no automated base construction/destruction, and the base object must 
 * explicitely be constructed/destroyed in the inheriting object's constructor/destructor.
 * 
 * Calling constructiors and destructiors:
 * ---------------------------------------
 * The methods 'cons' and 'free' work by building an object from an existing memory location, for
 * instance:
 * 
 * C++:
 * {
 *   Object object = Object(params...);
 * }
 * 
 * C:
 * {
 *   Object object;
 *   Object_cons(&object, params...);
 * 
 *   Object_free(&object);
 * }
 * 
 * The important thing to notice here is that there is no automated compiler destructor being called in C,
 * and so the programmer has the responsability to call it themselves.
 * 
 * For memory allocation the usage is even closer in syntax:
 * 
 * C++:
 * {
 *   Object *object = new Object(params...);
 * 
 *   delete object;
 * }
 * 
 * C:
 * {
 *   Object *object = NEW (Object) (params...)
 * 
 *   DELETE (object);
 * }
 */

// The object declaration macro
#define OBJECT(...) \
typedef struct EXPAND2(_, TYPENAME) EXPAND(TYPENAME); \
EXPAND(TYPENAME) *_(cons)(__VA_ARGS__); \
void _(free)() VIRTUAL (free); \
struct EXPAND2(_, TYPENAME) {

// Inherit from an object
#define INHERIT(BASE_TYPENAME) BASE_TYPENAME base;

// This is to standardize inheriting and non-inheriting objects' definitions
// (the brackets are hidden in the macros)
#define END_OBJECT }

// Underscore to imply member method
#define _(METHOD_NAME) EXPAND3(TYPENAME, _, METHOD_NAME)(EXPAND(TYPENAME) *_this __CONT__
#define __CONT__(...) __VA_OPT__(,)__VA_ARGS__)

// Replace underscore with static for static method
#define STATIC(FUNCTION_NAME) EXPAND3(TYPENAME, _, FUNCTION_NAME)

// Virtualization following this principle: https://stackoverflow.com/questions/3633896/append-items-to-an-array-with-a-macro-in-c

// This macro allows to add the current method in the virtual table of the current object
#define VIRTUAL(METHOD_NAME) ; static struct _virtual_entry EXPAND2(_ve_, __COUNTER__) __attribute__((used, section("virtual_table"))) = { \
.object = STRINGIZE(TYPENAME), \
.method = #METHOD_NAME, \
.fptr   = EXPAND3(TYPENAME, _, METHOD_NAME) \
}

// This macro allows to add any method to the virtual table of the current object
#define FOREIGN_VIRTUAL(METHOD_NAME, METHOD) static struct _virtual_entry EXPAND2(_fe_, __COUNTER__) __attribute__((used, section("virtual_table"))) = { \
.object = STRINGIZE(TYPENAME), \
.method = #METHOD_NAME, \
.fptr   = METHOD \
}

// Creates a new instance of the object
#define NEW(TYPENAME) TYPENAME ## _cons((TYPENAME*)_valloc(sizeof(TYPENAME), STRINGIZE(TYPENAME)) __NEW_CONT__
#define __NEW_CONT__(...) __VA_OPT__(,)__VA_ARGS__)

#define VCALL(OBJECT, METHOD_NAME) _virtual(#METHOD_NAME, *(char**)((char*)OBJECT + sizeof(*OBJECT)))

#define DELETE(VAR) \
if (VAR) { \
  VCALL(VAR, free)(VAR); \
  free(VAR); \
  VAR = NULL; \
}

#define BASE_0 &_this->base
#define BASE_1 BASE_0.base
#define BASE_2 BASE_1.base
#define BASE_3 BASE_2.base
#define BASE_4 BASE_3.base
#define BASE_5 BASE_4.base
#define BASE_6 BASE_5.base
#define BASE_7 BASE_6.base
#define BASE_8 BASE_7.base
#define BASE_9 BASE_8.base
#define BASE(N) (EXPAND2(BASE_, N))

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