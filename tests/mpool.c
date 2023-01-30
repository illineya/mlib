#include <mlib.h>

mboolean mtest_pool_alloc(mpointer_t udata) {
    MPool_t **pool = (MPool_t **) udata;
    MList_t *list = (MList_t *) mpool_alloc(*pool);
    if(list && sizeof(*list) == sizeof(MList_t)) {
        return TRUE;
    }
    return FALSE;
}

mboolean mtest_pool_free(mpointer_t udata) {
    MPool_t **pool = (MPool_t **) udata;
    MList_t *list = (MList_t *) mpool_alloc(*pool);
    mpool_free(*pool, (mpointer_t) list);
    if(mpool_allocated(*pool) == sizeof(MList_t)) {
        return TRUE;
    }

    return FALSE;
}

int main() {
    MPool_t *pool = mpool_init(sizeof(MList_t), 100);
    MTest_t *test = mtest_init();
    mtest_append(test, "mtest_map_add_one", mtest_pool_alloc);
    mtest_append(test, "mtest_pool_free", mtest_pool_free);
    mint32_t failed = mtest_run(test, (mpointer_t) &pool);
    mpool_deinit(pool);

    return failed;
}