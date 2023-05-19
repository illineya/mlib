#ifndef __MMAP_H__
#define __MMAP_H__

#if !defined (__MLIB_H_INSIDE__)
#error "Only <mlib.h> can be included directly."
#endif

#include <mlist.h>

typedef struct MMap MMap_t;
struct MMap {
    muint32_t length;
    MHashFunc hash;
    MEqualFunc equal;
    MFreeFunc key_free;
    MFreeFunc value_free;
    MList_t **bucket;
    muint16_t capacity;
};

/**
 * Инициализирует структуру MMap_t ёмкостью capacity
 * и функциями обратного вызова hash и equals
 * для строковых значений ключа реализованы функции
 * mstr_hash и mstr_equal
 *
 * @param capacity muint8_t
 * @param hash MHashFunc
 * @param equal MEqual_t
 * @return MMap_t *
 */
MMap_t *mmap_init(muint16_t capacity, MHashFunc hash, MEqualFunc equal);

/**
 * Инициализирует структуру MMap_t ёмкостью capacity
 * и функциями обратного вызова hash и equals
 * для строковых значений ключа реализованы функции
 * mstr_hash и mstr_equal
 *
 * @param capacity muint8_t
 * @param hash MHashFunc
 * @param equal MEqual_t
 * @param key MFreeFunc
 * @param value MFreeFunc
 * @return MMap_t *
 */
MMap_t *mmap_init_full(muint16_t capacity, MHashFunc hash, MEqualFunc equal, MFreeFunc key, MFreeFunc value);

/**
 * Очищает всю выделенную память для MMap_t
 *
 * @param map MMap_t *
 */
void mmap_deinit(MMap_t *map);

/**
 * Добавляет новый элемент в map
 *
 * @param map MMap_t *
 * @param key mpointer_t
 * @param value mpointer_t
 */
void mmap_add(MMap_t *map, mpointer_t key, mpointer_t value);

/**
 * Получает элемент из map по ключу
 *
 * @param map MMap_t *
 * @param key mpointer_t
 * @return mpointer_t
 */
mpointer_t mmap_get(MMap_t *map, mpointer_t key);

/**
 * Получает элемент из map по предикатной функции
 *
 * @param map MMap_t *
 * @param func MMapPredicatFunc
 * @param value mpointer_t
 * @return mpointer_t
 */
mpointer_t mmap_get_pr(MMap_t *map, MMapPredicatFunc func, mpointer_t value);

/**
 * Проверяет наличие элемента в map
 * Внимание! Слоожность алгоритма равна той-же, что и получение элемента
 * при помощи функции @see mmap_get, по этой причине, следует подумать о необходимости использования функции
 *
 * @param map MMap_t *
 * @param key mpointer_t
 * @return mboolean
 */
mboolean mmap_contains(MMap_t *map, mpointer_t key);

/**
 * Удаляет элемент по ключу
 *
 * @param map MMap_t *
 * @param key mpointer_r
 */
void mmap_remove(MMap_t *map, mpointer_t key);

/**
 * Удаляет все элементы из MMap_t
 *
 * @param map MMap_t *
 */
void mmap_remove_all(MMap_t *map);

/**
 * Получает длину map
 *
 * @param map MMap_t *
 * @return muint_32_t
 */
muint32_t mmap_length(MMap_t *map);

/**
 * Получает значения MMap_t в виде списка
 *
 * @param map MMap_t *
 * @return MList_t *
 */
MList_t *mmap_get_values(MMap_t *map);

/**
 * Получает ключи MMap_t в виде списка
 *
 * @param map MMap_t *
 * @return MList_t *
 */
MList_t *mmap_get_keys(MMap_t *map);

/**
 * Вызывает функцию для каждого элемента map
 *
 * @param map MMap_t *
 * @param func MMapForeach
 */
void mmap_foreach(MMap_t *map, MForeachFunc func, mpointer_t udata);

/**
 * Вызывает функцию для каждого элемента map начиная с позиции и заканчивая позицией
 *
 * @param map MMap_t *
 * @param func MMapForeach
 */
void mmap_foreach_nth(MMap_t *map, MForeachFunc func, mint32_t start, mint32_t num, mpointer_t udata);

#endif
