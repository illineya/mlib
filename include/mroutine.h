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
    MRoutineInfo_t **threads;
    muint64_t cores;
    pthread_mutex_t mutex;
    MQueue_t *queue;
};

/**
 * Создаёт новый пул рутин
 *
 * @return MRoutine_t *
 */
MRoutine_t *mroutine_init();

/**
 * Додавляет задачу в рутину
 *
 * @param routine MRoutine_t *
 * @param func MThreadFunc
 * @param data mpointer_t
 * @param destroy MThreadDestroyFunc
 */
void mroutine_attach(MRoutine_t *routine, MThreadFunc func, mpointer_t data, MThreadDestroyFunc destroy);

/**
 * Ощичает выделенную под рутины память
 *
 * @param routine MRoutine_t *
 */
void mroutine_deinit(MRoutine_t *routine);

#endif