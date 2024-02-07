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

/**
 * Получает первый элемент из списка
 *
 * @param list MList_t *
 * @return MLis_t *
 */
MList_t *mlist_first(MList_t *list);

/**
 * Получает последний элемент из списка
 *
 * @param list MList_t *
 * @return MLis_t *
 */
MList_t *mlist_last(MList_t *list);

/**
 * Получает элемент по индексу
 *
 * @param list MList_t *
 * @param n muint32_t
 * @return mpointer_t
 */
mpointer_t mlist_get(MList_t *list, muint32_t n);

/**
 * Кладёт новый элемент в конец списка
 *
 * @param list MLis_t *
 * @param data mpointer_t
 * @return MLis_t *
 */
MList_t *mlist_append(MList_t *list, mpointer_t data);

/**
 * Кладёт новый элемент в начало списка
 *
 * @param list MLis_t *
 * @param data mpointer_t
 * @return MLis_t *
 */
MList_t *mlist_prepend(MList_t *list, mpointer_t data);

/**
 * Кладёт новый элемент в список, в позицию определённую функцией MListSortFunc
 *
 * @param list MLis_t *
 * @param a mpointer_t
 * @param b mpointer_t
 * @return MLis_t *
 */
MList_t *mlist_insert_sorted(MList_t *list, mpointer_t data, MSortFunc func);

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
 * Удаляет все элементы из списка с удалением
 * значения при помощи free
 *
 * @param list MList_t *
 */
void mlist_remove_all_full(MList_t *list);

/**
 * Удаляет все элементы из списка с удалением
 * значения при помощи функции обратного вызова
 *
 * @param list MList_t *
 */
void mlist_remove_all_full2(MList_t *list, MFreeFunc func);

/**
 * Возвращает кол-во элементов в списке
 *
 * @param list MList_t *
 * @return muint32_t
 */
muint32_t mlist_length(MList_t *list);

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
void mlist_foreach(MList_t *list, MForeachFunc func, mpointer_t udata);

#endif
