#ifndef __MLOG_H__
#define __MLOG_H__

#if !defined (__MLIB_H_INSIDE__)
#error "Only <mlib.h> can be included directly."
#endif

#include <stdio.h>

#define ERROR 1
#define WARN 2
#define INFO 3
#define DEBUG 4

static muint8_t LOGLEVEL = ERROR;

#define M_LOG_ERR(format, ...) \
    if(LOGLEVEL >= ERROR) printf("\e[0;31m[ERROR]\e[0m %s:%d " format "\n", __FILE__, __LINE__, ##__VA_ARGS__);

#define M_LOG_WARN(format, ...) \
    if(LOGLEVEL >= WARN) printf("\e[0;33m[WARN]\e[0m %s:%d " format "\n", __FILE__, __LINE__, ##__VA_ARGS__);

#define M_LOG_INFO(format, ...) \
    if(LOGLEVEL >= INFO) printf("\e[0;34m[INFO]\e[0m %s:%d " format "\n", __FILE__, __LINE__, ##__VA_ARGS__);

#define M_LOG_DEBUG(format, ...) \
    if(LOGLEVEL >= DEBUG) printf("\e[0;37m[DEBUG]\e[0m %s:%d " format "\n", __FILE__, __LINE__, ##__VA_ARGS__);

#endif