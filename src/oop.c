#include <oop.h>

void *_valloc(size_t size, const char *name)
{
  char *mem = malloc(size + sizeof(const char*));

  *(const char**)(mem + size) = name;

  return mem;
}

VirtualFunction _virtual(const char *name, const char *typename)
{
  if (name && typename)
  {
    struct _virtual_entry *v_table     = ({ extern struct _virtual_entry __start_virtual_table; &__start_virtual_table; });
    struct _virtual_entry *v_table_end = ({ extern struct _virtual_entry __stop_virtual_table;  &__stop_virtual_table;  });

    // WARNING: This is most likely platform dependent
    // Space between entries is the size aligned on 16
    int space = (sizeof(struct _virtual_entry) + 0xF) & ~0xF;

    for (struct _virtual_entry *ve = v_table; ve != v_table_end; ve = (struct _virtual_entry*)((char*)ve + space)) {
      if (strcmp(ve->object, typename)) continue;
      if (strcmp(ve->method,     name)) continue;

      return ve->fptr;
    }
  }
  
  return NULL;
}