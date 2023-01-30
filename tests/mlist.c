#include <mlib.h>
#include <string.h>

mboolean mtest_list_add(mpointer_t udata) {
    MList_t **list = (MList_t **) udata;

    *list = mlist_append(*list, "1hello");
    if(mlist_length(*list) == 1)
        return TRUE;

    return FALSE;
}

mboolean mtest_list_first(mpointer_t udata) {
    MList_t **list = (MList_t **) udata;

    *list = mlist_append(*list, "2hello");
    *list = mlist_first(*list);
    if(!strcmp((*list)->data, "1hello"))
        return TRUE;

    return FALSE;
}

mboolean mtest_list_last(mpointer_t udata) {
    MList_t **list = (MList_t **) udata;

    *list = mlist_last(*list);
    if(!strcmp((*list)->data, "2hello"))
        return TRUE;

    return FALSE;
}

mboolean mtest_list_prepend(mpointer_t udata) {
    MList_t **list = (MList_t **) udata;

    *list = mlist_prepend(*list, "3hello");
    *list = mlist_first(*list);
    if(!strcmp((*list)->data, "3hello"))
        return TRUE;

    return FALSE;
}

mboolean mtest_list_insert_sorted(mpointer_t udata) {
    MList_t **list = (MList_t **) udata;

    *list = mlist_insert_sorted(*list, "0hello", (MSortFunc) strcmp);
    *list = mlist_first(*list);
    if(!strcmp((*list)->data, "0hello"))
        return TRUE;

    return FALSE;
}

mboolean mtest_list_remove(mpointer_t udata) {
    MList_t **list = (MList_t **) udata;

    *list = mlist_remove(*list, "3hello");
    if(mlist_length(*list) == 3)
        return TRUE;

    return FALSE;
}

mboolean mtest_list_remove_and_append(mpointer_t udata) {
    MList_t *list = NULL;
    list = mlist_append(list, "test");
    list = mlist_remove(list, "test");

    list = mlist_append(list, "test");
    mlist_remove(list, "test");

    return TRUE;
}

mboolean mtest_list_find(mpointer_t udata) {
    MList_t **list = (MList_t **) udata;

    if(mlist_find(*list, "2hello")) {
        return TRUE;
    }

    return FALSE;
}

int main() {
    MList_t *list = NULL;

    MTest_t *test = mtest_init();
    mtest_append(test, "mtest_list_add", mtest_list_add);
    mtest_append(test, "mtest_list_first", mtest_list_first);
    mtest_append(test, "mtest_list_last", mtest_list_last);
    mtest_append(test, "mtest_list_prepend", mtest_list_prepend);
    mtest_append(test, "mtest_list_insert_sorted", mtest_list_insert_sorted);
    mtest_append(test, "mtest_list_remove", mtest_list_remove);
    mtest_append(test, "mtest_list_find", mtest_list_find);
    mtest_append(test, "mtest_list_remove_and_append", mtest_list_remove_and_append);
    mint32_t failed = mtest_run(test, (mpointer_t) &list);
    mtest_deinit(test);

    mlist_remove_all(list);

    return failed;
}