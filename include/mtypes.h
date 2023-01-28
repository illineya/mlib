#ifndef __MTYPES_H__
#define __MTYPES_H__

#if !defined (__MLIB_H_INSIDE__)
#error "Only <mlib.h> can be included directly."
#endif

#define NULL (void *) 0

enum BOOL {FALSE, TRUE};

typedef enum BOOL mboolean;

typedef char * mpointer_t;
typedef const char * mconstpointer_t;

typedef unsigned long long int muint64_t;
typedef long long int mint64_t;

typedef unsigned int muint32_t;
typedef int mint32_t;

typedef unsigned short int muint16_t;
typedef short int mint16_t;

typedef unsigned char muint8_t;
typedef char mint8_t;

typedef unsigned char muchar_t;
typedef char mchar_t;

#endif