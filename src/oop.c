#include <oop.h>

void *_valloc(size_t size, const char *name)
{
  void *mem = malloc(size + sizeof(const char*));

  *(char**)(mem + size) = (char*)name;

  return mem;
}

VirtualFunction _virtual(const char *name, const char *typename)
{
  struct _virtual_entry *v_table     = ({ extern struct _virtual_entry __start_virtual_table; &__start_virtual_table; });
  struct _virtual_entry *v_table_end = ({ extern struct _virtual_entry __stop_virtual_table;  &__stop_virtual_table;  });

  for (struct _virtual_entry *ve = v_table; ve != v_table_end; ve++) {
    if (strcmp(ve->object, typename)) continue;
    if (strcmp(ve->method,     name)) continue;

    return ve->fptr;
  }
  
  return NULL;
}