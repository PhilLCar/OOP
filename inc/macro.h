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

#endif
