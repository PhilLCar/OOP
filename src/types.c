#include <types.h>

////////////////////////////////////////////////////////////////////////////////
const Type* findtype(const char *typename)
{
    const Type *result = NULL;

  if (typename) {
    char *_typename;

    // to handle composite types
    if (strchr(typename, ' ')) {
      int len = strlen(typename);

      _typename = malloc(len);

      for (int i = 0, j = 0; i < len; i++, j++) {
        while (typename[j] == ' ') ++j;
        _typename[i] = typename[j];
        if (!typename[j]) break;
      }
    } else {
      _typename = (void*)typename;
    }

    if (strchr(typename, '*')) {
      result = &_typeof_Pointer;
    } else {
      const Type *start = ({ extern const Type __start_reflection; &__start_reflection; });
      const Type *end   = ({ extern const Type __stop_reflection;  &__stop_reflection;  });

      if (start && end)
      {
        for (const Type *type = start; type != end; type++) {
          if (!strcmp(type->name, _typename)) {
            result = type;
            break;
          }
        }
      }
    }

    if (_typename != typename) {
      free(_typename);
    }
  }
  
  return result;
}


////////////////////////////////////////////////////////////////////////////////
VirtualFunction virtual(const Type *type, const char *method)
{
  do {
    if (type && method)
    {
      for (const VirtualEntry *ve = type->ve_start; ve != type->ve_stop; ve++) {
        if (strcmp(ve->method, method)) continue;

        return ve->fptr;
      }
    }
  } while ((type = getbase(type)));
  
  return NULL;
}

////////////////////////////////////////////////////////////////////////////////
ConstVirtualFunction constvirtual(const Type *type, const char *method)
{
  return (ConstVirtualFunction)virtual(type, method);
}

//#ifdef MEMORY_WATCH
////////////////////////////////////////////////////////////////////////////////
void *__talloc(const Type *type, const char *filename, int line)
{
  const Type **mem = __malloc(sizeof(const Type*) + type->size, filename, line);
               
  if (mem) *mem++ = type;

  return mem;
}

////////////////////////////////////////////////////////////////////////////////
void __tfree(void *object)
{
  __free((const Type**)object - 1);
}
//#endif

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
const Type *getbase(const Type *type)
{
  return findtype(type->basename ? *type->basename : NULL);
}

////////////////////////////////////////////////////////////////////////////////
const char *typename(const void *object)
{
  return gettype(object)->name;
}

////////////////////////////////////////////////////////////////////////////////
int isobject(const Type *type)
{
  return type->category == TYPES_OBJECT;
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

  return castable(base, getbase(derived));
}
