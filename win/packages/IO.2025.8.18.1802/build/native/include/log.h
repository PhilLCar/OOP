#ifndef LOG_H
#define LOG_H

// C
#include <stdlib.h>
#include <stdarg.h>

// CUT
#include <terminal.h>
#include "export.h"

#ifdef WIN
#undef ERROR
#endif

#define LOG_DEBUG 0
#define LOG_INFO  1
#define LOG_WARN  2
#define LOG_ERROR 3
#define LOG_FATAL 4

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_INFO
#endif

#define LOG_MSG_MAX 8192

#define LOG(LEVEL, MESSAGE, ...) loglvl(__FILE__, __LINE__, LEVEL, MESSAGE __VA_OPT__(,) __VA_ARGS__)

#if LOG_LEVEL == LOG_DEBUG
#define DEBUG(MESSAGE, ...) LOG(LOG_DEBUG, MESSAGE __VA_OPT__(,) __VA_ARGS__)
#else
#define DEBUG(MESSAGE, ...)
#endif

#if LOG_LEVEL == LOG_DEBUG || LOG_LEVEL == LOG_INFO
#define INFO(MESSAGE, ...) LOG(LOG_INFO,  MESSAGE __VA_OPT__(,) __VA_ARGS__)
#else
#define INFO(MESSAGE, ...)
#endif

#if LOG_LEVEL == LOG_DEBUG || LOG_LEVEL == LOG_INFO || LOG_LEVEL == LOG_WARN
#define WARN(MESSAGE, ...) LOG(LOG_WARN,  MESSAGE __VA_OPT__(,) __VA_ARGS__)
#else
#define WARN(MESSAGE, ...)
#endif 

#if LOG_LEVEL == LOG_DEBUG || LOG_LEVEL == LOG_INFO || LOG_LEVEL == LOG_WARN || LOG_LEVEL == LOG_ERROR
#define ERROR(MESSAGE, ...) LOG(LOG_ERROR, MESSAGE __VA_OPT__(,) __VA_ARGS__)
#else
#define ERROR(MESSAGE, ...)
#endif

// Fatal errors are always included
#define FATAL(MESSAGE, ...) LOG(LOG_FATAL, MESSAGE __VA_OPT__(,) __VA_ARGS__)

PUBLIC void loglvl(const char *filename, int line, int lvl, const char *message, ...);

#endif