#ifndef __MTYPES_H__
#define __MTYPES_H__

#if !defined (__MLIB_H_INSIDE__)
#error "Only <mlib.h> can be included directly."
#endif

#ifndef NULL
#define NULL (void *) 0
#endif

#define MPOINTER(p) (mpointer_t) p
#define MPOINTER_TO_INT8(p) (mint8_t) (*p)
#define MPOINTER_TO_INT16(p) (mint16_t) (*p)
#define MPOINTER_TO_INT32(p) (mint32_t) (*p)
#define MPOINTER_TO_INT64(p) (mint64_t) (*p)
#define MPOINTER_TO_UINT8(p) (muint8_t) (*p)
#define MPOINTER_TO_UINT16(p) (muint16_t) (*p)
#define MPOINTER_TO_UINT32(p) (muint32_t) (*p)
#define MPOINTER_TO_UINT64(p) (muint64_t) (*p)

enum BOOL {false, true};

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

typedef void (* MFreeFunc)(mpointer_t);
typedef mboolean (* MForeachFunc)(mpointer_t key, mpointer_t value, mpointer_t udata);
typedef mboolean (* MMapPredicatFunc)(mpointer_t a, mpointer_t b);
typedef int (* MSortFunc)(mpointer_t a, mpointer_t b);
typedef muint32_t (* MHashFunc)(mconstpointer_t key);
typedef mboolean (* MEqualFunc)(mconstpointer_t key, mconstpointer_t value);

typedef struct MPair MPair_t;
struct MPair {
    mpointer_t key;
    mpointer_t value;
};

#endif