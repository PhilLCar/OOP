#include <types.h>

////////////////////////////////////////////////////////////////////////////////
const Type* findtype(const char *typename)
{
  const Type *start = ({ extern const Type __start_reflection; &__start_reflection; });
  const Type *end   = ({ extern const Type __stop_reflection;  &__stop_reflection;  });

  if (start && end)
  {
    for (const Type *type = start; type != end; type++) {
      if (strcmp(type->name, typename)) continue;

      return type;
    }
  }
  
  return NULL;
}


////////////////////////////////////////////////////////////////////////////////
VirtualFunction virtual(const Type *type, const char *method)
{
  if (type && method)
  {
    for (const VirtualEntry *ve = type->ve_start; ve != type->ve_stop; ve++) {
      if (strcmp(ve->method, method)) continue;

      return ve->fptr;
    }
  }
  
  return NULL;
}

#ifdef MEMORY_WATCH
////////////////////////////////////////////////////////////////////////////////
void *__talloc(const Type *type, const char *filename, int line)
{
  const Type **mem = __malloc(sizeof(const Type*) + type->size, filename, line);
               
  if (mem) *mem++ = type;

  return mem;
}
#endif

////////////////////////////////////////////////////////////////////////////////
void *talloc(const Type *type)
{
  const Type **mem = malloc(sizeof(const Type*) + type->size);
               
  if (mem) *mem++ = type;

  return mem;
}

////////////////////////////////////////////////////////////////////////////////
void tfree(void *object)
{
  free((const Type**)object - 1);
}

////////////////////////////////////////////////////////////////////////////////
const Type *gettype(const void *object)
{
  return ((const Type**)object)[-1];
}

////////////////////////////////////////////////////////////////////////////////
const char *typename(const void *object)
{
  return gettype(object)->name;
}

////////////////////////////////////////////////////////////////////////////////
int isobject(const Type *type)
{
  return type->destruct != NULL;
}

////////////////////////////////////////////////////////////////////////////////
int sametype(const Type *a, const Type *b)
{
  return !strcmp(a->name, b->name);
}

////////////////////////////////////////////////////////////////////////////////
int castable(const Type *base, const Type *derived)
{
  if (!derived)                return 0;
  if (sametype(base, derived)) return 1;

  return castable(base, *derived->base);
}