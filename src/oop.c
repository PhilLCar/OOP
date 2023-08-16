#include <oop.h>

void *_virtual(size_t size, const char *name)
{
  void *mem = malloc(size + sizeof(const char*));

  *(char**)(mem + size) = (char*)name;

  return mem;
}

void *_v_call(const char *name, void *typename, void *params)
{
  struct _virtual_entry *v_table     = ({ extern struct _virtual_entry __start_virtual_table; &__start_virtual_table; });
  struct _virtual_entry *v_table_end = ({ extern struct _virtual_entry __stop_virtual_table;  &__stop_virtual_table;  });

  for (struct _virtual_entry *ve = v_table; ve != v_table_end; ve++) {
    if (strcmp(ve->object, typename)) continue;
    if (strcmp(ve->method,     name)) continue;

  }
  
  return NULL;
}