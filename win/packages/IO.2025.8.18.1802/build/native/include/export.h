#ifndef EXPORT_H
#define EXPORT_H

#ifdef WIN
#ifdef IMPORT_PUBLIC
#define PUBLIC __declspec(dllimport)
#else
#define PUBLIC __declspec(dllexport)
#endif
#ifdef __INTELLISENSE__
#define __VA_OPT__(X)
#endif
#else
#define PUBLIC __attribute__((visibility("default")))
#endif

#endif