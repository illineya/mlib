#ifndef __MMAP_H__
#define __MMAP_H__

#if !defined (__MLIB_H_INSIDE__)
#error "Only <mlib.h> can be included directly."
#endif

typedef muint8_t (* MHashFunc)(mpointer_t key);
typedef mboolean (* MEqualFunc)(mpointer_t key, mpointer_t value);

typedef struct MMap MMap_t;
struct MMap {
    muint8_t capacity;
    muint32_t length;
    MHashFunc hash;
    MEqualFunc equal;
    MList_t *bucket[];
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
MMap_t *mmap_init(muint8_t capacity, MHashFunc hash, MEqualFunc equal);

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
 * Получает длину map
 *
 * @param map MMap_t *
 * @return muint_32_t
 */
muint32_t mmap_length(MMap_t *map);

#endif