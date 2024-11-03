#ifndef EXCEPTION_H
#define EXCEPTION_H

// C
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <stdarg.h>

// CUT
#include <diagnostic.h>
#include <oop.h>

#define TYPENAME Exception

#define TRY _ex_setup(); if (!setjmp(_ex_jump))
#define CATCH(EXCEPTION_TYPE) else if (_exception && castable(&OBJECT_TYPE(EXCEPTION_TYPE), gettype(_exception)) && (_ex_caught = 1))
#define FINALLY if (_exception)
#define END_TRY _ex_teardown();

#define THROW(EXCEPTION) _exception = (Exception*)EXCEPTION; _exception->filename = __FILE__; _exception->line = __LINE__; throw(_exception)

OBJECT (const char *message, ...) BASED (char*)
  const char *filename;
  int         line;
  long        code;
END_OBJECT("An unknown error occured!");

extern Exception *_exception;
extern Exception  _ex_plchold;
extern jmp_buf    _ex_jump;
extern int        _ex_caught;

void _ex_setup();
void _ex_teardown();

void throw(Exception *exception);

#undef TYPENAME
#define TYPENAME SegmentationFaultException
OBJECT () INHERIT (Exception)
END_OBJECT();
#undef TYPENAME
#define TYPENAME ArithmeticException
OBJECT () INHERIT (Exception)
END_OBJECT();
#undef TYPENAME
#define TYPENAME MemoryAllocationException
OBJECT () INHERIT (Exception)
END_OBJECT();
#undef TYPENAME

#endif