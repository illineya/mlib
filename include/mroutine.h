#ifndef __MROUTINE_H__
#define __MROUTINE_H__

#if !defined (__MLIB_H_INSIDE__)
#error "Only <mlib.h> can be included directly."
#endif
#include <pthread.h>

typedef struct MRoutineData MRoutineData_t;
typedef struct MRoutine MRoutine_t;
typedef struct MRoutineInfo MRoutineInfo_t;

struct MRoutineData {
    MThreadFunc func;
    MThreadDestroyFunc destroy;
    mpointer_t data;
};

struct MRoutineInfo {
    MThread_t *thread;
    pthread_mutex_t mutex;
    mboolean running;
    MRoutine_t *routine;
};

struct MRoutine {
    MRoutineInfo_t *threads[5];
    muint64_t cores;
    pthread_mutex_t mutex;
    MQueue_t *queue;
};

MRoutine_t *mroutine_init();
void mroutine_attach(MRoutine_t *routine, MThreadFunc func, mpointer_t data, MThreadDestroyFunc destroy);
void mroutine_deinit(MRoutine_t *routine);

#endif