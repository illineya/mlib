#ifndef __MSTACK_H__
#define __MSTACK_H__

#if !defined (__MLIB_H_INSIDE__)
#error "Only <mlib.h> can be included directly."
#endif
#include <mlib.h>

typedef struct MStack MStack_t;

struct MStack {
    MList_t *list;
    muint32_t count;
};

/**
 * Создаёт новую очередь
 *
 * @return MStack_t *
 */
MStack_t *mstack_init();

/**
 * Добавляет элемент в очередь
 *
 * @param stack MStack_t *
 * @param data mpointer_t
 */
void mstack_push(MStack_t *stack, mpointer_t data);

/**
 * Удаляет элемент из очереди и возвращает значение
 *
 * @param stack MStack_t *
 * @return mpointer_r
 */
mpointer_t mstack_pop(MStack_t *stack);

/**
 * Очищает всю память занимаемую очередью
 *
 * @param stack MStack_t *
 */
void mstack_deinit(MStack_t *stack);

#endif