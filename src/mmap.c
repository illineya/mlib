#include <mlib.h>

typedef struct {
    mpointer_t key;
    mpointer_t value;
} MPair_t;

MMap_t *mmap_init(MHashFunc hash, MEqualFunc equal) {
    MMap_t *map = (MMap_t *) calloc(1, sizeof(MMap_t));

    map->hash = hash;
    map->equal = equal;

    return map;
}

void mmap_deinit(MMap_t *map) {
    if(map) {
        for(int i=0; i<CAPACITY; i++) {
            mlist_remove_all(map->bucket[i]);
        }
        free(map);
    }
}

static muint8_t mmap_hash(MMap_t *map, mpointer_t key) {
    return map->hash(key) % CAPACITY;
}

static MPair_t *mmap_find(MMap_t *map, mpointer_t key) {
    muint8_t index = mmap_hash(map, key);
    MList_t *list = map->bucket[index];

    if(list) {
        if(mlist_length(list) > 0) {
            while(list->next) {
                MPair_t *pair = (MPair_t *) list->data;
                if(map->equal(pair->key, key)) {
                    return pair;
                }
                list = list->next;
            }
        }

        return (MPair_t *) list->data;
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
        map->bucket[index] = mlist_append(map->bucket[index], (mpointer_t) pair);
        map->length++;
    }
}

mpointer_t mmap_get(MMap_t *map, mpointer_t key) {
    MPair_t *pair = mmap_find(map, key);
    if(pair) {
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
        map->bucket[index] = mlist_remove(map->bucket[index], (mconstpointer_t) pair);
        free(pair);
    }

}

muint32_t mmap_length(MMap_t *map) {
    if(map) {
        return map->length;
    }

    return 0;
}