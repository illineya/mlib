#include <mlib.h>

typedef struct {
    mpointer_t key;
    mpointer_t value;
} MPair_t;

MMap_t *mmap_init(muint8_t capacity, MHashFunc hash, MEqualFunc equal) {
    MMap_t *map = (MMap_t *) calloc(1, sizeof(MMap_t));

    map->hash = hash;
    map->equal = equal;
    map->capacity = capacity;
    *map->bucket = calloc(capacity, sizeof(MList_t));

    return map;
}

void mmap_deinit(MMap_t *map) {
    if(map) {
        for(int i=0; i<map->capacity; i++) {
            mlist_remove_all(map->bucket[i]);
        }
        free(map);
    }
}

static muint8_t mmap_hash(MMap_t *map, mpointer_t key) {
    return map->hash(key) % map->capacity;
}

void mmap_add(MMap_t *map, mpointer_t key, mpointer_t value) {
    if(map) {
        muint8_t index = mmap_hash(map, key);
        MPair_t *pair = malloc(sizeof(MPair_t));
        pair->key = key;
        pair->value = value;
        map->bucket[index] = mlist_append(map->bucket[index], (mpointer_t) pair);
        map->length++;
    }
}

mpointer_t mmap_get(MMap_t *map, mpointer_t key) {
    muint8_t index = mmap_hash(map, key);
    MList_t *list = map->bucket[index];

    if(mlist_length(list) > 0) {
        while(list->next) {
            MPair_t *pair = (MPair_t *) list->data;
            if(map->equal(pair->key, key)) {
                return pair->value;
            }
            list = list->next;
        }
    }

    MPair_t *pair = (MPair_t *) list->data;
    return pair->value;
}

mboolean mmap_contains(MMap_t *map, mpointer_t key) {
    muint8_t index = mmap_hash(map, key);
    MList_t *list = map->bucket[index];

    if(list) {
        if(mlist_length(list) > 0) {
            while(list->next) {
                MPair_t *pair = (MPair_t *) list->data;
                if(map->equal(pair->key, key)) {
                    return TRUE;
                }
                list = list->next;
            }
        }

        return TRUE;
    }

    return FALSE;
}

void mmap_remove(MMap_t *map, mpointer_t key) {
    muint8_t index = mmap_hash(map, key);
    MList_t *list = map->bucket[index];

    if(list) {
        if(mlist_length(list) > 0) {
            while(list->next) {
                MPair_t *pair = (MPair_t *) list->data;
                if(map->equal(pair->key, key)) {
                    map->bucket[index] = mlist_remove(list, list->data);
                    return;
                }
                list = list->next;
            }
        }
        map->bucket[index] = mlist_remove(list, list->data);
        map->length--;
    }
}

muint32_t mmap_length(MMap_t *map) {
    if(map) {
        return map->length;
    }

    return 0;
}