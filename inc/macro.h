#ifndef MACRO_H
#define MACRO_H

// Expansion helpers
#define EXPAND(A) __EXPAND_CONT__(A)
#define __EXPAND_CONT__(A) A

#define EXPAND2(A, B) __EXPAND2_CONT__(A, B)
#define __EXPAND2_CONT__(A, B) A ## B

#define EXPAND3(A, B, C) __EXPAND3_CONT__(A, B, C)
#define __EXPAND3_CONT__(A, B, C) A ## B ## C

#define STRINGIZE(A) __STRINGIZE_CONT__(A)
#define __STRINGIZE_CONT__(A) #A

#define IFNULL(A, B) ({ void *a = (void*)A; a ? a : B; })


#ifdef WIN
#define DECLARE_SECTION(NAME, TYPE) \
  __pragma(section(STRINGIZE(NAME), read)); \
  __declspec(allocate(STRINGIZE(NAME) "$0")) TYPE EXPAND2(__start_, NAME) = {}; \
  __declspec(allocate(STRINGIZE(NAME) "$2")) TYPE EXPAND2(__stop_,   NAME) = {};

#define USED_SECTION(NAME) __declspec(allocate(NAME "$1"))
#define UNUSED_SECTION(NAME) USED_SECTION(NAME)
#else
#define SECTION_DECLARATION(NAME, TYPE)
#define USED_SECTION(NAME)   __attribute__((used,   section(NAME)))
#define UNUSED_SECTION(NAME) __attribute__((unused, section(NAME)))
#endif

#endif
