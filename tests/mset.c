#include <mlib.h>

mboolean mtest_set_add(mpointer_t udata) {
    MSet_t **set = (MSet_t **) udata;
    mset_add(*set, "test");
    if(mset_length(*set) == 1) {
        return TRUE;
    }
    return FALSE;
}

mboolean mtest_set_remove(mpointer_t udata) {
    MSet_t **set = (MSet_t **) udata;
    mset_remove(*set, "test");
    if(mset_length(*set) == 0) {
        return TRUE;
    }
    return FALSE;
}

mboolean mtest_set_add_multiple(mpointer_t udata) {
    MSet_t **set = (MSet_t **) udata;
    mset_add(*set, "test");
    mset_add(*set, "lost");
    mset_add(*set, "test");
    if(mset_length(*set) == 2) {
        return TRUE;
    }
    return FALSE;
}

int main() {
    MSet_t *set = mset_init(mstr_hash, mstr_equal);
    MTest_t *test = mtest_init();
    mtest_append(test, "mtest_set_add", mtest_set_add);
    mtest_append(test, "mtest_set_remove", mtest_set_remove);
    mtest_append(test, "mtest_set_add_multiple", mtest_set_add_multiple);
    mint32_t failed = mtest_run(test, (mpointer_t) &set);
    mset_deinit(set);

    return failed;
}