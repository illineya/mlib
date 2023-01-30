#ifndef __MSET_H__
#define __MSET_H__

#if !defined (__MLIB_H_INSIDE__)
#error "Only <mlib.h> can be included directly."
#endif
#include <mlib.h>

typedef struct MSet MSet_t;
struct MSet {
    MMap_t *map;
};

MSet_t *mset_init(MHashFunc hash, MEqualFunc equal);
void mset_deinit(MSet_t *set);
void mset_add(MSet_t *set, mpointer_t data);
void mset_foreach(MSet_t *set, MForeachFunc func, mpointer_t data);
void mset_remove(MSet_t *set, mpointer_t data);
muint32_t mset_length(MSet_t *set);

#endif
