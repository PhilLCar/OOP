#ifndef MACRO_H
#define MACRO_H

// Expansion helpers
#define EXPAND(A) __EXPAND_CONT__(A)
#define __EXPAND_CONT__(A) A

#define EXPAND2(A, B) __EXPAND2_CONT__(A, B)
#define __EXPAND2_CONT__(A, B) A ## B

#define EXPAND3(A, B, C) __EXPAND3_CONT__(A, B, C)
#define __EXPAND3_CONT__(A, B, C) A ## B ## C

#define EXPAND4(A, B, C, D) __EXPAND4_CONT__(A, B, C, D)
#define __EXPAND4_CONT__(A, B, C, D) A ## B ## C ## D

#define STRINGIZE(A) __STRINGIZE_CONT__(A)
#define __STRINGIZE_CONT__(A) #A

#define IFNULL(A, B) ({ void *a = (void*)A; a ? a : B; })


#ifdef WIN

#define STATIC_EXPORT __declspec(dllexport) __declspec(selectany)
#define USED_SECTION(NAME)   _declspec(allocate(STRINGIZE(NAME) "$1"))
#define UNUSED_SECTION(NAME) USED_SECTION(NAME)
#define DECLARE_SECTION(NAME, TYPE) \
  __pragma(section(STRINGIZE(NAME), read)); \
  __declspec(allocate(STRINGIZE(NAME) "$0")) STATIC_EXPORT const TYPE EXPAND2(__start_, NAME) = {}; \
  __declspec(allocate(STRINGIZE(NAME) "$2")) STATIC_EXPORT const TYPE EXPAND2(__stop_,  NAME) = {}; 

#else

#define STATIC_EXPORT static
#define USED_SECTION(NAME)   __attribute__(used, section(STRINGIZE(NAME)))
#define UNUSED_SECTION(NAME) __attribute__((unused, section(STRINGIZE(NAME))))
#define DECLARE_SECTION(NAME, TYPE) \
extern TYPE EXPAND2(__start_, NAME), EXPAND2(__stop_, NAME); \
SECTION(NAME) STATIC_EXPORT const TYPE EXPAND2(_init_, NAME) = {};

#endif

#endif
