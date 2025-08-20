#ifndef __MASYNC_QUEUE_H__
#define __MASYNC_QUEUE_H__

#if !defined (__MLIB_H_INSIDE__)
#error "Only <mlib.h> can be included directly."
#endif
#include <mlib.h>

typedef struct MAsyncQueue MAsyncQueue_t;

struct MAsyncQueue {
    MQueue_t *queue;
    pthread_mutex_t mutex;
    pthread_mutex_t wait;
};

/**
 * Создаёт новую асинхронную очередь
 *
 * @return MAsyncQueue_t *
 */
MAsyncQueue_t *masync_queue_init();

/**
 * Добавляет элемент в очередь
 *
 * @param queue MAsyncQueue_t *
 * @param data mpointer_t
 */
void masync_queue_push(MAsyncQueue_t *queue, mpointer_t data);

/**
 * Удаляет элемент из очереди и возвращает значение
 *
 * @param queue MAsyncQueue_t *
 * @return mpointer_r
 */
mpointer_t masync_queue_pop(MAsyncQueue_t *queue);

/**
 * Получает кол-во элементов в очереди
 *
 * @param queue MAsyncQueue_t *
 * @return muint32_t
 */
muint32_t masync_queue_length(MAsyncQueue_t *queue);

/**
 * Очищает всю память занимаемую очередью
 *
 * @param queue MAsyncQueue_t *
 */
void masync_queue_deinit(MAsyncQueue_t *queue);

#endif