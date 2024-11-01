#ifndef EXCEPTION_H
#define EXCEPTION_H

// C
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

// CUT
#include <oop.h>

#define TYPENAME Exception

#define TRY _ex_setup(); if (!setjmp(_ex_jump))
#define CATCH(EXCEPTION_TYPE) else if ((((Exception*)EXCEPTION_TYPE##_Default((EXCEPTION_TYPE*)&_ex_plchold))->code == _exception->code \
                                    || !((Exception*)EXCEPTION_TYPE##_Default((EXCEPTION_TYPE*)&_ex_plchold))->code) && (_ex_caught = 1))
#define FINALLY if (_exception)
#define END_TRY _ex_teardown();

#define THROW(EXCEPTION) _exception = EXCEPTION; _exception->filename = __FILE__; _exception->line = __LINE__; throw(_exception)

OBJECT (const char *message, long code)
  const char *message;
  const char *filename;
  int         line;
  long        code;
END_OBJECT("An unknown error occured!", 0);

extern Exception *_exception;
extern Exception  _ex_plchold;
extern jmp_buf    _ex_jump;
extern int        _ex_caught;

void _ex_setup();
void _ex_teardown();

void throw(Exception *exception);

#undef TYPENAME
#define TYPENAME SegFaultException
OBJECT () INHERIT (Exception)

END_OBJECT();
#undef TYPENAME
#define TYPENAME ArithmeticException
OBJECT () INHERIT (Exception)

END_OBJECT();
#undef TYPENAME

#endif