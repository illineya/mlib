#include <mlib.h>
#include <stdio.h>
#include <sys/time.h>

static mboolean test_func(mpointer_t udata) {
    return TRUE;
}

MTest_t *mtest_init(void) {
    return calloc(1, sizeof(MTest_t));
}

void mtest_deinit(MTest_t *test) {
    MList_t *list = mlist_first(test->list);
    while(list) {
        MList_t *item = list;
        list = list->next;
        free(item->data);
        free(item);
    }
}

void mtest_append(MTest_t *test, mchar_t *name, MTestFunc func) {
    MPair_t *pair = malloc(sizeof(MPair_t));
    pair->key = name;
    pair->value = (mpointer_t) func;
    test->list = mlist_append(test->list, (mpointer_t) pair);
    test->length++;
}

static muint64_t mtest_microtime() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return 1000000 * tv.tv_sec + tv.tv_usec;
}

mint32_t mtest_run(MTest_t *test, mpointer_t udata) {
    MList_t *list = mlist_first(test->list);
    muint8_t success = 0;
    muint8_t failed = 0;

    muint64_t start = mtest_microtime();
    while(list) {
        MPair_t *pair = (MPair_t *) list->data;
        MTestFunc func = (MTestFunc) pair->value;
        mboolean status = func(udata);

        if(status)
            success++;
        else
            failed++;

        fprintf(stdout, "TEST %-50s %s\n", pair->key, status ? "\e[0;32mPASSED\e[0m" : "\e[0;31mFAILURE\e[0m");

        list = list->next;
    }
    muint64_t end = mtest_microtime();

    fprintf(stdout, "\n%s (%i tests, %i success, %i failure) ... %f sec\n", failed ? "\e[0;31mFAILURE\e[0m" : "\e[0;32mSUCCESS\e[0m", test->length, success, failed, ((float) (end - start) / 1000000));
    return failed;
}