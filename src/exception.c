#include <exception.h>

Exception *_exception   = NULL;
Exception  _ex_plchold  = {};
jmp_buf    _ex_jump     = {};
int        _ex_caught   = 0;
int        _handler_set = 0;

void _ex_set_exception(int signal)
{
  if (!_exception)
  {
    switch (signal)
    {
    case SIGSEGV:
      _exception = (Exception*) NEW (SegmentationFaultException) ();
      break;
    case SIGFPE:
      _exception = (Exception*) NEW (ArithmeticException) ();
      break;
    }
  }
}

void _ex_default_handler(int signal)
{
  Exception exception;

  _ex_set_exception(signal);

  exception = *_exception;

  DELETE(_exception);

  if (exception.filename)
  {
    fprintf(stderr, "%s(%ld): ", exception.filename, exception.code);
  }

  fprintf(stderr, "%s\n", exception.base);
  exit(exception.code);
}

void _ex_trycatch_handler(int signal)
{
  _ex_set_exception(signal);
  longjmp(_ex_jump, _exception->code);
}

void _ex_setup()
{
  if (!_handler_set)
  {
    signal(SIGUSR1, _ex_trycatch_handler);
    signal(SIGSEGV, _ex_trycatch_handler);
    signal(SIGFPE,  _ex_trycatch_handler);
  }

  _handler_set = 1;
}

void _ex_teardown()
{
  signal(SIGUSR1, _ex_default_handler);
  signal(SIGSEGV, _ex_default_handler);
  signal(SIGFPE,  _ex_default_handler);

  _handler_set = 0;

  if (_ex_caught) {
    DELETE (_exception);
    _ex_caught = 0;
  }

  if (_exception) {
    _ex_default_handler(SIGUSR1);
  }
}

void throw(Exception *exception)
{
  _exception = exception;

  raise(SIGUSR1);
}

#define TYPENAME Exception

Exception *_(Construct)(const char *message) {
  if (this) {
    this->base = malloc(strlen(message) + 1);
    
    if (this->base) {
      strcpy(this->base, message);
    }
  }

  return this;
}

void _(Destruct)()
{ 
  if (this) {
    free(this->base);
  }
}

#undef TYPENAME
#define TYPENAME SegmentationFaultException

SegmentationFaultException *_(Construct)()
{
  return (SegmentationFaultException*)Exception_Construct(BASE(0), "Segmentation fault!");
}

void _(Destruct)()
{ 
  Exception_Destruct(BASE(0));
}

#undef TYPENAME
#define TYPENAME ArithmeticException

ArithmeticException *_(Construct)()
{
  return (ArithmeticException*)Exception_Construct(BASE(0), "Segmentation fault!");
}

void _(Destruct)()
{ 
  Exception_Destruct(BASE(0));
}

#undef TYPENAME
#define TYPENAME MemoryAllocationException

MemoryAllocationException *_(Construct)()
{
  return (MemoryAllocationException*)Exception_Construct(BASE(0), "Memory allocation failed!");
}

void _(Destruct)()
{ 
  Exception_Destruct(BASE(0));
}

#undef TYPENAME