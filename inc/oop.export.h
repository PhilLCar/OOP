#ifndef OOP_EXPORT_H
#define OOP_EXPORT_H


#ifdef WIN
#ifdef OOP_EXPORTS
#define OOP_EXPORT __declspec(dllexport)
#else
#define OOP_EXPORT __declspec(dllimport)
#endif
#ifdef __INTELLISENSE__
#define __VA_OPT__(X)
#endif
#else
#define OOP_EXPORT __attribute__((visibility("default")))
#endif
#endif