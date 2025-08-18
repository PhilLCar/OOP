#ifndef PATH_H
#define PATH_H

#include <diagnostic.h>
#include "osal.h"
#include "export.h"

PUBLIC int pisabs(const char *path);
PUBLIC int pprotocol(const char *path, int size, char buffer[size]);
PUBLIC int pdrive(const char *path, int size, char buffer[size]);

PUBLIC int pclean(const char *path, int size, char buffer[size]);
PUBLIC int prel  (const char *path, int size, char buffer[size]);
PUBLIC int pabs  (const char *path, int size, char buffer[size]);

PUBLIC int pcombine(const char *path, const char *filename, int size, char buffer[size]);

#endif