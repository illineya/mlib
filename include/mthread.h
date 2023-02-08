#ifndef __MTHREAD_H__
#define __MTHREAD_H__

#if !defined (__MLIB_H_INSIDE__)
#error "Only <mlib.h> can be included directly."
#endif
#include <pthread.h>

typedef void (* MThreadFunc)(mpointer_t udata);
typedef void (* MThreadDestroyFunc)(mpointer_t udata);

typedef struct MThread MThread_t;
struct MThread {
    int id;
    pthread_t thread;
    mboolean detached;
};

/**
 * Создаёт новый поток
 *
 * @param func MThreadFunc
 * @param udata mpointer_t
 * @return MThread_t *
 */
MThread_t *mthread_create(MThreadFunc func, mpointer_t udata);

/**
 * Отсоединяет поток
 *
 * @param thread MThread_t *
 * @return mboolean
 */
mboolean mthread_detach(MThread_t *thread);

/**
 * Ожидает завершения потока
 *
 * @param thread MThread_t *
 * @return mboolean
 */
mboolean mthread_join(MThread_t *thread);

/**
 * Освобождает память выделенную для потока
 *
 * @param thread MThread_t *
 */
void mthread_deinit(MThread_t *thread);

#endif