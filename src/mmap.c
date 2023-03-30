#include <mlib.h>
#include <stdlib.h>

MMap_t *mmap_init(muint16_t capacity, MHashFunc hash, MEqualFunc equal) {
    MMap_t *map = (MMap_t *) calloc(1, sizeof(MMap_t));

    map->key_free = NULL;
    map->value_free = NULL;
    map->hash = hash;
    map->equal = equal;
    map->capacity = capacity;
    map->bucket = calloc(capacity, sizeof(MList_t));

    return map;
}

MMap_t *mmap_init_full(muint16_t capacity, MHashFunc hash, MEqualFunc equal, MFreeFunc key, MFreeFunc value) {
    MMap_t *map = mmap_init(capacity, hash, equal);
    map->key_free = key;
    map->value_free = value;

    return map;
}

void mmap_deinit(MMap_t *map) {
    if(map) {
        for(int i=0; i<map->capacity; i++) {
            mlist_remove_all_full(*(map->bucket + i));
        }
        free(map->bucket);
        free(map);
    }
}

static muint8_t mmap_hash(MMap_t *map, mpointer_t key) {
    return map->hash(key) % map->capacity;
}

static MPair_t *mmap_find(MMap_t *map, mpointer_t key) {
    muint8_t index = mmap_hash(map, key);
    MList_t *list = mlist_first(*(map->bucket + index));

    while(list) {
        MPair_t *pair = (MPair_t *) list->data;
        if(map->equal(pair->key, key))
            return pair;
        list = list->next;
    }

    return NULL;
}

void mmap_add(MMap_t *map, mpointer_t key, mpointer_t value) {
    if(map) {
        MPair_t *pair = mmap_find(map, key);
        if(pair) {
            pair->value = value;
            return;
        }

        muint8_t index = mmap_hash(map, key);
        pair = malloc(sizeof(MPair_t));
        pair->key = key;
        pair->value = value;
        *(map->bucket + index) = mlist_append(*(map->bucket + index), (mpointer_t) pair);
        map->length++;

        M_LOG_DEBUG("MAP ADD %i %s %p", index, pair->key, pair->value);
    }
}

mpointer_t mmap_get(MMap_t *map, mpointer_t key) {
    MPair_t *pair = mmap_find(map, key);
    if(pair) {
        M_LOG_DEBUG("MAP GET %s %p", pair->key, pair->value);
        return pair->value;
    }

    return NULL;
}

mpointer_t mmap_get_pr(MMap_t *map, MMapPredicatFunc func, mpointer_t value) {
    MList_t *list = mmap_get_values(map);
    muint32_t length = mlist_length(list);

    for(int i=0; i < length; i++) {
        mpointer_t data = mlist_get(list, i);
        if(func(data, value)) {
            mlist_remove_all(list);
            return data;
        }
    }

    mlist_remove_all(list);
    return NULL;
}

mboolean mmap_contains(MMap_t *map, mpointer_t key) {
    return mmap_find(map, key) != NULL;
}

void mmap_remove(MMap_t *map, mpointer_t key) {
    muint8_t index = mmap_hash(map, key);

    MPair_t *pair = mmap_find(map, key);
    if(pair) {
        *(map->bucket + index) = mlist_remove(*(map->bucket + index), (mconstpointer_t) pair);
        if(map->key_free) map->key_free(pair->key);
        if(map->value_free) map->value_free(pair->value);
        M_LOG_DEBUG("MAP REMOVE %i %s %p", index, pair->key, pair->value);
        free(pair);
        map->length--;
    }
}

void mmap_remove_all(MMap_t *map) {
    if(map) {
        for(int i=0; i<map->capacity; i++) {
            MList_t *list = *(map->bucket + i);
            while(list) {
                MPair_t *pair = (MPair_t *) list->data;
                if(pair) {
                    if(map->key_free) map->key_free(pair->key);
                    if(map->value_free) map->value_free(pair->value);
                }
                list = list->next;
            }
        }
    }
}

muint32_t mmap_length(MMap_t *map) {
    if(map) {
        return map->length;
    }

    return 0;
}

MList_t *mmap_get_values(MMap_t *map) {
    MList_t *list = NULL;

    for(int i=0; i<map->capacity; i++) {
        MList_t *item = *(map->bucket + i);
        item = mlist_first(item);

        while(item) {
            MPair_t *pair = (MPair_t *) item->data;
            list = mlist_append(list, pair->value);
            item = item->next;
        }
    }

    return list;
}

void mmap_foreach(MMap_t *map, MForeachFunc func, mpointer_t udata) {
    if(map) {
        for(int i=0; i<map->capacity; i++) {
            MList_t *list = *(map->bucket + i);
            list = mlist_first(list);

            while(list) {
                MPair_t *pair = (MPair_t *) list->data;
                if(!func(pair->key, pair->value, udata))
                    break;
                list = list->next;
            }
        }
    }
}

void mmap_foreach_nth(MMap_t *map, MForeachFunc func, mint32_t start, mint32_t num, mpointer_t udata) {
    MList_t *list = mmap_get_values(map);
    muint32_t length = mlist_length(list);
    muint32_t end = start + num;

    if(start < length) {
        for(int i=start; i<(end <= length ? end : length); i++) {
            mpointer_t data = mlist_get(list, i);
            if(data) {
                func((mpointer_t) &i, data, udata);
            }
        }
    }

    mlist_remove_all(list);
}
