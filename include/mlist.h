#ifndef __MLIST_H__
#define __MLIST_H__

#if !defined (__MLIB_H_INSIDE__)
#error "Only <mlib.h> can be included directly."
#endif

typedef struct MList MList_t;
struct MList {
    MList_t *next;
    MList_t *prev;
    mpointer_t data;
};

typedef void (* MListForeach)(mpointer_t data);

/**
 * Получает первый элемент из списка
 *
 * @param list MList_t *
 * @return MLis_t *
 */
MList_t *mlist_first(MList_t *list);

/**
 * Кладёт новый элемент в список
 *
 * @param list MLis_t *
 * @param data mpointer_t
 * @return MLis_t *
 */
MList_t *mlist_append(MList_t *list, mpointer_t data);

/**
 * Удаляет элемент из списка
 *
 * @param list MLis_t *
 * @param data mconstpointer_t
 * @return MLis_t *
 */
MList_t *mlist_remove(MList_t *list, mconstpointer_t data);

/**
 * Удаляет все элементы из списка
 *
 * @param list MLis_t *
 */
void mlist_remove_all(MList_t *list);

/**
 * Ищет элемент в списке
 *
 * @param list MLis_t *
 * @param data mconstpointer_t
 * @return MLis_t *
 */
MList_t *mlist_find(MList_t *list, mconstpointer_t data);

/**
 * Вызывает функцию обратного вызова для каждого элемента из списка
 *
 * @param list MLis_t *
 * @param func MListForeach
 */
void mlist_foreach(MList_t *list, MListForeach func);

#endif