#ifndef OOP_H
#define OOP_H

// C
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

// CUT
#include "macro.h"
#include <types.h>
#include <diagnostic.h>

// The object declaration macro
#define OBJECT(...) \
typedef struct EXPAND2(_, TYPENAME) EXPAND(TYPENAME); \
EXPAND(TYPENAME) *_(Construct)(__VA_ARGS__); \
void _(Destruct)(); \
struct EXPAND2(_, TYPENAME) {

// Inherit from an object
#define INHERIT(BASE_TYPENAME) BASE_TYPENAME base;

// This is to standardize inheriting and non-inheriting objects' definitions
// (the brackets are hidden in the macros)
#define END(...) }; \
static void *_(Default)() { \
  return EXPAND2(TYPENAME, _Construct)(this __VA_OPT__(,) __VA_ARGS__); \
} \
static VirtualEntry EXPAND2(_ve_, TYPENAME) __attribute__((used, section(STRINGIZE(EXPAND2(virtual_, TYPENAME))))) = { .method = "" }; \
extern VirtualEntry EXPAND2(__start_virtual_, TYPENAME), EXPAND2(__stop_virtual_, TYPENAME); \
__attribute__((unused)) static Type EXPAND2(_typeof_, TYPENAME) = { \
  .name      = STRINGIZE(TYPENAME), \
  .size      = sizeof(EXPAND(TYPENAME)), \
  .construct = (void*)EXPAND2(TYPENAME, _Default), \
  .destruct  = (void*)EXPAND2(TYPENAME, _Destruct), \
  .ve_start  = &EXPAND2(__start_virtual_, TYPENAME) + 1, \
  .ve_stop   = &EXPAND2(__stop_virtual_, TYPENAME) \
}

// Underscore to imply member method
#define _(METHOD_NAME) EXPAND3(TYPENAME, _, METHOD_NAME)(EXPAND(TYPENAME) *this __CONT__
#define __CONT__(...) __VA_OPT__(,)__VA_ARGS__)

// Underscore to imply member method
#define CONST(METHOD_NAME) EXPAND3(TYPENAME, _, METHOD_NAME)(const EXPAND(TYPENAME) *this __CONST_CONT__
#define __CONST_CONT__(...) __VA_OPT__(,)__VA_ARGS__)

// Replace underscore with static for static method
#define STATIC(FUNCTION_NAME) EXPAND3(TYPENAME, _, FUNCTION_NAME)

// Virtualization following this principle: https://stackoverflow.com/questions/3633896/append-items-to-an-array-with-a-macro-in-c

// This macro allows to add the current method in the virtual table of the current object
#define VIRTUAL(METHOD_NAME) ; static VirtualEntry EXPAND2(_ve_, __COUNTER__) __attribute__((used, section(STRINGIZE(EXPAND2(virtual_, TYPENAME))))) = { \
.method = #METHOD_NAME, \
.fptr   = EXPAND3(TYPENAME, _, METHOD_NAME) \
}

// This macro allows to add any method to the virtual table of the current object
#define FOREIGN_VIRTUAL(METHOD_NAME, METHOD) static VirtualEntry EXPAND2(_fe_, __COUNTER__) __attribute__((used, section(STRINGIZE(EXPAND2(virtual_, TYPENAME))))) = { \
.method = #METHOD_NAME, \
.fptr   = METHOD \
}

// Creates a new instance of the object
#define NEW(TYPENAME) TYPENAME ## _Construct((TYPENAME*)talloc(&EXPAND2(_typeof_, TYPENAME)) __NEW_CONT__
#define __NEW_CONT__(...) __VA_OPT__(,)__VA_ARGS__)
 
// Call a virtual method on the object
#define CALL(OBJECT, METHOD_NAME) virtual(gettype(OBJECT), #METHOD_NAME)(OBJECT __CALL_CONT__
#define __CALL_CONT__(...) __VA_OPT__(,)__VA_ARGS__)

#define DELETE(OBJECT) \
if (OBJECT) { \
  gettype(OBJECT)->destruct(OBJECT); \
  tfree(OBJECT); \
  OBJECT = NULL; \
}

#define BASE_0 &this->base
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

#define TYPENAME Object

OBJECT (void *object) INHERIT (void*)
END (NULL);

void *CONST (Get)();

#undef TYPENAME

#endif
