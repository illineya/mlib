#ifndef __MTHREAD_H__
#define __MTHREAD_H__

#if !defined (__MLIB_H_INSIDE__)
#error "Only <mlib.h> can be included directly."
#endif
#include <pthread.h>

typedef void (* MThreadFunc)(mpointer_t udata);

typedef struct MThread MThread_t;
struct MThread {
    int id;
    pthread_t thread;
    mboolean detached;
};

MThread_t *mthread_create(MThreadFunc func, mpointer_t udata);
mboolean mthread_detach(MThread_t *thread, mboolean detach);
mboolean mthread_join(MThread_t *thread);

#endif