#ifndef __MQUEUE_H__
#define __MQUEUE_H__

#if !defined (__MLIB_H_INSIDE__)
#error "Only <mlib.h> can be included directly."
#endif
#include <mlib.h>

typedef struct MQueue MQueue_t;

struct MQueue {
    MList_t *list;
    muint32_t count;
};

/**
 * Создаёт новую очередь
 *
 * @return MQueue_t *
 */
MQueue_t *mqueue_init();

/**
 * Добавляет элемент в очередь
 *
 * @param queue MQueue_t *
 * @param data mpointer_t
 */
void mqueue_push(MQueue_t *queue, mpointer_t data);

/**
 * Удаляет элемент из очереди и возвращает значение
 *
 * @param queue MQueue_t *
 * @return mpointer_r
 */
mpointer_t mqueue_pop(MQueue_t *queue);

/**
 * Очищает всю память занимаемую очередью
 *
 * @param queue MQueue_t *
 */
void mqueue_deinit(MQueue_t *queue);

#endif