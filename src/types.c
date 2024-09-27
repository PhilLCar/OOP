#include <types.h>

// Type instead of type id

////////////////////////////////////////////////////////////////////////////////
void *talloc(Type *type)
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
const char *typename(void *object)
{
  return gettype(object)->name;
}

////////////////////////////////////////////////////////////////////////////////
int isobject(Type *type)
{
  return type->free != NULL;
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