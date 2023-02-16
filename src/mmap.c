#include <mlib.h>
#include <stdlib.h>

MMap_t *mmap_init(muint16_t capacity, MHashFunc hash, MEqualFunc equal) {
    MMap_t *map = (MMap_t *) calloc(1, sizeof(MMap_t));

    map->hash = hash;
    map->equal = equal;
    map->capacity = capacity;
    map->bucket = calloc(capacity, sizeof(MList_t));

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

mboolean mmap_contains(MMap_t *map, mpointer_t key) {
    return mmap_find(map, key) != NULL;
}

void mmap_remove(MMap_t *map, mpointer_t key) {
    muint8_t index = mmap_hash(map, key);

    MPair_t *pair = mmap_find(map, key);
    if(pair) {
        *(map->bucket + index) = mlist_remove(*(map->bucket + index), (mconstpointer_t) pair);
        M_LOG_DEBUG("MAP REMOVE %i %s %p", index, pair->key, pair->value);
        free(pair);
        map->length--;
    }

}

muint32_t mmap_length(MMap_t *map) {
    if(map) {
        return map->length;
    }

    return 0;
}

void mmap_foreach(MMap_t *map, MForeachFunc func, mpointer_t udata) {
    if(map) {
        for(int i=0; i<map->capacity; i++) {
            MList_t *list = *(map->bucket + i);
            while(list) {
                MPair_t *pair = (MPair_t *) list->data;
                if(!func(pair->key, udata))
                    break;
                list = list->next;
            }
        }
    }
}
