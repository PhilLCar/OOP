#ifndef OSAL_UTILS
#define OSAL_UTILS

// C
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// CUT
#include <diagnostic.h>
#include "log.h"
#include "export.h"

#ifdef WIN
// Windows
#define long long long
#define PATH_MARKER '\\'
#define PATH_MAX_LENGTH 260 /* This is insanely small?? */
#undef max
#undef min
#define popen  _popen
#define pclose _pclose
#define memcpy(D, S, L) memcpy_s(D, L, S, L)
#define strcpy(D, S)    strcpy_s(D, strlen(S) + 1, S)
#define strncpy(D, S, L) strncpy_s(D, L + 1, S, L)
#else
// Linux
#define PATH_MARKER '/'
#define PATH_MAX_LENGTH 4096
#endif

static inline __attribute__((unused)) int max(int a, int b) {
  return a > b ? a : b;
}

static inline __attribute__((unused)) int min(int a, int b) {
  return a < b ? a : b;
}

PUBLIC int  nstrcpy(char *dst, const char *src, unsigned int n);
PUBLIC void sysargs(const char *command, int argc, const char *argv[argc]);
PUBLIC void *run(const char *command);
PUBLIC void *runargs(const char *command, int argc, const char *argv[argc]);

PUBLIC void newdir(const char *dirname);
PUBLIC void deldir(const char *dirname);
PUBLIC void newfile(const char *filename);
PUBLIC void delfile(const char *filename);
PUBLIC long lastmod(const char *filename);
PUBLIC void workdir(int size, char buffer[size]);

#endif