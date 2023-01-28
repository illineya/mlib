#ifndef __MPOOL_H__
#define __MPOOL_H__

#if !defined (__MLIB_H_INSIDE__)
#error "Only <mlib.h> can be included directly."
#endif

#include <stdio.h>

#if LOGLEVEL >= 3
#define M_LOG_ERR(format, ...) printf("\e[0;31m[ERROR]\e[0m %s:%d " format "\n", __FILE__, __LINE__, ##__VA_ARGS__);
#else
#define M_LOG_ERR(format, ...)
#endif

#if LOGLEVEL >= 2
#define M_LOG_WARN(format, ...) printf("\e[0;33m[WARN]\e[0m %s:%d " format "\n", __FILE__, __LINE__, ##__VA_ARGS__);
#else
#define M_LOG_WARN(format, ...)
#endif

#if LOGLEVEL >= 1
#define M_LOG_INFO(format, ...) printf("\e[0;34m[INFO]\e[0m %s:%d " format "\n", __FILE__, __LINE__, ##__VA_ARGS__);
#else
#define M_LOG_INFO(format, ...)
#endif

#endif