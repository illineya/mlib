#include <mlib.h>
#include <string.h>

mboolean mtest_map_add_one(mpointer_t udata) {
    MMap_t *map = (MMap_t *) udata;

    mmap_add(map, "test", "test");
    mpointer_t data = mmap_get(map, "test");
    if(!strcmp(data, "test")) {
        return TRUE;
    }

    return FALSE;
}

mboolean mtest_map_add_multiple(mpointer_t udata) {
    MMap_t *map = (MMap_t *) udata;

    mmap_add(map, "test", "test");
    mmap_add(map, "lost", "lost");
    mpointer_t data = mmap_get(map, "test");
    if(!strcmp(data, "test")) {
        return TRUE;
    }

    return FALSE;
}

mboolean mtest_map_remove(mpointer_t udata) {
    MMap_t *map = (MMap_t *) udata;
    mmap_remove(map, "test");
    mpointer_t data = mmap_get(map, "test");
    if(!data) {
        return TRUE;
    }
    return FALSE;
}

mboolean mtest_map_contains(mpointer_t udata) {
    MMap_t *map = (MMap_t *) udata;
    if(mmap_contains(map, "lost")) {
        return TRUE;
    }
    return FALSE;
}

muint32_t mtest_map_length(mpointer_t udata) {
    MMap_t *map = (MMap_t *) udata;
    if(mmap_length(map) == 1) {
        return TRUE;
    }
    return FALSE;
}

int main() {
    MMap_t *map = mmap_init(16, mstr_hash, mstr_equal);
    MTest_t *test = mtest_init();
    mtest_append(test, "mtest_map_add_one", mtest_map_add_one);
    mtest_append(test, "mtest_map_add_multiple", mtest_map_add_multiple);
    mtest_append(test, "mtest_map_remove", mtest_map_remove);
    mtest_append(test, "mtest_map_contains", mtest_map_contains);
    mtest_append(test, "mtest_map_length", mtest_map_length);
    mint32_t failed = mtest_run(test, (mpointer_t) map);
    mmap_deinit(map);
    mtest_deinit(test);

    return failed;
}