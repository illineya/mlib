#ifndef __MPOOL_H__
#define __MPOOL_H__

#if !defined (__MLIB_H_INSIDE__)
#error "Only <mlib.h> can be included directly."
#endif

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <mtypes.h>

typedef struct MPool MPool_t;
struct MPool {
	mpointer_t pool;
	pthread_mutex_t mutex;
    muint64_t size;
	muint32_t count;
    mpointer_t in;
};

/**
 * Создаёт pool объектов
 * 
 * @param size muint64_t
 * @param int count
 * @return mpool_t *
 */
MPool_t *mpool_create(muint64_t size, int count);

/**
 * Выделяет обдасть памяти из pool
 * 
 * @param p mpool_t *
 * @return mpointer_t
 */
mpointer_t mpool_alloc(MPool_t *p);

/**
 * Освобождает область памяти
 * 
 * @param p mpool_t *
 * @param p mpointer_t *
 * @return mpointer_t
 */
void mpool_free(MPool_t *p, mconstpointer_t d);

/**
 * Выделяет обдасть памяти из pool
 * MT-save
 * 
 * @param p mpool_t *
 * @return mpointer_t
 */
mpointer_t mpool_alloc_mt(MPool_t *p);

/**
 * Освобождает область памяти
 * MT-save
 * 
 * @param p mpool_t *
 * @param p mpointer_t *
 * @return mpointer_t
 */
void mpool_free_mt(MPool_t *p, mconstpointer_t d);

/**
 * Освобождает всю память занимаемую pool
 * 
 * @param p mpool_t *
 */
void mpool_destroy(MPool_t *p);

#endif