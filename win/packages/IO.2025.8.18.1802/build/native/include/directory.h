#ifndef DIRECTORY_H
#define DIRECTORY_H

// C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// CUT
#include <diagnostic.h>
#include "export.h"
#include "osal.h"
#include "file.h"
#include "path.h"

#ifdef WIN
#include <windows.h>
#else
#ifndef __USE_MISC
#define __USE_MISC
#endif
#include <dirent.h>
#endif


typedef enum dir_type {
  DIRTYPE_FILE,
  DIRTYPE_DIRECTORY,
  DIRTYPE_OTHER,
  DIRTYPE_DONE
} DirectoryType;

typedef struct dir_item {
  char          name[PATH_MAX_LENGTH];
  DirectoryType type;
} DirectoryItem;

typedef struct dir_iterator {
  char           path[PATH_MAX_LENGTH];
  char           filter[PATH_MAX_LENGTH];
  void          *handle;
  DirectoryItem  current;
} DirectoryIterator;

PUBLIC DirectoryIterator *dopen(const char *dirname);
PUBLIC void               dclose(DirectoryIterator *iterator);
PUBLIC DirectoryItem     *dnext(DirectoryIterator *iterator);
PUBLIC int                ddone(DirectoryIterator *iterator);
PUBLIC void               dclose(DirectoryIterator *iterator);
PUBLIC void               dname(const DirectoryIterator *iterator, int size, char buffer[size]);
PUBLIC int                dexists(const char *dirname);

#endif