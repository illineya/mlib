#include <mlib.h>

MSet_t *mset_init(MHashFunc hash, MEqualFunc equal) {
    MSet_t *set = calloc(1, sizeof(MSet_t));
    set->map = mmap_init(hash, equal);
    return set;
}

void mset_deinit(MSet_t *set) {
    if(set) {
        mmap_deinit(set->map);
        free(set);
    }
}

void mset_add(MSet_t *set, mpointer_t data) {
    if(set) {
        if(!mmap_contains(set->map, data)) {
            mmap_add(set->map, data, data);
        }
    }
}

void mset_foreach(MSet_t *set, MListForeachFunc func, mpointer_t data) {
    if(set) {
        mmap_foreach(set->map, func, data);
    }
}

void mset_remove(MSet_t *set, mpointer_t data) {
    if(set) {
        mmap_remove(set->map, data);
    }
}

muint32_t mset_length(MSet_t *set) {
    return set->map->length;
}
